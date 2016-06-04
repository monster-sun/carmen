cmake_minimum_required(VERSION 2.8.3)
project(carmen_moveit_config)

find_package(catkin REQUIRED COMPONENTS roscpp moveit_ros_planning_interface)

find_package(cmake_modules REQUIRED)
find_package(Eigen REQUIRED)
include_directories(SYSTEM ${Boost_INCLUDE_DIR} ${EIGEN_INCLUDE_DIRS})

catkin_package()

install(DIRECTORY launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
install(DIRECTORY config DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

add_executable(move_group_interface_random src/move_group_interface_random.cpp)
target_link_libraries(move_group_interface_random ${catkin_LIBRARIES})

add_executable(move_group_interface_coordinate src/move_group_interface_coordinate.cpp)
target_link_libraries(move_group_interface_coordinate ${catkin_LIBRARIES})

add_executable(move_group_interface_coordinate2 src/move_group_interface_coordinate2.cpp)
target_link_libraries(move_group_interface_coordinate2 ${catkin_LIBRARIES})

add_executable(move_group_interface_coordinate3 src/move_group_interface_coordinate3.cpp)
target_link_libraries(move_group_interface_coordinate3 ${catkin_LIBRARIES})

add_executable(carmen_node src/carmen_node.cpp)
target_link_libraries(carmen_node ${catkin_LIBRARIES})
