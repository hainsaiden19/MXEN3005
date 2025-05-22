from setuptools import find_packages, setup
import os
from glob import glob

package_name = 'wx250s_teleop'

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
            'pick_and_place_node = wx250s_teleop.pick_and_place_node:main',
            'homing_node = wx250s_teleop.homing_node:main',
            'joystick_node = wx250s_teleop.joystick_node:main',
            'shrine_build_node = wx250s_teleop.shrine_build_node:main',
            'state_change_node = wx250s_teleop.state_change_node:main',
            'testing_node = wx250s_teleop.testing_node:main',
        ],
    },
)
