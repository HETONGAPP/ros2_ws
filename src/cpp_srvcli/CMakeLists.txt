cmake_minimum_required(VERSION 3.5)
project(cpp_srvcli)

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

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rcl_interfaces REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(tutorial_interfaces REQUIRED)
add_executable(server src/add_two_ints_server.cpp)
add_executable(client src/add_two_ints_client.cpp)
add_executable(web src/web_service.cpp)
add_executable(web_stop src/web_service_stop.cpp)
ament_target_dependencies(server rclcpp tutorial_interfaces example_interfaces)
ament_target_dependencies(client rclcpp tutorial_interfaces example_interfaces)
ament_target_dependencies(web rclcpp tutorial_interfaces rcl_interfaces)
ament_target_dependencies(web_stop rclcpp tutorial_interfaces rcl_interfaces)

include_directories(
  ${rcl_interfaces_INCLUDE_DIRS} 
)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)
install(TARGETS
  server
  client
  web
  web_stop
  DESTINATION lib/${PROJECT_NAME}
)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
