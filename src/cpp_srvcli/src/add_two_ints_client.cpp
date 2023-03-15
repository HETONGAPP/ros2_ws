#include <chrono>
#include <cstdlib>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"
#include "tutorial_interfaces/srv/add_three_ints.hpp"
using namespace std::chrono_literals;

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);

    if(argc!=4)
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "usage: add_three_ints_client x y z");
        return 1;   
    }

    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_three_ints_client");
    rclcpp::Client<tutorial_interfaces::srv::AddThreeInts>::SharedPtr client = 
    node->create_client<tutorial_interfaces::srv::AddThreeInts>("add_three_ints");

    auto request = std::make_shared<tutorial_interfaces::srv::AddThreeInts::Request>();
    request->a = atoll(argv[1]);
    request->b = atoll(argv[2]);
    request->c = atoll(argv[3]);
    while(!client->wait_for_service(1s))
    {
        if(!rclcpp::ok())
        {
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"Interrupted while waitting for the service. Exiting.");
            return 0;
        }
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"service not available, waiting again....");
    }

    auto result = client->async_send_request(request);

    if(rclcpp::spin_until_future_complete(node, result) == rclcpp::FutureReturnCode::SUCCESS)
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"Sum: %ld",result.get()->sum);
    }
    else
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"Failed to call service add_three_ints");
    }

    rclcpp::shutdown();
    return 0;
}
