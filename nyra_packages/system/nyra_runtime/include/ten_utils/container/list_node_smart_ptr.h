//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include <stdbool.h>

#include "nyra_utils/container/list_node.h"
#include "nyra_utils/lib/signature.h"
#include "nyra_utils/lib/smart_ptr.h"

#define NYRA_SMART_PTR_LISTNODE_SIGNATURE 0x00C0ADEEF6B9A421U

typedef struct nyra_smart_ptr_listnode_t {
  nyra_listnode_t hdr;
  nyra_signature_t signature;
  nyra_smart_ptr_t *ptr;
} nyra_smart_ptr_listnode_t;

NYRA_UTILS_API nyra_listnode_t *nyra_smart_ptr_listnode_create(
    nyra_smart_ptr_t *ptr);

NYRA_UTILS_API nyra_smart_ptr_listnode_t *nyra_listnode_to_smart_ptr_listnode(
    nyra_listnode_t *self);

NYRA_UTILS_API nyra_listnode_t *nyra_listnode_from_smart_ptr_listnode(
    nyra_smart_ptr_listnode_t *self);

NYRA_UTILS_API nyra_smart_ptr_t *nyra_smart_ptr_listnode_get(nyra_listnode_t *self);
