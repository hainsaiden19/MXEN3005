from setuptools import find_packages, setup
import os
from glob import glob

package_name = 'wx250s'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (
            os.path.join("share", package_name, "launch"),
            glob(os.path.join("launch", "*launch.[pxy][yma]*")),
        ),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='robot',
    maintainer_email='robot@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'homing_node = wx250s.homing_node:main',
            'gripper_node = wx250s.gripper_node:main',
            'joint_state_node = wx250s.joint_state_node:main',
            'joint_ptp_node = wx250s.joint_ptp_node:main',
            'pose_node = wx250s.pose_node:main',
            'cartesian_ptp_node = wx250s.cartesian_ptp_node:main',
            'pick_and_place_node = wx250s.pick_and_place_node:main',
        ],
    },
)