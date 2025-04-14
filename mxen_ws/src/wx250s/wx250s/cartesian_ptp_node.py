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
    """Minimal action server that processes one goal at a time."""

    def __init__(self):
        super().__init__("cartesian_ptp_node")

        ### Class Variables ###
        self.goal_handle = None
        self.goal_lock = threading.Lock()

        self.xarm = XArm()

        self.count = 0.0
        #######################

        # Action servers are created using interface type, action name and multiple callback functions
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
        x_query = True; y_query = True; z_query = True
        if (goal_request.goal_pos[0] < 0.32) and (goal_request.goal_pos[0] > -0.32):
            x_query = False
            if (goal_request.goal_pos[1] < 0.32) and (goal_request.goal_pos[1] > -0.32):
                y_query = False
                if (goal_request.goal_pos[2] < 0.60) and (goal_request.goal_pos[2] > 0):
                    z_query = False

        if ((not x_query) and (not y_query) and (not z_query)):
            self.get_logger().info("## Goal is Acceptable ##")  
            return GoalResponse.ACCEPT
        else:
            self.get_logger().info("## Goal is Unacceptable ##")
            self.get_logger().info(f"x pos failed: {x_query}")
            self.get_logger().info(f"y pos failed: {y_query}")
            self.get_logger().info(f"z pos failed: {z_query}")
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

        pose_goal_mm = [i*1000 for i in goal_handle.pose_goal]

        num_increments = int(pose_goal_mm/10)
        remainder = pose_goal_mm % num_increments

        # get incremental pose goals, then use that to give a set of incremental joint goals
        # which you then loop throough and simply check if the current pose is equal to the 
        # goal pose

        goal_reached = False
        while not goal_reached:

            time.sleep(0.1)

            #        goal aborting and cancelling       #
            if not goal_handle.is_active:   
                self.get_logger().info("Goal aborted")
                return CartesianPTP.Result()
            if goal_handle.is_cancel_requested:
                goal_handle.canceled()
                self.get_logger().info("Goal canceled")
                return CartesianPTP.Result()
            #                                           #
        
            feedback_msg.present_pos = self.xarm.get_joints()
            goal_handle.publish_feedback(feedback_msg)

            

            



            

        with self.goal_lock:
            if not goal_handle.is_active:
                self.get_logger().info("Goal aborted")
                return CartesianPTP.Result()
            goal_handle.succeed()

        # Populate result message
        result = CartesianPTP.Result()
        result.success = True
        self.get_logger().info(f"Joint Positions At Success: {feedback_msg.present_pos}")

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