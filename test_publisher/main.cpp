#include "rclcpp/rclcpp.hpp"

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::NodeOptions options;
  options.start_parameter_event_publisher(true);
  auto node = rclcpp::Node::make_shared("test_publisher", options);
  rclcpp::shutdown();
  return 0;
}
