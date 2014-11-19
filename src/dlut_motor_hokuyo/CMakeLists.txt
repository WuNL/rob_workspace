cmake_minimum_required(VERSION 2.8.3)
project(dlut_motor_hokuyo)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs message_generation)

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
## Declare a cpp executable
 add_executable(dlut_motor_hokuyo src/motor_hokuyo.cpp)
 add_executable(dlut_motor_net src/motor_net.cpp)
## Add cmake target dependencies of the executable/library
## as an example, message headers may need to be generated before nodes
 add_dependencies(dlut_motor_hokuyo motor_hokuyo_gencpp)
 add_dependencies(dlut_motor_net motor_hokuyo_gencpp)
## Specify libraries to link a library or executable target against
 target_link_libraries(dlut_motor_hokuyo
   ${catkin_LIBRARIES}
 )
 target_link_libraries(dlut_motor_net
   ${catkin_LIBRARIES}
 )

#############
## Install ##
#############

install(TARGETS dlut_motor_hokuyo dlut_motor_net RUNTIME DESTINATION ~/catkin_ws/bin)

