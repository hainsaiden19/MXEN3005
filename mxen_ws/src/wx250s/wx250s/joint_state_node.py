import rclpy
from rclpy.node import Node

from sensor_msgs.msg import JointState

from xarmclient import XArm

class JointStateNode(Node):
    def __init__(self):
        super().__init__("Joint_State_Node")

        ### Class Variables ###
        self.msg = JointState()
        self.xarm = XArm()
        #######################

        ### Publishing Creation ##
        self.publisher = self.create_publisher(JointState, "/joint_state", 10)
        timer_period = 0.2
        self.timer = self.create_timer(timer_period, self.timer_callback)

    ### Publishing Execution ###
    def timer_callback(self):
        self.msg.position = self.xarm.get_joints()
        self.publisher.publish(self.msg)

def main(args=None):

    rclpy.init(args=args)

    node = JointStateNode()
    rclpy.spin(node)
    node.destroy_node()

    rclpy.shutdown()

    return 0

if __name__ == '__main__':
    main()