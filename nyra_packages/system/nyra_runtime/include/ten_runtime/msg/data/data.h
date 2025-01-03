//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_runtime/nyra_config.h"

#include <stddef.h>

#include "nyra_utils/lib/buf.h"
#include "nyra_utils/lib/error.h"
#include "nyra_utils/lib/smart_ptr.h"

typedef struct nyra_data_t nyra_data_t;

NYRA_RUNTIME_API nyra_shared_ptr_t *nyra_data_create(const char *name,
                                                  nyra_error_t *err);

NYRA_RUNTIME_API nyra_buf_t *nyra_data_peek_buf(nyra_shared_ptr_t *self);

NYRA_RUNTIME_API void nyra_data_set_buf_with_move(nyra_shared_ptr_t *self,
                                                nyra_buf_t *buf);

NYRA_RUNTIME_API uint8_t *nyra_data_alloc_buf(nyra_shared_ptr_t *self,
                                            size_t size);
