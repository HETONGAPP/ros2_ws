#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include <depth_image.h>
#include <librealsense2/rs.hpp>
#include <memory>
#include <pcl/filters/filter.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <rgb_image.h>
#include <sensor_msgs/image_encodings.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <string>
#include <thread>
#include <X11/Xlib.h>

// add the using thread and pcl declare
using namespace std::chrono_literals;
using PointT = pcl::PointXYZRGB;
using PointcloudT = pcl::PointCloud<PointT>;

// Create a publisher thread for the color images
void RGB_image_thread(rs2::pipeline &pipe) {
  auto RGB_node = std::make_shared<RgbImage>(pipe);
  rclcpp::spin(RGB_node);
}

// Create a publisher thread for the depth images
void depth_image_thread(rs2::pipeline &pipe) {
  auto depth_node = std::make_shared<DepthImage>(pipe);
  rclcpp::spin(depth_node);
}

int main(int argc, char *argv[]) {

  rclcpp::init(argc, argv);
  XInitThreads();
  // Declare the RealSense pipeline and configure it for depth and color streams
  rs2::pipeline pipe;
  rs2::config cfg;
  cfg.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 30);
  cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_RGB8, 30);

  // Start the RealSense pipeline
  pipe.start(cfg);

  std::thread RGB(RGB_image_thread, std::ref(pipe));
  std::thread depth(depth_image_thread, std::ref(pipe));

  RGB.join();
  depth.join();

  rclcpp::shutdown();

  return 0;
}