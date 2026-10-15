// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robot_patrol:action/GoToPose.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_PATROL__ACTION__DETAIL__GO_TO_POSE__STRUCT_H_
#define ROBOT_PATROL__ACTION__DETAIL__GO_TO_POSE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'goal_pos'
#include "geometry_msgs/msg/detail/pose2_d__struct.h"

/// Struct defined in action/GoToPose in the package robot_patrol.
typedef struct robot_patrol__action__GoToPose_Goal
{
  geometry_msgs__msg__Pose2D goal_pos;
} robot_patrol__action__GoToPose_Goal;

// Struct for a sequence of robot_patrol__action__GoToPose_Goal.
typedef struct robot_patrol__action__GoToPose_Goal__Sequence
{
  robot_patrol__action__GoToPose_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_patrol__action__GoToPose_Goal__Sequence;


// Constants defined in the message

/// Struct defined in action/GoToPose in the package robot_patrol.
typedef struct robot_patrol__action__GoToPose_Result
{
  bool status;
} robot_patrol__action__GoToPose_Result;

// Struct for a sequence of robot_patrol__action__GoToPose_Result.
typedef struct robot_patrol__action__GoToPose_Result__Sequence
{
  robot_patrol__action__GoToPose_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_patrol__action__GoToPose_Result__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'current_pos'
// already included above
// #include "geometry_msgs/msg/detail/pose2_d__struct.h"

/// Struct defined in action/GoToPose in the package robot_patrol.
typedef struct robot_patrol__action__GoToPose_Feedback
{
  geometry_msgs__msg__Pose2D current_pos;
} robot_patrol__action__GoToPose_Feedback;

// Struct for a sequence of robot_patrol__action__GoToPose_Feedback.
typedef struct robot_patrol__action__GoToPose_Feedback__Sequence
{
  robot_patrol__action__GoToPose_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_patrol__action__GoToPose_Feedback__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "robot_patrol/action/detail/go_to_pose__struct.h"

/// Struct defined in action/GoToPose in the package robot_patrol.
typedef struct robot_patrol__action__GoToPose_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  robot_patrol__action__GoToPose_Goal goal;
} robot_patrol__action__GoToPose_SendGoal_Request;

// Struct for a sequence of robot_patrol__action__GoToPose_SendGoal_Request.
typedef struct robot_patrol__action__GoToPose_SendGoal_Request__Sequence
{
  robot_patrol__action__GoToPose_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_patrol__action__GoToPose_SendGoal_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/GoToPose in the package robot_patrol.
typedef struct robot_patrol__action__GoToPose_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} robot_patrol__action__GoToPose_SendGoal_Response;

// Struct for a sequence of robot_patrol__action__GoToPose_SendGoal_Response.
typedef struct robot_patrol__action__GoToPose_SendGoal_Response__Sequence
{
  robot_patrol__action__GoToPose_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_patrol__action__GoToPose_SendGoal_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/GoToPose in the package robot_patrol.
typedef struct robot_patrol__action__GoToPose_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} robot_patrol__action__GoToPose_GetResult_Request;

// Struct for a sequence of robot_patrol__action__GoToPose_GetResult_Request.
typedef struct robot_patrol__action__GoToPose_GetResult_Request__Sequence
{
  robot_patrol__action__GoToPose_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_patrol__action__GoToPose_GetResult_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "robot_patrol/action/detail/go_to_pose__struct.h"

/// Struct defined in action/GoToPose in the package robot_patrol.
typedef struct robot_patrol__action__GoToPose_GetResult_Response
{
  int8_t status;
  robot_patrol__action__GoToPose_Result result;
} robot_patrol__action__GoToPose_GetResult_Response;

// Struct for a sequence of robot_patrol__action__GoToPose_GetResult_Response.
typedef struct robot_patrol__action__GoToPose_GetResult_Response__Sequence
{
  robot_patrol__action__GoToPose_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_patrol__action__GoToPose_GetResult_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "robot_patrol/action/detail/go_to_pose__struct.h"

/// Struct defined in action/GoToPose in the package robot_patrol.
typedef struct robot_patrol__action__GoToPose_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  robot_patrol__action__GoToPose_Feedback feedback;
} robot_patrol__action__GoToPose_FeedbackMessage;

// Struct for a sequence of robot_patrol__action__GoToPose_FeedbackMessage.
typedef struct robot_patrol__action__GoToPose_FeedbackMessage__Sequence
{
  robot_patrol__action__GoToPose_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_patrol__action__GoToPose_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_PATROL__ACTION__DETAIL__GO_TO_POSE__STRUCT_H_
