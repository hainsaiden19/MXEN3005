from .wx250s_kinematics import *

import rclpy
from rclpy.node import Node

from geometry_msgs.msg import PoseStamped
from geometry_msgs.msg import Point
from geometry_msgs.msg import Quaternion

from xarmclient import XArm

import scipy.spatial.transform as spst

class PoseNode(Node):
    def __init__(self):
        super().__init__("Pose_Node")

        ### Class Variables ###
        self.msg = PoseStamped()
        self.xarm = XArm()
        #######################

        ### Publishing Creation ##
        self.publisher = self.create_publisher(PoseStamped, "/pose", 10)
        timer_period = 0.05
        self.timer = self.create_timer(timer_period, self.timer_callback)

    ### Publishing Execution ###
    def timer_callback(self):   
        joint_angles = self.xarm.get_joints()

        transform, _ = fk(joint_angles)

        transform_pos = Point()
        transform_pos.x, transform_pos.y, transform_pos.z = list((transform[0:3, 3]) / 1000)
        self.msg.pose.position = transform_pos

        transform_rot = Quaternion()
        transform_rot = transform[0:3, 0:3]
        quart_rot = spst.Rotation.from_matrix(transform_rot).as_quat()
        self.msg.pose.orientation.x, self.msg.pose.orientation.y, self.msg.pose.orientation.z, self.msg.pose.orientation.w = quart_rot
        
        self.msg.header.frame_id = "base_link"

        #self.get_logger().info(f'\n\nlhs: {self.msg.pose.orientation}' )
        #self.get_logger().info(f'\n\nrhs: {self.msg.pose.position}' )

        self.publisher.publish(self.msg)

def main(args=None):

    rclpy.init(args=args)

    node = PoseNode()
    rclpy.spin(node)
    node.destroy_node()

    rclpy.shutdown()

    return 0

if __name__ == '__main__':
    main()