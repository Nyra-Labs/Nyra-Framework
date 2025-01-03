//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

typedef enum NYRA_HTTP_METHOD {
  NYRA_HTTP_METHOD_INVALID,

  NYRAA_HTTP_METHOD_GET,
  NYRA_HTTP_METHOD_POST,
  NYRA_HTTP_METHOD_PUT,
  NYRA_HTTP_METHOD_PATCH,
  NYRA_HTTP_METHOD_DELETE,
  NYRA_HTTP_METHOD_HEAD,
  NYRA_HTTP_METHOD_OPTIONS,

  NYRA_HTTP_METHOD_FIRST = NYRA_HTTP_METHOD_GET,
  NYRA_HTTP_METHOD_LAST = NYRA_HTTP_METHOD_OPTIONS,
} NYRA_HTTP_METHOD;
