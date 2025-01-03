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

#include "nyra_utils/lib/signature.h"
#include "nyra_utils/lib/string.h"

typedef int64_t nyra_errno_t;

#define NYRA_ERROR_SIGNATURE 0xCA49E5F63FC43623U

// 0 is a special NYRA errno value, representing success/ok.
#define NYRA_ERRNO_OK 0

typedef struct nyra_error_t {
  nyra_signature_t signature;

  nyra_errno_t err_no;
  nyra_string_t err_msg;
} nyra_error_t;

NYRA_UTILS_API bool nyra_error_check_integrity(nyra_error_t *self);

NYRA_UTILS_API void nyra_error_init(nyra_error_t *self);

NYRA_UTILS_API void nyra_error_deinit(nyra_error_t *self);

NYRA_UTILS_API nyra_error_t *nyra_error_create(void);

NYRA_UTILS_API void nyra_error_copy(nyra_error_t *self, nyra_error_t *other);

// Set error info, return true if set success, false otherwise.
NYRA_UTILS_API bool nyra_error_set(nyra_error_t *self, nyra_errno_t err_no,
                                 const char *fmt, ...);

NYRA_UTILS_API bool nyra_error_vset(nyra_error_t *self, nyra_errno_t err_no,
                                  const char *fmt, va_list ap);

NYRA_UTILS_API bool nyra_error_prepend_errmsg(nyra_error_t *self, const char *fmt,
                                            ...);

NYRA_UTILS_API bool nyra_error_append_errmsg(nyra_error_t *self, const char *fmt,
                                           ...);

// Get last errno in current context, return NYRA_ERRNO_OK if no error set
// before.
NYRA_UTILS_API nyra_errno_t nyra_error_errno(nyra_error_t *self);

NYRA_UTILS_API const char *nyra_error_errmsg(nyra_error_t *self);

NYRA_UTILS_API void nyra_error_reset(nyra_error_t *self);

NYRA_UTILS_API void nyra_error_destroy(nyra_error_t *self);

NYRA_UTILS_API bool nyra_error_is_success(nyra_error_t *self);
