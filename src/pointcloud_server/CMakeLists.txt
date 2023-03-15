cmake_minimum_required(VERSION 3.5)
project(pointcloud_server)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()
link_directories(/usr/lib/x86_64-linux-gnu)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rcl_interfaces REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(msgpack REQUIRED)
find_package(realsense2 REQUIRED)
find_package(PCL REQUIRED COMPONENTS common io filters)
find_package(OpenCV REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(X11 REQUIRED)
find_package(image_transport REQUIRED)

# add executable
add_executable(web_start src/web_service_start.cpp)
add_executable(web_stop src/web_service_stop.cpp)
#add_executable(web_pcl src/point_server.cpp)
add_executable(open_cam src/open_realsense_cam.cpp)
add_executable(launch_realsense src/launch_realsense.cpp include/${PROJECT_NAME}/rgb_image.h include/${PROJECT_NAME}/depth_image.h)
add_executable(image_publisher src/image_publisher.cpp)

# include directories
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/
  ${rcl_interfaces_INCLUDE_DIRS} 
  ${PCL_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${cv_bridge_INCLUDE_DIRS}
  ${X11_INCLUDE_DIR}
)

# ament target dependencies
ament_target_dependencies(web_start rclcpp rcl_interfaces)
ament_target_dependencies(web_stop rclcpp rcl_interfaces)
#ament_target_dependencies(web_pcl rclcpp rcl_interfaces std_msgs sensor_msgs)
ament_target_dependencies(open_cam rclcpp rcl_interfaces std_msgs sensor_msgs)
ament_target_dependencies(launch_realsense rclcpp rcl_interfaces std_msgs sensor_msgs)
ament_target_dependencies(image_publisher rclcpp rcl_interfaces std_msgs sensor_msgs image_transport)

# target link libraries
#target_link_libraries(web_pcl OpenSSL::SSL OpenSSL::Crypto msgpackc realsense2::realsense2)
target_link_libraries(open_cam OpenSSL::SSL OpenSSL::Crypto msgpackc realsense2::realsense2 ${PCL_LIBRARIES} ${OpenCV_LIBRARIES} ${cv_bridge_LIBRARIES})
target_link_libraries(launch_realsense OpenSSL::SSL OpenSSL::Crypto msgpackc realsense2::realsense2 ${PCL_LIBRARIES} ${OpenCV_LIBRARIES} ${cv_bridge_LIBRARIES})
target_link_libraries(image_publisher OpenSSL::SSL OpenSSL::Crypto msgpackc realsense2::realsense2 ${PCL_LIBRARIES} ${OpenCV_LIBRARIES} ${cv_bridge_LIBRARIES})


#link directories 
link_directories(
  ${PCL_LIBRARY_DIRS}
  ${CMAKE_CURRENT_BINARY_DIR}/pointcloud_server
)

# install launch to share
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

add_definitions(${PCL_DEFINITIONS})

# install targets to lib
install(TARGETS
  web_start
  web_stop
  #web_pcl
  open_cam
  launch_realsense
  image_publisher
  DESTINATION lib/${PROJECT_NAME}
)

# for the srv and msg
rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/LaunchCommands.srv"
)

rosidl_target_interfaces(web_start
  ${PROJECT_NAME} "rosidl_typesupport_cpp"
)

rosidl_target_interfaces(web_stop
  ${PROJECT_NAME} "rosidl_typesupport_cpp"
)

ament_export_dependencies(rosidl_default_runtime)

#file(COPY ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}/ DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME})


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
