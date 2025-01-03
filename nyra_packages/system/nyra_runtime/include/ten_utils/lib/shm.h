//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include <stddef.h>

NYRA_UTILS_API void *nyra_shm_map(const char *name, size_t size);

NYRA_UTILS_API size_t nyra_shm_get_size(void *addr);

NYRA_UTILS_API void nyra_shm_unmap(void *addr);

NYRA_UTILS_API void nyra_shm_unlink(const char *name);
