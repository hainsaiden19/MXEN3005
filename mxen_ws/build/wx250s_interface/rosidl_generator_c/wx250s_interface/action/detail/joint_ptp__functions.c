// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from wx250s_interface:action/JointPTP.idl
// generated code does not contain a copyright notice
#include "wx250s_interface/action/detail/joint_ptp__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
wx250s_interface__action__JointPTP_Goal__init(wx250s_interface__action__JointPTP_Goal * msg)
{
  if (!msg) {
    return false;
  }
  // joint_goal
  return true;
}

void
wx250s_interface__action__JointPTP_Goal__fini(wx250s_interface__action__JointPTP_Goal * msg)
{
  if (!msg) {
    return;
  }
  // joint_goal
}

bool
wx250s_interface__action__JointPTP_Goal__are_equal(const wx250s_interface__action__JointPTP_Goal * lhs, const wx250s_interface__action__JointPTP_Goal * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // joint_goal
  for (size_t i = 0; i < 6; ++i) {
    if (lhs->joint_goal[i] != rhs->joint_goal[i]) {
      return false;
    }
  }
  return true;
}

bool
wx250s_interface__action__JointPTP_Goal__copy(
  const wx250s_interface__action__JointPTP_Goal * input,
  wx250s_interface__action__JointPTP_Goal * output)
{
  if (!input || !output) {
    return false;
  }
  // joint_goal
  for (size_t i = 0; i < 6; ++i) {
    output->joint_goal[i] = input->joint_goal[i];
  }
  return true;
}

wx250s_interface__action__JointPTP_Goal *
wx250s_interface__action__JointPTP_Goal__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wx250s_interface__action__JointPTP_Goal * msg = (wx250s_interface__action__JointPTP_Goal *)allocator.allocate(sizeof(wx250s_interface__action__JointPTP_Goal), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(wx250s_interface__action__JointPTP_Goal));
  bool success = wx250s_interface__action__JointPTP_Goal__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
