#include "geometry_msgs/msg/detail/twist__struct.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/callback_group.hpp"
#include "rclcpp/create_timer.hpp"
#include "rclcpp/executors.hpp"
#include "rclcpp/executors/multi_threaded_executor.hpp"
#include "rclcpp/logging.hpp"
#include "rclcpp/node.hpp"
#include "rclcpp/qos.hpp"
#include "rclcpp/subscription.hpp"
#include "rclcpp/subscription_options.hpp"
#include "rclcpp/timer.hpp"
#include "sensor_msgs/msg/detail/laser_scan__struct.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "std_msgs/msg/string.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <custom_interface/srv/get_direction.hpp>
#include <functional>
#include <limits>
#include <map>
#include <memory>
#include <rclcpp/client.hpp>
#include <rclcpp/rclcpp.hpp>
#include <string>
#include <utility>

using namespace std::chrono_literals; // to recognize literals in the timers.

class Patrol : public rclcpp::Node {

private:
  // pointers and variables
  std::string client_name = "/direction_service";
  std::string direction_string;
  custom_interface::srv::GetDirection::Request::SharedPtr msg_laser;
  rclcpp::Client<custom_interface::srv::GetDirection>::SharedPtr client_service;
  rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr subscriber_laser;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_cmd;
  rclcpp::TimerBase::SharedPtr timer_send_laser;
  rclcpp::TimerBase::SharedPtr timer_velocity;

  // create the separate groups for mulithread
  rclcpp::CallbackGroup::SharedPtr timer_laser_cb_group_;
  rclcpp::CallbackGroup::SharedPtr client_cb_group_;
  rclcpp::CallbackGroup::SharedPtr timer_velocity_cb_group;

  // object to save velocity
  struct VelocityPatrol {
    double linear_x;
    double angular_z;
  };

  VelocityPatrol robot_velocity;

public:
  Patrol() : Node("patrol_client_node") {
    // init the request object in memory
    msg_laser =
        std::make_shared<custom_interface::srv::GetDirection::Request>();

    // init the callback groups as mutually exclusive, laser, client, and
    // velocity
    timer_laser_cb_group_ = this->create_callback_group(
        rclcpp::CallbackGroupType::MutuallyExclusive);
    client_cb_group_ = this->create_callback_group(
        rclcpp::CallbackGroupType::MutuallyExclusive);
    timer_velocity_cb_group = this->create_callback_group(
        rclcpp::CallbackGroupType::MutuallyExclusive);

    // init the client, the laser and the the timer pointers
    client_service = this->create_client<custom_interface::srv::GetDirection>(
        client_name, rmw_qos_profile_services_default, client_cb_group_);

    subscriber_laser = this->create_subscription<sensor_msgs::msg::LaserScan>(
        "/scan", 10,
        std::bind(&Patrol::laser_callback, this, std::placeholders::_1));
    publisher_cmd =
        this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);

    timer_send_laser = this->create_wall_timer(
        100ms, std::bind(&Patrol::timer_laser_callback, this),
        timer_laser_cb_group_);

    timer_velocity = this->create_wall_timer(
        100ms, std::bind(&Patrol::timer_vel_callback, this),
        timer_velocity_cb_group);

    // Wait for the service to be available (checks every second)
    while (!client_service->wait_for_service(3s)) {
      if (!rclcpp::ok()) {
        RCLCPP_ERROR(this->get_logger(),
                     "Interrupted while waiting for the service. Exiting.");
        return;
      }
      RCLCPP_INFO(this->get_logger(),
                  "Service not available, waiting again...");
    }
  }

private:
  // callbacks implementation
  // get the data frequently from the robot
  //-------------------------------------------------------------------------------
  void laser_callback(const std::shared_ptr<sensor_msgs::msg::LaserScan> msg) {
    msg_laser->laser_data = *msg;
  }

  // callback to publish velocity of the robot
  //--------------------------------------------------------------------------------
  void timer_vel_callback() {
    // create cmd object to publish the velocity
    auto cmd = geometry_msgs::msg::Twist();
    if (direction_string == "Forward") {
      cmd.linear.x = 0.1;
      cmd.angular.z = 0.0;
      publisher_cmd->publish(cmd);
    } else if (direction_string == "Left") {
      cmd.linear.x = 0.1;
      cmd.angular.z = 0.5;
      publisher_cmd->publish(cmd);
    } else if (direction_string == "Right") {
      cmd.linear.x = 0.1;
      cmd.angular.z = -0.5;
      publisher_cmd->publish(cmd);
    } else {
      cmd.linear.x = 0.0;
      cmd.angular.z = 0.0;
      publisher_cmd->publish(cmd);
    }
  }
  // callback to sent the laser to the server
  //--------------------------------------------------------------------------------
  void timer_laser_callback() {

    // to guarantee the correct communication ensure we have data before calling
    // the service
    if (msg_laser->laser_data.ranges.empty()) {
      RCLCPP_WARN(this->get_logger(), "Waiting for laser_scan data ...");
      return;
    }
    // send the request in asynchronous mode
    auto result_future = client_service->async_send_request(msg_laser);
    RCLCPP_INFO(this->get_logger(), "Reques Sent");

    // wait for the response
    std::future_status status = result_future.wait_for(2s);
    if (status == std::future_status::ready) {
      auto response = result_future.get();
      if (!response) {
        RCLCPP_WARN(this->get_logger(), "Something when wrong");
      }

      direction_string = response->direction;
      RCLCPP_INFO(this->get_logger(), "Response received: %s",
                  response->direction.c_str());

    } else {
      RCLCPP_INFO(this->get_logger(), "Error to call the service");
    }
  }
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto client_node = std::make_shared<Patrol>();
  rclcpp::executors::MultiThreadedExecutor executors;
  executors.add_node(client_node);
  executors.spin();
  rclcpp::shutdown();
  return 0;
}