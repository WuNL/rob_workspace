cmake_minimum_required(VERSION 2.8.3)
project(dlut_pc_odom)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp std_msgs tf message_generation  pcl_ros)
find_package(PCL 1.2 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})

include_directories(
    ${PCL_INCLUDE_DIRS}
)
AUX_SOURCE_DIRECTORY(src SRC_LIST)

#######################################
## Declare ROS messages and services ##
#######################################

## Generate messages in the 'msg' folder
 add_message_files(
   FILES
   motor.msg
   UInt32.msg
 )

## Generate added messages and services with any dependencies listed here
 generate_messages(
   DEPENDENCIES
   std_msgs
 )

###################################
## catkin specific configuration ##
###################################

catkin_package(
   INCLUDE_DIRS include
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(include
  ${catkin_INCLUDE_DIRS}
)
add_executable(dlut_odom_hash_v1 src/odom_hash_v1.cpp) 
add_executable(dlut_odom_hash src/odom_hash.cpp)
add_executable(dlut_odom_pc src/odom_pc.cpp)
#add_executable(hz_test src/hz_test.cpp)
target_link_libraries(dlut_odom_hash_v1
	${catkin_LIBRARIES}
	${PCL_LIBRARIES}
)
target_link_libraries(dlut_odom_hash
	${catkin_LIBRARIES}
	${PCL_LIBRARIES}
)
target_link_libraries(dlut_odom_pc
	${catkin_LIBRARIES}
	${PCL_LIBRARIES}
)

#############
## Install ##
#############

install(TARGETS dlut_odom_hash_v1 dlut_odom_hash dlut_odom_pc RUNTIME DESTINATION ~/catkin_ws/bin)
