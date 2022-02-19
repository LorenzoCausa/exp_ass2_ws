cmake_minimum_required(VERSION 3.0.2)
project(rosplan_interface_ass2)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rosplan_planning_system
)


catkin_package(

)


include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)


add_executable(initialize src/initialize.cpp)
add_executable(goto_waypoint src/goto_waypoint.cpp)
add_executable(take_hint src/take_hint.cpp)
add_executable(check_hp src/check_hp.cpp)
add_executable(test_hp src/test_hp.cpp)
add_executable(test_stuff src/test_stuff.cpp)
 

add_dependencies(initialize ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(goto_waypoint ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(take_hint ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(check_hp ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(test_hp ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(test_stuff ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

 target_link_libraries(initialize
   ${catkin_LIBRARIES}
 )

 target_link_libraries(goto_waypoint
   ${catkin_LIBRARIES}
 )

 target_link_libraries(take_hint
   ${catkin_LIBRARIES}
 )
 
  target_link_libraries(check_hp
   ${catkin_LIBRARIES}
 )
 
   target_link_libraries(test_hp
   ${catkin_LIBRARIES}
 )
 
   target_link_libraries(test_stuff
   ${catkin_LIBRARIES}
 )
