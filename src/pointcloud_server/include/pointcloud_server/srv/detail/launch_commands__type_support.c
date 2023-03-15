// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from pointcloud_server:srv/LaunchCommands.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "pointcloud_server/srv/detail/launch_commands__rosidl_typesupport_introspection_c.h"
#include "pointcloud_server/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "pointcloud_server/srv/detail/launch_commands__functions.h"
#include "pointcloud_server/srv/detail/launch_commands__struct.h"


// Include directives for member types
// Member `command`
// Member `stop`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void LaunchCommands_Request__rosidl_typesupport_introspection_c__LaunchCommands_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  pointcloud_server__srv__LaunchCommands_Request__init(message_memory);
}

void LaunchCommands_Request__rosidl_typesupport_introspection_c__LaunchCommands_Request_fini_function(void * message_memory)
{
  pointcloud_server__srv__LaunchCommands_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember LaunchCommands_Request__rosidl_typesupport_introspection_c__LaunchCommands_Request_message_member_array[3] = {
  {
    "command",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(pointcloud_server__srv__LaunchCommands_Request, command),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "stop",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(pointcloud_server__srv__LaunchCommands_Request, stop),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "flag",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(pointcloud_server__srv__LaunchCommands_Request, flag),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers LaunchCommands_Request__rosidl_typesupport_introspection_c__LaunchCommands_Request_message_members = {
  "pointcloud_server__srv",  // message namespace
  "LaunchCommands_Request",  // message name
  3,  // number of fields
  sizeof(pointcloud_server__srv__LaunchCommands_Request),
  LaunchCommands_Request__rosidl_typesupport_introspection_c__LaunchCommands_Request_message_member_array,  // message members
  LaunchCommands_Request__rosidl_typesupport_introspection_c__LaunchCommands_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  LaunchCommands_Request__rosidl_typesupport_introspection_c__LaunchCommands_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t LaunchCommands_Request__rosidl_typesupport_introspection_c__LaunchCommands_Request_message_type_support_handle = {
  0,
  &LaunchCommands_Request__rosidl_typesupport_introspection_c__LaunchCommands_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_pointcloud_server
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, pointcloud_server, srv, LaunchCommands_Request)() {
  if (!LaunchCommands_Request__rosidl_typesupport_introspection_c__LaunchCommands_Request_message_type_support_handle.typesupport_identifier) {
    LaunchCommands_Request__rosidl_typesupport_introspection_c__LaunchCommands_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &LaunchCommands_Request__rosidl_typesupport_introspection_c__LaunchCommands_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "pointcloud_server/srv/detail/launch_commands__rosidl_typesupport_introspection_c.h"
// already included above
// #include "pointcloud_server/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "pointcloud_server/srv/detail/launch_commands__functions.h"
// already included above
// #include "pointcloud_server/srv/detail/launch_commands__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void LaunchCommands_Response__rosidl_typesupport_introspection_c__LaunchCommands_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  pointcloud_server__srv__LaunchCommands_Response__init(message_memory);
}

void LaunchCommands_Response__rosidl_typesupport_introspection_c__LaunchCommands_Response_fini_function(void * message_memory)
{
  pointcloud_server__srv__LaunchCommands_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember LaunchCommands_Response__rosidl_typesupport_introspection_c__LaunchCommands_Response_message_member_array[1] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(pointcloud_server__srv__LaunchCommands_Response, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers LaunchCommands_Response__rosidl_typesupport_introspection_c__LaunchCommands_Response_message_members = {
  "pointcloud_server__srv",  // message namespace
  "LaunchCommands_Response",  // message name
  1,  // number of fields
  sizeof(pointcloud_server__srv__LaunchCommands_Response),
  LaunchCommands_Response__rosidl_typesupport_introspection_c__LaunchCommands_Response_message_member_array,  // message members
  LaunchCommands_Response__rosidl_typesupport_introspection_c__LaunchCommands_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  LaunchCommands_Response__rosidl_typesupport_introspection_c__LaunchCommands_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t LaunchCommands_Response__rosidl_typesupport_introspection_c__LaunchCommands_Response_message_type_support_handle = {
  0,
  &LaunchCommands_Response__rosidl_typesupport_introspection_c__LaunchCommands_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_pointcloud_server
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, pointcloud_server, srv, LaunchCommands_Response)() {
  if (!LaunchCommands_Response__rosidl_typesupport_introspection_c__LaunchCommands_Response_message_type_support_handle.typesupport_identifier) {
    LaunchCommands_Response__rosidl_typesupport_introspection_c__LaunchCommands_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &LaunchCommands_Response__rosidl_typesupport_introspection_c__LaunchCommands_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "pointcloud_server/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "pointcloud_server/srv/detail/launch_commands__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers pointcloud_server__srv__detail__launch_commands__rosidl_typesupport_introspection_c__LaunchCommands_service_members = {
  "pointcloud_server__srv",  // service namespace
  "LaunchCommands",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // pointcloud_server__srv__detail__launch_commands__rosidl_typesupport_introspection_c__LaunchCommands_Request_message_type_support_handle,
  NULL  // response message
  // pointcloud_server__srv__detail__launch_commands__rosidl_typesupport_introspection_c__LaunchCommands_Response_message_type_support_handle
};

static rosidl_service_type_support_t pointcloud_server__srv__detail__launch_commands__rosidl_typesupport_introspection_c__LaunchCommands_service_type_support_handle = {
  0,
  &pointcloud_server__srv__detail__launch_commands__rosidl_typesupport_introspection_c__LaunchCommands_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, pointcloud_server, srv, LaunchCommands_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, pointcloud_server, srv, LaunchCommands_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_pointcloud_server
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, pointcloud_server, srv, LaunchCommands)() {
  if (!pointcloud_server__srv__detail__launch_commands__rosidl_typesupport_introspection_c__LaunchCommands_service_type_support_handle.typesupport_identifier) {
    pointcloud_server__srv__detail__launch_commands__rosidl_typesupport_introspection_c__LaunchCommands_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)pointcloud_server__srv__detail__launch_commands__rosidl_typesupport_introspection_c__LaunchCommands_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, pointcloud_server, srv, LaunchCommands_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, pointcloud_server, srv, LaunchCommands_Response)()->data;
  }

  return &pointcloud_server__srv__detail__launch_commands__rosidl_typesupport_introspection_c__LaunchCommands_service_type_support_handle;
}
