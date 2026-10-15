// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_patrol:action/GoToPose.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_PATROL__ACTION__DETAIL__GO_TO_POSE__BUILDER_HPP_
#define ROBOT_PATROL__ACTION__DETAIL__GO_TO_POSE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_patrol/action/detail/go_to_pose__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_patrol
{

namespace action
{

namespace builder
{

class Init_GoToPose_Goal_goal_pos
{
public:
  Init_GoToPose_Goal_goal_pos()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::robot_patrol::action::GoToPose_Goal goal_pos(::robot_patrol::action::GoToPose_Goal::_goal_pos_type arg)
  {
    msg_.goal_pos = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_patrol::action::GoToPose_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_patrol::action::GoToPose_Goal>()
{
  return robot_patrol::action::builder::Init_GoToPose_Goal_goal_pos();
}

}  // namespace robot_patrol


namespace robot_patrol
{

namespace action
{

namespace builder
{

class Init_GoToPose_Result_status
{
public:
  Init_GoToPose_Result_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::robot_patrol::action::GoToPose_Result status(::robot_patrol::action::GoToPose_Result::_status_type arg)
  {
    msg_.status = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_patrol::action::GoToPose_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_patrol::action::GoToPose_Result>()
{
  return robot_patrol::action::builder::Init_GoToPose_Result_status();
}

}  // namespace robot_patrol


namespace robot_patrol
{

namespace action
{

namespace builder
{

class Init_GoToPose_Feedback_current_pos
{
public:
  Init_GoToPose_Feedback_current_pos()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::robot_patrol::action::GoToPose_Feedback current_pos(::robot_patrol::action::GoToPose_Feedback::_current_pos_type arg)
  {
    msg_.current_pos = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_patrol::action::GoToPose_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_patrol::action::GoToPose_Feedback>()
{
  return robot_patrol::action::builder::Init_GoToPose_Feedback_current_pos();
}

}  // namespace robot_patrol


namespace robot_patrol
{

namespace action
{

namespace builder
{

class Init_GoToPose_SendGoal_Request_goal
{
public:
  explicit Init_GoToPose_SendGoal_Request_goal(::robot_patrol::action::GoToPose_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::robot_patrol::action::GoToPose_SendGoal_Request goal(::robot_patrol::action::GoToPose_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_patrol::action::GoToPose_SendGoal_Request msg_;
};

class Init_GoToPose_SendGoal_Request_goal_id
{
public:
  Init_GoToPose_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GoToPose_SendGoal_Request_goal goal_id(::robot_patrol::action::GoToPose_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_GoToPose_SendGoal_Request_goal(msg_);
  }

private:
  ::robot_patrol::action::GoToPose_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_patrol::action::GoToPose_SendGoal_Request>()
{
  return robot_patrol::action::builder::Init_GoToPose_SendGoal_Request_goal_id();
}

}  // namespace robot_patrol


namespace robot_patrol
{

namespace action
{

namespace builder
{

class Init_GoToPose_SendGoal_Response_stamp
{
public:
  explicit Init_GoToPose_SendGoal_Response_stamp(::robot_patrol::action::GoToPose_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::robot_patrol::action::GoToPose_SendGoal_Response stamp(::robot_patrol::action::GoToPose_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_patrol::action::GoToPose_SendGoal_Response msg_;
};

class Init_GoToPose_SendGoal_Response_accepted
{
public:
  Init_GoToPose_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GoToPose_SendGoal_Response_stamp accepted(::robot_patrol::action::GoToPose_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_GoToPose_SendGoal_Response_stamp(msg_);
  }

private:
  ::robot_patrol::action::GoToPose_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_patrol::action::GoToPose_SendGoal_Response>()
{
  return robot_patrol::action::builder::Init_GoToPose_SendGoal_Response_accepted();
}

}  // namespace robot_patrol


namespace robot_patrol
{

namespace action
{

namespace builder
{

class Init_GoToPose_GetResult_Request_goal_id
{
public:
  Init_GoToPose_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::robot_patrol::action::GoToPose_GetResult_Request goal_id(::robot_patrol::action::GoToPose_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_patrol::action::GoToPose_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_patrol::action::GoToPose_GetResult_Request>()
{
  return robot_patrol::action::builder::Init_GoToPose_GetResult_Request_goal_id();
}

}  // namespace robot_patrol


namespace robot_patrol
{

namespace action
{

namespace builder
{

class Init_GoToPose_GetResult_Response_result
{
public:
  explicit Init_GoToPose_GetResult_Response_result(::robot_patrol::action::GoToPose_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::robot_patrol::action::GoToPose_GetResult_Response result(::robot_patrol::action::GoToPose_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_patrol::action::GoToPose_GetResult_Response msg_;
};

class Init_GoToPose_GetResult_Response_status
{
public:
  Init_GoToPose_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GoToPose_GetResult_Response_result status(::robot_patrol::action::GoToPose_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_GoToPose_GetResult_Response_result(msg_);
  }

private:
  ::robot_patrol::action::GoToPose_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_patrol::action::GoToPose_GetResult_Response>()
{
  return robot_patrol::action::builder::Init_GoToPose_GetResult_Response_status();
}

}  // namespace robot_patrol


namespace robot_patrol
{

namespace action
{

namespace builder
{

class Init_GoToPose_FeedbackMessage_feedback
{
public:
  explicit Init_GoToPose_FeedbackMessage_feedback(::robot_patrol::action::GoToPose_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::robot_patrol::action::GoToPose_FeedbackMessage feedback(::robot_patrol::action::GoToPose_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_patrol::action::GoToPose_FeedbackMessage msg_;
};

class Init_GoToPose_FeedbackMessage_goal_id
{
public:
  Init_GoToPose_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GoToPose_FeedbackMessage_feedback goal_id(::robot_patrol::action::GoToPose_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_GoToPose_FeedbackMessage_feedback(msg_);
  }

private:
  ::robot_patrol::action::GoToPose_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_patrol::action::GoToPose_FeedbackMessage>()
{
  return robot_patrol::action::builder::Init_GoToPose_FeedbackMessage_goal_id();
}

}  // namespace robot_patrol

#endif  // ROBOT_PATROL__ACTION__DETAIL__GO_TO_POSE__BUILDER_HPP_
