//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_runtime/nyra_config.h"

#include <stdint.h>

#include "nyra_utils/container/list.h"
#include "nyra_utils/value/value.h"

typedef struct nyra_extension_t nyra_extension_t;
typedef struct nyra_error_t nyra_error_t;
typedef struct nyra_msg_t nyra_msg_t;

// NYRA runtime supports 2 kinds of message mapping.
//
// > 1-to-1
//   Apply for : all messages.
//   This is the normal message mapping. The message will be transmitted to
//   the next node in the graph for non-status-command message, and to the
//   previous node in the graph for status-command message.
//
// > 1-to-N (when a message leaves an extension)
//   Apply for : all messages.
//   This can be declared in 'dests' in the graph declaration. The message
//   will be cloned to N copies, and sent to the N destinations.

// Note: To achieve the best compatibility, any new enum item, whether it is
// cmd/data/video_frame/audio_frame, should be added to the end to avoid
// changing the value of previous enum items.
typedef enum NYRA_MSG_TYPE {
  NYRA_MSG_TYPE_INVALID,
  NYRA_MSG_TYPE_CMD,
  NYRA_MSG_TYPE_CMD_RESULT,
  NYRA_MSG_TYPE_CMD_CLOSE_APP,
  NYRA_MSG_TYPE_CMD_START_GRAPH,
  NYRA_MSG_TYPE_CMD_STOP_GRAPH,
  NYRA_MSG_TYPE_CMD_TIMER,
  NYRA_MSG_TYPE_CMD_TIMEOUT,
  NYRA_MSG_TYPE_DATA,
  NYRA_MSG_TYPE_VIDEO_FRAME,
  NYRA_MSG_TYPE_AUDIO_FRAME,
  NYRA_MSG_TYPE_LAST,
} NYRA_MSG_TYPE;

/**
 * @brief The "clone" function of a command _does_ generate a new command ID.
 */
NYRA_RUNTIME_API nyra_shared_ptr_t *nyra_msg_clone(nyra_shared_ptr_t *self,
                                                nyra_list_t *excluded_field_ids);

NYRA_RUNTIME_API bool nyra_msg_is_property_exist(nyra_shared_ptr_t *self,
                                               const char *path,
                                               nyra_error_t *err);

/**
 * @brief Note that the ownership of @a value_kv would be transferred into
 * the NYRA runtime, so the caller of this function could _not_ consider the
 * value_kv instance is still valid.
 */
NYRA_RUNTIME_API bool nyra_msg_set_property(nyra_shared_ptr_t *self,
                                          const char *path, nyra_value_t *value,
                                          nyra_error_t *err);

// Because each NYRA extension has its own messages (in almost all cases, except
// for the data-type messages), so the returned value_kv of this function is
// from the message directly, not a cloned one.
NYRA_RUNTIME_API nyra_value_t *nyra_msg_peek_property(nyra_shared_ptr_t *self,
                                                   const char *path,
                                                   nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_msg_clear_and_set_dest(
    nyra_shared_ptr_t *self, const char *app_uri, const char *graph_id,
    const char *extension_group_name, const char *extension_name,
    nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_msg_from_json(nyra_shared_ptr_t *self, nyra_json_t *json,
                                       nyra_error_t *err);

NYRA_RUNTIME_API nyra_json_t *nyra_msg_to_json(nyra_shared_ptr_t *self,
                                            nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_msg_add_locked_res_buf(nyra_shared_ptr_t *self,
                                                const uint8_t *data,
                                                nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_msg_remove_locked_res_buf(nyra_shared_ptr_t *self,
                                                   const uint8_t *data,
                                                   nyra_error_t *err);

NYRA_RUNTIME_API const char *nyra_msg_get_name(nyra_shared_ptr_t *self);

NYRA_RUNTIME_API NYRA_MSG_TYPE nyra_msg_get_type(nyra_shared_ptr_t *self);

NYRA_RUNTIME_API bool nyra_msg_set_name(nyra_shared_ptr_t *self,
                                      const char *msg_name, nyra_error_t *err);
