#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/opencv.hpp>
#include <sensor_msgs/msg/image.hpp>

int main(int argc, char **argv) {
  // Initialize ROS2 node
  rclcpp::init(argc, argv);
  auto node = std::make_shared<rclcpp::Node>("cv_image_publisher");

  // Load the PNG image using OpenCV
  cv::Mat image =
      cv::imread("/home/tong/ros2_ws/src/pointcloud_server/src/image.png",
                 cv::IMREAD_UNCHANGED);

  // Convert the cv image to a ROS2 message
  sensor_msgs::msg::Image::Ptr image_msg =
      cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", image).toImageMsg();

  // Initialize ROS2 image publisher
  image_transport::ImageTransport image_transport(node);
  auto publisher = image_transport.advertise("image_topic", 1);

  // Publish the ROS2 message on the image topic
  rclcpp::Rate loop_rate(30);
  while (rclcpp::ok()) {
    publisher.publish(image_msg);
    loop_rate.sleep();
  }

  return 0;
}
