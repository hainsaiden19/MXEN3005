import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient

import time

import numpy as np

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
        pick_pos = [xpick, ypick, 200.0]

        self.xarm.home()

        time.sleep(3)

        mov1 = [300.0, 0.0, 400.0]
        mov2 = [xpick, ypick, 100.0]

        self.move(mov1)
        time.sleep(2)
        
        self.move(mov2)

        #self.action_callback(pick_pos)
        return response
    #######################################################


    def move(self, xyzgoal):
        joint_goals = self.get_jointgoals(xyzgoal)
        self.get_logger().info(f'joint goals: {joint_goals} \n\n') 
        final_pos = joint_goals[np.shape(joint_goals)[0]-1]
        self.xarm.set_joints(final_pos)
        # wait until at desired position
        #accept_dif = [3, 3, 3, 3, 3, 3]
        #goalreached = False
        #while not goalreached:
            #currentpos = self.xarm.get_joints()
            #if all([abs(g - c)<ad for g, c, ad in zip(list(final_pos), currentpos, accept_dif)]):
                #goalreached = True
        return 0


    def get_jointgoals(self, xyzgoal):
        goal_pos_mm = xyzgoal
        # get current htm
        htm_init, _ = fk(self.xarm.get_joints())
        rotation = htm_init[0:3, 0:3]
        xyz_init = htm_init[0:3, 3]
        bottomrow = np.array([[0, 0, 0, 1]])

        initial_pos_mm = xyz_init

        difference = [abs(g - i) for g, i in zip(goal_pos_mm, initial_pos_mm)]
        direction = [int((g - i)/abs(g - i)) for g, i in zip(goal_pos_mm, initial_pos_mm)]

        step_size = 1 # mm
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

        # goal poulation
        # goals = nX3 matrix, any number of goals, only 3 columns, x y z
        # find largest number of increments
        n = int(max(num_total_increments))+1
        goals = np.zeros((n, 3))

        for r in range(n):
            if r == 0:
                goals[r] = initial_pos_mm
            else: 
                goals[r] = goals[r-1] + [direction[0]*step_size, direction[1]*step_size, direction[2]*step_size]
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
                htm_current = np.append(np.append(rotation, np.reshape(xyz, newshape=(3, 1)), axis=1), bottomrow, axis=0)
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