# The following imports are necessary
import threading
import rclpy
from rclpy.action import ActionServer, CancelResponse, GoalResponse
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node

# Replace the following import with the interface this node is using
from wx250s_interface.action import JointPTP

from std_msgs.msg import Float64MultiArray

import time
import numpy as np

from xarmclient import XArm


class JointPTPNode(Node):
    """Minimal action server that processes one goal at a time."""

    def __init__(self):
        super().__init__("joint_ptp_node")

        ### Class Variables ###
        self.goal_handle = None
        self.goal_lock = threading.Lock()

        self.xarm = XArm()

        self.count = 0.0
        #######################

        # Action servers are created using interface type, action name and multiple callback functions
        self.action_server = ActionServer(
            self,
            JointPTP,
            "set_point_ptp",
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
        self.get_logger().info(f"## New Goal Requested ## {goal_request.joint_goal} ")
        
        error_query = self.xarm.is_goal_valid(goal_request.joint_goal)
        
        if (error_query == 0):
            self.get_logger().info("## Goal is Acceptable ##")  
            return GoalResponse.ACCEPT
        else:
            self.get_logger().info("## Goal is Unacceptable ##")
            self.get_logger().info(self.xarm.ERRORS[error_query])
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

        robot_goal = goal_handle.request.joint_goal
        acceptable_difference = [3, 3, 3, 2, 3, 2]
        speed_threshold = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
        previous_value = self.xarm.get_joints()

        feedback_msg = JointPTP.Feedback()

        self.xarm.set_joints(robot_goal)

        goal_reached = False
        while not goal_reached:

            time.sleep(0.1)

            #        goal aborting and cancelling       #
            if not goal_handle.is_active:   
                self.get_logger().info("Goal aborted")
                return JointPTP.Result()
            if goal_handle.is_cancel_requested:
                goal_handle.canceled()
                self.get_logger().info("Goal canceled")
                return JointPTP.Result()
            #                                           #
        
            feedback_msg.joint_present = self.xarm.get_joints()
            current_value = self.xarm.get_joints()

            goal_reached_check = [abs(joint_current - joint_goal) < difference for joint_current, joint_goal, difference in zip(current_value, robot_goal, acceptable_difference)]

            if all(goal_reached_check) == True:
                goal_reached = True
                #self.get_logger().info(f'current: {current_value}, goal: {robot_goal}')
                break

            speed_check = [(abs(joint_current - joint_previous) < threshold) and (goal_check == False) for joint_current, joint_previous, threshold, goal_check in zip(current_value, previous_value, speed_threshold, goal_reached_check)]

            if any(speed_check) == True:
                goal_handle.abort()
                result = JointPTP.Result()
                result.success = False
                return result
            
            previous_value = current_value

            goal_handle.publish_feedback(feedback_msg)

        with self.goal_lock:
            if not goal_handle.is_active:
                self.get_logger().info("Goal aborted")
                return JointPTP.Result()
            goal_handle.succeed()

        # Populate result message
        result = JointPTP.Result()
        result.success = True
        self.get_logger().info(f"Joint Positions At Success: {feedback_msg.joint_present}")

        return result


def main(args=None):
    rclpy.init(args=args)

    node = JointPTPNode()

    # We use a MultiThreadedExecutor to handle incoming goal requests concurrently
    executor = MultiThreadedExecutor()
    rclpy.spin(node, executor=executor)

    node.destroy()
    rclpy.shutdown()


if __name__ == "__main__":
    main()