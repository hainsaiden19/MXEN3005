// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from wx250s_interface:action/JointPTP.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "wx250s_interface/action/joint_ptp.h"


#ifndef WX250S_INTERFACE__ACTION__DETAIL__JOINT_PTP__STRUCT_H_
#define WX250S_INTERFACE__ACTION__DETAIL__JOINT_PTP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in action/JointPTP in the package wx250s_interface.
typedef struct wx250s_interface__action__JointPTP_Goal
{
  double joint_goal[6];
} wx250s_interface__action__JointPTP_Goal;

// Struct for a sequence of wx250s_interface__action__JointPTP_Goal.
typedef struct wx250s_interface__action__JointPTP_Goal__Sequence
{
  wx250s_interface__action__JointPTP_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} wx250s_interface__action__JointPTP_Goal__Sequence;

// Constants defined in the message

/// Struct defined in action/JointPTP in the package wx250s_interface.
typedef struct wx250s_interface__action__JointPTP_Result
{
  bool success;
} wx250s_interface__action__JointPTP_Result;

// Struct for a sequence of wx250s_interface__action__JointPTP_Result.
typedef struct wx250s_interface__action__JointPTP_Result__Sequence
{
  wx250s_interface__action__JointPTP_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} wx250s_interface__action__JointPTP_Result__Sequence;

// Constants defined in the message

/// Struct defined in action/JointPTP in the package wx250s_interface.
typedef struct wx250s_interface__action__JointPTP_Feedback
{
  double joint_present[6];
} wx250s_interface__action__JointPTP_Feedback;

// Struct for a sequence of wx250s_interface__action__JointPTP_Feedback.
typedef struct wx250s_interface__action__JointPTP_Feedback__Sequence
{
  wx250s_interface__action__JointPTP_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} wx250s_interface__action__JointPTP_Feedback__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "wx250s_interface/action/detail/joint_ptp__struct.h"

/// Struct defined in action/JointPTP in the package wx250s_interface.
typedef struct wx250s_interface__action__JointPTP_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  wx250s_interface__action__JointPTP_Goal goal;
} wx250s_interface__action__JointPTP_SendGoal_Request;

// Struct for a sequence of wx250s_interface__action__JointPTP_SendGoal_Request.
typedef struct wx250s_interface__action__JointPTP_SendGoal_Request__Sequence
{
  wx250s_interface__action__JointPTP_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} wx250s_interface__action__JointPTP_SendGoal_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/JointPTP in the package wx250s_interface.
typedef struct wx250s_interface__action__JointPTP_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} wx250s_interface__action__JointPTP_SendGoal_Response;

// Struct for a sequence of wx250s_interface__action__JointPTP_SendGoal_Response.
typedef struct wx250s_interface__action__JointPTP_SendGoal_Response__Sequence
{
  wx250s_interface__action__JointPTP_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} wx250s_interface__action__JointPTP_SendGoal_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  wx250s_interface__action__JointPTP_SendGoal_Event__request__MAX_SIZE = 1
};
// response
enum
{
  wx250s_interface__action__JointPTP_SendGoal_Event__response__MAX_SIZE = 1
};

/// Struct defined in action/JointPTP in the package wx250s_interface.
typedef struct wx250s_interface__action__JointPTP_SendGoal_Event
{
  service_msgs__msg__ServiceEventInfo info;
  wx250s_interface__action__JointPTP_SendGoal_Request__Sequence request;
  wx250s_interface__action__JointPTP_SendGoal_Response__Sequence response;
} wx250s_interface__action__JointPTP_SendGoal_Event;

// Struct for a sequence of wx250s_interface__action__JointPTP_SendGoal_Event.
typedef struct wx250s_interface__action__JointPTP_SendGoal_Event__Sequence
{
  wx250s_interface__action__JointPTP_SendGoal_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} wx250s_interface__action__JointPTP_SendGoal_Event__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/JointPTP in the package wx250s_interface.
typedef struct wx250s_interface__action__JointPTP_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} wx250s_interface__action__JointPTP_GetResult_Request;

// Struct for a sequence of wx250s_interface__action__JointPTP_GetResult_Request.
typedef struct wx250s_interface__action__JointPTP_GetResult_Request__Sequence
{
  wx250s_interface__action__JointPTP_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} wx250s_interface__action__JointPTP_GetResult_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "wx250s_interface/action/detail/joint_ptp__struct.h"

/// Struct defined in action/JointPTP in the package wx250s_interface.
typedef struct wx250s_interface__action__JointPTP_GetResult_Response
{
  int8_t status;
  wx250s_interface__action__JointPTP_Result result;
} wx250s_interface__action__JointPTP_GetResult_Response;

// Struct for a sequence of wx250s_interface__action__JointPTP_GetResult_Response.
typedef struct wx250s_interface__action__JointPTP_GetResult_Response__Sequence
{
  wx250s_interface__action__JointPTP_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} wx250s_interface__action__JointPTP_GetResult_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
// already included above
// #include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  wx250s_interface__action__JointPTP_GetResult_Event__request__MAX_SIZE = 1
};
// response
enum
{
  wx250s_interface__action__JointPTP_GetResult_Event__response__MAX_SIZE = 1
};

/// Struct defined in action/JointPTP in the package wx250s_interface.
typedef struct wx250s_interface__action__JointPTP_GetResult_Event
{
  service_msgs__msg__ServiceEventInfo info;
  wx250s_interface__action__JointPTP_GetResult_Request__Sequence request;
  wx250s_interface__action__JointPTP_GetResult_Response__Sequence response;
} wx250s_interface__action__JointPTP_GetResult_Event;

// Struct for a sequence of wx250s_interface__action__JointPTP_GetResult_Event.
typedef struct wx250s_interface__action__JointPTP_GetResult_Event__Sequence
{
  wx250s_interface__action__JointPTP_GetResult_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} wx250s_interface__action__JointPTP_GetResult_Event__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "wx250s_interface/action/detail/joint_ptp__struct.h"

/// Struct defined in action/JointPTP in the package wx250s_interface.
typedef struct wx250s_interface__action__JointPTP_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  wx250s_interface__action__JointPTP_Feedback feedback;
} wx250s_interface__action__JointPTP_FeedbackMessage;

// Struct for a sequence of wx250s_interface__action__JointPTP_FeedbackMessage.
typedef struct wx250s_interface__action__JointPTP_FeedbackMessage__Sequence
{
  wx250s_interface__action__JointPTP_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} wx250s_interface__action__JointPTP_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WX250S_INTERFACE__ACTION__DETAIL__JOINT_PTP__STRUCT_H_
