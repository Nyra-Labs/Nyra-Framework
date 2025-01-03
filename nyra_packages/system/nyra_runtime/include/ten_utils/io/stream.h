//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once
#include "nyra_utils/nyra_config.h"

#include <stdbool.h>
#include <stdint.h>

#include "nyra_utils/io/runloop.h"
#include "nyra_utils/lib/atomic.h"
#include "nyra_utils/lib/signature.h"

#define NYRA_STREAM_SIGNATURE 0xDE552052E7F8EE10U
#define NYRA_STREAM_DEFAULT_BUF_SIZE (64 * 1024)

typedef struct nyra_stream_t nyra_stream_t;
typedef struct nyra_transport_t nyra_transport_t;
typedef struct nyra_streambackend_t nyra_streambackend_t;

struct nyra_stream_t {
  nyra_signature_t signature;
  nyra_atomic_t close;

  nyra_transport_t *transport;
  nyra_streambackend_t *backend;

  void *user_data;

  void (*on_message_read)(nyra_stream_t *stream, void *msg, int size);
  void (*on_message_sent)(nyra_stream_t *stream, int status, void *args);
  void (*on_message_free)(nyra_stream_t *stream, int status, void *args);

  void (*on_closed)(void *on_closed_data);
  void *on_closed_data;
};

// Public interface
/**
 * @brief Begin read from stream.
 * @param self The stream to read from.
 * @return 0 if success, otherwise -1.
 */
NYRA_UTILS_API int nyra_stream_start_read(nyra_stream_t *self);

/**
 * @brief Stop read from stream.
 * @param self The stream to read from.
 * @return 0 if success, otherwise -1.
 */
NYRA_UTILS_API int nyra_stream_stop_read(nyra_stream_t *self);

/**
 * @brief Send a message to stream.
 * @param self The stream to send to.
 * @param msg The message to send.
 * @param size The size of message.
 * @return 0 if success, otherwise -1.
 */
NYRA_UTILS_API int nyra_stream_send(nyra_stream_t *self, const char *msg,
                                  uint32_t size, void *user_data);

/**
 * @brief Close the stream.
 * @param self The stream to close.
 */
NYRA_UTILS_API void nyra_stream_close(nyra_stream_t *self);

/**
 * @brief Set close callback for stream.
 * @param self The stream to set close callback for.
 * @param close_cb The callback to set.
 * @param close_cb_data The args of |close_cb| when it's been called
 */
NYRA_UTILS_API void nyra_stream_set_on_closed(nyra_stream_t *self, void *on_closed,
                                            void *on_closed_data);

/**
 * @brief Migrate a stream from one runloop to another.
 *
 * @param self The stream to migrate
 * @param from The runloop to migrate from
 * @param to The runloop to migrate to
 * @param user_data The user data to be passed to the callback
 * @param cb The callback to be called when the migration is done
 *
 * @return 0 on success, -1 on failure
 *
 * @note 1. |cb| will be called in |to| loop thread if success
 *       2. |from| and |to| have to be the same implementation type
 *          (e.g.event2, uv, etc.)
 *       3. |self| will be removed from |from| loop and no more data
 *          will be read from it
 */
NYRA_UTILS_API int nyra_stream_migrate(nyra_stream_t *self, nyra_runloop_t *from,
                                     nyra_runloop_t *to, void **user_data,
                                     void (*cb)(nyra_stream_t *new_stream,
                                                void **user_data));

NYRA_UTILS_API bool nyra_stream_check_integrity(nyra_stream_t *self);

NYRA_UTILS_API void nyra_stream_init(nyra_stream_t *self);

NYRA_UTILS_API void nyra_stream_on_close(nyra_stream_t *self);
