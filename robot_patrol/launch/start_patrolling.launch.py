from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():

    rviz_config_path = "/home/user/ros2_ws/src/citylab_project/rviz/robot_patrol_view.rviz"
    return LaunchDescription([
        
        Node(
            package = "rviz2",
            executable= "rviz2",
            output = "screen",
            arguments=['-d', rviz_config_path] if rviz_config_path else []
        ),
        Node(
            package = "robot_patrol",
            executable = "patrol_executable",
            output = "screen",
            emulate_tty=True
        )
    ])