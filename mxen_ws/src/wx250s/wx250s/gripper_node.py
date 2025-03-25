import rclpy
from rclpy.node import Node

from std_srvs.srv import SetBool
from std_msgs.msg import String

from xarmclient import XArm

class GripperNode(Node):
    def __init__(self):
        super().__init__("Gripper_Node")

        ### Class Variables ###
        self.gripping = False
        self.msg = String()
        self.xarm = XArm()
        #######################

        ### Service Creation ###
        self.service = self.create_service(
            SetBool, "grip", self.service_callback
        )
        ########################

    ### Service Execution ###
    def service_callback(self, request, response):
        self.gripping = request.data
        self.get_logger().info(f"Gripping: {self.gripping}")
        self.xarm.grip(self.gripping)
        return response
    #########################

def main(args=None):

    rclpy.init(args=args)

    node = GripperNode()
    rclpy.spin(node)
    node.destroy_node()

    rclpy.shutdown()

    return 0

if __name__ == '__main__':
    main()