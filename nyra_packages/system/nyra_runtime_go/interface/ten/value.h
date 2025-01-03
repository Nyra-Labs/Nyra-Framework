//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "common.h"

typedef struct nyra_value_t nyra_value_t;
typedef struct nyra_go_value_t nyra_go_value_t;

void nyra_go_value_finalize(nyra_go_value_t *self);

/**
 * @brief Destroy the nyra_value_t instance from GO.
 *
 * @param value_addr The bit pattern of the pointer to a nyra_value_t. Note that
 * there is no bridge for nyra_value_t.
 */
void nyra_go_value_destroy(uintptr_t value_addr);

// These functions are used in getting property from nyra_env_t. Refer to the
// comments in ten.h. Please keep in mind that the input nyra_vale_t* is cloned
// in the previous stage (refer to nyra_go_nyra_property_get_type_and_size), so it
// must be destroyed in these functions.

/**
 * @param value_addr The bit pattern of the pointer to a nyra_value_t. Note that
 * there is no bridge for nyra_value_t.
 */
nyra_go_error_t nyra_go_value_get_string(uintptr_t value_addr, void *value);

nyra_go_error_t nyra_go_value_get_buf(uintptr_t value_addr, void *value);
