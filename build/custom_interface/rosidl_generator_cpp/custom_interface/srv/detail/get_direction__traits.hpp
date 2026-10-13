// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from custom_interface:srv/GetDirection.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACE__SRV__DETAIL__GET_DIRECTION__TRAITS_HPP_
#define CUSTOM_INTERFACE__SRV__DETAIL__GET_DIRECTION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "custom_interface/srv/detail/get_direction__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'laser_data'
#include "sensor_msgs/msg/detail/laser_scan__traits.hpp"

namespace custom_interface
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetDirection_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: laser_data
  {
    out << "laser_data: ";
    to_flow_style_yaml(msg.laser_data, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetDirection_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: laser_data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "laser_data:\n";
    to_block_style_yaml(msg.laser_data, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetDirection_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace custom_interface

namespace rosidl_generator_traits
{

[[deprecated("use custom_interface::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const custom_interface::srv::GetDirection_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  custom_interface::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use custom_interface::srv::to_yaml() instead")]]
inline std::string to_yaml(const custom_interface::srv::GetDirection_Request & msg)
{
  return custom_interface::srv::to_yaml(msg);
}

template<>
inline const char * data_type<custom_interface::srv::GetDirection_Request>()
{
  return "custom_interface::srv::GetDirection_Request";
}

template<>
inline const char * name<custom_interface::srv::GetDirection_Request>()
{
  return "custom_interface/srv/GetDirection_Request";
}

template<>
struct has_fixed_size<custom_interface::srv::GetDirection_Request>
  : std::integral_constant<bool, has_fixed_size<sensor_msgs::msg::LaserScan>::value> {};

template<>
struct has_bounded_size<custom_interface::srv::GetDirection_Request>
  : std::integral_constant<bool, has_bounded_size<sensor_msgs::msg::LaserScan>::value> {};

template<>
struct is_message<custom_interface::srv::GetDirection_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace custom_interface
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetDirection_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: direction
  {
    out << "direction: ";
    rosidl_generator_traits::value_to_yaml(msg.direction, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetDirection_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: direction
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "direction: ";
    rosidl_generator_traits::value_to_yaml(msg.direction, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetDirection_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace custom_interface

namespace rosidl_generator_traits
{

[[deprecated("use custom_interface::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const custom_interface::srv::GetDirection_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  custom_interface::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use custom_interface::srv::to_yaml() instead")]]
inline std::string to_yaml(const custom_interface::srv::GetDirection_Response & msg)
{
  return custom_interface::srv::to_yaml(msg);
}

template<>
inline const char * data_type<custom_interface::srv::GetDirection_Response>()
{
  return "custom_interface::srv::GetDirection_Response";
}

template<>
inline const char * name<custom_interface::srv::GetDirection_Response>()
{
  return "custom_interface/srv/GetDirection_Response";
}

template<>
struct has_fixed_size<custom_interface::srv::GetDirection_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<custom_interface::srv::GetDirection_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<custom_interface::srv::GetDirection_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<custom_interface::srv::GetDirection>()
{
  return "custom_interface::srv::GetDirection";
}

template<>
inline const char * name<custom_interface::srv::GetDirection>()
{
  return "custom_interface/srv/GetDirection";
}

template<>
struct has_fixed_size<custom_interface::srv::GetDirection>
  : std::integral_constant<
    bool,
    has_fixed_size<custom_interface::srv::GetDirection_Request>::value &&
    has_fixed_size<custom_interface::srv::GetDirection_Response>::value
  >
{
};

template<>
struct has_bounded_size<custom_interface::srv::GetDirection>
  : std::integral_constant<
    bool,
    has_bounded_size<custom_interface::srv::GetDirection_Request>::value &&
    has_bounded_size<custom_interface::srv::GetDirection_Response>::value
  >
{
};

template<>
struct is_service<custom_interface::srv::GetDirection>
  : std::true_type
{
};

template<>
struct is_service_request<custom_interface::srv::GetDirection_Request>
  : std::true_type
{
};

template<>
struct is_service_response<custom_interface::srv::GetDirection_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // CUSTOM_INTERFACE__SRV__DETAIL__GET_DIRECTION__TRAITS_HPP_
