#include <memory>
#include <msgpack.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <sensor_msgs/point_cloud2_iterator.hpp>
#include <thread>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/server.hpp>

using namespace std::chrono_literals;
typedef websocketpp::client<websocketpp::config::asio_client> client;
class PointCloudPublisher : public rclcpp::Node {
public:
  PointCloudPublisher() : Node("point_cloud_publisher") {
    publisher_ = this->create_publisher<sensor_msgs::msg::PointCloud2>(
        "point_cloud", 10);

    timer_ = this->create_wall_timer(100ms, [this]() {
      // Generate some point cloud data
      sensor_msgs::msg::PointCloud2 point_cloud;
      point_cloud.header.frame_id = "world";
      point_cloud.height = 1;
      point_cloud.width = 1000;
      point_cloud.is_dense = true;

      sensor_msgs::PointCloud2Modifier modifier(point_cloud);
      modifier.setPointCloud2FieldsByString(1, "xyz");
      modifier.resize(1000 * point_cloud.point_step);

      for (size_t i = 0; i < 1000; ++i) {
        float x = static_cast<float>(rand()) / RAND_MAX;
        float y = static_cast<float>(rand()) / RAND_MAX;
        float z = static_cast<float>(rand()) / RAND_MAX;

        memcpy(&point_cloud.data[i * point_cloud.point_step], &x,
               sizeof(float));
        memcpy(&point_cloud.data[i * point_cloud.point_step + 4], &y,
               sizeof(float));
        memcpy(&point_cloud.data[i * point_cloud.point_step + 8], &z,
               sizeof(float));
      }

      publisher_->publish(point_cloud);

      // RCLCPP_INFO(this->get_logger(), "Publishing point cloud");
    });
  }

private:
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<PointCloudPublisher>();

  client c;

  // Set up WebSocket server
  using websocket_server = websocketpp::server<websocketpp::config::asio>;
  websocket_server server;
  try {
    // Create a separate logger for the WebSocket server
    auto server_logger = rclcpp::get_logger("websocket_server");
    server.init_asio();
    server.set_reuse_addr(true);
    server.listen(9001);
    server.start_accept();
    RCLCPP_INFO(server_logger, "WebSocket server listening on port 9001");
    server.set_message_handler(
        [&node, &server, &server_logger](
            websocketpp::connection_hdl hdl,
            websocketpp::server<websocketpp::config::asio>::message_ptr msg) {
          // Convert the point cloud data to binary and send it over the
          // WebSocket connection
          // RCLCPP_INFO(server_logger, "Received WebSocket message");
          std::cout << "Received message: " << msg->get_payload() << std::endl;
          sensor_msgs::msg::PointCloud2 point_cloud;
          point_cloud.header.frame_id = "world";
          point_cloud.height = 1;
          point_cloud.width = 1000;
          point_cloud.is_dense = true;

          sensor_msgs::PointCloud2Modifier modifier(point_cloud);
          modifier.setPointCloud2FieldsByString(1, "xyz");
          modifier.resize(1000 * point_cloud.point_step);

          for (size_t i = 0; i < 1000; ++i) {
            float x = static_cast<float>(rand()) / RAND_MAX;
            float y = static_cast<float>(rand()) / RAND_MAX;
            float z = static_cast<float>(rand()) / RAND_MAX;

            memcpy(&point_cloud.data[i * point_cloud.point_step], &x,
                   sizeof(float));
            memcpy(&point_cloud.data[i * point_cloud.point_step + 4], &y,
                   sizeof(float));
            memcpy(&point_cloud.data[i * point_cloud.point_step + 8], &z,
                   sizeof(float));
          }

          // Serialize the point cloud data using MessagePack
          msgpack::sbuffer sbuf;
          msgpack::packer<msgpack::sbuffer> packer(&sbuf);

          packer.pack_array(6);
          packer.pack(point_cloud.header.frame_id);
          packer.pack(point_cloud.height);
          packer.pack(point_cloud.width);
          packer.pack(point_cloud.is_bigendian);
          packer.pack(point_cloud.point_step);
          packer.pack_bin(point_cloud.data.size());
          packer.pack_bin_body(
              reinterpret_cast<const char *>(point_cloud.data.data()),
              point_cloud.data.size());
          RCLCPP_INFO(server_logger, "MESSAGE RECEIVED: %d",
                      point_cloud.data.size());

          // Send the binary data over the WebSocket connection
          // server.send(hdl, reinterpret_cast<const char*>(sbuf.data()),
          // sbuf.size(), websocketpp::frame::opcode::binary);

          // RCLCPP_INFO(server_logger, "Sending point cloud over WebSocket");
        });

    // Run the WebSocket server on a separate thread
    std::thread websocket_thread([&server, server_logger]() {
      server.set_access_channels(websocketpp::log::alevel::all);
      server.set_error_channels(websocketpp::log::elevel::all);
      server.run();
      RCLCPP_INFO(server_logger, "WebSocket server stopped");
    });

    // Start the ROS 2 node
    rclcpp::spin(node);

    // Stop the WebSocket server and wait for the thread to finish
    server.stop();
    websocket_thread.join();
  } catch (const std::exception &e) {
    RCLCPP_ERROR(node->get_logger(), "Failed to start WebSocket server: %s",
                 e.what());
    return 1;
  }

  rclcpp::shutdown();
  return 0;
}