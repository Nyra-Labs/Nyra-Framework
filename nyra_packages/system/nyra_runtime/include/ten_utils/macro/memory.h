//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include "nyra_utils/lib/alloc.h"
#include "nyra_utils/sanitizer/memory_check.h"  // IWYU pragma: keep

#if defined(NYRA_ENABLE_MEMORY_CHECK)

#define NYRA_MALLOC(size) \
  nyra_sanitizer_memory_malloc((size), __FILE__, __LINE__, __FUNCTION__)

#define NYRA_CALLOC(cnt, size) \
  nyra_sanitizer_memory_calloc((cnt), (size), __FILE__, __LINE__, __FUNCTION__)

#define NYRA_FREE(address)                         \
  do {                                            \
    nyra_sanitizer_memory_free((void *)(address)); \
    address = NULL;                               \
  } while (0)

#define NYRA_FREE_(address)                        \
  do {                                            \
    nyra_sanitizer_memory_free((void *)(address)); \
  } while (0)

#define NYRA_REALLOC(address, size)                                    \
  nyra_sanitizer_memory_realloc((address), (size), __FILE__, __LINE__, \
                               __FUNCTION__)

#define NYRA_STRDUP(str) \
  nyra_sanitizer_memory_strdup((str), __FILE__, __LINE__, __FUNCTION__)

#else

#define NYRA_MALLOC(size) nyra_malloc((size))

#define NYRA_CALLOC(cnt, size) nyra_calloc((cnt), (size))

#define NYRA_FREE(address)        \
  do {                           \
    nyra_free((void *)(address)); \
    address = NULL;              \
  } while (0)

#define NYRA_FREE_(address)       \
  do {                           \
    nyra_free((void *)(address)); \
  } while (0)

#define NYRA_REALLOC(address, size) nyra_realloc((address), (size))

#define NYRA_STRDUP(str) nyra_strdup((str))

#endif
