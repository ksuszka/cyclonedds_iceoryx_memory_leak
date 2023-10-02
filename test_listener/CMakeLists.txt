cmake_minimum_required(VERSION 3.5)
project(test_listener)

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

ament_auto_add_executable(test_listener main.cpp)
ament_target_dependencies(test_listener rclcpp std_msgs)

ament_auto_package()
