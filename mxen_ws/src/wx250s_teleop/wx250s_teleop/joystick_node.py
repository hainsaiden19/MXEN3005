import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient

import time

import numpy as np
import scipy.spatial.transform as spst

from sensor_msgs.msg import Joy

from .wx250s_kinematics import *

from xarmclient import XArm

class JoystickNode(Node):
    def __init__(self):
        super().__init__("joystick_node")

        ### Robot Init ###
        self.xarm = XArm()
        self.joystickvalues = Joy()
        self.dead = 0
        self.i = 0

        self.xarm.home()
        time.sleep(2)
        self.currentpos = np.array(self.xarm.get_joints())
        #######################
        
        ### Subscription ###
        self.subscription = self.create_subscription(Joy, "/joy", self.listener_callback, 10)

    

    ### Publishing Execution ###
    def listener_callback(self, msg):
        
        self.i += 1

        limiter = self.i % 10

        if limiter == 0:
            self.send_to_robot(msg)
        
        return 0
    #####################################################################################


    def send_to_robot(self, msg):
        self.joystickvalues.axes = msg.axes
        self.joystickvalues.buttons = msg.buttons

        #currentpos = np.array(self.xarm.get_joints())

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


        self.homing(self.joystickvalues.buttons[10])

        self.controlGripper(self.joystickvalues.buttons[4], self.joystickvalues.buttons[5])


        return 0


    def controlGripper(self, openbutton, closebutton):
        if openbutton > 0:
            self.xarm.grip(0)
        if closebutton > 0:
            self.xarm.grip(1)
        return 0

    def homing(self, homebutton):
        if homebutton > 0:
            self.xarm.home()
            time.sleep(2)

def main(args=None):

    rclpy.init(args=args)

    node = JoystickNode()
    rclpy.spin(node)
    node.destroy_node()

    rclpy.shutdown()

    return 0

if __name__ == '__main__':
    main()