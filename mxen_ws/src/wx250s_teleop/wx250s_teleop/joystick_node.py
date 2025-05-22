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
        self.limiter = 0
        self.shrinelimiter = 0
        
        self.newstate = False

        self.goal_id = UUID(uuid=list(uuid.uuid4().bytes))
        self.goal_future = Future()

        self.tester = 0

        self.execution_delay = 0

        

        # Modes:
        # 0 : Joint Mode
        # 1 : Cartesian Mode
        # 2 : Shrine Build Mode
        # Default : 0 : Joint Mode
        self.robotstate = 0

        #######################
        
        ### Subscription ###
        self.subscription = self.create_subscription(Joy, "/joy", self.listener_callback, 10)

        ### Timer ###
        timer_period = 0.1
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.timer_2 = self.create_timer(timer_period, self.timer_callback_2)

        ### Action Client ###
        self.action_client = ActionClient(self, ShrineBuild, "build_shrine")

        self.get_logger().info(f'\n\n### Homing Requested')
        self.xarm.home()

        time.sleep(3)

        self.currentpos = np.array(self.xarm.get_joints())

        self.cart_goal_joints = self.currentpos

        self.htm_Curr_rel_Base, _ = fk(self.xarm.get_joints())
        self.constant_rotation = self.htm_Curr_rel_Base[0:3, 0:3]
        
        self.get_logger().info(f'\n\n### Ready For Control')



    ### Only Listens ###
    def listener_callback(self, msg):
        self.joystickvalues.axes = msg.axes
        self.joystickvalues.buttons = msg.buttons
        self.execution_delay += 1
        return 0
    
    ### Takes state changes and informs the main timer callback ###
    def timer_callback_2(self):

        if self.execution_delay > 50:
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
    
            jointmode_button = self.joystickvalues.buttons[9]
            if jointmode_button > 0:
                self.robotstate = 0
                self.cancelrequest = True
                self.newstate = True
            
            cartesianmode_button = self.joystickvalues.buttons[8]
            if cartesianmode_button > 0:
                self.robotstate = 1
                self.cancelrequest = True
                self.newstate = True
    
            shrinebuildmode_button = self.joystickvalues.buttons[0]
            if shrinebuildmode_button > 0:
                self.robotstate = 2
                self.newgoal = True
                self.newstate = True
                self.shrinelimiter += 1

        return 0


    ### Master function ###
    ### Executes all state changes ###
    def timer_callback(self):

        if self.execution_delay > 50:
        
            #self.limiter += 1
            if self.execution_delay > 50 and self.execution_delay < 52:
                self.get_logger().info(f'{self.joystickvalues.axes}')

                self.get_logger().info(f'\n\n### Control Allowed')
                
            match self.robotstate:
                case 0:
                    if self.newstate == True:
                        self.get_logger().info(f'### Joint Mode ###')
                        self.newstate = False

                    if self.cancelrequest == True:
                        self.cancelshrineBuild()
                        self.cancelrequest = False
                    self.shrinelimiter = 0
                    self.jointMode()

                case 1:
                    if self.newstate == True:
                        self.get_logger().info(f'### Cartesian Mode ###')
                        self.newstate = False
                        self.constant_rotation = self.htm_Curr_rel_Base[0:3, 0:3]

                    if self.cancelrequest == True:
                        self.cancelshrineBuild()
                        self.cancelrequest = False
                    self.shrinelimiter = 0
                    self.cartesianMode()

                case 2:
                    if self.newstate == True and self.shrinelimiter == 1:
                        #self.shrinelimiter = 0
                        self.get_logger().info(f'### Shrine Build Mode ###')
                        self.shrinebuildMode()
                        self.newstate = False
                        


        return 0
    
    ### Joint Mode ###
    def jointMode(self):
        
        j1 = self.joystickvalues.axes[3]
        j2 = -1*self.joystickvalues.axes[4]
        j3 = self.joystickvalues.axes[1]
        j4 = -1*self.joystickvalues.axes[0]
        j5 = self.joystickvalues.axes[7]
        j6 = -1*self.joystickvalues.axes[6]

        jointmove = np.array([j1, j2, j3, j4, j5, j6])
        prop_gain = 3
        if np.any(jointmove > 0.1) or np.any(jointmove < -0.1):
            self.currentpos = self.currentpos + (prop_gain*jointmove)**3
            self.xarm.set_joints(self.currentpos, "high_acc")
            self.dead  = 1
        
        elif np.any(jointmove < 0.1) and np.any(jointmove > -0.1):
            if self.dead  == 1:
                self.currentpos = self.xarm.get_joints()
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
            self.currentpos = self.xarm.get_joints()
        return 0
    

    def cartesianMode(self):
        gain = 2
        forwardmove = (gain*self.joystickvalues.axes[4])**3
        sidemove = (gain*self.joystickvalues.axes[3])**3
        upmove = (gain*self.joystickvalues.axes[1])**3

        moving = any([((i > 0.1) or (i < -0.1)) for i in [self.joystickvalues.axes[4], self.joystickvalues.axes[3], self.joystickvalues.axes[1]]])

        htm_Curr_rel_Base, _ = fk(self.currentpos)

        translation_Goal_rel_Curr = np.array([[forwardmove], [sidemove], [upmove]]) # column matrix

        htm_Goal_rel_Curr = np.append(np.append(self.constant_rotation, translation_Goal_rel_Curr, axis=1), np.array([[0.0, 0.0, 0.0, 1.0]]), axis=0)

        htm_Goal_rel_Base = htm_Curr_rel_Base @ htm_Goal_rel_Curr
            
        self.cart_goal_joints = ik(self.currentpos, htm_Goal_rel_Base)

        if moving:
            if self.cart_goal_joints is not None:
                disp_1 = np.round(self.currentpos, decimals=3)
                disp_2 = np.round(self.cart_goal_joints, decimals=3)
                #self.get_logger().info(f'\n\ncurrent theoretical: \n{disp_1}\n\n current actual: \n{self.xarm.get_joints()}\n\ngoal: \n{disp_2}')

                self.currentpos = self.cart_goal_joints
                self.xarm.set_joints(self.currentpos, "high_acc")
                self.dead  = 1
        
        else:
            if self.dead  == 1:
                self.currentpos = self.xarm.get_joints()
                self.xarm.set_joints(self.currentpos, "high_acc")
                self.dead  = 0

        self.homing()
        self.controlGripper()

        disp_3 = np.round(htm_Curr_rel_Base, decimals=3)
        disp_4 = np.round(htm_Goal_rel_Curr, decimals=3)
        disp_5 = np.round(htm_Goal_rel_Base, decimals=3)
        #self.get_logger().info(f'\n\nCurrent relative to base: \n{disp_3}\n')
        #self.get_logger().info(f'\nGoal relative to current: \n{disp_4}\n')
        #self.get_logger().info(f'\nGoal relative to base: \n{disp_5}\n\n')

        return 0


    def shrinebuildMode(self):
        if self.newgoal == True:
            self.cancelshrineBuild()
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