cmake_minimum_required(VERSION 3.5)
project(test_publisher)

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

ament_auto_add_executable(test_publisher main.cpp)
ament_target_dependencies(test_publisher rclcpp std_msgs)

ament_auto_package()
