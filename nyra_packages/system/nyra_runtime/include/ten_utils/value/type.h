//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

typedef enum NYRA_TYPE {
  NYRA_TYPE_INVALID,

  NYRA_TYPE_NULL,

  NYRA_TYPE_BOOL,

  NYRA_TYPE_INT8,
  NYRA_TYPE_INT16,
  NYRA_TYPE_INT32,
  NYRA_TYPE_INT64,

  NYRA_TYPE_UINT8,
  NYRA_TYPE_UINT16,
  NYRA_TYPE_UINT32,
  NYRA_TYPE_UINT64,

  NYRA_TYPE_FLOAT32,
  NYRA_TYPE_FLOAT64,

  NYRA_TYPE_STRING,
  NYRA_TYPE_BUF,

  NYRA_TYPE_ARRAY,
  NYRA_TYPE_OBJECT,

  NYRA_TYPE_PTR,
} NYRA_TYPE;
