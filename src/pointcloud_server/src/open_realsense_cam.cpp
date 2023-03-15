#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include <librealsense2/rs.hpp>
#include <memory>
#include <pcl/filters/filter.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <sensor_msgs/image_encodings.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <string>

using PointT = pcl::PointXYZRGB;
using PointCloudT = pcl::PointCloud<PointT>;

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<rclcpp::Node>("realsense_camera");

  // Declare the RealSense pipeline and configure it for depth and color streams
  rs2::pipeline pipe;
  rs2::config cfg;
  cfg.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 30);
  cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_RGB8, 30);

  // Start the RealSense pipeline
  pipe.start(cfg);

  // Create a publisher for the depth and color images
  auto depth_publisher =
      node->create_publisher<sensor_msgs::msg::Image>("depth", 10);
  auto color_publisher =
      node->create_publisher<sensor_msgs::msg::Image>("color", 10);
  auto point_cloud_publisher =
      node->create_publisher<sensor_msgs::msg::PointCloud2>("point_cloud", 10);

  // Set up a timer to read frames from the RealSense pipeline and publish them
  auto timer = node->create_wall_timer(std::chrono::milliseconds(33), [&]() {
    rs2::frameset frames = pipe.wait_for_frames();

    // Publish the depth image
    rs2::depth_frame depth_frame = frames.get_depth_frame();
    sensor_msgs::msg::Image depth_image;
    depth_image.header.frame_id = "realsense_camera";
    depth_image.header.stamp = node->now();
    depth_image.width = depth_frame.get_width();
    depth_image.height = depth_frame.get_height();
    depth_image.encoding = sensor_msgs::image_encodings::TYPE_16UC1;
    depth_image.step = depth_image.width * sizeof(uint16_t);
    depth_image.data.resize(depth_image.height * depth_image.step);
    memcpy(depth_image.data.data(), depth_frame.get_data(),
           depth_image.data.size());
    depth_publisher->publish(depth_image);

    // Publish the color image
    rs2::video_frame color_frame = frames.get_color_frame();
    sensor_msgs::msg::Image color_image;
    color_image.header.frame_id = "realsense_camera";
    color_image.header.stamp = node->now();
    color_image.width = color_frame.get_width();
    color_image.height = color_frame.get_height();
    color_image.encoding = sensor_msgs::image_encodings::RGB8;
    color_image.step = color_image.width * 3;
    color_image.data.resize(color_image.height * color_image.step);

    memcpy(color_image.data.data(), color_frame.get_data(),
           color_image.data.size());
    color_publisher->publish(color_image);

    // Convert the depth and color images to a point cloud
    rs2::points points = rs2::pointcloud().calculate(depth_frame);
    PointCloudT::Ptr cloud(new PointCloudT);
    for (const rs2::vertex *vertex = points.get_vertices();
         vertex < points.get_vertices() + points.size(); vertex++) {
      PointT pt;
      pt.x = vertex->x;
      pt.y = vertex->y;
      pt.z = vertex->z;
      const uint8_t *color =
          reinterpret_cast<const uint8_t *>(color_frame.get_data());
      const size_t width = color_frame.get_width();
      const size_t height = color_frame.get_height();
      const float x_norm = (vertex->x + 0.5f) / width;
      const float y_norm = (vertex->y + 0.5f) / height;
      const int x = static_cast<int>(x_norm * vertex->x);
      const int y = static_cast<int>(y_norm * vertex->y);
      pt.r = color[3 * (y * width + x) + 0];
      pt.g = color[3 * (y * width + x) + 1];
      pt.b = color[3 * (y * width + x) + 2];
      cloud->push_back(pt);
    }

    // Remove NaN values from the point cloud
    std::vector<int> indices;
    pcl::removeNaNFromPointCloud(*cloud, *cloud, indices);

    // Publish the point cloud data
    sensor_msgs::msg::PointCloud2 point_cloud;
    pcl::toROSMsg(*cloud, point_cloud);
    point_cloud.header.frame_id = "realsense_camera";
    point_cloud.header.stamp = node->now();
    point_cloud_publisher->publish(point_cloud);
  });

  rclcpp::spin(node);
  rclcpp::shutdown();

  return 0;
}
