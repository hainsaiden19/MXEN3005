import rclpy
from rclpy.node import Node

import numpy as np

from sensor_msgs.msg import Joy

from std_msgs.msg import Int16

from xarmclient import XArm

class StateChangeNode(Node):
    def __init__(self):
        super().__init__("state_change_node")

        ### Class Variables ###
        self.xarm = XArm()

        self.joystickvalues = Joy()
        self.robotstate = 1
        #######################

        ### Subscription ###
        self.subscription = self.create_subscription(Joy, "/joy", self.listener_callback, 10)

        ### Timer ###
        timer_period = 0.1
        self.timer = self.create_timer(timer_period, self.timer_callback)

        ### Publishing ###
        self.publisher = self.create_publisher(Int16, "/robot_state", 10)


    def listener_callback(self, msg):
        self.joystickvalues.buttons = msg.buttons
        return 0


    def timer_callback(self):
        self.publisher.publish(self.robotstate)

        return 0



def main(args=None):

    rclpy.init(args=args)

    node = StateChangeNode()
    rclpy.spin(node)
    node.destroy_node()

    rclpy.shutdown()

    return 0

if __name__ == '__main__':
    main()