//#include "../include/pointcloud_server/srv/launch_commands.hpp"
#include <cstdlib>
#include <iostream>
#include <pointcloud_server/srv/launch_commands.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
using namespace std::placeholders;

class LaunchServiceNode : public rclcpp::Node {
public:
  LaunchServiceNode() : Node("launch_service") {
    auto handle_list_parameters =
        [this](const std::shared_ptr<rmw_request_id_t> request_header,
               const std::shared_ptr<
                   pointcloud_server::srv::LaunchCommands::Request>
                   request,
               std::shared_ptr<pointcloud_server::srv::LaunchCommands::Response>
                   response) -> void {
      (void)request_header;
      //(void)request;

      // Code to handle the list parameters request and populate the response

      std::string received_data = request->command;

      // int resul = system(received_data.c_str());
      system(received_data.c_str());

      response->success = true;

      RCLCPP_INFO(this->get_logger(), "List parameters request received %s",
                  received_data.c_str());
    };

    // Create the list parameters service
    launch_service_ =
        this->create_service<pointcloud_server::srv::LaunchCommands>(
            "/launch", handle_list_parameters);
  }

private:
  rclcpp::Service<pointcloud_server::srv::LaunchCommands>::SharedPtr
      launch_service_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  //   rclcpp::spin(std::make_shared<LaunchServiceNode>());
  //   rclcpp::shutdown();

  return 0;
}