import launch
import launch_ros.actions

def generate_launch_description():
    service1 = launch_ros.actions.Node(
        package='pointcloud_server',
        executable='web_start',
        name='launch'
    )

    service2 = launch_ros.actions.Node(
        package='cpp_srvcli',
        executable='web_stop',
        name='launch_stop'
    )

    return launch.LaunchDescription([
        service1,
        service2
    ])