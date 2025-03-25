import sys
if sys.prefix == '/home/robot/ros2jazzy/.ros2jazzyvenv':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/robot/ros2jazzy/GitRepo/MXEN3005/mxen_ws/install/wx250s'
