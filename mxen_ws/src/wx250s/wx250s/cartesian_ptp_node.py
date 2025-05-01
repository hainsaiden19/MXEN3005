# The following imports are necessary
import threading
import rclpy
from rclpy.action import ActionServer, CancelResponse, GoalResponse
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node

# Replace the following import with the interface this node is using
from wx250s_interface.action import CartesianPTP

from .wx250s_kinematics import *

from std_msgs.msg import Float64MultiArray

import time
import numpy as np

from xarmclient import XArm


class CartesianPTPNode(Node):

    def __init__(self):
        super().__init__("cartesian_ptp_node")

        ### Class Variables ###
        self.goal_handle = None
        self.goal_lock = threading.Lock()

        self.xarm = XArm()
        #######################

        self.action_server = ActionServer(
            self,
            CartesianPTP,
            "set_cartesian_ptp",
            execute_callback=self.execute_callback,
            goal_callback=self.goal_callback,
            handle_accepted_callback=self.handle_accepted_callback,
            cancel_callback=self.cancel_callback,
            callback_group=ReentrantCallbackGroup(),
        )


    def destroy(self):
        self.action_server.destroy()
        super().destroy_node()


    ### New goal requested ###
    def goal_callback(self, goal_request):
        self.get_logger().info(f"## New Goal Requested ## {goal_request.goal_pos} ")
        x_query = False; y_query = False; z_query = False

        if (goal_request.goal_pos[0] < 320) and (goal_request.goal_pos[0] > -320):
            x_query = True
            if (goal_request.goal_pos[1] < 320) and (goal_request.goal_pos[1] > -320):
                y_query = True
                if (goal_request.goal_pos[2] < 600) and (goal_request.goal_pos[2] > 0):
                    z_query = True

        if ((x_query) and (y_query) and (z_query)):
            self.get_logger().info("## Goal is Acceptable ##")  
            return GoalResponse.ACCEPT
        else:
            self.get_logger().info("## Goal is Unacceptable ##")
            self.get_logger().info(f"x pos success: {x_query}")
            self.get_logger().info(f"y pos success: {y_query}")
            self.get_logger().info(f"z pos success: {z_query}")
            return GoalResponse.REJECT


    # This function is called whenever new goal has been accepted
    def handle_accepted_callback(self, goal_handle):
        with self.goal_lock:
            # This server only allows one goal at a time
            if self.goal_handle is not None and self.goal_handle.is_active:
                self.get_logger().info("Aborting previous goal")
                # Abort the existing goal
                self.goal_handle.abort()
            self.goal_handle = goal_handle

        goal_handle.execute()

    # This function is called whenever cancel request is received
    def cancel_callback(self, goal):
        # Accept or reject a client request to cancel an action
        self.get_logger().info("Received cancel request")
        return CancelResponse.ACCEPT

    # This function is called at the start of action execution
    def execute_callback(self, goal_handle):
        self.get_logger().info("## Executing Goal ##")

        feedback_msg = CartesianPTP.Feedback()
        goal_pos_mm = goal_handle.request.goal_pos

        # get current htm
        htm_init, _ = fk(self.xarm.get_joints())
        rotation = htm_init[0:3, 0:3]
        xyz_init = htm_init[0:3, 3]
        bottomrow = np.array([[0, 0, 0, 1]])

        initial_pos_mm = xyz_init

        difference = [abs(g - i) for g, i in zip(goal_pos_mm, initial_pos_mm)]
        direction = [int((g - i)/abs(g - i)) for g, i in zip(goal_pos_mm, initial_pos_mm)]

        step_size = 5 # mm
        num_whole_increments = [int(i/step_size) for i in difference]
        num_remainder_increments = [0, 0, 0]
        num_total_increments = [0, 0, 0]
        
        remainder = [0, 0, 0]
        for i in range(len(remainder)):
            d = difference[i]
            n = num_whole_increments[i]
            if n == 0:
                remainder[i] = d
            else:
                remainder[i] = d%step_size

        for i, r in enumerate(remainder):
            if r > 0:
                num_remainder_increments[i] += 1
            num_total_increments[i] = num_whole_increments[i] + num_remainder_increments[i]

        # goal poulation
        # goals = nX3 matrix, any number of goals, only 3 columns, x y z
        # find largest number of increments
        n = int(max(num_total_increments))+1
        goals = np.zeros((n, 3))

        for r in range(n):
            if r == 0:
                goals[r] = initial_pos_mm
            else: 
                goals[r] = goals[r-1] + [direction[0]*step_size, direction[1]*step_size, direction[2]*step_size]
                for c in range(len(goals[r])):
                    if direction[c] > 0:
                        if goals[r][c] > goal_pos_mm[c]:
                            goals[r][c] = goal_pos_mm[c]
                    else: 
                        if goals[r][c] < goal_pos_mm[c]:
                            goals[r][c] = goal_pos_mm[c]

        xyzgoals = goals
        
        acceptablegoal_difference = 5 # mm
        
        # iterate through the htms, keeping the rotation matrix constant and the xyz changing
        # skipping the first row, since thats just where we are right now
        for xyz in xyzgoals[1:]:
            time.sleep(0.1)
            
            goal_htm = np.append(np.append(rotation, np.reshape(xyz, newshape=(3, 1)), axis=1), bottomrow, axis=0)
            joint_positions = ik(self.xarm.get_joints(), goal_htm)
            self.xarm.set_joints(joint_positions)

            goal_reached_check = [abs(c - g)<acceptablegoal_difference for c, g in zip(xyz, goal_pos_mm)]
            if np.all(goal_reached_check):
                break
            
            dist_vector = [abs(c - g) for c, g in zip(xyz, goal_pos_mm)]
            feedback_msg.distance_to_goal = np.linalg.norm(dist_vector)
            goal_handle.publish_feedback(feedback_msg)


            #        goal aborting and cancelling       #
            if not goal_handle.is_active:   
                self.get_logger().info("Goal aborted")
                return CartesianPTP.Result()
            if goal_handle.is_cancel_requested:
                goal_handle.canceled()
                self.get_logger().info("Goal canceled")
                return CartesianPTP.Result()
            #                                           #
            
        with self.goal_lock:
            if not goal_handle.is_active:
                self.get_logger().info("Goal aborted")
                return CartesianPTP.Result()
            goal_handle.succeed()

        # Populate result message
        result = CartesianPTP.Result()
        result.success = True
        self.get_logger().info(f"Distance to goal: {feedback_msg.distance_to_goal}")

        return result


def main(args=None):
    rclpy.init(args=args)

    node = CartesianPTPNode()

    # We use a MultiThreadedExecutor to handle incoming goal requests concurrently
    executor = MultiThreadedExecutor()
    rclpy.spin(node, executor=executor)

    node.destroy()
    rclpy.shutdown()


if __name__ == "__main__":
    main()