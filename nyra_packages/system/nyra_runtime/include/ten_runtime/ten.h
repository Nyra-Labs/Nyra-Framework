//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

// This header file should be the only header file where outside world should
// include in the C programming language.

#include "nyra_runtime/nyra_config.h"

#include "nyra_runtime/addon/addon.h"                  // IWYU pragma: export
#include "nyra_runtime/addon/extension/extension.h"    // IWYU pragma: export
#include "nyra_runtime/app/app.h"                      // IWYU pragma: export
#include "nyra_runtime/common/errno.h"                 // IWYU pragma: export
#include "nyra_runtime/extension/extension.h"          // IWYU pragma: export
#include "nyra_runtime/msg/audio_frame/audio_frame.h"  // IWYU pragma: export
#include "nyra_runtime/msg/cmd/close_app/cmd.h"        // IWYU pragma: export
#include "nyra_runtime/msg/cmd_result/cmd_result.h"    // IWYU pragma: export
#include "nyra_runtime/msg/data/data.h"                // IWYU pragma: export
#include "nyra_runtime/msg/msg.h"                      // IWYU pragma: export
#include "nyra_runtime/msg/video_frame/video_frame.h"  // IWYU pragma: export
#include "nyra_runtime/nyra_env/nyra_env.h"              // IWYU pragma: export
