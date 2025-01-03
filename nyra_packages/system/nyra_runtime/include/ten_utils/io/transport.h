//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include "nyra_utils/io/runloop.h"
#include "nyra_utils/lib/atomic.h"
#include "nyra_utils/lib/mutex.h"

typedef struct nyra_transportbackend_t nyra_transportbackend_t;
typedef struct nyra_string_t nyra_string_t;
typedef struct nyra_stream_t nyra_stream_t;

typedef enum NYRA_TRANSPORT_DROP_TYPE {
  /* Drop oldest data when transport channel is full, only available when
     transport type is shm or raw pointer */
  NYRA_TRANSPORT_DROP_OLD,

  /* Drop current data when transport channel is full */
  NYRA_TRANSPORT_DROP_NEW,

  /* Drop current data if no reader is waiting */
  NYRA_TRANSPORT_DROP_IF_NO_READER,

  /* Drop current data by asking, only available when
     transport type is shm or raw pointer .
     Useful if user wan't to drop by bussiness logic (e.g. never drop I frame)
   */
  NYRA_TRANSPORT_DROP_ASK
} NYRA_TRANSPORT_DROP_TYPE;

typedef struct nyra_transport_t nyra_transport_t;

struct nyra_transport_t {
  /**
   * uv loop that attached to current thread
   */
  nyra_runloop_t *loop;

  void *user_data;

  nyra_transportbackend_t *backend;
  nyra_atomic_t close;

  nyra_mutex_t *lock;
  int drop_when_full;
  NYRA_TRANSPORT_DROP_TYPE drop_type;

  /**
   * Callback when a new rx stream is connected
   */
  void (*on_server_connected)(nyra_transport_t *transport, nyra_stream_t *stream,
                              int status);
  void *on_server_connected_data;

  /**
   * Callback when a new rx stream is created
   */
  void (*on_client_accepted)(nyra_transport_t *transport, nyra_stream_t *stream,
                             int status);
  void *on_client_accepted_data;

  /**
   * Callback when transport closed
   */
  void (*on_closed)(void *on_closed_data);
  void *on_closed_data;
};

// Public interface
NYRA_UTILS_API nyra_transport_t *nyra_transport_create(nyra_runloop_t *loop);

NYRA_UTILS_API int nyra_transport_close(nyra_transport_t *self);

NYRA_UTILS_API void nyra_transport_set_close_cb(nyra_transport_t *self,
                                              void *close_cb,
                                              void *close_cb_data);

NYRA_UTILS_API int nyra_transport_listen(nyra_transport_t *self,
                                       const nyra_string_t *my_uri);

NYRA_UTILS_API int nyra_transport_connect(nyra_transport_t *self,
                                        nyra_string_t *dest);
