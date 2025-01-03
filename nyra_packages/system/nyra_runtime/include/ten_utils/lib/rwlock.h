//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

/**
 * Reader-writer lock
 *
 * Keep in mind that RW lock is more expensive than mutex even in reader side
 *
 * The case you want an RW lock is that you need several readers working at the
 * same time. If you want a "faster-reader-side-locks", consider RCU
 *
 * Windows Slim Reader/Writer (SRW) lock is neither phase fair nor task fair.
 * Noticed that SRW lock may faster than this implementation (because of no
 * fairness), but we are not going to use it
 *
 * Darwin pthread_mutex is task fair with dramatically performance drops, we
 * have to give up fairness from pthread_mutex and grant it in rwlock by
 * ourselves if we use mutex-condition flavor implementation (which is also done
 * by Darwin pthread_rwlock_t). But here we use atomic-spin flavor, which is
 * faster than Darwin pthread_rwlock_t .
 *
 * Fairness of posix pthread_rwlock is depends on implementation. Generally
 * speaking it's task fair with some kind of preference on readers.
 * Comments from Oracle:
 *    If there are multiple threads waiting to acquire the read-write
 *    lock object for reading, the scheduling policy is used to determine the
 *    order in which the waiting threads acquire the read-write lock object for
 *    reading. If there are multiple threads blocked on rwlock for both read
 *    locks and write locks, it is unspecified whether the readers acquire the
 *    lock first or whether a writer acquires the lock first.
 * As a result of testing, Linux pthread_rwlock_t will re-balance fairness and
 * performance when switching between heavy contention and light contention,
 * which is really good. But we still use our own implementation because
 * (usually) we need phase fair.
 *
 * Here is the performance and fairness matrix
 * (y means better than native)
 * (x means worse than native)
 * (e means almost same as native)
 *
 * --------------------------------------------------
 *             | Linux  |  Darwin  |  Windows
 * performance |   e    |    yy    |   e
 * Fairness    |   y    |    y     |   yy
 * --------------------------------------------------
 */

typedef enum NYRA_RW_FAIRNESS {
  NYRA_RW_NATIVE,
  NYRA_RW_PHASE_FAIR,
} NYRA_RW_FAIRNESS;

#define NYRA_RW_DEFAULT_FAIRNESS NYRA_RW_PHASE_FAIR

typedef struct nyra_rwlock_t nyra_rwlock_t;

/**
 * @brief Create a reader-writer lock
 * @param fairness The fairness flavor of the lock
 * @return The reader-writer lock
 */
NYRA_UTILS_API nyra_rwlock_t *nyra_rwlock_create(NYRA_RW_FAIRNESS fair);

/**
 * @brief Destroy a reader-writer lock
 * @param lock The reader-writer lock
 */
NYRA_UTILS_API void nyra_rwlock_destroy(nyra_rwlock_t *lock);

/**
 * @brief Acquire a reader-writer lock
 * @param lock The reader-writer lock
 * @param reader Whether it is a read lock
 */
NYRA_UTILS_API int nyra_rwlock_lock(nyra_rwlock_t *lock, int reader);

/**
 * @brief Release a reader-writer lock
 * @param lock The reader-writer lock
 * @param reader Whether it is a read lock
 */
NYRA_UTILS_API int nyra_rwlock_unlock(nyra_rwlock_t *lock, int reader);
