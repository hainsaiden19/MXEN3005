// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from wx250s_interface:action/JointPTP.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "wx250s_interface/action/joint_ptp.hpp"


#ifndef WX250S_INTERFACE__ACTION__DETAIL__JOINT_PTP__BUILDER_HPP_
#define WX250S_INTERFACE__ACTION__DETAIL__JOINT_PTP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "wx250s_interface/action/detail/joint_ptp__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace wx250s_interface
{

namespace action
{

namespace builder
{

class Init_JointPTP_Goal_joint_goal
{
public:
  Init_JointPTP_Goal_joint_goal()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::wx250s_interface::action::JointPTP_Goal joint_goal(::wx250s_interface::action::JointPTP_Goal::_joint_goal_type arg)
  {
    msg_.joint_goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wx250s_interface::action::JointPTP_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::wx250s_interface::action::JointPTP_Goal>()
{
  return wx250s_interface::action::builder::Init_JointPTP_Goal_joint_goal();
}

}  // namespace wx250s_interface


namespace wx250s_interface
{

namespace action
{

namespace builder
{

class Init_JointPTP_Result_success
{
public:
  Init_JointPTP_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::wx250s_interface::action::JointPTP_Result success(::wx250s_interface::action::JointPTP_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wx250s_interface::action::JointPTP_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::wx250s_interface::action::JointPTP_Result>()
{
  return wx250s_interface::action::builder::Init_JointPTP_Result_success();
}

}  // namespace wx250s_interface


namespace wx250s_interface
{

namespace action
{

namespace builder
{

class Init_JointPTP_Feedback_joint_present
{
public:
  Init_JointPTP_Feedback_joint_present()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::wx250s_interface::action::JointPTP_Feedback joint_present(::wx250s_interface::action::JointPTP_Feedback::_joint_present_type arg)
  {
    msg_.joint_present = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wx250s_interface::action::JointPTP_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::wx250s_interface::action::JointPTP_Feedback>()
{
  return wx250s_interface::action::builder::Init_JointPTP_Feedback_joint_present();
}

}  // namespace wx250s_interface


namespace wx250s_interface
{

namespace action
{

namespace builder
{

class Init_JointPTP_SendGoal_Request_goal
{
public:
  explicit Init_JointPTP_SendGoal_Request_goal(::wx250s_interface::action::JointPTP_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::wx250s_interface::action::JointPTP_SendGoal_Request goal(::wx250s_interface::action::JointPTP_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wx250s_interface::action::JointPTP_SendGoal_Request msg_;
};

class Init_JointPTP_SendGoal_Request_goal_id
{
public:
  Init_JointPTP_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_JointPTP_SendGoal_Request_goal goal_id(::wx250s_interface::action::JointPTP_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_JointPTP_SendGoal_Request_goal(msg_);
  }

private:
  ::wx250s_interface::action::JointPTP_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::wx250s_interface::action::JointPTP_SendGoal_Request>()
{
  return wx250s_interface::action::builder::Init_JointPTP_SendGoal_Request_goal_id();
}

}  // namespace wx250s_interface


namespace wx250s_interface
{

namespace action
{

namespace builder
{

class Init_JointPTP_SendGoal_Response_stamp
{
public:
  explicit Init_JointPTP_SendGoal_Response_stamp(::wx250s_interface::action::JointPTP_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::wx250s_interface::action::JointPTP_SendGoal_Response stamp(::wx250s_interface::action::JointPTP_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wx250s_interface::action::JointPTP_SendGoal_Response msg_;
};

class Init_JointPTP_SendGoal_Response_accepted
{
public:
  Init_JointPTP_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_JointPTP_SendGoal_Response_stamp accepted(::wx250s_interface::action::JointPTP_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_JointPTP_SendGoal_Response_stamp(msg_);
  }

private:
  ::wx250s_interface::action::JointPTP_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::wx250s_interface::action::JointPTP_SendGoal_Response>()
{
  return wx250s_interface::action::builder::Init_JointPTP_SendGoal_Response_accepted();
}

}  // namespace wx250s_interface


namespace wx250s_interface
{

namespace action
{

namespace builder
{

class Init_JointPTP_SendGoal_Event_response
{
public:
  explicit Init_JointPTP_SendGoal_Event_response(::wx250s_interface::action::JointPTP_SendGoal_Event & msg)
  : msg_(msg)
  {}
  ::wx250s_interface::action::JointPTP_SendGoal_Event response(::wx250s_interface::action::JointPTP_SendGoal_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wx250s_interface::action::JointPTP_SendGoal_Event msg_;
};

class Init_JointPTP_SendGoal_Event_request
{
public:
  explicit Init_JointPTP_SendGoal_Event_request(::wx250s_interface::action::JointPTP_SendGoal_Event & msg)
  : msg_(msg)
  {}
  Init_JointPTP_SendGoal_Event_response request(::wx250s_interface::action::JointPTP_SendGoal_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_JointPTP_SendGoal_Event_response(msg_);
  }

private:
  ::wx250s_interface::action::JointPTP_SendGoal_Event msg_;
};

class Init_JointPTP_SendGoal_Event_info
{
public:
  Init_JointPTP_SendGoal_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_JointPTP_SendGoal_Event_request info(::wx250s_interface::action::JointPTP_SendGoal_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_JointPTP_SendGoal_Event_request(msg_);
  }

private:
  ::wx250s_interface::action::JointPTP_SendGoal_Event msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::wx250s_interface::action::JointPTP_SendGoal_Event>()
{
  return wx250s_interface::action::builder::Init_JointPTP_SendGoal_Event_info();
}

}  // namespace wx250s_interface


namespace wx250s_interface
{

namespace action
{

namespace builder
{

class Init_JointPTP_GetResult_Request_goal_id
{
public:
  Init_JointPTP_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::wx250s_interface::action::JointPTP_GetResult_Request goal_id(::wx250s_interface::action::JointPTP_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wx250s_interface::action::JointPTP_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::wx250s_interface::action::JointPTP_GetResult_Request>()
{
  return wx250s_interface::action::builder::Init_JointPTP_GetResult_Request_goal_id();
}

}  // namespace wx250s_interface


namespace wx250s_interface
{

namespace action
{

namespace builder
{

class Init_JointPTP_GetResult_Response_result
{
public:
  explicit Init_JointPTP_GetResult_Response_result(::wx250s_interface::action::JointPTP_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::wx250s_interface::action::JointPTP_GetResult_Response result(::wx250s_interface::action::JointPTP_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wx250s_interface::action::JointPTP_GetResult_Response msg_;
};

class Init_JointPTP_GetResult_Response_status
{
public:
  Init_JointPTP_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_JointPTP_GetResult_Response_result status(::wx250s_interface::action::JointPTP_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_JointPTP_GetResult_Response_result(msg_);
  }

private:
  ::wx250s_interface::action::JointPTP_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::wx250s_interface::action::JointPTP_GetResult_Response>()
{
  return wx250s_interface::action::builder::Init_JointPTP_GetResult_Response_status();
}

}  // namespace wx250s_interface


namespace wx250s_interface
{

namespace action
{

namespace builder
{

class Init_JointPTP_GetResult_Event_response
{
public:
  explicit Init_JointPTP_GetResult_Event_response(::wx250s_interface::action::JointPTP_GetResult_Event & msg)
  : msg_(msg)
  {}
  ::wx250s_interface::action::JointPTP_GetResult_Event response(::wx250s_interface::action::JointPTP_GetResult_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wx250s_interface::action::JointPTP_GetResult_Event msg_;
};

class Init_JointPTP_GetResult_Event_request
{
public:
  explicit Init_JointPTP_GetResult_Event_request(::wx250s_interface::action::JointPTP_GetResult_Event & msg)
  : msg_(msg)
  {}
  Init_JointPTP_GetResult_Event_response request(::wx250s_interface::action::JointPTP_GetResult_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_JointPTP_GetResult_Event_response(msg_);
  }

private:
  ::wx250s_interface::action::JointPTP_GetResult_Event msg_;
};

class Init_JointPTP_GetResult_Event_info
{
public:
  Init_JointPTP_GetResult_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_JointPTP_GetResult_Event_request info(::wx250s_interface::action::JointPTP_GetResult_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_JointPTP_GetResult_Event_request(msg_);
  }

private:
  ::wx250s_interface::action::JointPTP_GetResult_Event msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::wx250s_interface::action::JointPTP_GetResult_Event>()
{
  return wx250s_interface::action::builder::Init_JointPTP_GetResult_Event_info();
}

}  // namespace wx250s_interface


namespace wx250s_interface
{

namespace action
{

namespace builder
{

class Init_JointPTP_FeedbackMessage_feedback
{
public:
  explicit Init_JointPTP_FeedbackMessage_feedback(::wx250s_interface::action::JointPTP_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::wx250s_interface::action::JointPTP_FeedbackMessage feedback(::wx250s_interface::action::JointPTP_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wx250s_interface::action::JointPTP_FeedbackMessage msg_;
};

class Init_JointPTP_FeedbackMessage_goal_id
{
public:
  Init_JointPTP_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_JointPTP_FeedbackMessage_feedback goal_id(::wx250s_interface::action::JointPTP_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_JointPTP_FeedbackMessage_feedback(msg_);
  }

private:
  ::wx250s_interface::action::JointPTP_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::wx250s_interface::action::JointPTP_FeedbackMessage>()
{
  return wx250s_interface::action::builder::Init_JointPTP_FeedbackMessage_goal_id();
}

}  // namespace wx250s_interface

#endif  // WX250S_INTERFACE__ACTION__DETAIL__JOINT_PTP__BUILDER_HPP_
