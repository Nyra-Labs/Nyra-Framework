//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

typedef void *nyra_atomic_ptr_t;

NYRA_UTILS_API void *nyra_atomic_ptr_load(volatile nyra_atomic_ptr_t *a);

NYRA_UTILS_API void nyra_atomic_ptr_store(volatile nyra_atomic_ptr_t *a, void *v);
