cmake_minimum_required(VERSION 3.0.2)
project(exproblab_ass2)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED
  roscpp
  rospy
  std_msgs
  urdf
  sensor_msgs
  moveit_ros_planning_interface
  visualization_msgs
  gazebo_msgs
  message_generation
  turtlesim
  tf
  moveit_commander
  moveit_msgs
  rosplan_planning_system
)


################################################
## Declare ROS messages, services and actions ##
################################################

## Generate messages in the 'msg' folder
 add_message_files(
   FILES
   ErlOracle.msg
#   Message2.msg
 )

## Generate services in the 'srv' folder
add_service_files(
   FILES
   Oracle.srv
   Move_arm.srv
   Cons_IDs.srv
   Replan_srv.srv
#   Service2.srv
 )

## Generate actions in the 'action' folder
 add_action_files(
   FILES
   go_to_point.action
#   Action2.action
 )
## Generate added messages and services with any dependencies listed here
 generate_messages(
   DEPENDENCIES
   std_msgs  # Or other packages containing msgs
   actionlib_msgs
 )

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################


###################################
## catkin specific configuration ##
###################################

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES exproblab_ass2
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
 include
 ${catkin_INCLUDE_DIRS}
)


 add_executable(simulation src/simulation.cpp)
 

## Add cmake target dependencies of the executable
## same as for the library above
add_dependencies(simulation ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
 target_link_libraries(simulation
   ${catkin_LIBRARIES}
 )
######
## Install ##
#############


 catkin_install_python(PROGRAMS
   scripts/go_to_point.py
   scripts/move_arm.py
   scripts/start.py
   scripts/listener.py
   scripts/replan.py
   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
 )


#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_exproblab_ass2.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
