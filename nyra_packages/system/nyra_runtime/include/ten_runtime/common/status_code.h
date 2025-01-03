//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_runtime/nyra_config.h"

typedef enum NYRA_STATUS_CODE {
  NYRA_STATUS_CODE_INVALID = -1,

  // 0 representing OK is a common convention.
  NYRA_STATUS_CODE_OK = 0,
  NYRA_STATUS_CODE_ERROR = 1,

  NYRA_STATUS_CODE_LAST = 2,
} NYRA_STATUS_CODE;
