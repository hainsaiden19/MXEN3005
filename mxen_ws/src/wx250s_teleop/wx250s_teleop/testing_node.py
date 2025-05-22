import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient
from rclpy.task import Future
from rclpy.action.client import ClientGoalHandle

import uuid
from unique_identifier_msgs.msg import UUID

import time

import numpy as np
import scipy.spatial.transform as spst

from sensor_msgs.msg import Joy

from .wx250s_kinematics import *

from wx250s_interface.action import ShrineBuild

from xarmclient import XArm


class TestingNode(Node):
    def __init__(self):
        super().__init__("testing_node")

        ### Robot Init ###
        self.xarm = XArm()
        self.tick = 0
        self.goal_id = UUID(uuid=list(uuid.uuid4().bytes))
        self.goal_future = Future()


        ### Timer ###
        timer_period = 0.2
        self.timer = self.create_timer(timer_period, self.timer_callback)

        ### Action Client ###
        self.action_client = ActionClient(self, ShrineBuild, "build_shrine")


    def timer_callback(self):

        #self.tick += 1
#
        #self.get_logger().info(f'{self.tick}')
#
        #if self.tick == 50:
        #    self.get_logger().info(f'build shrine please')
        #    self.shrinebuildMode()
#
        #if self.tick == 120:
        #    self.cancelshrineBuild()
#
        #if self.tick == 200:
        #    self.get_logger().info(f'build shrine please')
        #    self.shrinebuildMode()


        return 0
    

    def shrinebuildMode(self):
        self.cancelshrineBuild()
        self.get_logger().info(f'### Shrine Build Requested ###')
        goal = ShrineBuild.Goal()
        self.action_client.wait_for_server(timeout_sec=20)

        self.goal_id = UUID(uuid=list(uuid.uuid4().bytes))
        self.goal_future = self.action_client.send_goal_async(goal, goal_uuid=self.goal_id)

        return 0


    def cancelshrineBuild(self):

        self.goal_handle = ClientGoalHandle(self.action_client, self.goal_id, self.goal_future)
        self.action_client._cancel_goal_async(self.goal_handle)

        return 0



def main(args=None):

    rclpy.init(args=args)

    node = TestingNode()
    rclpy.spin(node)
    node.destroy_node()

    rclpy.shutdown()

    return 0

if __name__ == '__main__':
    main()