import rclpy
from rclpy.node import Node

from std_srvs.srv import Trigger
from std_msgs.msg import String

from xarmclient import XArm

class HomingNode(Node):
    def __init__(self):
        super().__init__("Homing_Node")

        ### Class Variables ###
        self.homing = False
        self.msg = String()
        self.xarm = XArm()
        #######################

        ### Service Creation ###
        self.service = self.create_service(
            Trigger, "homing", self.service_callback
        )
        ########################

    ### Service Execution ###
    def service_callback(self, request, response):
        self.homing = True
        self.get_logger().info(f"Homing: {self.homing}")
        if self.homing: 
            self.xarm.grip(0)
            self.xarm.home()
            response.success = True
        return response
    #########################

def main(args=None):

    rclpy.init(args=args)

    node = HomingNode()
    rclpy.spin(node)
    node.destroy_node()

    rclpy.shutdown()

    return 0

if __name__ == '__main__':
    main()