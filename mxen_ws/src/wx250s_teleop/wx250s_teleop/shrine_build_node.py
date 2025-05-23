# The following imports are necessary
import threading
import rclpy
from rclpy.action import ActionServer, CancelResponse, GoalResponse
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node


from wx250s_interface.action import ShrineBuild

from .wx250s_kinematics import *

import time
import numpy as np
import scipy.spatial.transform as spst

from xarmclient import XArm


class ShrineBuildNode(Node):

    def __init__(self):
        super().__init__("shrine_build_node")

        ### Class Variables ###
        self.goal_handle = None
        self.goal_lock = threading.Lock()

        self.goal_abort = False

        self.xarm = XArm()
        #######################

        self.action_server = ActionServer(
            self,
            ShrineBuild,
            "build_shrine",
            execute_callback=self.execute_callback,
            goal_callback=self.goal_callback,
            handle_accepted_callback=self.handle_accepted_callback,
            cancel_callback=self.cancel_callback,
            callback_group=ReentrantCallbackGroup(),
        )


    def destroy(self):
        self.action_server.destroy()
        super().destroy_node()


    ### New goal requested ###
    def goal_callback(self, goal_request):
        self.get_logger().info(f"## Shrine Build Requested ##")
        return GoalResponse.ACCEPT


    # This function is called whenever new goal has been accepted
    def handle_accepted_callback(self, goal_handle):
        with self.goal_lock:
            # This server only allows one goal at a time
            if self.goal_handle is not None and self.goal_handle.is_active:
                self.get_logger().info("Aborting previous goal")
                # Abort the existing goal
                self.goal_handle.abort()
            self.goal_handle = goal_handle

        goal_handle.execute()
        self.goal_abort = False


    # This function is called whenever cancel request is received
    def cancel_callback(self, goal):
        # Accept or reject a client request to cancel an action
        self.get_logger().info("Received cancel request")
        self.goal_abort = True
        self.xarm.home()
        time.sleep(3)
        self.xarm.grip(0)
        return CancelResponse.ACCEPT
    

    def grab(self):
        if self.goal_abort == False:
            self.xarm.grip(1)
            time.sleep(2)
        return 0
    

    def release(self):
        if self.goal_abort == False:
            time.sleep(1)
            self.xarm.grip(0)
            time.sleep(1)
        return 0


    def move(self, xyzgoal, fr, ry, rx, rz):

        if self.goal_abort == True:
            result = ShrineBuild.Result()
            result.success = True
            #self.xarm.set_joints(self.xarm.get_joints(), motion_mode="low_acc")
            #self.xarm.home()
            #time.sleep(2)
            #self.xarm.grip(0)
            return result

        else:
            step_size=20

            joint_goals = self.get_jointgoals(xyzgoal, step_size, fixedrotation=fr, rotation_y=ry, rotation_x=rx, rotation_z=rz)

            final_pos = joint_goals[np.shape(joint_goals)[0]-1]

            error_query = self.xarm.is_goal_valid(final_pos)

            #if (error_query == 0) and (not self.goal_abort):

            if error_query == 12:
                final_pos[3] = 0.0

            if error_query == 13:
                final_pos[5] = 0.0

            self.xarm.set_joints(final_pos, motion_mode="low_acc")
            time.sleep(0.05)
            self.xarm.set_joints(final_pos, motion_mode="low_acc")


            if (error_query != 0):
                self.get_logger().info(f'### Error ###')
                self.get_logger().info(f'Errors: {error_query}')
                #self.get_logger().info(f'Errors: {self.xarm.ERRORS(error_query)}')

            #wait until at desired position
            goalreached = False
            upper_limit = 150
            i = 0
            while (not goalreached) and (i < upper_limit) and (not self.goal_abort):
                #time.sleep(0.1)
                #self.get_logger().info(f'{self.xarm.get_joints()}')
                current_joints = np.array(self.xarm.get_joints())
                htm_current, _ = fk(current_joints)

                currentpos = htm_current[0:3, 3]

                htm_final, _ = fk(final_pos)

                goalpos = htm_final[0:3, 3]

                xyzdif = [20, 20, 10]

                goalreachedcheck = [abs(g - c) < d for c, g, d in zip(currentpos, goalpos, xyzdif)]
                dif = [abs(g - c) for c, g in zip(currentpos, goalpos)]

                if all(goalreachedcheck):
                    goalreached = True
                    self.get_logger().info(f'\n\nReached Position\n')

                i += 1

            time.sleep(0.1)
           

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
    
    
    def movePillar(self, xpick, ypick, xplace, yplace, zplace, ryplace):

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
        mov2 = [xpick, ypick, 350.0]
        move2_1 = [xpick, ypick, 150.0]
        mov3 = [xpick, ypick, 40.0]
        mov4 = [xpick+30, ypick+30, 350.0]
        mov5 = [xplace, yplace, 300.0]
        mov6 = [xplace, yplace, zplace]
        mov6_1 = [xplace+30, yplace+30, 200.0]
        mov7 = [xplace+20, yplace+20, 350.0]

        self.release()

        self.move(movorigin, fr=False, ry=0, rx=0, rz=moving)

        self.move(mov2, fr=False, ry=30, rx=0, rz=moving)

        self.move(move2_1, fr=False, ry=60, rx=0, rz=moving)

        self.move(mov3, fr=False, ry=ryplace, rx=0, rz=moving)

        self.grab()

        self.move(mov4, fr=False, ry=30, rx=0, rz=moving)

        self.move(mov5, fr=False, ry=30, rx=0, rz=moving)

        self.move(mov6, fr=False, ry=ryplace, rx=0, rz=moving) 

        self.release() 

        self.move(mov6_1, fr=False, ry=30, rx=0, rz=moving) 

        #self.xarm.home()

        self.move(mov7, fr=False, ry=30, rx=0, rz=moving) 

        self.move(movorigin, fr=False, ry=0, rx=0, rz=moving) 

        self.get_logger().info(f"\n\n### Pick and Place Executed Succesfully ###\n\n")

        return 0
    

    def movePlatform(self, xpick, ypick, xplace, yplace, zplace, backmove, backadd, aboveplaceheight, aboveaddition, orientation):

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
        mov2_1 = [xpick, ypick, 100.0] 
        mov3 = [xpick, ypick, 40.0]
        mov4 = [xpick*f, ypick*f, 250.0]
        mov5 = [xplace+30, yplace+30, aboveplaceheight]
        mov6 = [xplace, yplace, zplace]
        mov7 = [xplace-backmove, yplace-backmove, zplace]
        mov8 = [xplace-(backmove+backadd), yplace-(backmove+backadd), aboveplaceheight+aboveaddition]

        self.release()

        self.move(movorigin, fr=False, ry=0, rx=0, rz=moving)

        self.move(mov2, fr=False, ry=30, rx=rx_pick, rz=moving)

        self.move(mov2_1, fr=False, ry=60, rx=rx_pick, rz=moving)

        self.move(mov3, fr=False, ry=90, rx=0.0, rz=0.0)

        self.grab()

        self.move(mov4, fr=False, ry=90, rx=0, rz=moving)

        self.move(movorigin, fr=False, ry=0, rx=0, rz=moving) 

        self.move(mov5, fr=False, ry=0, rx=orientation*60, rz=moving)

        self.move(mov5, fr=False, ry=-40, rx=orientation*90, rz=moving)

        self.move(mov6, fr=False, ry=0, rx=orientation*90, rz=moving) 

        self.release() 

        self.move(mov7, fr=False, ry=20, rx=orientation*90, rz=moving) 

        #self.move(mov8, fr=False, ry=60, rx=0, rz=moving) 

        self.xarm.home()

        #self.move(movorigin, fr=False, ry=0, rx=0, rz=moving) 

        self.get_logger().info(f"\n\n### Pick and Place Executed Succesfully ###\n\n")

        return 0


    # This function is called at the start of action execution
    def execute_callback(self, goal_handle):
        self.get_logger().info("## Executing Shrine Build ##")

        result = ShrineBuild.Result()

        self.xarm.get_joints()
        self.xarm.home()
        self.xarm.get_joints()
        time.sleep(3)
        
        ### level 1 ##################################
        self.movePillar(190, -190, 275, 225, 55.0, 90)
        self.movePillar(260, -194, 175, 320, 55.0, 90)
        self.movePlatform(180, -325, 215, 265, 100.0, 40.0, 0.0, 400.0, 20.0, 1)
        ##############################################
        
        ### level 2 ##################################
        self.movePillar(190, -80, 275, 215, 135.0, 90)
        self.movePillar(260, -80, 175, 320, 135.0, 90)
        self.movePlatform(0, -285, 210, 260, 100.0, 320.0, 20.0, 400.0, 20.0, -1)
        ##############################################
        
        ### level 3 ##################################
        self.movePillar(190, 10, 275, 225, 195.0, 45)
        self.movePillar(260, 10, 175, 320, 195.0, 45)
        self.movePlatform(160, -265, 210, 260, 100.0, 360.0, 70.0, 450.0, 20.0, 1)
        ##############################################

        self.get_logger().info("## Shrine Built ##")


        #        goal aborting and cancelling       #
        if not goal_handle.is_active:   
            self.get_logger().info("Goal aborted")
            return ShrineBuild.Result()
        if goal_handle.is_cancel_requested:
            goal_handle.canceled()
            self.get_logger().info("Goal canceled")
            return ShrineBuild.Result()
        #                                           #
            
        with self.goal_lock:
            if not goal_handle.is_active:
                self.get_logger().info("Goal aborted")
                return ShrineBuild.Result()
            goal_handle.succeed()


        result.success = True
        #feedback_msg = ShrineBuild.Feedback()
        #self.get_logger().info(f"Currently Building: {feedback_msg.buildstate}")

        return result


def main(args=None):
    rclpy.init(args=args)

    node = ShrineBuildNode()

    # We use a MultiThreadedExecutor to handle incoming goal requests concurrently
    executor = MultiThreadedExecutor()
    rclpy.spin(node, executor=executor)

    node.destroy()
    rclpy.shutdown()


if __name__ == "__main__":
    main()