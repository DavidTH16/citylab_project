#include "geometry_msgs/msg/detail/pose2_d__struct.hpp"
#include "geometry_msgs/msg/detail/twist__struct.hpp"
#include "nav_msgs/msg/detail/odometry__struct.hpp"
#include "rclcpp/logging.hpp"
#include "rclcpp/node.hpp"
#include "rclcpp/publisher.hpp"
#include "rclcpp/rate.hpp"
#include "rclcpp/subscription.hpp"
#include "rclcpp/timer.hpp"
#include "rclcpp_action/create_server.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "rclcpp_action/server.hpp"
#include "rclcpp_action/server_goal_handle.hpp"
#include "robot_patrol/action/go_to_pose.hpp"
#include <chrono>
#include <cmath>
#include <functional>
#include <geometry_msgs/msg/pose2_d.hpp>
#include <memory>
#include <nav_msgs/msg/odometry.hpp>
#include <rclcpp/rclcpp.hpp>
#include <string>
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2/LinearMath/Quaternion.h>
#include <thread>

// aliases for timer
using namespace std::chrono_literals;

class GoToPose : public rclcpp::Node {
  // using aliases
  using ToPose = robot_patrol::action::GoToPose;
  using GoalHandleToPose = rclcpp_action::ServerGoalHandle<ToPose>;

private:
  // declare initial pointers(subscribers, clients), variables
  std::string name_action = "/go_to_pose";
  rclcpp_action::Server<ToPose>::SharedPtr action_server_;
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr subsciber_odom_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_cmd_;
  rclcpp::TimerBase::SharedPtr timer_velocity_;

  // variables for logic
  geometry_msgs::msg::Pose2D desired_pos_;
  geometry_msgs::msg::Pose2D current_pos_;
  // create velocity object to save cmd values and publish;
  geometry_msgs::msg::Twist velocity;
  std::atomic<bool> goal_execution = false;
  bool position_reached = false;
  double current_yaw_ = 0.0;

public:
  // init. the constructor and allocation of pointer in memory
  GoToPose() : Node("position_server_node") {
    // aliases
    using namespace std::placeholders;

    this->action_server_ = rclcpp_action::create_server<ToPose>(
        this, name_action, std::bind(&GoToPose::handle_goal, this, _1, _2),
        std::bind(&GoToPose::handle_cancel, this, _1),
        std::bind(&GoToPose::handle_accepted, this, _1));

    subsciber_odom_ = this->create_subscription<nav_msgs::msg::Odometry>(
        "/odom", 10, std::bind(&GoToPose::odom_callback, this, _1));

    publisher_cmd_ =
        this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);

    timer_velocity_ = this->create_wall_timer(
        10ms, std::bind(&GoToPose::timer_callback, this));

    RCLCPP_INFO(this->get_logger(), "Action Server Ready ...");
  }

