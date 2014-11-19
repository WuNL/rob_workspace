#! /bin/bash

for pid in $(ps -ef|grep dlut|grep -v grep|cut -c 10-15)
do
    echo "ready to kill ${pid}"
    kill -9 ${pid}
done
killall -9 urg_node

killall -9 rqt_graph
killall -9 rviz
killall -9 rosout
killall -9 rosmaster
killall -9 roscore
