cmake_minimum_required(VERSION 2.8.3)
project(dlut_move_base)


find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs message_generation tf geometry_msgs nav_msgs)

 add_message_files(
   FILES
   Vector3.msg
   Twist.msg
   Pose.msg
   Color.msg
   Velocity.msg
 )

 generate_messages(
   DEPENDENCIES
   std_msgs
 )

catkin_package(
   INCLUDE_DIRS include

)

include_directories(include
  ${catkin_INCLUDE_DIRS}
)

## Declare a cpp executable
 add_executable(dlut_sick_key src/sick_key.cpp)
 add_executable(dlut_serial_com src/serial_com.cpp)
## Add cmake target dependencies of the executable/library
## as an example, message headers may need to be generated before nodes
 add_dependencies(dlut_sick_key dlut_move_base_gencpp)
 add_dependencies(dlut_serial_com dlut_move_base_gencpp)
## Specify libraries to link a library or executable target against
 target_link_libraries(dlut_sick_key
   ${catkin_LIBRARIES}
 )
 target_link_libraries(dlut_serial_com
   ${catkin_LIBRARIES}
 )
install(TARGETS dlut_sick_key dlut_serial_com RUNTIME DESTINATION ~/catkin_ws/bin)

