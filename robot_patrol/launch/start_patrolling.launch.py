from launch import LaunchDescription
<<<<<<< HEAD
=======
#from ament_index_python.packages import get_package_share_directory
>>>>>>> main
from launch_ros.actions import Node

def generate_launch_description():

<<<<<<< HEAD
    rviz_config_path = "/home/user/ros2_ws/src/citylab_project/rviz/robot_patrol_view.rviz"
=======
    rviz_config_path = "/home/user/ros2_ws/src/citylab_project/robot_patrol/rviz/robot_patrol_view.rviz"
    
>>>>>>> main
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