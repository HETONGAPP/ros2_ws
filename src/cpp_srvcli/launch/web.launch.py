import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource

def generate_launch_description():
    xml_file_path = '/opt/ros/foxy/share/rosbridge_server/launch/rosbridge_websocket_launch.xml'
    web_service = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            '/home/tong/ros2_ws/src/cpp_srvcli/launch/launch_web_service.launch.py'
        )
    )

    return LaunchDescription([
        web_service,
        IncludeLaunchDescription(
            launch_description_source = xml_file_path,
        )
    ])