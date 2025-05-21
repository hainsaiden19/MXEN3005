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

class JoystickNode(Node):
    def __init__(self):
        super().__init__("joystick_node")

        ### Robot Init ###
        self.xarm = XArm()
        self.joystickvalues = Joy()
        self.dead = 0
        self.homestate = False
        self.gripstate = False
        self.griplimiter = 0
        self.newgoal = True
        self.cancelrequest = False

        self.goal_id = UUID(uuid=list(uuid.uuid4().bytes))
        self.goal_future = Future()

        self.tester = 0

        # Modes:
        # 0 : Joint Mode
        # 1 : Cartesian Mode
        # 2 : Shrine Build Mode
        # Default : 0 : Joint Mode

        self.robotstate = 2

        self.xarm.home()
        time.sleep(2)

        self.currentpos = np.array(self.xarm.get_joints())
        #######################
        
        ### Subscription ###
        self.subscription = self.create_subscription(Joy, "/joy", self.listener_callback, 10)

        ### Timer ###
        timer_period = 0.1
        self.timer = self.create_timer(timer_period, self.timer_callback)

        ### Action Client ###
        self.action_client = ActionClient(self, ShrineBuild, "build_shrine")



    ### Listens and checks for states and state changes ###
    def listener_callback(self, msg):
        self.joystickvalues.axes = msg.axes
        self.joystickvalues.buttons = msg.buttons

        home_button = self.joystickvalues.buttons[10]
        if home_button > 0:
            self.homestate = True

        grip_open_button = self.joystickvalues.buttons[4]
        grip_close_button = self.joystickvalues.buttons[5]

        if grip_open_button > 0:
            self.gripstate = False
            self.griplimiter = 1

        if grip_close_button > 0:
            self.gripstate = True
            self.griplimiter = 1


        jointmode_button = self.joystickvalues.buttons[dontknow]
        if jointmode_button > 0:
            self.robotstate = 0
            self.cancelrequest = True
        
        cartesianmode_button = self.joystickvalues.buttons[dontknow]
        if cartesianmode_button > 0:
            self.robotstate = 1
            self.cancelrequest = True

        shrinebuildmode_button = self.joystickvalues.buttons[1]
        if shrinebuildmode_button > 0:
            self.robotstate = 2
            self.newgoal = True

        return 0


    ### Master function ###
    ### Executes all state changes ###
    def timer_callback(self):

        self.tester += 1

        if self.tester == 100:
            self.cancelshrineBuild()
    
        match self.robotstate:
            case 0:
                if self.cancelrequest == True:
                    self.cancelshrineBuild()
                    self.cancelrequest = False
                self.jointMode()

            case 1:
                if self.cancelrequest == True:
                    self.cancelshrineBuild()
                    self.cancelrequest = False
                self.cartesianMode()

            case 2:
                self.shrinebuildMode()


        return 0
    
    ### Joint Mode ###
    def jointMode(self):
        joystick_input = np.delete(np.array(self.joystickvalues.axes), [2, 5])
        
        j1 = joystick_input[2]
        j2 = joystick_input[3]
        j3 = joystick_input[1]
        j4 = -1*joystick_input[0]
        j5 = joystick_input[5]
        j6 = joystick_input[4]

        jointmove = np.array([j1, j2, j3, j4, j5, j6])
        prop_gain = 3
        if np.any(jointmove > 0.1) or np.any(jointmove < -0.1):
            self.currentpos = self.currentpos + (prop_gain*jointmove)**3
            self.xarm.set_joints(self.currentpos, "high_acc")
            velocities=[40, 50, 20, 20, 20, 20]
            self.dead  = 1
        
        elif np.any(jointmove < 0.1) and np.any(jointmove > -0.1):
            if self.dead  == 1:
                self.xarm.set_joints(self.currentpos, "high_acc")
                self.dead  = 0

        self.homing()
        self.controlGripper()
        return 0


    def controlGripper(self):

        if self.griplimiter == 1:
            if self.gripstate == False:
                self.xarm.grip(0)

            if self.gripstate == True:
                self.xarm.grip(1)

            self.griplimiter = 0

        return 0


    def homing(self):
        if self.homestate == True:
            self.xarm.home()
            self.homestate = False
            time.sleep(2)
        return 0


    def cartesianMode(self):


        return 0


    def shrinebuildMode(self):
        if self.newgoal == True:
            self.get_logger().info(f'### Shrine Build Requested ###')
            goal = ShrineBuild.Goal()
            goal.buildshrine = True
            self.action_client.wait_for_server(timeout_sec=20)

            self.goal_id = UUID(uuid=list(uuid.uuid4().bytes))
            self.goal_future = self.action_client.send_goal_async(goal, goal_uuid=self.goal_id)

            self.newgoal = False
        return 0

    def cancelshrineBuild(self):

        self.goal_handle = ClientGoalHandle(self.action_client, self.goal_id, self.goal_future)
        self.action_client._cancel_goal_async(self.goal_handle)

        return 0

def main(args=None):

    rclpy.init(args=args)

    node = JoystickNode()
    rclpy.spin(node)
    node.destroy_node()

    rclpy.shutdown()

    return 0

if __name__ == '__main__':
    main()