#include "rclcpp/logger.hpp"
#include "rclcpp/logging.hpp"
#include "rclcpp/node.hpp"
#include "rclcpp/subscription.hpp"
#include "sensor_msgs/msg/detail/laser_scan__struct.hpp"
#include <algorithm>
#include <chrono>
#include <custom_interface/srv/get_direction.hpp>
#include <map>
#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/service.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>

class DirectionService : public rclcpp::Node {
private:
  // pointers and variables
  // minimum distance allowed
  const double safety_distance = 0.35;
  rclcpp::Service<custom_interface::srv::GetDirection>::SharedPtr server_ptr;
  // rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr
  // subscriber_laser;
  std::string name_server = "/direction_service";

public:
  DirectionService() : Node("service_node") {

    // create the server
    server_ptr = this->create_service<custom_interface::srv::GetDirection>(
        name_server, std::bind(&DirectionService::server_callback, this,
                               std::placeholders::_1, std::placeholders::_2));

    RCLCPP_INFO(this->get_logger(), "Service Ready ...");
  }

private:
  // callbacks
  // server callback implementation, receive request and respond
  void server_callback(
      const std::shared_ptr<custom_interface::srv::GetDirection::Request>
          request,
      std::shared_ptr<custom_interface::srv::GetDirection::Response> response) {

    auto msg = request;

    // add safeguard to ensure we get data from laser
    if (msg->laser_data.ranges.empty()) {
      RCLCPP_WARN(this->get_logger(), "Empty laser data received..");
      return;
    }

    RCLCPP_INFO(this->get_logger(), "Request received");

    // zones to cover frontal 180 of the robot
    // covering front of robot
    int front_right_start = 189;
    int front_left_end = 11;

    // covering sides of the robot
    int right_start = 149;
    int right_end = 188; //
    int left_start = 12; //
    int left_end = 49;

    // map to define right and left zone using index
    std::map<std::string, std::pair<int, int>> zones = {
        {"front", {front_right_start, front_left_end}},
        {"right", {right_start, right_end}},
        {"left", {left_start, left_end}}};

    // map to save final value by zone, and all the values by laser
    std::map<std::string, float> min_distance;
    std::map<std::string, float> total_distance_by_zone;

    // access values from laser and store them by index
    for (const auto &[zone_name, idx_range] : zones) {
      int start_idx = idx_range.first;
      int end_idx = idx_range.second;

      float min_value = std::numeric_limits<float>::infinity();
      float total_ray_zone = 0.0f;

      int array_size = static_cast<int>(msg->laser_data.ranges.size());

      // Lambda to process a single ray
      auto process_ray = [&](int i) {
        float ray = msg->laser_data.ranges[i];
        if (std::isfinite(ray) && ray >= msg->laser_data.range_min &&
            ray <= msg->laser_data.range_max) {
          if (ray < min_value) {
            min_value = ray;
          }
          total_ray_zone += ray;
        }
      };

      // handle index for front zone since the index change here
      if (start_idx > end_idx) {
        for (int i = start_idx; i < array_size; ++i) {
          process_ray(i);
        }
        for (int i = 0; i <= end_idx; ++i) {
          process_ray(i);
        }
      } else {
        // Normal zones without wrap-around
        if (start_idx < array_size && end_idx < array_size) {
          for (int i = start_idx; i <= end_idx; ++i) {
            process_ray(i);
          }
        }
      }

      // get min distance by zone and total distance by zone
      min_distance[zone_name] = min_value;
      total_distance_by_zone[zone_name] = total_ray_zone;
    }

    // display laser info for debugging purpose-------->
    // for (const auto &[zone_value, dist] : total_distance_by_zone) {
    //  RCLCPP_INFO(this->get_logger(), "sensor laser zone: %s, dist: %.2fm",
    //              zone_value.c_str(), dist);
    //}

    // check if obstacle ahead, and decide to what side turns
    if (min_distance["front"] > safety_distance) {
      RCLCPP_INFO(this->get_logger(), "Request Completed");
      response->direction = "Forward";
    } else {

      // RCLCPP_WARN(this->get_logger(), "Obstacle detect...");
      //  check which side is optimum
      if (total_distance_by_zone["left"] > total_distance_by_zone["right"]) {
        RCLCPP_INFO(this->get_logger(), "Request Completed");
        response->direction = "Left";
      } else {
        RCLCPP_INFO(this->get_logger(), "Request Completed");
        response->direction = "Right";
      }
    }
  }
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto server_node = std::make_shared<DirectionService>();
  rclcpp::spin(server_node);
  rclcpp::shutdown();
  return 0;
}