//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include <assert.h>
#include <stdio.h>   // IWYU pragma: keep
#include <stdlib.h>  // IWYU pragma: keep

#include "nyra_utils/backtrace/backtrace.h"  // IWYU pragma: keep

#if defined(__has_feature)
#if __has_feature(address_sanitizer)
#define NYRA_USE_ASAN
#endif
#endif

#if defined(__SANITIZE_ADDRESS__)
#define NYRA_USE_ASAN
#endif

#if defined(NYRA_PRODUCTION)

// Remove all protections in the final production release.

#define NYRA_ASSERT(expr, fmt, ...) \
  do {                             \
  } while (0)

#else  // NYRA_PRODUCTION

// NYRA_ASSERT is used within `nyra_string_t`, so do not use `nyra_string_t` inside
// `NYRA_ASSERT` to avoid circular dependencies.
//
// This size should not be too large; otherwise, it may cause a stack overflow
// in the deep call chain.
#define ASSERT_ERR_MSG_MAX_LENGTH 128

#ifndef NDEBUG

#define NYRA_ASSERT(expr, fmt, ...)                                        \
  do {                                                                    \
    /* NOLINTNEXTLINE */                                                  \
    if (!(expr)) {                                                        \
      /* NOLINTNEXTLINE */                                                \
      char ____err_msg[ASSERT_ERR_MSG_MAX_LENGTH];                        \
      int written =                                                       \
          snprintf(____err_msg, sizeof(____err_msg), fmt, ##__VA_ARGS__); \
      assert(written > 0);                                                \
      written = fprintf(stderr, "%s\n", ____err_msg);                     \
      assert(written > 0);                                                \
      nyra_backtrace_dump_global(0);                                       \
      /* NOLINTNEXTLINE */                                                \
      assert(0);                                                          \
    }                                                                     \
  } while (0)

#else  // NDEBUG

// Enable minimal protection if the optimization is enabled.

#define NYRA_ASSERT(expr, fmt, ...)                                        \
  do {                                                                    \
    /* NOLINTNEXTLINE */                                                  \
    if (!(expr)) {                                                        \
      /* NOLINTNEXTLINE */                                                \
      char ____err_msg[ASSERT_ERR_MSG_MAX_LENGTH];                        \
      int written =                                                       \
          snprintf(____err_msg, sizeof(____err_msg), fmt, ##__VA_ARGS__); \
      if (written <= 0) {                                                 \
        abort();                                                          \
      }                                                                   \
      written = fprintf(stderr, "%s\n", ____err_msg);                     \
      if (written <= 0) {                                                 \
        abort();                                                          \
      }                                                                   \
      nyra_backtrace_dump_global(0);                                       \
      /* NOLINTNEXTLINE */                                                \
      abort();                                                            \
    }                                                                     \
  } while (0)

#endif  // NDEBUG

#endif  // NYRA_PRODUCTION
