//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include "nyra_utils/io/runloop.h"

typedef struct nyra_shm_channel_t nyra_shm_channel_t;

NYRA_UTILS_API int nyra_shm_channel_create(const char *name,
                                         nyra_shm_channel_t *channel[2]);

NYRA_UTILS_API void nyra_shm_channel_close(nyra_shm_channel_t *channel);

NYRA_UTILS_API int nyra_shm_channel_active(nyra_shm_channel_t *channel, int read);

NYRA_UTILS_API int nyra_shm_channel_inactive(nyra_shm_channel_t *channel,
                                           int read);

NYRA_UTILS_API int nyra_shm_channel_wait_remote(nyra_shm_channel_t *channel,
                                              int wait_ms);

NYRA_UTILS_API int nyra_shm_channel_send(nyra_shm_channel_t *channel, void *data,
                                       size_t size, int nonblock);

NYRA_UTILS_API int nyra_shm_channel_recv(nyra_shm_channel_t *channel, void *data,
                                       size_t size, int nonblock);

NYRA_UTILS_API int nyra_shm_channel_get_capacity(nyra_shm_channel_t *channel);

NYRA_UTILS_API int nyra_shm_channel_set_signal(nyra_shm_channel_t *channel,
                                             nyra_runloop_async_t *signal,
                                             int read);
