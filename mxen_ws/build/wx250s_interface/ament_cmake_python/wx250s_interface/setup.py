from setuptools import find_packages
from setuptools import setup

setup(
    name='wx250s_interface',
    version='0.0.0',
    packages=find_packages(
        include=('wx250s_interface', 'wx250s_interface.*')),
)
