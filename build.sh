#! /bin/bash

cd ~/catkin_ws/bin/
rm dlut_*
cd ~/catkin_ws/
catkin_make
catkin_make install
