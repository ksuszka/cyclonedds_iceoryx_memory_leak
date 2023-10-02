#include <iostream>
#include <thread>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

void topic_callback(const std_msgs::msg::String & msg)
{
  std::cout << "Received " << std::string(msg.data).substr(0,25) << std::endl;
  std::this_thread::sleep_for(100ms);
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("test_listener");
  auto subscription =
    node->create_subscription<std_msgs::msg::String>("topic", 250, topic_callback);

  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}