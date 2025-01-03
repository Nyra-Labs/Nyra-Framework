//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include <stdbool.h>

#include "nyra_utils/lib/signature.h"
#include "nyra_utils/lib/thread.h"

#define NYRA_SANITIZER_THREAD_CHECK_SIGNATURE 0x6204388773560E59U

typedef struct nyra_sanitizer_thread_check_t {
  nyra_signature_t signature;

  nyra_thread_t *belonging_thread;
  bool is_fake;
} nyra_sanitizer_thread_check_t;

NYRA_UTILS_PRIVATE_API bool nyra_sanitizer_thread_check_check_integrity(
    nyra_sanitizer_thread_check_t *self);

NYRA_UTILS_API void nyra_sanitizer_thread_check_init_with_current_thread(
    nyra_sanitizer_thread_check_t *self);

NYRA_UTILS_API void nyra_sanitizer_thread_check_init_from(
    nyra_sanitizer_thread_check_t *self, nyra_sanitizer_thread_check_t *other);

NYRA_UTILS_API nyra_thread_t *nyra_sanitizer_thread_check_get_belonging_thread(
    nyra_sanitizer_thread_check_t *self);

NYRA_UTILS_API void nyra_sanitizer_thread_check_set_belonging_thread(
    nyra_sanitizer_thread_check_t *self, nyra_thread_t *thread);

NYRA_UTILS_API void
nyra_sanitizer_thread_check_set_belonging_thread_to_current_thread(
    nyra_sanitizer_thread_check_t *self);

NYRA_UTILS_API void nyra_sanitizer_thread_check_inherit_from(
    nyra_sanitizer_thread_check_t *self, nyra_sanitizer_thread_check_t *from);

NYRA_UTILS_API bool nyra_sanitizer_thread_check_do_check(
    nyra_sanitizer_thread_check_t *self);

NYRA_UTILS_API void nyra_sanitizer_thread_check_deinit(
    nyra_sanitizer_thread_check_t *self);
