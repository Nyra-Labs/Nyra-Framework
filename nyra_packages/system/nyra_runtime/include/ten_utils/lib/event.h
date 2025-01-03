//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

typedef struct nyra_event_t nyra_event_t;

/**
 * @brief Create an event object.
 * @param init_state The initial state of the event object.
 * @param auto_reset Whether the event object will be automatically reset to
 *                   non-signaled state after it is waked up by another thread.
 * @return The event object.
 */
NYRA_UTILS_API nyra_event_t *nyra_event_create(int init_state, int auto_reset);

/**
 * @brief Wait for the event object to be signaled.
 * @param event The event object.
 * @param wait_ms The timeout in milliseconds.
 * @return 0 if the event object is signaled; otherwise, -1.
 */
NYRA_UTILS_API int nyra_event_wait(nyra_event_t *event, int wait_ms);

/**
 * @brief Set the event object to signaled state.
 * @param event The event object.
 */
NYRA_UTILS_API void nyra_event_set(nyra_event_t *event);

/**
 * @brief Reset the event object to non-signaled state.
 * @param event The event object.
 */
NYRA_UTILS_API void nyra_event_reset(nyra_event_t *event);

/**
 * @brief Destroy the event object.
 */
NYRA_UTILS_API void nyra_event_destroy(nyra_event_t *event);
