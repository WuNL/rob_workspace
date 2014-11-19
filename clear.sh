#! /bin/bash

cd ~/catkin_ws/build/
echo -n "ready to rm"
ls dlut*
rm -r dlut_*
cd ~/catkin_ws/devel/lib
rm -r dlut_*
cd ~/catkin_ws/bin/
rm dlut_*
exit 0
