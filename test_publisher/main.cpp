#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("test_publisher");
  auto publisher = node->create_publisher<std_msgs::msg::String>("topic", 250);
  std_msgs::msg::String message;
  auto publish_count = 0;
  for(auto cnt=0; cnt<1000; cnt++) {
    message.data = "Hello, world! " + std::to_string(publish_count++) + " " + std::string(7000, '.');
    publisher->publish(message);
    rclcpp::spin_some(node);
  }
  throw std::runtime_error("forced error");  
  return 0;
}
