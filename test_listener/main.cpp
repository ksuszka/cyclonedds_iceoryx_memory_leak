#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("test_listener");

  auto tf_buffer = tf2_ros::Buffer(node->get_clock());
  auto tf_listener = tf2_ros::TransformListener(tf_buffer);

  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}