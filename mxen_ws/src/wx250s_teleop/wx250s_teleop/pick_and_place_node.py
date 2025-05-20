import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient

import time

import numpy as np
import scipy.spatial.transform as spst

from wx250s_interface.action import CartesianPTP
from wx250s_interface.srv import PickPlace

from std_srvs.srv import Trigger

from .wx250s_kinematics import *

from xarmclient import XArm

class PickAndPlaceNode(Node):
    def __init__(self):
        super().__init__("pick_and_place_node")

        ### Robot Init ###
        self.xarm = XArm()
        #######################

        ### Service Server ###
        self.service = self.create_service(Trigger, "pick_and_place", self.service_callback)
        #####################################################################################


    def grab(self):
        self.xarm.grip(1)
        time.sleep(1)
        return 0
    

    def release(self):
        time.sleep(1)
        self.xarm.grip(0)
        time.sleep(1)
        return 0


    def move(self, xyzgoal, fr, ry, rx, rz):

        step_size=5

        joint_goals = self.get_jointgoals(xyzgoal, step_size, fixedrotation=fr, rotation_y=ry, rotation_x=rx, rotation_z=rz)

        #self.get_logger().info(f'joint goals: {joint_goals} \n\n') 

        final_pos = joint_goals[np.shape(joint_goals)[0]-1]

        self.get_logger().info(f"\n\n### Joint goals: {final_pos}")

        error_query = self.xarm.is_goal_valid(final_pos)

        if error_query == 0:
            self.get_logger().info(f'Errors: {error_query}')

            self.xarm.set_joints(final_pos, motion_mode="low_acc")
            time.sleep(0.05)
            self.xarm.set_joints(final_pos, motion_mode="low_acc")

        if error_query != 0:
            self.get_logger().info(f'### Error ###')
            self.get_logger().info(f'Errors: {error_query}')
            #self.get_logger().info(f'Errors: {self.xarm.ERRORS(error_query)}')

        #wait until at desired position
        accept_dif = [8, 8, 8, 8, 8, 8]
        goalreached = False
        upper_limit = 150
        i = 0
        while (not goalreached) and (i < upper_limit):

            #currentpos = self.xarm.get_joints()

            #goalreachedcheck = [abs(g - c)<ad for g, c, ad in zip(list(final_pos), currentpos, accept_dif)]
            #diff = [abs(g - c) for g, c in zip(list(final_pos), currentpos)]

            #self.get_logger().info(f'\ninside?: {goalreachedcheck}\n')
            #self.get_logger().info(f'\ndif: {diff}\n')

            htm_current, _ = fk(self.xarm.get_joints())

            currentpos = htm_current[0:3, 3]

            htm_final, _ = fk(final_pos)

            goalpos = htm_final[0:3, 3]

            xyzdif = [20, 20, 10]

            goalreachedcheck = [abs(g - c) < d for c, g, d in zip(currentpos, goalpos, xyzdif)]
            dif = [abs(g - c) for c, g in zip(currentpos, goalpos)]

            #self.get_logger().info(f'\ntesting\n')
            #self.get_logger().info(f'\n{goalreachedcheck}\n')
            #self.get_logger().info(f'\n{dif}\n')

            if all(goalreachedcheck):
                goalreached = True
                self.get_logger().info(f'\n\nReached Goal\n')
            
            i += 1
           

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
    

    def get_jointgoals(self, xyzgoal, step_size, fixedrotation, rotation_y, rotation_x, rotation_z):
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

        if rotation_z == 0.0:
            rz = 0.0

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
    

    def goalchecker(self, xpick, ypick, xplace, yplace):

        criteria_x_pick = [(xpick > 0) and (xpick < 350)]
        criteria_y_pick = [(ypick > -350) and (ypick < 350)]
        criteria_xy_pick = [np.sqrt(xpick**2 + ypick**2) > 150.0]

        criteria_x_place = [(xplace > 0) and (xplace < 350)]
        criteria_y_place = [(yplace > -350) and (yplace < 350)]
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
    
    
    def movePillar(self, xpick, ypick, xplace, yplace, zplace):

        # moves:
        # 1. go up [go from current position and orientation to the origin position with origin orientation]
        # 2. rotate to the picking position with flat orientation, dont turn downwards
        # 3. go down to the object and close gripper
        # 4. go back up to position 2 with downturned orientation
        # 5. rotate to placing position with downturned orientation
        # 6. go down to place with downturned orientation and release

        moving = 1.0

        movorigin = [350, 0.0, 400.0]
        
        f = 1
        mov2 = [xpick*f, ypick*f, 300.0]
        mov3 = [xpick, ypick, 50.0]
        mov4 = [xpick*f, ypick*f, 300.0]
        mov5 = [xplace*f, yplace*f, 300.0]
        mov6 = [xplace, yplace, zplace]
        mov7 = [xplace*f, yplace*f, 300.0]

        self.release()

        self.move(movorigin, fr=False, ry=0, rx=0, rz=moving)
            
        self.move(mov2, fr=False, ry=30, rx=0, rz=moving)

        self.move(mov3, fr=False, ry=90, rx=0, rz=moving)

        self.grab()

        self.move(mov4, fr=False, ry=30, rx=0, rz=moving)
        
        self.move(mov5, fr=False, ry=30, rx=0, rz=moving)

        self.move(mov6, fr=False, ry=90, rx=0, rz=moving) 

        self.release() 

        self.move(mov7, fr=False, ry=30, rx=0, rz=moving) 

        self.move(movorigin, fr=False, ry=0, rx=0, rz=moving) 

        self.get_logger().info(f"\n\n### Pick and Place Executed Succesfully ###\n\n")

        return 0
    

    def movePlatform(self, xpick, ypick, xplace, yplace, zplace):

        # Movements:
        # 1. Move to origin position
        # 2. Go to pick position above
        # 3. Go to pick 
        # 4. Move back to above position
        # 5. Rotate to place position above
        # 6. Place platform
        # 7. Move backwards at same height
        # 8. Go up to above position
        # 9. Go back to origin

        rx_pick = -np.rad2deg(np.arctan2(yplace, xplace))
        moving = 1.0 # place holder number means nothing

        f = 0.7
        movorigin = [350, 0.0, 400.0]
        mov2 = [xpick, ypick, 250.0] 
        mov3 = [xpick, ypick, 50.0]
        mov4 = [xpick*f, ypick*f, 250.0]
        mov5 = [xplace*1.1, yplace*1.1, 400.0]
        mov6 = [xplace, yplace, zplace]
        mov7 = [xplace-40, yplace-40, zplace]
        mov8 = [xplace-40, yplace-40, 400.0]

        self.release()

        self.move(movorigin, fr=False, ry=0, rx=0, rz=moving)

        self.move(mov2, fr=False, ry=30, rx=rx_pick, rz=moving)

        self.move(mov3, fr=False, ry=90, rx=0.0, rz=0.0)

        self.grab()

        self.move(mov4, fr=False, ry=90, rx=0, rz=moving)

        self.move(movorigin, fr=False, ry=0, rx=0, rz=moving) 

        self.move(mov5, fr=False, ry=0, rx=45, rz=moving)

        self.move(mov5, fr=False, ry=-40, rx=90, rz=moving)

        self.move(mov6, fr=False, ry=0, rx=90, rz=moving) 

        self.release() 

        self.move(mov7, fr=False, ry=15, rx=90, rz=moving) 

        self.move(mov8, fr=False, ry=30, rx=0, rz=moving) 

        #self.move(movorigin, fr=False, ry=0, rx=0, rz=moving) 

        self.get_logger().info(f"\n\n### Pick and Place Executed Succesfully ###\n\n")

        return 0


    ### Service Execution ###
    def service_callback(self, request, response):

        # moves:
        # 1. go up [go from current position and orientation to the origin position with origin orientation]
        # 2. rotate to the picking position with flat orientation, dont turn downwards
        # 3. go down to the object and close gripper
        # 4. go back up to position 2 with downturned orientation
        # 5. rotate to placing position with downturned orientation
        # 6. go down to place with downturned orientation and release

        self.get_logger().info("\n\n### Pick and Place Initiated ###\n")


        #xpick = 200
        #ypick = 200
        #xplace = 200
        #yplace = 200
        #goalsvalid = self.goalchecker(xpick, ypick, xplace, yplace)

        goalsvalid = True
        if goalsvalid:

            ### level 1 ##################################
            self.movePillar(190, -190, 275, 225, 55.0)
            self.movePillar(260, -194, 175, 320, 55.0)
            self.movePlatform(180, -325, 235, 285, 70.0)
            ##############################################

            ### level 2 ##################################
            self.movePillar(190, -80, 275, 225, 125.0)
            self.movePillar(260, -80, 175, 320, 125.0)
            self.movePlatform(0, -285, 235, 285, 140.0)
            ##############################################

            ### level 3 ##################################
            self.movePillar(190, 20, 375, 225, 195.0)
            self.movePillar(260, 20, 175, 320, 195.0)
            self.movePlatform(160, -265, 235, 285, 300.0)
            ##############################################

            response.success = True

        else:
            response.success = False
            
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