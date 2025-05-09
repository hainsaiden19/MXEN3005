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


    def grab(self):
        self.xarm.grip(1)
        time.sleep(1)
        return 0
    

    def release(self):
        self.xarm.grip(0)
        time.sleep(1)
        return 0


    def move(self, xyzgoal, fr, ry, rx):

        joint_goals = self.get_jointgoals(xyzgoal, step_size=5, fixedrotation=fr, rotation_y=ry, rotation_x=rx)

        #self.get_logger().info(f'joint goals: {joint_goals} \n\n') 

        final_pos = joint_goals[np.shape(joint_goals)[0]-1]

        self.get_logger().info(f"\n\n### Joint goals: {final_pos}")

        error_query = self.xarm.is_goal_valid(final_pos)

        if error_query == 0:
            self.get_logger().info(f'Errors: {error_query}')

            self.xarm.set_joints(final_pos, motion_mode="low_acc")

        #wait until at desired position
        accept_dif = [7, 7, 7, 7, 7, 7]
        goalreached = False
        while not goalreached:
            currentpos = self.xarm.get_joints()
            if all([abs(g - c)<ad for g, c, ad in zip(list(final_pos), currentpos, accept_dif)]):
                goalreached = True
                self.get_logger().info(f'\n\nReached Goal\n')
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
    

    def get_jointgoals(self, xyzgoal, step_size, fixedrotation, rotation_y, rotation_x):
        goal_pos_mm = xyzgoal

        htm_init, _ = fk(self.xarm.get_joints())  

        rotation_init = htm_init[0:3, 0:3]      

        initial_pos_mm = htm_init[0:3, 3]

        bottomrow = np.array([[0, 0, 0, 1]])

        direction = [int((g - i)/abs(g - i)) for g, i in zip(goal_pos_mm, initial_pos_mm)]

        num_total_increments = self.gettotalIncrements(initial_pos_mm, goal_pos_mm, step_size)
        
        # goal poulation
        n = int(num_total_increments)+1

        goals = np.zeros((n, 3))
        
        eulergoals = np.zeros((n, 3))
        rotationgoals = np.zeros([n*3, 3])

        x = xyzgoal[0]; y = xyzgoal[1]
        rz = np.rad2deg(np.arctan2(y, x))

        asquat = spst.Rotation.from_matrix(rotation_init).as_quat()
        euler_init = spst.Rotation.from_quat(asquat).as_euler('xyz', degrees=True)
        eulergoals[0] = euler_init
        euler_final = np.array([rotation_x, rotation_y, rz])
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
                    self.get_logger().info(f'\n\n Error: Didnt Converge\n') 
                    #return None

        return joint_goals
    

    # this function will be used to get a set of goals from any specified starting position
    def get_jointgoals_projection(self, xyzgoal, current_pos, step_size, fixedrotation, rotation_y):
        goal_pos_mm = xyzgoal

        htm_init, _ = fk(self.xarm.get_joints())  

        rotation_init = htm_init[0:3, 0:3]      

        initial_pos_mm = htm_init[0:3, 3]

        bottomrow = np.array([[0, 0, 0, 1]])

        #self.get_logger().info(f'htm: {htm_init} \n\n') 

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
        euler_final = np.array([0, rotation_y, rz])
        eulerstep = (euler_final - euler_init)/num_total_increments

        for r in range(n):
            if r == 0:
                goals[r] = initial_pos_mm
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


    def goalchecker(self, xpick, ypick, xplace, yplace):

        criteria_x_pick = [(xpick > 0) and (xpick < 320)]
        criteria_y_pick = [(ypick > -320) and (ypick < 320)]
        criteria_xy_pick = [np.sqrt(xpick**2 + ypick**2) > 150.0]

        criteria_x_place = [(xplace > 0) and (xplace < 320)]
        criteria_y_place = [(yplace > -320) and (yplace < 320)]
        criteria_xy_place = [np.sqrt(xplace**2 + yplace**2) > 150.0]

        goalvalid = False
        if criteria_x_pick[0] == False:
            goalvalid = False
            self.get_logger().info(f'\n\n##### Error #####\n\n> X pick position is out of bounds\n')
        elif criteria_y_pick[0] == False:
            goalvalid = False
            self.get_logger().info(f'\n\n##### Error #####\n\n> Y pick position is out of bounds\n')
        elif criteria_xy_pick[0] == False:
            goalvalid = False
            self.get_logger().info(f'\n\n##### Error #####\n\n> X and Y pick positions are too close to robot base\n')
        elif criteria_x_place[0] == False:
            goalvalid = False
            self.get_logger().info(f'\n\n##### Error #####\n\n> X place position is out of bounds\n')
        elif criteria_y_place[0] == False:
            goalvalid = False
            self.get_logger().info(f'\n\n##### Error #####\n\n> Y place position is out of bounds\n')
        elif criteria_xy_place[0] == False:
            goalvalid = False
            self.get_logger().info(f'\n\n##### Error #####\n\n> X and Y place positions are too close to robot base\n')
        else: 
            goalvalid = True
            self.get_logger().info(f'\n\n### All goals are acceptable ###\n\n')

        return goalvalid


    ### Service Execution ###
    def service_callback(self, request, response):
        xpick = request.xpick
        ypick = request.ypick
        xplace = request.xplace
        yplace = request.yplace

        # moves:
        # 1. go up [go from current position and orientation to the origin position with origin orientation]
        # 2. rotate to the picking position with flat orientation, dont turn downwards
        # 3. go down to the object and close gripper
        # 4. go back up to position 2 with downturned orientation
        # 5. rotate to placing position with downturned orientation
        # 6. go down to place with downturned orientation and release

        self.get_logger().info("\n\n### Pick and Place Initiated ###\n")

        goalsvalid = self.goalchecker(xpick, ypick, xplace, yplace)

        if goalsvalid:

            movorigin = [350, 0.0, 400.0]
            f = 1.1
            mov2 = [xpick*f, ypick*f, 300.0]
            mov3 = [xpick, ypick, 15.0]
            mov4 = [xpick*f, ypick*f, 300.0]
            mov5 = [xplace*f, yplace*f, 300.0]
            mov6 = [xplace, yplace, 15.0]
            mov7 = [xplace*f, yplace*f, 300.0]

            self.release()

            self.move(movorigin, fr=False, ry=0, rx=0)
                
            self.move(mov2, fr=False, ry=60, rx=90)

            self.move(mov3, fr=False, ry=90, rx=90)

            self.grab()

            self.move(mov4, fr=False, ry=60, rx=90)

            self.move(mov5, fr=False, ry=60, rx=90)

            self.move(mov6, fr=False, ry=90, rx=0)

            self.release()

            self.move(mov7, fr=False, ry=60, rx=0)

            self.move(movorigin, fr=False, ry=0, rx=0)

            self.get_logger().info(f"\n\n### Pick and Place Executed Succesfully ###\n\n")

            response.response = True

        else:
            response.response = False
            
        return response
        #######################################################


def main(args=None):

    rclpy.init(args=args)

    node = PickAndPlaceNode()
    rclpy.spin(node)
    node.destroy_node()

    rclpy.shutdown()

    return 0

if __name__ == '__main__':
    main()