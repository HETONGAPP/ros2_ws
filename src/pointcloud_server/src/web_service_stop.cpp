//#include "../include/pointcloud_server/srv/launch_commands.hpp"
#include "pointcloud_server/srv/launch_commands.hpp"
#include <cstdlib>
#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <string>
#include <sys/wait.h>
#include <thread>
#include <unistd.h>
using namespace std::placeholders;

class LaunchServiceNode : public rclcpp::Node {
public:
  LaunchServiceNode() : Node("launch_service_stop") {
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
      pid_t pid = fork();
      if (pid == -1) {
        perror("fork");
        exit(1);
      } else if (pid == 0) {
        std::string received_data = request->stop;

        std::string cmd1 = "gnome-terminal";
        std::string cmd2 = "-e";
        std::string cmd3 = "killall my_publisher";
        char *const argv[] = {&cmd1[0], &cmd2[0], &cmd3[0], NULL};

        // int resul = system(received_data.c_str());
        execvp("gnome-terminal", argv);
        exit(1);
      } else {
        int status;
        waitpid(pid, &status, 0);
      }

      response->success = true;

      // RCLCPP_INFO(this->get_logger(), "List parameters request received
      // %s",received_data.c_str());
    };

    // Create the list parameters service
    launch_service_ =
        this->create_service<pointcloud_server::srv::LaunchCommands>(
            "/launch_stop", handle_list_parameters);
  }

private:
  rclcpp::Service<pointcloud_server::srv::LaunchCommands>::SharedPtr
      launch_service_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<LaunchServiceNode>());
  rclcpp::shutdown();

  return 0;
}