#include <iostream>
#include <memory>

#include <unistd.h>
#include <stdlib.h>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class MinimalSubscriber : public rclcpp::Node
{
public:
    MinimalSubscriber()
    : Node("minimal_subscriber")
    {
        RCLCPP_INFO(this->get_logger(), "Launching node...");

        int *leakInteger = static_cast<int *>(malloc(sizeof(int)));
        *leakInteger = 1;
        RCLCPP_INFO(this->get_logger(), "Integer = %i", *leakInteger);

        subscription_ = this->create_subscription<std_msgs::msg::String>(
                        "topic",
                        10,
                        [this](std_msgs::msg::String::UniquePtr msg) {
                            RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
                        });
    }

private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MinimalSubscriber>());
    rclcpp::shutdown();

    return 0;
}
