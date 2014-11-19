#!/bin/bash

ERROR_CODE=65
datetime=$(date +%Y_%m_%d_%H)
WARNNING="Please start with sudo"

if [ ${UID} -ne 0 ]
then
    echo ${WARNNING}
    exit ${ERROR_CODE}
fi

if [ -e ~/catkin_ws/log/deviceERR_${datetime}.txt ]
then
    touch ~/catkin_ws/log/deviceERR.txt
fi

chmod 777 /dev/ttyS0 2>>~/catkin_ws/log/deviceERR_${datetime}.txt
CODE1=$?
if [ ${CODE1} -ne 0 ]
then
    echo "chmod ttyS0 fail"
fi

chmod 777 /dev/ttyS3 2>>~/catkin_ws/log/deviceERR_${datetime}.txt
CODE2=$?
if [ ${CODE2} -ne 0 ]
then
    echo "chmod ttyS3 fail"
fi

chmod 777 /dev/ttyACM0 2>>~/catkin_ws/log/deviceERR_${datetime}.txt
CODE3=$?
if [ ${CODE3} -ne 0 ]
then
    echo "chmod ttyACM0 fail"
fi

let "result=$CODE1||$CODE2||$CODE3"
if [ ${result} -ne 0 ]
then
    echo "Device error"
    exit ${ERROR_CODE}
else
    echo "Success!"
    exit 0
fi