private:
  // callback implementation
  //--------------------------------------------------------------------------------------
  rclcpp_action::GoalResponse
  handle_goal(const rclcpp_action::GoalUUID &uuid,
              std::shared_ptr<const ToPose::Goal> goal) {
    RCLCPP_INFO(
        this->get_logger(),
        "Received goal request, coordinates -> X: %.2f, Y: %.2f, Theta:%.2f",
        goal->goal_pos.x, goal->goal_pos.y, goal->goal_pos.theta);

    (void)uuid;
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
  }

  // callback to cancel the goal if something was wrong at time of the goal
  // execution
  //----------------------------------------------------------------------------------------
  rclcpp_action::CancelResponse
  handle_cancel(const std::shared_ptr<GoalHandleToPose> goal_handle) {
    RCLCPP_INFO(this->get_logger(), "Received request to cancel ...");
    (void)goal_handle;
    return rclcpp_action::CancelResponse::ACCEPT;
  }

  // callback to execute proceed to execute the goal
  void handle_accepted(const std::shared_ptr<GoalHandleToPose> goal_handle) {
    using namespace std::placeholders;
    std::thread{std::bind(&GoToPose::execute, this, _1), goal_handle}.detach();
  }

  // callback to execute the current goal, send feedback
  //---------------------------------------------------------------------------------------
  void execute(const std::shared_ptr<GoalHandleToPose> goal_handle) {
    RCLCPP_INFO(this->get_logger(), "Goal Received");
    goal_execution = true;
    position_reached = false;

    // get goal, declare feedback and result
    const auto goal = goal_handle->get_goal();
    desired_pos_ = goal->goal_pos;
    // convert theta to rads
    desired_pos_.theta = desired_pos_.theta * (M_PI / 180.0);

    // rate for this loop at 10Hz
    rclcpp::Rate loop_rate(10);

    auto feedback = std::make_shared<ToPose::Feedback>();
    auto result = std::make_shared<ToPose::Result>();

    // loping the executor thread
    while (goal_execution && rclcpp::ok()) {

      if (goal_handle->is_canceling()) {
        result->status = false;
        goal_handle->canceled(result);
        RCLCPP_INFO(this->get_logger(), "Goal cancealed");
        stop_patrol();
        return;
      }

      feedback->current_pos = current_pos_;
      goal_handle->publish_feedback(feedback);

      loop_rate.sleep();
    }

    // Check if goal is done
    if (rclcpp::ok()) {
      result->status = true;
      goal_handle->succeed(result);
      RCLCPP_INFO(this->get_logger(), "Goal Completed");
    }
  }

  // callback to handle data from odometry
  //---------------------------------------------------------------------------------------
  void odom_callback(const std::shared_ptr<nav_msgs::msg::Odometry> msg) {

    // check if the server has a goal, if not do all the logic.
    if (!goal_execution) {
      return;
    }

    if (msg->header.frame_id.empty()) {
      RCLCPP_WARN(this->get_logger(), "Data from Odometry is empty...");
      return;
    }

    current_pos_.x = msg->pose.pose.position.x;
    current_pos_.y = msg->pose.pose.position.y;

    // RCLCPP_INFO(this->get_logger(), "X: %.2f, Y:%.2F, THETA:%.2f",
    //             current_pos_.x, current_pos_.y, current_yaw_);

    // extract yaw from quaternion
    tf2::Quaternion q(
        msg->pose.pose.orientation.x, msg->pose.pose.orientation.y,
        msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
    tf2::Matrix3x3 m(q);
    double roll, pitch;
    m.getRPY(roll, pitch, current_yaw_);

    current_pos_.theta = current_yaw_;

    if (!position_reached) { // goal_execution
      double distance_to_goal = calculate_distance(desired_pos_, current_pos_);
      // RCLCPP_INFO(this->get_logger(), "Distance to the target: %.3f",
      //             distance_to_goal);

      // check if position is less than position tolerance
      if (distance_to_goal < 0.075) {
        stop_patrol();
        position_reached = true; // goal_execution
        // RCLCPP_INFO(this->get_logger(), "Robot has reached position ...");
      }
    } else { // rotate to final heading
      double final_yaw_error = desired_pos_.theta - current_yaw_;

      // normalize the pi value
      final_yaw_error =
          std::atan2(std::sin(final_yaw_error), std::cos(final_yaw_error));

      // check condition
      if (std::abs(final_yaw_error) > 0.174) // 10 degrees tolerance
      {
        velocity.linear.x = 0.0;
        velocity.angular.z = (final_yaw_error > 0) ? 0.5 : -0.5;
      } else {
        RCLCPP_INFO(this->get_logger(), "Final orientation reached.");
        stop_patrol();
        goal_execution = false;
        return;
      }
    }
  }

  // method to compute the distance from the current post. to the target post.
  //--------------------------------------------------------------------------------------------
  double
  calculate_distance(const geometry_msgs::msg::Pose2D &target_position,
                     const geometry_msgs::msg::Pose2D &current_position) {

    double dx = target_position.x - current_position.x;
    double dy = target_position.y - current_position.y;

    double distance_to_target = std::hypot(dx, dy);

    double desired_yaw = std::atan2(dy, dx);
    double yaw_error = desired_yaw - current_yaw_;

    // Normalize yaw error to [-pi, pi]
    yaw_error = std::atan2(std::sin(yaw_error), std::cos(yaw_error));

    // check goal, verify yaw and set velocity
    if (goal_execution) {
      // verify yaw desire with minimu error
      if (std::abs(yaw_error) > 0.17) {
        velocity.linear.x = 0.0;
        velocity.angular.z = (yaw_error > 0) ? 0.5 : -0.5;
        // RCLCPP_INFO(this->get_logger(),
        //             "Turning towards target. Yaw error: %.2f", yaw_error);
      } else {
        velocity.linear.x = 0.1; // 0.1
        velocity.angular.z = 0.0;
      }
    }
    return distance_to_target;
  }

  //----------------------------------------------------------------------------------------------------------------------
  void timer_callback() {
    if (!goal_execution) {
      return;
    }
    publisher_cmd_->publish(velocity);
  }

  // method to stop the rover once the target has been
  // reached.--------------------------------------------------------------------------------------------------------------
  void stop_patrol() {
    geometry_msgs::msg::Twist stop_cmd;
    stop_cmd.linear.x = 0.0;
    stop_cmd.linear.y = 0.0;
    stop_cmd.angular.z = 0.0;
    publisher_cmd_->publish(stop_cmd);
  }
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto server_node = std::make_shared<GoToPose>();
  rclcpp::spin(server_node);
  rclcpp::shutdown();
  return 0;
}