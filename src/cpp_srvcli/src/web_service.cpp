#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include "tutorial_interfaces/srv/launch_commands.hpp"
#include <string>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std::placeholders;

class LaunchServiceNode : public rclcpp::Node
{
public:
  LaunchServiceNode() : Node("launch_service")
  {
    auto handle_list_parameters =
        [this](const std::shared_ptr<rmw_request_id_t> request_header,
               const std::shared_ptr<tutorial_interfaces::srv::LaunchCommands::Request> request,
               std::shared_ptr<tutorial_interfaces::srv::LaunchCommands::Response> response) -> void
    {
      (void)request_header;
      //(void)request;

      // Code to handle the list parameters request and populate the response
      
      std::string received_data = request->command;
      
      int resul = system(received_data.c_str());
      
      response->success = true;
      
      RCLCPP_INFO(this->get_logger(), "List parameters request received %s",received_data.c_str());
    };

    // Create the list parameters service
    launch_service_ =
        this->create_service<tutorial_interfaces::srv::LaunchCommands>(
            "/launch", handle_list_parameters);
  }

private:
  rclcpp::Service<tutorial_interfaces::srv::LaunchCommands>::SharedPtr launch_service_;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<LaunchServiceNode>());
  rclcpp::shutdown();

  return 0;
}