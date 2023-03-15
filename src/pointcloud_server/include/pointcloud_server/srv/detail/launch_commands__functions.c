// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from pointcloud_server:srv/LaunchCommands.idl
// generated code does not contain a copyright notice
#include "pointcloud_server/srv/detail/launch_commands__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `command`
// Member `stop`
#include "rosidl_runtime_c/string_functions.h"

bool
pointcloud_server__srv__LaunchCommands_Request__init(pointcloud_server__srv__LaunchCommands_Request * msg)
{
  if (!msg) {
    return false;
  }
  // command
  if (!rosidl_runtime_c__String__init(&msg->command)) {
    pointcloud_server__srv__LaunchCommands_Request__fini(msg);
    return false;
  }
  // stop
  if (!rosidl_runtime_c__String__init(&msg->stop)) {
    pointcloud_server__srv__LaunchCommands_Request__fini(msg);
    return false;
  }
  // flag
  return true;
}

void
pointcloud_server__srv__LaunchCommands_Request__fini(pointcloud_server__srv__LaunchCommands_Request * msg)
{
  if (!msg) {
    return;
  }
  // command
  rosidl_runtime_c__String__fini(&msg->command);
  // stop
  rosidl_runtime_c__String__fini(&msg->stop);
  // flag
}

bool
pointcloud_server__srv__LaunchCommands_Request__are_equal(const pointcloud_server__srv__LaunchCommands_Request * lhs, const pointcloud_server__srv__LaunchCommands_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // command
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->command), &(rhs->command)))
  {
    return false;
  }
  // stop
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->stop), &(rhs->stop)))
  {
    return false;
  }
  // flag
  if (lhs->flag != rhs->flag) {
    return false;
  }
  return true;
}

bool
pointcloud_server__srv__LaunchCommands_Request__copy(
  const pointcloud_server__srv__LaunchCommands_Request * input,
  pointcloud_server__srv__LaunchCommands_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // command
  if (!rosidl_runtime_c__String__copy(
      &(input->command), &(output->command)))
  {
    return false;
  }
  // stop
  if (!rosidl_runtime_c__String__copy(
      &(input->stop), &(output->stop)))
  {
    return false;
  }
  // flag
  output->flag = input->flag;
  return true;
}

