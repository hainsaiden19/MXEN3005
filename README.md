# MXEN3005
Mechatronics Design Project Workspace


# Command Line Executables:
- python -m colcon build
- source install/setup.bash
- ros2 launch wx250s wx250s_launch.xml
- ros2 action send_goal /set_point_ptp wx250s_interface/action/JointPTP "{joint_goal: [x, x, x, x, x, x]}"


# Stuff to Remember:
- always launch in VM, never vscode, otherwise it wont execute xarmserver properly


checking pull requests
