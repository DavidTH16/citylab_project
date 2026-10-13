// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from custom_interface:srv/GetDirection.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACE__SRV__DETAIL__GET_DIRECTION__STRUCT_H_
#define CUSTOM_INTERFACE__SRV__DETAIL__GET_DIRECTION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'laser_data'
#include "sensor_msgs/msg/detail/laser_scan__struct.h"

/// Struct defined in srv/GetDirection in the package custom_interface.
typedef struct custom_interface__srv__GetDirection_Request
{
  sensor_msgs__msg__LaserScan laser_data;
} custom_interface__srv__GetDirection_Request;

// Struct for a sequence of custom_interface__srv__GetDirection_Request.
typedef struct custom_interface__srv__GetDirection_Request__Sequence
{
  custom_interface__srv__GetDirection_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_interface__srv__GetDirection_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'direction'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/GetDirection in the package custom_interface.
typedef struct custom_interface__srv__GetDirection_Response
{
  /// Response
  rosidl_runtime_c__String direction;
} custom_interface__srv__GetDirection_Response;

// Struct for a sequence of custom_interface__srv__GetDirection_Response.
typedef struct custom_interface__srv__GetDirection_Response__Sequence
{
  custom_interface__srv__GetDirection_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_interface__srv__GetDirection_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CUSTOM_INTERFACE__SRV__DETAIL__GET_DIRECTION__STRUCT_H_
