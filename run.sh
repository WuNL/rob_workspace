#! /bin/bash

bash kill.sh
roscore &
sleep 3
cd ~/catkin_ws/bin/

#datetime=${date +%Y_%m_%d_%H_%M_%S};
touch hokuyo.txt
rosrun urg_node urg_node 1>/dev/null 2>>hukuyo.txt &
touch serial_com.txt;
./dlut_serial_com 1>/dev/null 2>>serial_com.txt &

touch motor_hokuyo.txt
./dlut_motor_hokuyo 1>/dev/null 2>>motor_hokuyo.txt &
touch hash.txt
./dlut_odom_hash_v1 1>>hash.txt 2>>hash.txt &
rqt_graph &
sleep 1;
./dlut_sick_key
exit 0;
