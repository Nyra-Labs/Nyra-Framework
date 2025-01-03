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
#include "nyra_utils/lib/signature.h"
#include "nyra_utils/lib/string.h"
#include "nyra_utils/sanitizer/thread_check.h"

#define NYRA_ASYNC_SIGNATURE 0xD4CD6DEDB7906C26U

typedef struct nyra_async_t {
  nyra_signature_t signature;
  nyra_sanitizer_thread_check_t thread_check;

  nyra_string_t name;
  nyra_atomic_t close;

  nyra_runloop_t *loop;
  nyra_runloop_async_t *async;
  nyra_runloop_async_t *async_for_close;

  void (*on_trigger)(struct nyra_async_t *, void *);
  void *on_trigger_data;

  void (*on_closed)(struct nyra_async_t *, void *);
  void *on_closed_data;
} nyra_async_t;

NYRA_UTILS_API nyra_async_t *nyra_async_create(const char *name,
                                            nyra_runloop_t *loop,
                                            void *on_trigger,
                                            void *on_trigger_data);

NYRA_UTILS_API void nyra_async_set_on_closed(nyra_async_t *self, void *on_closed,
                                           void *on_closed_data);

NYRA_UTILS_API void nyra_async_trigger(nyra_async_t *self);

NYRA_UTILS_API void nyra_async_close(nyra_async_t *self);
