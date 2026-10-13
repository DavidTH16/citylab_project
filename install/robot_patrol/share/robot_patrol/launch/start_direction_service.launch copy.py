from launch import LaunchDescription
#from ament_index_python.packages import get_package_share_directory
from launch_ros.actions import Node

def generate_launch_description():

    rviz_config_path = "/home/user/ros2_ws/src/citylab_project/robot_patrol/rviz/robot_patrol_view.rviz"
    
    return LaunchDescription([
        Node(
            package = "robot_patrol",
            executable = "direction_service_node",
            output = "screen",
            emulate_tty=True
        )
    ])