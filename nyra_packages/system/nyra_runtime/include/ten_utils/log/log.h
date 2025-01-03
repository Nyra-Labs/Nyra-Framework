//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

#include "nyra_utils/lib/signature.h"

#define NYRA_LOGV(...)                                                       \
  do {                                                                      \
    nyra_log_log_formatted(&nyra_global_log, NYRA_LOG_LEVEL_VERBOSE, __func__, \
                          __FILE__, __LINE__, __VA_ARGS__);                 \
  } while (0)

#define NYRA_LOGD(...)                                                     \
  do {                                                                    \
    nyra_log_log_formatted(&nyra_global_log, NYRA_LOG_LEVEL_DEBUG, __func__, \
                          __FILE__, __LINE__, __VA_ARGS__);               \
  } while (0)

#define NYRA_LOGI(...)                                                    \
  do {                                                                   \
    nyra_log_log_formatted(&nyra_global_log, NYRA_LOG_LEVEL_INFO, __func__, \
                          __FILE__, __LINE__, __VA_ARGS__);              \
  } while (0)

#define NYRA_LOGW(...)                                                    \
  do {                                                                   \
    nyra_log_log_formatted(&nyra_global_log, NYRA_LOG_LEVEL_WARN, __func__, \
                          __FILE__, __LINE__, __VA_ARGS__);              \
  } while (0)

#define NYRA_LOGE(...)                                                     \
  do {                                                                    \
    nyra_log_log_formatted(&nyra_global_log, NYRA_LOG_LEVEL_ERROR, __func__, \
                          __FILE__, __LINE__, __VA_ARGS__);               \
  } while (0)

#define NYRA_LOGF(...)                                                     \
  do {                                                                    \
    nyra_log_log_formatted(&nyra_global_log, NYRA_LOG_LEVEL_FATAL, __func__, \
                          __FILE__, __LINE__, __VA_ARGS__);               \
  } while (0)

#define NYRA_LOGV_AUX(log, ...)                                            \
  do {                                                                    \
    nyra_log_log_formatted(log, NYRA_LOG_LEVEL_VERBOSE, __func__, __FILE__, \
                          __LINE__, __VA_ARGS__);                         \
  } while (0)

#define NYRA_LOGD_AUX(log, ...)                                          \
  do {                                                                  \
    nyra_log_log_formatted(log, NYRA_LOG_LEVEL_DEBUG, __func__, __FILE__, \
                          __LINE__, __VA_ARGS__);                       \
  } while (0)

#define NYRA_LOGI_AUX(log, ...)                                         \
  do {                                                                 \
    nyra_log_log_formatted(log, NYRA_LOG_LEVEL_INFO, __func__, __FILE__, \
                          __LINE__, __VA_ARGS__);                      \
  } while (0)

#define NYRA_LOGW_AUX(log, ...)                                         \
  do {                                                                 \
    nyra_log_log_formatted(log, NYRA_LOG_LEVEL_WARN, __func__, __FILE__, \
                          __LINE__, __VA_ARGS__);                      \
  } while (0)

#define NYRA_LOGE_AUX(log, ...)                                          \
  do {                                                                  \
    nyra_log_log_formatted(log, NYRA_LOG_LEVEL_ERROR, __func__, __FILE__, \
                          __LINE__, __VA_ARGS__);                       \
  } while (0)

#define NYRA_LOGF_AUX(log, ...)                                          \
  do {                                                                  \
    nyra_log_log_formatted(log, NYRA_LOG_LEVEL_FATAL, __func__, __FILE__, \
                          __LINE__, __VA_ARGS__);                       \
  } while (0)

typedef enum NYRA_LOG_LEVEL {
  NYRA_LOG_LEVEL_INVALID,

  NYRA_LOG_LEVEL_VERBOSE,
  NYRA_LOG_LEVEL_DEBUG,
  NYRA_LOG_LEVEL_INFO,
  NYRA_LOG_LEVEL_WARN,
  NYRA_LOG_LEVEL_ERROR,
  NYRA_LOG_LEVEL_FATAL,
} NYRA_LOG_LEVEL;

typedef struct nyra_string_t nyra_string_t;

typedef void (*nyra_log_output_func_t)(nyra_string_t *msg, void *user_data);
typedef void (*nyra_log_close_func_t)(void *user_data);
typedef void (*nyra_log_formatter_func_t)(nyra_string_t *buf, NYRA_LOG_LEVEL level,
                                         const char *func_name,
                                         size_t func_name_len,
                                         const char *file_name,
                                         size_t file_name_len, size_t line_no,
                                         const char *msg, size_t msg_len);

typedef struct nyra_log_output_t {
  nyra_log_output_func_t output_cb;
  nyra_log_close_func_t close_cb;
  void *user_data;
} nyra_log_output_t;

typedef struct nyra_log_formatter_t {
  nyra_log_formatter_func_t format_cb;
  void *user_data;  // In case the formatter needs any user data
} nyra_log_formatter_t;

typedef struct nyra_log_t {
  nyra_signature_t signature;

  NYRA_LOG_LEVEL output_level;
  nyra_log_output_t output;

  nyra_log_formatter_t formatter;
} nyra_log_t;

NYRA_UTILS_API nyra_log_t nyra_global_log;

NYRA_UTILS_API void nyra_log_log_formatted(nyra_log_t *self, NYRA_LOG_LEVEL level,
                                         const char *func_name,
                                         const char *file_name, size_t line_no,
                                         const char *fmt, ...);
