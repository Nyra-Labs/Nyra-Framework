//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_runtime/nyra_config.h"

#include "nyra_utils/lib/error.h"

// Define various error numbers here.
//
// Note: To achieve the best compatibility, any new enum item, should be added
// to the end to avoid changing the value of previous enum items.
typedef enum NYRA_ERRNO {
  // Generic errno.
  NYRA_ERRNO_GENERIC = 1,

  // Invalid json.
  NYRA_ERRNO_INVALID_JSON = 2,

  // Invalid argument.
  NYRA_ERRNO_INVALID_ARGUMENT = 3,

  // Invalid type.
  NYRA_ERRNO_INVALID_TYPE = 4,

  // Invalid graph.
  NYRA_ERRNO_INVALID_GRAPH = 5,

  // The NYRA world is closed.
  NYRA_ERRNO_NYRA_IS_CLOSED = 6,

  // The msg is not connected in the graph.
  NYRA_ERRNO_MSG_NOT_CONNECTED = 7,
} NYRA_ERRNO;

static_assert(
    sizeof(NYRA_ERRNO) <= sizeof(nyra_errno_t),
    "The size of field NYRA_ERRNO enum should be less or equal to the size "
    "of nyra_errno_t.");
