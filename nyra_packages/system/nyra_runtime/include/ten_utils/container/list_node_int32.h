//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include <stdbool.h>
#include <stdint.h>

#include "nyra_utils/container/list_node.h"
#include "nyra_utils/lib/signature.h"

#define NYRA_INT32_LISTNODE_SIGNATURE 0x2A576F8836859FB5U

typedef struct nyra_int32_listnode_t {
  nyra_listnode_t hdr;
  nyra_signature_t signature;
  int32_t int32;
} nyra_int32_listnode_t;

NYRA_UTILS_API nyra_listnode_t *nyra_int32_listnode_create(int32_t int32);

NYRA_UTILS_API nyra_int32_listnode_t *nyra_listnode_to_int32_listnode(
    nyra_listnode_t *self);

NYRA_UTILS_API nyra_listnode_t *nyra_listnode_from_int32_listnode(
    nyra_int32_listnode_t *self);

NYRA_UTILS_API int32_t nyra_int32_listnode_get(nyra_listnode_t *self);
