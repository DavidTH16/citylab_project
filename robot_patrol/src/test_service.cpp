#include "rclcpp/callback_group.hpp"
#include "rclcpp/executors.hpp"
#include "rclcpp/executors/multi_threaded_executor.hpp"
#include "rclcpp/node.hpp"
#include "rclcpp/subscription.hpp"
#include "rclcpp/timer.hpp"
#include "sensor_msgs/msg/detail/laser_scan__struct.hpp"
#include <chrono>
#include <custom_interface/srv/get_direction.hpp>
#include <functional>
#include <future>
#include <memory>
#include <rclcpp/client.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <string>

using namespace std::chrono_literals; // to recognize literals in the timers

class TestClient : public rclcpp::Node {
private:
  // pointers and variables
  std::string client_name = "/direction_service";
  custom_interface::srv::GetDirection::Request::SharedPtr msg_laser;
  rclcpp::Client<custom_interface::srv::GetDirection>::SharedPtr client_service;
  rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr subscriber_laser;
  rclcpp::TimerBase::SharedPtr timer_pointer;

  // create the separate groups for mulithread
  rclcpp::CallbackGroup::SharedPtr timer_cb_group_;
  rclcpp::CallbackGroup::SharedPtr client_cb_group_;

public:
  TestClient() : Node("test_client_node") {
    // init the request object in memory
    msg_laser =
        std::make_shared<custom_interface::srv::GetDirection::Request>();

    // init the callback groups as mutually exclusive
    timer_cb_group_ = this->create_callback_group(
        rclcpp::CallbackGroupType::MutuallyExclusive);
    client_cb_group_ = this->create_callback_group(
        rclcpp::CallbackGroupType::MutuallyExclusive);

    // init the client, the laser and the the timer pointers
    client_service = this->create_client<custom_interface::srv::GetDirection>(
        client_name, rmw_qos_profile_services_default, client_cb_group_);

    subscriber_laser = this->create_subscription<sensor_msgs::msg::LaserScan>(
        "/fastbot_1/scan", 10,
        std::bind(&TestClient::laser_callback, this, std::placeholders::_1));

    timer_pointer = this->create_wall_timer(
        100ms, std::bind(&TestClient::timer_callback, this), timer_cb_group_);

    // Wait for the service to be available (checks every second)
    while (!client_service->wait_for_service(1s)) {
      if (!rclcpp::ok()) {
        RCLCPP_ERROR(this->get_logger(),
                     "Interrupted while waiting for the service. Exiting.");
        return;
      }
      RCLCPP_INFO(this->get_logger(),
                  "Service not available, waiting again...");
    }

    RCLCPP_INFO(this->get_logger(), "Client Ready ...");
  }

private:
  // callbacks implementation
  void laser_callback(const std::shared_ptr<sensor_msgs::msg::LaserScan> msg) {
    msg_laser->laser_data = *msg;
  }

  void timer_callback() {
    // send the request in asynchronous mode
    RCLCPP_INFO(this->get_logger(), "Reques Sent");
    auto result_future = client_service->async_send_request(msg_laser);

    // wait for the response
    std::future_status status = result_future.wait_for(2s);
    if (status == std::future_status::ready) {
      auto response = result_future.get();
      if (!response) {
        RCLCPP_WARN(this->get_logger(), "Something when wrong");
      }

      RCLCPP_INFO(this->get_logger(), "Response Received: %s",
                  response->direction.c_str());

    } else {
      RCLCPP_INFO(this->get_logger(), "Error to call the service");
    }
  }
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto client_node = std::make_shared<TestClient>();
  rclcpp::executors::MultiThreadedExecutor executors;
  executors.add_node(client_node);
  executors.spin();
  rclcpp::shutdown();
  return 0;
}