wx250s_interface__action__JointPTP_Goal__destroy(wx250s_interface__action__JointPTP_Goal * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    wx250s_interface__action__JointPTP_Goal__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
wx250s_interface__action__JointPTP_Goal__Sequence__init(wx250s_interface__action__JointPTP_Goal__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wx250s_interface__action__JointPTP_Goal * data = NULL;

  if (size) {
    data = (wx250s_interface__action__JointPTP_Goal *)allocator.zero_allocate(size, sizeof(wx250s_interface__action__JointPTP_Goal), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = wx250s_interface__action__JointPTP_Goal__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        wx250s_interface__action__JointPTP_Goal__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
wx250s_interface__action__JointPTP_Goal__Sequence__fini(wx250s_interface__action__JointPTP_Goal__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      wx250s_interface__action__JointPTP_Goal__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

wx250s_interface__action__JointPTP_Goal__Sequence *
wx250s_interface__action__JointPTP_Goal__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wx250s_interface__action__JointPTP_Goal__Sequence * array = (wx250s_interface__action__JointPTP_Goal__Sequence *)allocator.allocate(sizeof(wx250s_interface__action__JointPTP_Goal__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = wx250s_interface__action__JointPTP_Goal__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
wx250s_interface__action__JointPTP_Goal__Sequence__destroy(wx250s_interface__action__JointPTP_Goal__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    wx250s_interface__action__JointPTP_Goal__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
wx250s_interface__action__JointPTP_Goal__Sequence__are_equal(const wx250s_interface__action__JointPTP_Goal__Sequence * lhs, const wx250s_interface__action__JointPTP_Goal__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!wx250s_interface__action__JointPTP_Goal__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
wx250s_interface__action__JointPTP_Goal__Sequence__copy(
  const wx250s_interface__action__JointPTP_Goal__Sequence * input,
  wx250s_interface__action__JointPTP_Goal__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(wx250s_interface__action__JointPTP_Goal);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    wx250s_interface__action__JointPTP_Goal * data =
      (wx250s_interface__action__JointPTP_Goal *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!wx250s_interface__action__JointPTP_Goal__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          wx250s_interface__action__JointPTP_Goal__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!wx250s_interface__action__JointPTP_Goal__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
wx250s_interface__action__JointPTP_Result__init(wx250s_interface__action__JointPTP_Result * msg)
{
  if (!msg) {
    return false;
  }
  // success
  return true;
}

void
wx250s_interface__action__JointPTP_Result__fini(wx250s_interface__action__JointPTP_Result * msg)
{
  if (!msg) {
    return;
  }
  // success
}

bool
wx250s_interface__action__JointPTP_Result__are_equal(const wx250s_interface__action__JointPTP_Result * lhs, const wx250s_interface__action__JointPTP_Result * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  return true;
}

bool
wx250s_interface__action__JointPTP_Result__copy(
  const wx250s_interface__action__JointPTP_Result * input,
  wx250s_interface__action__JointPTP_Result * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  return true;
}

wx250s_interface__action__JointPTP_Result *
wx250s_interface__action__JointPTP_Result__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wx250s_interface__action__JointPTP_Result * msg = (wx250s_interface__action__JointPTP_Result *)allocator.allocate(sizeof(wx250s_interface__action__JointPTP_Result), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(wx250s_interface__action__JointPTP_Result));
  bool success = wx250s_interface__action__JointPTP_Result__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
wx250s_interface__action__JointPTP_Result__destroy(wx250s_interface__action__JointPTP_Result * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    wx250s_interface__action__JointPTP_Result__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
wx250s_interface__action__JointPTP_Result__Sequence__init(wx250s_interface__action__JointPTP_Result__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wx250s_interface__action__JointPTP_Result * data = NULL;

  if (size) {
    data = (wx250s_interface__action__JointPTP_Result *)allocator.zero_allocate(size, sizeof(wx250s_interface__action__JointPTP_Result), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = wx250s_interface__action__JointPTP_Result__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        wx250s_interface__action__JointPTP_Result__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
wx250s_interface__action__JointPTP_Result__Sequence__fini(wx250s_interface__action__JointPTP_Result__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      wx250s_interface__action__JointPTP_Result__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

wx250s_interface__action__JointPTP_Result__Sequence *
wx250s_interface__action__JointPTP_Result__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wx250s_interface__action__JointPTP_Result__Sequence * array = (wx250s_interface__action__JointPTP_Result__Sequence *)allocator.allocate(sizeof(wx250s_interface__action__JointPTP_Result__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = wx250s_interface__action__JointPTP_Result__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
wx250s_interface__action__JointPTP_Result__Sequence__destroy(wx250s_interface__action__JointPTP_Result__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    wx250s_interface__action__JointPTP_Result__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
wx250s_interface__action__JointPTP_Result__Sequence__are_equal(const wx250s_interface__action__JointPTP_Result__Sequence * lhs, const wx250s_interface__action__JointPTP_Result__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!wx250s_interface__action__JointPTP_Result__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
wx250s_interface__action__JointPTP_Result__Sequence__copy(
  const wx250s_interface__action__JointPTP_Result__Sequence * input,
  wx250s_interface__action__JointPTP_Result__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(wx250s_interface__action__JointPTP_Result);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    wx250s_interface__action__JointPTP_Result * data =
      (wx250s_interface__action__JointPTP_Result *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!wx250s_interface__action__JointPTP_Result__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          wx250s_interface__action__JointPTP_Result__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!wx250s_interface__action__JointPTP_Result__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
wx250s_interface__action__JointPTP_Feedback__init(wx250s_interface__action__JointPTP_Feedback * msg)
{
  if (!msg) {
    return false;
  }
  // joint_present
  return true;
}

void
wx250s_interface__action__JointPTP_Feedback__fini(wx250s_interface__action__JointPTP_Feedback * msg)
{
  if (!msg) {
    return;
  }
  // joint_present
}

bool
wx250s_interface__action__JointPTP_Feedback__are_equal(const wx250s_interface__action__JointPTP_Feedback * lhs, const wx250s_interface__action__JointPTP_Feedback * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // joint_present
  for (size_t i = 0; i < 6; ++i) {
    if (lhs->joint_present[i] != rhs->joint_present[i]) {
      return false;
    }
  }
  return true;
}

bool
wx250s_interface__action__JointPTP_Feedback__copy(
  const wx250s_interface__action__JointPTP_Feedback * input,
  wx250s_interface__action__JointPTP_Feedback * output)
{
  if (!input || !output) {
    return false;
  }
  // joint_present
  for (size_t i = 0; i < 6; ++i) {
    output->joint_present[i] = input->joint_present[i];
  }
  return true;
}

wx250s_interface__action__JointPTP_Feedback *
wx250s_interface__action__JointPTP_Feedback__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wx250s_interface__action__JointPTP_Feedback * msg = (wx250s_interface__action__JointPTP_Feedback *)allocator.allocate(sizeof(wx250s_interface__action__JointPTP_Feedback), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(wx250s_interface__action__JointPTP_Feedback));
  bool success = wx250s_interface__action__JointPTP_Feedback__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
wx250s_interface__action__JointPTP_Feedback__destroy(wx250s_interface__action__JointPTP_Feedback * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    wx250s_interface__action__JointPTP_Feedback__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
wx250s_interface__action__JointPTP_Feedback__Sequence__init(wx250s_interface__action__JointPTP_Feedback__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wx250s_interface__action__JointPTP_Feedback * data = NULL;

  if (size) {
    data = (wx250s_interface__action__JointPTP_Feedback *)allocator.zero_allocate(size, sizeof(wx250s_interface__action__JointPTP_Feedback), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = wx250s_interface__action__JointPTP_Feedback__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        wx250s_interface__action__JointPTP_Feedback__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
wx250s_interface__action__JointPTP_Feedback__Sequence__fini(wx250s_interface__action__JointPTP_Feedback__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      wx250s_interface__action__JointPTP_Feedback__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

wx250s_interface__action__JointPTP_Feedback__Sequence *
wx250s_interface__action__JointPTP_Feedback__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wx250s_interface__action__JointPTP_Feedback__Sequence * array = (wx250s_interface__action__JointPTP_Feedback__Sequence *)allocator.allocate(sizeof(wx250s_interface__action__JointPTP_Feedback__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = wx250s_interface__action__JointPTP_Feedback__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
wx250s_interface__action__JointPTP_Feedback__Sequence__destroy(wx250s_interface__action__JointPTP_Feedback__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    wx250s_interface__action__JointPTP_Feedback__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
wx250s_interface__action__JointPTP_Feedback__Sequence__are_equal(const wx250s_interface__action__JointPTP_Feedback__Sequence * lhs, const wx250s_interface__action__JointPTP_Feedback__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!wx250s_interface__action__JointPTP_Feedback__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
wx250s_interface__action__JointPTP_Feedback__Sequence__copy(
  const wx250s_interface__action__JointPTP_Feedback__Sequence * input,
  wx250s_interface__action__JointPTP_Feedback__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(wx250s_interface__action__JointPTP_Feedback);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    wx250s_interface__action__JointPTP_Feedback * data =
      (wx250s_interface__action__JointPTP_Feedback *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!wx250s_interface__action__JointPTP_Feedback__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          wx250s_interface__action__JointPTP_Feedback__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!wx250s_interface__action__JointPTP_Feedback__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `goal`
// already included above
// #include "wx250s_interface/action/detail/joint_ptp__functions.h"

bool
wx250s_interface__action__JointPTP_SendGoal_Request__init(wx250s_interface__action__JointPTP_SendGoal_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    wx250s_interface__action__JointPTP_SendGoal_Request__fini(msg);
    return false;
  }
  // goal
  if (!wx250s_interface__action__JointPTP_Goal__init(&msg->goal)) {
    wx250s_interface__action__JointPTP_SendGoal_Request__fini(msg);
    return false;
  }
  return true;
}

void
wx250s_interface__action__JointPTP_SendGoal_Request__fini(wx250s_interface__action__JointPTP_SendGoal_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // goal
  wx250s_interface__action__JointPTP_Goal__fini(&msg->goal);
}

bool
wx250s_interface__action__JointPTP_SendGoal_Request__are_equal(const wx250s_interface__action__JointPTP_SendGoal_Request * lhs, const wx250s_interface__action__JointPTP_SendGoal_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // goal
  if (!wx250s_interface__action__JointPTP_Goal__are_equal(
      &(lhs->goal), &(rhs->goal)))
  {
    return false;
  }
  return true;
}

bool
wx250s_interface__action__JointPTP_SendGoal_Request__copy(
  const wx250s_interface__action__JointPTP_SendGoal_Request * input,
  wx250s_interface__action__JointPTP_SendGoal_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // goal
  if (!wx250s_interface__action__JointPTP_Goal__copy(
      &(input->goal), &(output->goal)))
  {
    return false;
  }
  return true;
}

wx250s_interface__action__JointPTP_SendGoal_Request *
wx250s_interface__action__JointPTP_SendGoal_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wx250s_interface__action__JointPTP_SendGoal_Request * msg = (wx250s_interface__action__JointPTP_SendGoal_Request *)allocator.allocate(sizeof(wx250s_interface__action__JointPTP_SendGoal_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(wx250s_interface__action__JointPTP_SendGoal_Request));
  bool success = wx250s_interface__action__JointPTP_SendGoal_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
wx250s_interface__action__JointPTP_SendGoal_Request__destroy(wx250s_interface__action__JointPTP_SendGoal_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    wx250s_interface__action__JointPTP_SendGoal_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
wx250s_interface__action__JointPTP_SendGoal_Request__Sequence__init(wx250s_interface__action__JointPTP_SendGoal_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wx250s_interface__action__JointPTP_SendGoal_Request * data = NULL;

  if (size) {
    data = (wx250s_interface__action__JointPTP_SendGoal_Request *)allocator.zero_allocate(size, sizeof(wx250s_interface__action__JointPTP_SendGoal_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = wx250s_interface__action__JointPTP_SendGoal_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        wx250s_interface__action__JointPTP_SendGoal_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
wx250s_interface__action__JointPTP_SendGoal_Request__Sequence__fini(wx250s_interface__action__JointPTP_SendGoal_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      wx250s_interface__action__JointPTP_SendGoal_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

wx250s_interface__action__JointPTP_SendGoal_Request__Sequence *
wx250s_interface__action__JointPTP_SendGoal_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wx250s_interface__action__JointPTP_SendGoal_Request__Sequence * array = (wx250s_interface__action__JointPTP_SendGoal_Request__Sequence *)allocator.allocate(sizeof(wx250s_interface__action__JointPTP_SendGoal_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = wx250s_interface__action__JointPTP_SendGoal_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
wx250s_interface__action__JointPTP_SendGoal_Request__Sequence__destroy(wx250s_interface__action__JointPTP_SendGoal_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    wx250s_interface__action__JointPTP_SendGoal_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
wx250s_interface__action__JointPTP_SendGoal_Request__Sequence__are_equal(const wx250s_interface__action__JointPTP_SendGoal_Request__Sequence * lhs, const wx250s_interface__action__JointPTP_SendGoal_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!wx250s_interface__action__JointPTP_SendGoal_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
wx250s_interface__action__JointPTP_SendGoal_Request__Sequence__copy(
  const wx250s_interface__action__JointPTP_SendGoal_Request__Sequence * input,
  wx250s_interface__action__JointPTP_SendGoal_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(wx250s_interface__action__JointPTP_SendGoal_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    wx250s_interface__action__JointPTP_SendGoal_Request * data =
      (wx250s_interface__action__JointPTP_SendGoal_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!wx250s_interface__action__JointPTP_SendGoal_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          wx250s_interface__action__JointPTP_SendGoal_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!wx250s_interface__action__JointPTP_SendGoal_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
wx250s_interface__action__JointPTP_SendGoal_Response__init(wx250s_interface__action__JointPTP_SendGoal_Response * msg)
{
  if (!msg) {
    return false;
  }
  // accepted
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    wx250s_interface__action__JointPTP_SendGoal_Response__fini(msg);
    return false;
  }
  return true;
}

void
wx250s_interface__action__JointPTP_SendGoal_Response__fini(wx250s_interface__action__JointPTP_SendGoal_Response * msg)
{
  if (!msg) {
    return;
  }
  // accepted
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
}

bool
wx250s_interface__action__JointPTP_SendGoal_Response__are_equal(const wx250s_interface__action__JointPTP_SendGoal_Response * lhs, const wx250s_interface__action__JointPTP_SendGoal_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // accepted
  if (lhs->accepted != rhs->accepted) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  return true;
}

bool
wx250s_interface__action__JointPTP_SendGoal_Response__copy(
  const wx250s_interface__action__JointPTP_SendGoal_Response * input,
  wx250s_interface__action__JointPTP_SendGoal_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // accepted
  output->accepted = input->accepted;
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  return true;
}

wx250s_interface__action__JointPTP_SendGoal_Response *
wx250s_interface__action__JointPTP_SendGoal_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wx250s_interface__action__JointPTP_SendGoal_Response * msg = (wx250s_interface__action__JointPTP_SendGoal_Response *)allocator.allocate(sizeof(wx250s_interface__action__JointPTP_SendGoal_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(wx250s_interface__action__JointPTP_SendGoal_Response));
  bool success = wx250s_interface__action__JointPTP_SendGoal_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
wx250s_interface__action__JointPTP_SendGoal_Response__destroy(wx250s_interface__action__JointPTP_SendGoal_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    wx250s_interface__action__JointPTP_SendGoal_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
wx250s_interface__action__JointPTP_SendGoal_Response__Sequence__init(wx250s_interface__action__JointPTP_SendGoal_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wx250s_interface__action__JointPTP_SendGoal_Response * data = NULL;

  if (size) {
    data = (wx250s_interface__action__JointPTP_SendGoal_Response *)allocator.zero_allocate(size, sizeof(wx250s_interface__action__JointPTP_SendGoal_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = wx250s_interface__action__JointPTP_SendGoal_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        wx250s_interface__action__JointPTP_SendGoal_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
wx250s_interface__action__JointPTP_SendGoal_Response__Sequence__fini(wx250s_interface__action__JointPTP_SendGoal_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      wx250s_interface__action__JointPTP_SendGoal_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

wx250s_interface__action__JointPTP_SendGoal_Response__Sequence *
wx250s_interface__action__JointPTP_SendGoal_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wx250s_interface__action__JointPTP_SendGoal_Response__Sequence * array = (wx250s_interface__action__JointPTP_SendGoal_Response__Sequence *)allocator.allocate(sizeof(wx250s_interface__action__JointPTP_SendGoal_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = wx250s_interface__action__JointPTP_SendGoal_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
wx250s_interface__action__JointPTP_SendGoal_Response__Sequence__destroy(wx250s_interface__action__JointPTP_SendGoal_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    wx250s_interface__action__JointPTP_SendGoal_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
wx250s_interface__action__JointPTP_SendGoal_Response__Sequence__are_equal(const wx250s_interface__action__JointPTP_SendGoal_Response__Sequence * lhs, const wx250s_interface__action__JointPTP_SendGoal_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!wx250s_interface__action__JointPTP_SendGoal_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
wx250s_interface__action__JointPTP_SendGoal_Response__Sequence__copy(
  const wx250s_interface__action__JointPTP_SendGoal_Response__Sequence * input,
  wx250s_interface__action__JointPTP_SendGoal_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(wx250s_interface__action__JointPTP_SendGoal_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    wx250s_interface__action__JointPTP_SendGoal_Response * data =
      (wx250s_interface__action__JointPTP_SendGoal_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!wx250s_interface__action__JointPTP_SendGoal_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          wx250s_interface__action__JointPTP_SendGoal_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!wx250s_interface__action__JointPTP_SendGoal_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `info`
#include "service_msgs/msg/detail/service_event_info__functions.h"
// Member `request`
// Member `response`
// already included above
// #include "wx250s_interface/action/detail/joint_ptp__functions.h"

bool
wx250s_interface__action__JointPTP_SendGoal_Event__init(wx250s_interface__action__JointPTP_SendGoal_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    wx250s_interface__action__JointPTP_SendGoal_Event__fini(msg);
    return false;
  }
  // request
  if (!wx250s_interface__action__JointPTP_SendGoal_Request__Sequence__init(&msg->request, 0)) {
    wx250s_interface__action__JointPTP_SendGoal_Event__fini(msg);
    return false;
  }
  // response
  if (!wx250s_interface__action__JointPTP_SendGoal_Response__Sequence__init(&msg->response, 0)) {
    wx250s_interface__action__JointPTP_SendGoal_Event__fini(msg);
    return false;
  }
  return true;
}

void
wx250s_interface__action__JointPTP_SendGoal_Event__fini(wx250s_interface__action__JointPTP_SendGoal_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  wx250s_interface__action__JointPTP_SendGoal_Request__Sequence__fini(&msg->request);
  // response
  wx250s_interface__action__JointPTP_SendGoal_Response__Sequence__fini(&msg->response);
}

bool
wx250s_interface__action__JointPTP_SendGoal_Event__are_equal(const wx250s_interface__action__JointPTP_SendGoal_Event * lhs, const wx250s_interface__action__JointPTP_SendGoal_Event * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // request
  if (!wx250s_interface__action__JointPTP_SendGoal_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!wx250s_interface__action__JointPTP_SendGoal_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
wx250s_interface__action__JointPTP_SendGoal_Event__copy(
  const wx250s_interface__action__JointPTP_SendGoal_Event * input,
  wx250s_interface__action__JointPTP_SendGoal_Event * output)
{
  if (!input || !output) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // request
  if (!wx250s_interface__action__JointPTP_SendGoal_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!wx250s_interface__action__JointPTP_SendGoal_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

wx250s_interface__action__JointPTP_SendGoal_Event *
wx250s_interface__action__JointPTP_SendGoal_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wx250s_interface__action__JointPTP_SendGoal_Event * msg = (wx250s_interface__action__JointPTP_SendGoal_Event *)allocator.allocate(sizeof(wx250s_interface__action__JointPTP_SendGoal_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(wx250s_interface__action__JointPTP_SendGoal_Event));
  bool success = wx250s_interface__action__JointPTP_SendGoal_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
wx250s_interface__action__JointPTP_SendGoal_Event__destroy(wx250s_interface__action__JointPTP_SendGoal_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    wx250s_interface__action__JointPTP_SendGoal_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
wx250s_interface__action__JointPTP_SendGoal_Event__Sequence__init(wx250s_interface__action__JointPTP_SendGoal_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wx250s_interface__action__JointPTP_SendGoal_Event * data = NULL;

  if (size) {
    data = (wx250s_interface__action__JointPTP_SendGoal_Event *)allocator.zero_allocate(size, sizeof(wx250s_interface__action__JointPTP_SendGoal_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = wx250s_interface__action__JointPTP_SendGoal_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        wx250s_interface__action__JointPTP_SendGoal_Event__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
wx250s_interface__action__JointPTP_SendGoal_Event__Sequence__fini(wx250s_interface__action__JointPTP_SendGoal_Event__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      wx250s_interface__action__JointPTP_SendGoal_Event__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

wx250s_interface__action__JointPTP_SendGoal_Event__Sequence *
wx250s_interface__action__JointPTP_SendGoal_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wx250s_interface__action__JointPTP_SendGoal_Event__Sequence * array = (wx250s_interface__action__JointPTP_SendGoal_Event__Sequence *)allocator.allocate(sizeof(wx250s_interface__action__JointPTP_SendGoal_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = wx250s_interface__action__JointPTP_SendGoal_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
wx250s_interface__action__JointPTP_SendGoal_Event__Sequence__destroy(wx250s_interface__action__JointPTP_SendGoal_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    wx250s_interface__action__JointPTP_SendGoal_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
wx250s_interface__action__JointPTP_SendGoal_Event__Sequence__are_equal(const wx250s_interface__action__JointPTP_SendGoal_Event__Sequence * lhs, const wx250s_interface__action__JointPTP_SendGoal_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!wx250s_interface__action__JointPTP_SendGoal_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
wx250s_interface__action__JointPTP_SendGoal_Event__Sequence__copy(
  const wx250s_interface__action__JointPTP_SendGoal_Event__Sequence * input,
  wx250s_interface__action__JointPTP_SendGoal_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(wx250s_interface__action__JointPTP_SendGoal_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    wx250s_interface__action__JointPTP_SendGoal_Event * data =
      (wx250s_interface__action__JointPTP_SendGoal_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!wx250s_interface__action__JointPTP_SendGoal_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          wx250s_interface__action__JointPTP_SendGoal_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!wx250s_interface__action__JointPTP_SendGoal_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"

bool
wx250s_interface__action__JointPTP_GetResult_Request__init(wx250s_interface__action__JointPTP_GetResult_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    wx250s_interface__action__JointPTP_GetResult_Request__fini(msg);
    return false;
  }
  return true;
}

void
wx250s_interface__action__JointPTP_GetResult_Request__fini(wx250s_interface__action__JointPTP_GetResult_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
}

bool
wx250s_interface__action__JointPTP_GetResult_Request__are_equal(const wx250s_interface__action__JointPTP_GetResult_Request * lhs, const wx250s_interface__action__JointPTP_GetResult_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  return true;
}

bool
wx250s_interface__action__JointPTP_GetResult_Request__copy(
  const wx250s_interface__action__JointPTP_GetResult_Request * input,
  wx250s_interface__action__JointPTP_GetResult_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  return true;
}

wx250s_interface__action__JointPTP_GetResult_Request *
wx250s_interface__action__JointPTP_GetResult_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wx250s_interface__action__JointPTP_GetResult_Request * msg = (wx250s_interface__action__JointPTP_GetResult_Request *)allocator.allocate(sizeof(wx250s_interface__action__JointPTP_GetResult_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(wx250s_interface__action__JointPTP_GetResult_Request));
  bool success = wx250s_interface__action__JointPTP_GetResult_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
wx250s_interface__action__JointPTP_GetResult_Request__destroy(wx250s_interface__action__JointPTP_GetResult_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    wx250s_interface__action__JointPTP_GetResult_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
wx250s_interface__action__JointPTP_GetResult_Request__Sequence__init(wx250s_interface__action__JointPTP_GetResult_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wx250s_interface__action__JointPTP_GetResult_Request * data = NULL;

  if (size) {
    data = (wx250s_interface__action__JointPTP_GetResult_Request *)allocator.zero_allocate(size, sizeof(wx250s_interface__action__JointPTP_GetResult_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = wx250s_interface__action__JointPTP_GetResult_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        wx250s_interface__action__JointPTP_GetResult_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
wx250s_interface__action__JointPTP_GetResult_Request__Sequence__fini(wx250s_interface__action__JointPTP_GetResult_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      wx250s_interface__action__JointPTP_GetResult_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

wx250s_interface__action__JointPTP_GetResult_Request__Sequence *
wx250s_interface__action__JointPTP_GetResult_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wx250s_interface__action__JointPTP_GetResult_Request__Sequence * array = (wx250s_interface__action__JointPTP_GetResult_Request__Sequence *)allocator.allocate(sizeof(wx250s_interface__action__JointPTP_GetResult_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = wx250s_interface__action__JointPTP_GetResult_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
wx250s_interface__action__JointPTP_GetResult_Request__Sequence__destroy(wx250s_interface__action__JointPTP_GetResult_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    wx250s_interface__action__JointPTP_GetResult_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
wx250s_interface__action__JointPTP_GetResult_Request__Sequence__are_equal(const wx250s_interface__action__JointPTP_GetResult_Request__Sequence * lhs, const wx250s_interface__action__JointPTP_GetResult_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!wx250s_interface__action__JointPTP_GetResult_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
wx250s_interface__action__JointPTP_GetResult_Request__Sequence__copy(
  const wx250s_interface__action__JointPTP_GetResult_Request__Sequence * input,
  wx250s_interface__action__JointPTP_GetResult_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(wx250s_interface__action__JointPTP_GetResult_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    wx250s_interface__action__JointPTP_GetResult_Request * data =
      (wx250s_interface__action__JointPTP_GetResult_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!wx250s_interface__action__JointPTP_GetResult_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          wx250s_interface__action__JointPTP_GetResult_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!wx250s_interface__action__JointPTP_GetResult_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `result`
// already included above
// #include "wx250s_interface/action/detail/joint_ptp__functions.h"

bool
wx250s_interface__action__JointPTP_GetResult_Response__init(wx250s_interface__action__JointPTP_GetResult_Response * msg)
{
  if (!msg) {
    return false;
  }
  // status
  // result
  if (!wx250s_interface__action__JointPTP_Result__init(&msg->result)) {
    wx250s_interface__action__JointPTP_GetResult_Response__fini(msg);
    return false;
  }
  return true;
}

void
wx250s_interface__action__JointPTP_GetResult_Response__fini(wx250s_interface__action__JointPTP_GetResult_Response * msg)
{
  if (!msg) {
    return;
  }
  // status
  // result
  wx250s_interface__action__JointPTP_Result__fini(&msg->result);
}

bool
wx250s_interface__action__JointPTP_GetResult_Response__are_equal(const wx250s_interface__action__JointPTP_GetResult_Response * lhs, const wx250s_interface__action__JointPTP_GetResult_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // status
  if (lhs->status != rhs->status) {
    return false;
  }
  // result
  if (!wx250s_interface__action__JointPTP_Result__are_equal(
      &(lhs->result), &(rhs->result)))
  {
    return false;
  }
  return true;
}

bool
wx250s_interface__action__JointPTP_GetResult_Response__copy(
  const wx250s_interface__action__JointPTP_GetResult_Response * input,
  wx250s_interface__action__JointPTP_GetResult_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // status
  output->status = input->status;
  // result
  if (!wx250s_interface__action__JointPTP_Result__copy(
      &(input->result), &(output->result)))
  {
    return false;
  }
  return true;
}

wx250s_interface__action__JointPTP_GetResult_Response *
wx250s_interface__action__JointPTP_GetResult_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wx250s_interface__action__JointPTP_GetResult_Response * msg = (wx250s_interface__action__JointPTP_GetResult_Response *)allocator.allocate(sizeof(wx250s_interface__action__JointPTP_GetResult_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(wx250s_interface__action__JointPTP_GetResult_Response));
  bool success = wx250s_interface__action__JointPTP_GetResult_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
wx250s_interface__action__JointPTP_GetResult_Response__destroy(wx250s_interface__action__JointPTP_GetResult_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    wx250s_interface__action__JointPTP_GetResult_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
wx250s_interface__action__JointPTP_GetResult_Response__Sequence__init(wx250s_interface__action__JointPTP_GetResult_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wx250s_interface__action__JointPTP_GetResult_Response * data = NULL;

  if (size) {
    data = (wx250s_interface__action__JointPTP_GetResult_Response *)allocator.zero_allocate(size, sizeof(wx250s_interface__action__JointPTP_GetResult_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = wx250s_interface__action__JointPTP_GetResult_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        wx250s_interface__action__JointPTP_GetResult_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
wx250s_interface__action__JointPTP_GetResult_Response__Sequence__fini(wx250s_interface__action__JointPTP_GetResult_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      wx250s_interface__action__JointPTP_GetResult_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

wx250s_interface__action__JointPTP_GetResult_Response__Sequence *
wx250s_interface__action__JointPTP_GetResult_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wx250s_interface__action__JointPTP_GetResult_Response__Sequence * array = (wx250s_interface__action__JointPTP_GetResult_Response__Sequence *)allocator.allocate(sizeof(wx250s_interface__action__JointPTP_GetResult_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = wx250s_interface__action__JointPTP_GetResult_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
wx250s_interface__action__JointPTP_GetResult_Response__Sequence__destroy(wx250s_interface__action__JointPTP_GetResult_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    wx250s_interface__action__JointPTP_GetResult_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
wx250s_interface__action__JointPTP_GetResult_Response__Sequence__are_equal(const wx250s_interface__action__JointPTP_GetResult_Response__Sequence * lhs, const wx250s_interface__action__JointPTP_GetResult_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!wx250s_interface__action__JointPTP_GetResult_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
wx250s_interface__action__JointPTP_GetResult_Response__Sequence__copy(
  const wx250s_interface__action__JointPTP_GetResult_Response__Sequence * input,
  wx250s_interface__action__JointPTP_GetResult_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(wx250s_interface__action__JointPTP_GetResult_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    wx250s_interface__action__JointPTP_GetResult_Response * data =
      (wx250s_interface__action__JointPTP_GetResult_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!wx250s_interface__action__JointPTP_GetResult_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          wx250s_interface__action__JointPTP_GetResult_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!wx250s_interface__action__JointPTP_GetResult_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `info`
// already included above
// #include "service_msgs/msg/detail/service_event_info__functions.h"
// Member `request`
// Member `response`
// already included above
// #include "wx250s_interface/action/detail/joint_ptp__functions.h"

bool
wx250s_interface__action__JointPTP_GetResult_Event__init(wx250s_interface__action__JointPTP_GetResult_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    wx250s_interface__action__JointPTP_GetResult_Event__fini(msg);
    return false;
  }
  // request
  if (!wx250s_interface__action__JointPTP_GetResult_Request__Sequence__init(&msg->request, 0)) {
    wx250s_interface__action__JointPTP_GetResult_Event__fini(msg);
    return false;
  }
  // response
  if (!wx250s_interface__action__JointPTP_GetResult_Response__Sequence__init(&msg->response, 0)) {
    wx250s_interface__action__JointPTP_GetResult_Event__fini(msg);
    return false;
  }
  return true;
}

void
wx250s_interface__action__JointPTP_GetResult_Event__fini(wx250s_interface__action__JointPTP_GetResult_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  wx250s_interface__action__JointPTP_GetResult_Request__Sequence__fini(&msg->request);
  // response
  wx250s_interface__action__JointPTP_GetResult_Response__Sequence__fini(&msg->response);
}

bool
wx250s_interface__action__JointPTP_GetResult_Event__are_equal(const wx250s_interface__action__JointPTP_GetResult_Event * lhs, const wx250s_interface__action__JointPTP_GetResult_Event * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // request
  if (!wx250s_interface__action__JointPTP_GetResult_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!wx250s_interface__action__JointPTP_GetResult_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
wx250s_interface__action__JointPTP_GetResult_Event__copy(
  const wx250s_interface__action__JointPTP_GetResult_Event * input,
  wx250s_interface__action__JointPTP_GetResult_Event * output)
{
  if (!input || !output) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // request
  if (!wx250s_interface__action__JointPTP_GetResult_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!wx250s_interface__action__JointPTP_GetResult_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

wx250s_interface__action__JointPTP_GetResult_Event *
wx250s_interface__action__JointPTP_GetResult_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wx250s_interface__action__JointPTP_GetResult_Event * msg = (wx250s_interface__action__JointPTP_GetResult_Event *)allocator.allocate(sizeof(wx250s_interface__action__JointPTP_GetResult_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(wx250s_interface__action__JointPTP_GetResult_Event));
  bool success = wx250s_interface__action__JointPTP_GetResult_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
wx250s_interface__action__JointPTP_GetResult_Event__destroy(wx250s_interface__action__JointPTP_GetResult_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    wx250s_interface__action__JointPTP_GetResult_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
wx250s_interface__action__JointPTP_GetResult_Event__Sequence__init(wx250s_interface__action__JointPTP_GetResult_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wx250s_interface__action__JointPTP_GetResult_Event * data = NULL;

  if (size) {
    data = (wx250s_interface__action__JointPTP_GetResult_Event *)allocator.zero_allocate(size, sizeof(wx250s_interface__action__JointPTP_GetResult_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = wx250s_interface__action__JointPTP_GetResult_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        wx250s_interface__action__JointPTP_GetResult_Event__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
wx250s_interface__action__JointPTP_GetResult_Event__Sequence__fini(wx250s_interface__action__JointPTP_GetResult_Event__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      wx250s_interface__action__JointPTP_GetResult_Event__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

wx250s_interface__action__JointPTP_GetResult_Event__Sequence *
wx250s_interface__action__JointPTP_GetResult_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wx250s_interface__action__JointPTP_GetResult_Event__Sequence * array = (wx250s_interface__action__JointPTP_GetResult_Event__Sequence *)allocator.allocate(sizeof(wx250s_interface__action__JointPTP_GetResult_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = wx250s_interface__action__JointPTP_GetResult_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
wx250s_interface__action__JointPTP_GetResult_Event__Sequence__destroy(wx250s_interface__action__JointPTP_GetResult_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    wx250s_interface__action__JointPTP_GetResult_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
wx250s_interface__action__JointPTP_GetResult_Event__Sequence__are_equal(const wx250s_interface__action__JointPTP_GetResult_Event__Sequence * lhs, const wx250s_interface__action__JointPTP_GetResult_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!wx250s_interface__action__JointPTP_GetResult_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
wx250s_interface__action__JointPTP_GetResult_Event__Sequence__copy(
  const wx250s_interface__action__JointPTP_GetResult_Event__Sequence * input,
  wx250s_interface__action__JointPTP_GetResult_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(wx250s_interface__action__JointPTP_GetResult_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    wx250s_interface__action__JointPTP_GetResult_Event * data =
      (wx250s_interface__action__JointPTP_GetResult_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!wx250s_interface__action__JointPTP_GetResult_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          wx250s_interface__action__JointPTP_GetResult_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!wx250s_interface__action__JointPTP_GetResult_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `feedback`
// already included above
// #include "wx250s_interface/action/detail/joint_ptp__functions.h"

bool
wx250s_interface__action__JointPTP_FeedbackMessage__init(wx250s_interface__action__JointPTP_FeedbackMessage * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    wx250s_interface__action__JointPTP_FeedbackMessage__fini(msg);
    return false;
  }
  // feedback
  if (!wx250s_interface__action__JointPTP_Feedback__init(&msg->feedback)) {
    wx250s_interface__action__JointPTP_FeedbackMessage__fini(msg);
    return false;
  }
  return true;
}

void
wx250s_interface__action__JointPTP_FeedbackMessage__fini(wx250s_interface__action__JointPTP_FeedbackMessage * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // feedback
  wx250s_interface__action__JointPTP_Feedback__fini(&msg->feedback);
}

bool
wx250s_interface__action__JointPTP_FeedbackMessage__are_equal(const wx250s_interface__action__JointPTP_FeedbackMessage * lhs, const wx250s_interface__action__JointPTP_FeedbackMessage * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // feedback
  if (!wx250s_interface__action__JointPTP_Feedback__are_equal(
      &(lhs->feedback), &(rhs->feedback)))
  {
    return false;
  }
  return true;
}

bool
wx250s_interface__action__JointPTP_FeedbackMessage__copy(
  const wx250s_interface__action__JointPTP_FeedbackMessage * input,
  wx250s_interface__action__JointPTP_FeedbackMessage * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // feedback
  if (!wx250s_interface__action__JointPTP_Feedback__copy(
      &(input->feedback), &(output->feedback)))
  {
    return false;
  }
  return true;
}

wx250s_interface__action__JointPTP_FeedbackMessage *
wx250s_interface__action__JointPTP_FeedbackMessage__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wx250s_interface__action__JointPTP_FeedbackMessage * msg = (wx250s_interface__action__JointPTP_FeedbackMessage *)allocator.allocate(sizeof(wx250s_interface__action__JointPTP_FeedbackMessage), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(wx250s_interface__action__JointPTP_FeedbackMessage));
  bool success = wx250s_interface__action__JointPTP_FeedbackMessage__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
wx250s_interface__action__JointPTP_FeedbackMessage__destroy(wx250s_interface__action__JointPTP_FeedbackMessage * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    wx250s_interface__action__JointPTP_FeedbackMessage__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
wx250s_interface__action__JointPTP_FeedbackMessage__Sequence__init(wx250s_interface__action__JointPTP_FeedbackMessage__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wx250s_interface__action__JointPTP_FeedbackMessage * data = NULL;

  if (size) {
    data = (wx250s_interface__action__JointPTP_FeedbackMessage *)allocator.zero_allocate(size, sizeof(wx250s_interface__action__JointPTP_FeedbackMessage), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = wx250s_interface__action__JointPTP_FeedbackMessage__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        wx250s_interface__action__JointPTP_FeedbackMessage__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
wx250s_interface__action__JointPTP_FeedbackMessage__Sequence__fini(wx250s_interface__action__JointPTP_FeedbackMessage__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      wx250s_interface__action__JointPTP_FeedbackMessage__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

wx250s_interface__action__JointPTP_FeedbackMessage__Sequence *
wx250s_interface__action__JointPTP_FeedbackMessage__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wx250s_interface__action__JointPTP_FeedbackMessage__Sequence * array = (wx250s_interface__action__JointPTP_FeedbackMessage__Sequence *)allocator.allocate(sizeof(wx250s_interface__action__JointPTP_FeedbackMessage__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = wx250s_interface__action__JointPTP_FeedbackMessage__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
wx250s_interface__action__JointPTP_FeedbackMessage__Sequence__destroy(wx250s_interface__action__JointPTP_FeedbackMessage__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    wx250s_interface__action__JointPTP_FeedbackMessage__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
wx250s_interface__action__JointPTP_FeedbackMessage__Sequence__are_equal(const wx250s_interface__action__JointPTP_FeedbackMessage__Sequence * lhs, const wx250s_interface__action__JointPTP_FeedbackMessage__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!wx250s_interface__action__JointPTP_FeedbackMessage__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
wx250s_interface__action__JointPTP_FeedbackMessage__Sequence__copy(
  const wx250s_interface__action__JointPTP_FeedbackMessage__Sequence * input,
  wx250s_interface__action__JointPTP_FeedbackMessage__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(wx250s_interface__action__JointPTP_FeedbackMessage);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    wx250s_interface__action__JointPTP_FeedbackMessage * data =
      (wx250s_interface__action__JointPTP_FeedbackMessage *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!wx250s_interface__action__JointPTP_FeedbackMessage__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          wx250s_interface__action__JointPTP_FeedbackMessage__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!wx250s_interface__action__JointPTP_FeedbackMessage__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
