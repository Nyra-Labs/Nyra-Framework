//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include "nyra_utils/container/list.h"
#include "nyra_utils/lib/mutex.h"
#include "nyra_utils/lib/string.h"

// As the source files are compiled in `out/<os>/<cpu>`, the `__FILE__`
// will be a relative path starts with '../../../'.
#define NYRA_FILE_PATH_RELATIVE_PREFIX_LENGTH 9

typedef struct nyra_sanitizer_memory_record_t {
  void *addr;
  size_t size;

  // Do not use `nyra_string_t` here to avoid a circular dependency between
  // `nyra_string_t` and `nyra_malloc`.
  char *func_name;
  char *file_name;

  uint32_t lineno;
} nyra_sanitizer_memory_record_t;

typedef struct nyra_sanitizer_memory_records_t {
  nyra_mutex_t *lock;
  nyra_list_t records;  // nyra_sanitizer_memory_record_t
  size_t total_size;
} nyra_sanitizer_memory_records_t;

NYRA_UTILS_API void nyra_sanitizer_memory_record_init(void);

NYRA_UTILS_API void nyra_sanitizer_memory_record_deinit(void);

NYRA_UTILS_API void nyra_sanitizer_memory_record_dump(void);

/**
 * @brief Malloc and record memory info.
 * @see NYRA_MALLOC
 * @note Please free memory using nyra_sanitizer_memory_free().
 */
NYRA_UTILS_API void *nyra_sanitizer_memory_malloc(size_t size,
                                                const char *file_name,
                                                uint32_t lineno,
                                                const char *func_name);

NYRA_UTILS_API void *nyra_sanitizer_memory_calloc(size_t cnt, size_t size,
                                                const char *file_name,
                                                uint32_t lineno,
                                                const char *func_name);

/**
 * @brief Free memory and remove the record.
 * @see nyra_free
 */
NYRA_UTILS_API void nyra_sanitizer_memory_free(void *address);

/**
 * @brief Realloc memory and record memory info.
 * @see nyra_realloc
 * @note Please free memory using nyra_sanitizer_memory_free().
 */
NYRA_UTILS_API void *nyra_sanitizer_memory_realloc(void *addr, size_t size,
                                                 const char *file_name,
                                                 uint32_t lineno,
                                                 const char *func_name);

/**
 * @brief Duplicate string and record memory info.
 * @see nyra_strdup
 * @note Please free memory using nyra_sanitizer_memory_free().
 */
NYRA_UTILS_API char *nyra_sanitizer_memory_strdup(const char *str,
                                                const char *file_name,
                                                uint32_t lineno,
                                                const char *func_name);