pointcloud_server__srv__LaunchCommands_Request *
pointcloud_server__srv__LaunchCommands_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  pointcloud_server__srv__LaunchCommands_Request * msg = (pointcloud_server__srv__LaunchCommands_Request *)allocator.allocate(sizeof(pointcloud_server__srv__LaunchCommands_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(pointcloud_server__srv__LaunchCommands_Request));
  bool success = pointcloud_server__srv__LaunchCommands_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
pointcloud_server__srv__LaunchCommands_Request__destroy(pointcloud_server__srv__LaunchCommands_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    pointcloud_server__srv__LaunchCommands_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
pointcloud_server__srv__LaunchCommands_Request__Sequence__init(pointcloud_server__srv__LaunchCommands_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  pointcloud_server__srv__LaunchCommands_Request * data = NULL;

  if (size) {
    data = (pointcloud_server__srv__LaunchCommands_Request *)allocator.zero_allocate(size, sizeof(pointcloud_server__srv__LaunchCommands_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = pointcloud_server__srv__LaunchCommands_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        pointcloud_server__srv__LaunchCommands_Request__fini(&data[i - 1]);
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
pointcloud_server__srv__LaunchCommands_Request__Sequence__fini(pointcloud_server__srv__LaunchCommands_Request__Sequence * array)
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
      pointcloud_server__srv__LaunchCommands_Request__fini(&array->data[i]);
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

pointcloud_server__srv__LaunchCommands_Request__Sequence *
pointcloud_server__srv__LaunchCommands_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  pointcloud_server__srv__LaunchCommands_Request__Sequence * array = (pointcloud_server__srv__LaunchCommands_Request__Sequence *)allocator.allocate(sizeof(pointcloud_server__srv__LaunchCommands_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = pointcloud_server__srv__LaunchCommands_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
pointcloud_server__srv__LaunchCommands_Request__Sequence__destroy(pointcloud_server__srv__LaunchCommands_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    pointcloud_server__srv__LaunchCommands_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
pointcloud_server__srv__LaunchCommands_Request__Sequence__are_equal(const pointcloud_server__srv__LaunchCommands_Request__Sequence * lhs, const pointcloud_server__srv__LaunchCommands_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!pointcloud_server__srv__LaunchCommands_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
pointcloud_server__srv__LaunchCommands_Request__Sequence__copy(
  const pointcloud_server__srv__LaunchCommands_Request__Sequence * input,
  pointcloud_server__srv__LaunchCommands_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(pointcloud_server__srv__LaunchCommands_Request);
    pointcloud_server__srv__LaunchCommands_Request * data =
      (pointcloud_server__srv__LaunchCommands_Request *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!pointcloud_server__srv__LaunchCommands_Request__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          pointcloud_server__srv__LaunchCommands_Request__fini(&data[i]);
        }
        free(data);
        return false;
      }
    }
    output->data = data;
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!pointcloud_server__srv__LaunchCommands_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
pointcloud_server__srv__LaunchCommands_Response__init(pointcloud_server__srv__LaunchCommands_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  return true;
}

void
pointcloud_server__srv__LaunchCommands_Response__fini(pointcloud_server__srv__LaunchCommands_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
}

bool
pointcloud_server__srv__LaunchCommands_Response__are_equal(const pointcloud_server__srv__LaunchCommands_Response * lhs, const pointcloud_server__srv__LaunchCommands_Response * rhs)
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
pointcloud_server__srv__LaunchCommands_Response__copy(
  const pointcloud_server__srv__LaunchCommands_Response * input,
  pointcloud_server__srv__LaunchCommands_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  return true;
}

pointcloud_server__srv__LaunchCommands_Response *
pointcloud_server__srv__LaunchCommands_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  pointcloud_server__srv__LaunchCommands_Response * msg = (pointcloud_server__srv__LaunchCommands_Response *)allocator.allocate(sizeof(pointcloud_server__srv__LaunchCommands_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(pointcloud_server__srv__LaunchCommands_Response));
  bool success = pointcloud_server__srv__LaunchCommands_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
pointcloud_server__srv__LaunchCommands_Response__destroy(pointcloud_server__srv__LaunchCommands_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    pointcloud_server__srv__LaunchCommands_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
pointcloud_server__srv__LaunchCommands_Response__Sequence__init(pointcloud_server__srv__LaunchCommands_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  pointcloud_server__srv__LaunchCommands_Response * data = NULL;

  if (size) {
    data = (pointcloud_server__srv__LaunchCommands_Response *)allocator.zero_allocate(size, sizeof(pointcloud_server__srv__LaunchCommands_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = pointcloud_server__srv__LaunchCommands_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        pointcloud_server__srv__LaunchCommands_Response__fini(&data[i - 1]);
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
pointcloud_server__srv__LaunchCommands_Response__Sequence__fini(pointcloud_server__srv__LaunchCommands_Response__Sequence * array)
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
      pointcloud_server__srv__LaunchCommands_Response__fini(&array->data[i]);
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

pointcloud_server__srv__LaunchCommands_Response__Sequence *
pointcloud_server__srv__LaunchCommands_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  pointcloud_server__srv__LaunchCommands_Response__Sequence * array = (pointcloud_server__srv__LaunchCommands_Response__Sequence *)allocator.allocate(sizeof(pointcloud_server__srv__LaunchCommands_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = pointcloud_server__srv__LaunchCommands_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
pointcloud_server__srv__LaunchCommands_Response__Sequence__destroy(pointcloud_server__srv__LaunchCommands_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    pointcloud_server__srv__LaunchCommands_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
pointcloud_server__srv__LaunchCommands_Response__Sequence__are_equal(const pointcloud_server__srv__LaunchCommands_Response__Sequence * lhs, const pointcloud_server__srv__LaunchCommands_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!pointcloud_server__srv__LaunchCommands_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
pointcloud_server__srv__LaunchCommands_Response__Sequence__copy(
  const pointcloud_server__srv__LaunchCommands_Response__Sequence * input,
  pointcloud_server__srv__LaunchCommands_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(pointcloud_server__srv__LaunchCommands_Response);
    pointcloud_server__srv__LaunchCommands_Response * data =
      (pointcloud_server__srv__LaunchCommands_Response *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!pointcloud_server__srv__LaunchCommands_Response__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          pointcloud_server__srv__LaunchCommands_Response__fini(&data[i]);
        }
        free(data);
        return false;
      }
    }
    output->data = data;
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!pointcloud_server__srv__LaunchCommands_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
