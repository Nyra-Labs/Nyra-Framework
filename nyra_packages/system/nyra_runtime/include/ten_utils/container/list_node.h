//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include <stdbool.h>

#include "nyra_utils/lib/signature.h"
#include "nyra_utils/lib/string.h"

#define NYRA_LISTNODE_SIGNATURE 0x00D7B10E642B105CU

typedef struct nyra_listnode_t nyra_listnode_t;
typedef struct nyra_list_t nyra_list_t;

struct nyra_listnode_t {
  nyra_signature_t signature;
  nyra_listnode_t *next, *prev;
  void (*destroy)(nyra_listnode_t *);
};

#include "nyra_utils/container/list_node_int32.h"      // IWYU pragma: keep
#include "nyra_utils/container/list_node_ptr.h"        // IWYU pragma: keep
#include "nyra_utils/container/list_node_smart_ptr.h"  // IWYU pragma: keep
#include "nyra_utils/container/list_node_str.h"        // IWYU pragma: keep

NYRA_UTILS_PRIVATE_API bool nyra_listnode_check_integrity(nyra_listnode_t *self);

NYRA_UTILS_PRIVATE_API void nyra_listnode_init(nyra_listnode_t *self,
                                             void *destroy);

NYRA_UTILS_API void nyra_listnode_destroy(nyra_listnode_t *self);
NYRA_UTILS_API void nyra_listnode_destroy_only(nyra_listnode_t *self);
