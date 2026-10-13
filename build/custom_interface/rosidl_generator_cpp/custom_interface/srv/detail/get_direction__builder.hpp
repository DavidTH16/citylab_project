// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from custom_interface:srv/GetDirection.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACE__SRV__DETAIL__GET_DIRECTION__BUILDER_HPP_
#define CUSTOM_INTERFACE__SRV__DETAIL__GET_DIRECTION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "custom_interface/srv/detail/get_direction__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace custom_interface
{

namespace srv
{

namespace builder
{

class Init_GetDirection_Request_laser_data
{
public:
  Init_GetDirection_Request_laser_data()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::custom_interface::srv::GetDirection_Request laser_data(::custom_interface::srv::GetDirection_Request::_laser_data_type arg)
  {
    msg_.laser_data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_interface::srv::GetDirection_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_interface::srv::GetDirection_Request>()
{
  return custom_interface::srv::builder::Init_GetDirection_Request_laser_data();
}

}  // namespace custom_interface


namespace custom_interface
{

namespace srv
{

namespace builder
{

class Init_GetDirection_Response_direction
{
public:
  Init_GetDirection_Response_direction()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::custom_interface::srv::GetDirection_Response direction(::custom_interface::srv::GetDirection_Response::_direction_type arg)
  {
    msg_.direction = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_interface::srv::GetDirection_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_interface::srv::GetDirection_Response>()
{
  return custom_interface::srv::builder::Init_GetDirection_Response_direction();
}

}  // namespace custom_interface

#endif  // CUSTOM_INTERFACE__SRV__DETAIL__GET_DIRECTION__BUILDER_HPP_
