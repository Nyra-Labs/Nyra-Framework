//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include <stdint.h>

#include "nyra_utils/lib/atomic.h"
#include "nyra_utils/lib/event.h"

typedef struct nyra_thread_t {
  void *(*routine)(void *);
  void *args;
  nyra_atomic_t id;
  nyra_event_t *ready;
  nyra_event_t *exit;
  const char *name;
  nyra_atomic_t detached;
  void *aux;
} nyra_thread_t;

typedef nyra_atomic_t nyra_tid_t;

/**
 * @brief Create a new thread.
 * @param name The name of the thread.
 * @param routine The routine of the thread.
 * @param args The arguments of the routine.
 * @return The thread object
 */
NYRA_UTILS_API nyra_thread_t *nyra_thread_create(const char *name,
                                              void *(*routine)(void *),
                                              void *args);

/**
 * @brief Suspend the thread.
 * @param thread The thread object to suspend.
 * @return 0 on success, -1 on error.
 */
NYRA_UTILS_API int nyra_thread_suspend(nyra_thread_t *thread);

/**
 * @brief Resume the thread.
 * @param thread The thread object to resume.
 * @return 0 on success, -1 on error.
 */
NYRA_UTILS_API int nyra_thread_resume(nyra_thread_t *thread);

/**
 * @brief Join the thread.
 * @param thread The thread object to join.
 * @param wait_ms The timeout in milliseconds.
 * @return 0 on success, -1 on error.
 * @note You can not join a detached thread, crash will happen if you do.
 */
NYRA_UTILS_API int nyra_thread_join(nyra_thread_t *thread, int wait_ms);

/**
 * @brief Detach the thread.
 * @param thread The thread object to detach.
 * @return 0 on success, -1 on error.
 * @note You can not detach a detached thread, crash will happen if you do.
 */
NYRA_UTILS_API int nyra_thread_detach(nyra_thread_t *thread);

/**
 * @brief Get the thread id.
 * @param thread The thread object.
 * @return The thread id.
 */
NYRA_UTILS_API nyra_tid_t nyra_thread_get_id(nyra_thread_t *thread);

/**
 * @brief Get current thread.
 * @return The current thread object.
 * @note Will return NULL if it is not created by |nyra_thread_create|
 */
NYRA_UTILS_API nyra_thread_t *nyra_thread_self();

/**
 * @brief Yield the thread.
 */
NYRA_UTILS_API void nyra_thread_yield();

/**
 * @brief Set the thread name.
 * @param thread The thread object.
 * @param name The name of the thread.
 * @return 0 on success, -1 on error.
 */
NYRA_UTILS_API int nyra_thread_set_name(nyra_thread_t *thread, const char *name);

/**
 * @brief Get the thread name.
 * @param thread The thread object, will return the current thread's if NULL.
 * @return The thread name.
 */
NYRA_UTILS_API const char *nyra_thread_get_name(nyra_thread_t *thread);

/**
 * @brief Let current CPU run into low power mode until interrupt.
 */
NYRA_UTILS_API void nyra_thread_pause_cpu();

/**
 * @brief Set thread affinity.
 * @param thread The thread object.
 * @param mask The affinity mask.
 * @note The mask is a bit mask of CPU id. For example, if you want to set the
 *       thread to run on CPU 0 and 2, the mask is 0x3.
 *       Currently only support 64 CPUs.
 */
NYRA_UTILS_API void nyra_thread_set_affinity(nyra_thread_t *thread, uint64_t mask);

/**
 * @brief Compare two threads.
 * @param thread The thread object to be compared
 * @param target The thread object to compare.
 * @return If the two thread are equal, it returns 1; otherwise, it returns 0.
 */
NYRA_UTILS_API int nyra_thread_equal(nyra_thread_t *thread, nyra_thread_t *target);

/**
 * @brief Compare the threads to the current thread.
 * @param thread The thread object to be compared
 * @return If the thread equals to the current thread, it returns 1; otherwise,
 * it returns 0.
 */
NYRA_UTILS_API int nyra_thread_equal_to_current_thread(nyra_thread_t *thread);

/**
 * @brief The current thread was not created by nyra_thread_create(). This
 * function is used to populate the nyra_thread_t with relevant information, but
 * it doesn't actually create a native thread.
 * @return The thread object
 */
NYRA_UTILS_API nyra_thread_t *nyra_thread_create_fake(const char *name);

/**
 * @brief Join the fake thread.
 * @param thread The fake thread object to join.
 * @return 0 on success, -1 on error.
 */
NYRA_UTILS_API int nyra_thread_join_fake(nyra_thread_t *thread);
