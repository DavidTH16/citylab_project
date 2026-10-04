#include "geometry_msgs/msg/detail/twist__struct.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "nav_msgs/msg/detail/odometry__struct.hpp"
#include "nav_msgs/msg/odometry.hpp"
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
#include <functional>
#include <limits>
#include <map>
#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2/LinearMath/Quaternion.h>
#include <utility>

using namespace std::chrono_literals; // to recognize literals in the timers.

class Patrol : public rclcpp::Node {

private:
  // subscriptors, publisher and timer required
  rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr
      subscription_laser;

  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_cmd;
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::TimerBase::SharedPtr watchdog_timer_;
  rclcpp::Time laser_scan_time_;

  // minimum distance allowed
  const double safety_distance = 0.35;

  // object to save velocity
  struct VelocityPatrol {
    double linear_x;
    double angular_z;
  };

  VelocityPatrol robot_velocity;

public:
  Patrol() : Node("patrol_node") {

    // adding standard sensor QoS
    auto qos = rclcpp::SensorDataQoS();

    rclcpp::SubscriptionOptions options;

    options.event_callbacks.deadline_callback =
        [this](rclcpp::QOSDeadlineRequestedInfo &info) {
          RCLCPP_ERROR(this->get_logger(),
                       "CRITICAL: Laser Sensor Deadline Missed! No data "
                       "received within 500ms. Total misses: %d",
                       info.total_count);
        };

    // subs and pubsh set up
    subscription_laser = this->create_subscription<sensor_msgs::msg::LaserScan>(
        "/fastbot_1/scan", qos,
        std::bind(&Patrol::laser_callback, this, std::placeholders::_1));

    publisher_cmd = this->create_publisher<geometry_msgs::msg::Twist>(
        "/fastbot_1/cmd_vel", 10);

    // timer to publish every 10Hz velocity
    timer_ = this->create_wall_timer(100ms, // 10Hz
                                     std::bind(&Patrol::timer_callback, this));

    // timer to chech if laser data comes every 200ms
    watchdog_timer_ = this->create_wall_timer(
        200ms, std::bind(&Patrol::watchdog_callback, this));

    RCLCPP_INFO(this->get_logger(), "Patrol node active!...");
  }

private: // define callbacks for each subs, publs.
  void laser_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg) {

    // trigger timer to track if callback is receiving data
    laser_scan_time_ = this->now();

    // zones to cover frontal 180 of the robot
    // covering front of robot
    int front_left_start = 0;
    int front_left_end = 11;
    int front_right_start = 189;
    int front_right_end = 199;

    // covering sides of the robot
    int right_start = 149;
    int right_end = 169; // 169  // fail 188
    int left_start = 20; // 20 ->init //fail 12
    int left_end = 49;

    // map to define right and left zone using index
    std::map<std::string, std::pair<int, int>> zones = {
        {"front right", {front_right_start, front_right_end}},
        {"front left", {front_left_start, front_left_end}},
        {"right", {right_start, right_end}},
        {"left", {left_start, left_end}}};

    // map to save final value by zone
    std::map<std::string, float> min_distance;

    // access values from laser and store them by index
    for (const auto &[zone_name, idx_range] : zones) {
      int start_idx = idx_range.first;
      int end_idx = idx_range.second;

      // init the min value as positive infinite
      float min_value = std::numeric_limits<float>::infinity();

      if (start_idx < static_cast<int>(msg->ranges.size()) &&
          end_idx < static_cast<int>(msg->ranges.size())) {
        for (int i = start_idx; i <= end_idx; ++i) {
          float ray = msg->ranges[i];
          if (std::isfinite(ray) && ray >= msg->range_min &&
              ray <= msg->range_max) {
            if (ray < min_value) {
              min_value = ray;
            }
          }
        }
      }
      min_distance[zone_name] = min_value;
    }

    // display laser info for debugging purpose
    for (const auto &[zone_value, dist] : min_distance) {
      RCLCPP_INFO(this->get_logger(), "sensor laser zone: %s, dist: %.2fm",
                  zone_value.c_str(), dist);
    }

    // map to check safety zone
    std::map<std::string, bool> check_zone;
    for (const auto &zone : min_distance) {
      check_zone[zone.first] = zone.second < safety_distance;
    }

    // check if obstacle ahead, and decide to what side turns
    if (!check_zone["front right"] && !check_zone["front left"]) {
      robot_velocity.linear_x = 0.1;
      robot_velocity.angular_z = 0.0;
    } else {
      robot_velocity.linear_x = 0.05;
      RCLCPP_WARN(this->get_logger(), "Obstacle detect...");
      // check which side is optimum
      if (min_distance["left"] > min_distance["right"]) {
        robot_velocity.angular_z = 0.5;
      } else {
        robot_velocity.angular_z = -0.5;
      }
    }
  }

  // timers implementation
  void timer_callback() {
    // create cmd object to publish the velocity
    auto cmd = geometry_msgs::msg::Twist();
    cmd.linear.x = robot_velocity.linear_x;
    cmd.angular.z = robot_velocity.angular_z;
    publisher_cmd->publish(cmd);
  }

  void watchdog_callback() {
    auto elapsed = (this->now() - laser_scan_time_).seconds();
    if (elapsed > 3.0) {
      RCLCPP_ERROR(this->get_logger(),
                   "Laser data stalled, No data received... %.2f", elapsed);
    }
  }
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto patrol_node = std::make_shared<Patrol>();
  rclcpp::spin(patrol_node);
  rclcpp::shutdown();
  return 0;
}