import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient

import time

import numpy as np
import scipy.spatial.transform as spst

from wx250s_interface.action import CartesianPTP
from wx250s_interface.srv import PickPlace

from .wx250s_kinematics import *

from xarmclient import XArm

class PickAndPlaceNode(Node):
    def __init__(self):
        super().__init__("pick_and_place_node")

        ### Robot Init ###
        self.xarm = XArm()
        #######################

        ### Service Server ###
        self.service = self.create_service(PickPlace, "pick_and_place", self.service_callback)
        #####################################################################################

        ### Action Client ###
        #self.action_client = ActionClient(self, CartesianPTP, 'set_cartesian_ptp')
        ############################################################################

    ### Service Execution ###
    def service_callback(self, request, response):
        xpick = request.xpick
        ypick = request.ypick
        xplace = request.xplace
        yplace = request.yplace

        #self.xarm.home()

        #time.sleep(3)

        movorigin = [200, 0.0, 300.0]
        mov2 = [xpick, ypick, 300.0]
        mov3 = [xpick, ypick, 10.0]
        mov4 = [xpick, ypick, 300.0]
        mov5 = [xplace, yplace, 300.0]
        mov6 = [xplace, yplace, 10.0]


        self.move(movorigin, fr=True)
        
        self.move(mov2, fr=False)

        self.move(mov3, fr=False)

        self.xarm.grip(1)

        self.move(mov4, fr=True)

        self.move(mov5, fr=False)

        self.move(mov6, fr=False)

        self.xarm.grip(0)
        

        #self.action_callback(pick_pos)
        return response
    #######################################################


    def move(self, xyzgoal, fr):

        joint_goals = self.get_jointgoals(xyzgoal, step_size=5, fixedrotation=fr)

        self.get_logger().info(f'joint goals: {joint_goals} \n\n') 

        final_pos = joint_goals[np.shape(joint_goals)[0]-1]

        self.xarm.set_joints(final_pos)

        #wait until at desired position
        accept_dif = [3, 3, 3, 3, 3, 3]
        goalreached = False
        while not goalreached:
            currentpos = self.xarm.get_joints()
            if all([abs(g - c)<ad for g, c, ad in zip(list(final_pos), currentpos, accept_dif)]):
                goalreached = True
        return 0
    

    def gettotalIncrements(self, initial_pos_mm, goal_pos_mm, step_size):
        difference = [abs(g - i) for g, i in zip(goal_pos_mm, initial_pos_mm)]

        num_whole_increments = [int(i/step_size) for i in difference]
        num_remainder_increments = [0, 0, 0]
        num_total_increments = [0, 0, 0]
        
        remainder = [0, 0, 0]
        for i in range(len(remainder)):
            d = difference[i]
            n = num_whole_increments[i]
            if n == 0:
                remainder[i] = d
            else:
                remainder[i] = d%step_size

        for i, r in enumerate(remainder):
            if r > 0:
                num_remainder_increments[i] += 1
            num_total_increments[i] = num_whole_increments[i] + num_remainder_increments[i]

        return max(num_total_increments)
    

    def get_jointgoals(self, xyzgoal, step_size, fixedrotation):
        goal_pos_mm = xyzgoal

        htm_init, _ = fk(self.xarm.get_joints())  

        rotation_init = htm_init[0:3, 0:3]      

        initial_pos_mm = htm_init[0:3, 3]

        bottomrow = np.array([[0, 0, 0, 1]])

        self.get_logger().info(f'htm: {htm_init} \n\n') 

        direction = [int((g - i)/abs(g - i)) for g, i in zip(goal_pos_mm, initial_pos_mm)]

        num_total_increments = self.gettotalIncrements(initial_pos_mm, goal_pos_mm, step_size)
        
        # goal poulation
        # goals = nX3 matrix, any number of goals, only 3 columns, x y z
        # find largest number of increments
        n = int(num_total_increments)+1
        goals = np.zeros((n, 3))
        eulergoals = np.zeros(((n, 3)))
        rotationgoals = np.zeros([n*3, 3])

        x = xyzgoal[0]; y = xyzgoal[1]
        rz = np.rad2deg(np.arctan2(y, x))

        asquat = spst.Rotation.from_matrix(rotation_init).as_quat()
        euler_init = spst.Rotation.from_quat(asquat).as_euler('xyz', degrees=True)
        euler_init = np.array([0, 0, 0])
        euler_final = np.array([0, 60, rz])
        eulerstep = (euler_final - euler_init)/num_total_increments

        for r in range(n):
            if r == 0:
                goals[r] = initial_pos_mm
                #eulergoals[r] = [0, 0, 0]
            else: 
                goals[r] = goals[r-1] + [direction[0]*step_size, direction[1]*step_size, direction[2]*step_size]

                eulergoals[r] = eulergoals[r-1] + eulerstep
                quats = spst.Rotation.from_euler('xyz', eulergoals[r], degrees=True).as_quat()
                rotationgoals[3*r : 3+3*r] = spst.Rotation.from_quat(quats).as_matrix()
                
                for c in range(len(goals[r])):
                    if direction[c] > 0:
                        if goals[r][c] > goal_pos_mm[c]:
                            goals[r][c] = goal_pos_mm[c]
                    else: 
                        if goals[r][c] < goal_pos_mm[c]:
                            goals[r][c] = goal_pos_mm[c]

        xyzgoals = goals

        joint_goals = np.zeros((n, 6))
        joint_goals[0] = self.xarm.get_joints()
        #error_query = 0
        for i, xyz in enumerate(xyzgoals):
            if i > 0:
                if fixedrotation:
                    htm_current = np.append(np.append(rotation_init, np.reshape(xyz, newshape=(3, 1)), axis=1), bottomrow, axis=0)
                else: 
                    htm_current = np.append(np.append(rotationgoals[3*i : 3+3*i], np.reshape(xyz, newshape=(3, 1)), axis=1), bottomrow, axis=0)

                joint_goals[i] = ik(joint_goals[i-1], htm_current)
                if joint_goals[i] is None:
                    self.get_logger().info(f'didnt converge') 
                    #return None

        return joint_goals


def main(args=None):

    rclpy.init(args=args)

    node = PickAndPlaceNode()
    rclpy.spin(node)
    node.destroy_node()

    rclpy.shutdown()

    return 0

if __name__ == '__main__':
    main()