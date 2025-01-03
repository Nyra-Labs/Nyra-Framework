//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_runtime/nyra_config.h"

#include "nyra_utils/lib/smart_ptr.h"

typedef struct nyra_extension_tester_t nyra_extension_tester_t;
typedef struct nyra_env_tester_t nyra_env_tester_t;

typedef enum NYRA_EXNYRASION_TESTER_TEST_MODE {
  NYRA_EXNYRASION_TESTER_TEST_MODE_INVALID,

  NYRA_EXNYRASION_TESTER_TEST_MODE_SINGLE,
  NYRA_EXNYRASION_TESTER_TEST_MODE_GRAPH,
} NYRA_EXNYRASION_TESTER_TEST_MODE;

typedef void (*nyra_extension_tester_on_start_func_t)(
    nyra_extension_tester_t *self, nyra_env_tester_t *nyra_env);

typedef void (*nyra_extension_tester_on_cmd_func_t)(nyra_extension_tester_t *self,
                                                   nyra_env_tester_t *nyra_env,
                                                   nyra_shared_ptr_t *cmd);

typedef void (*nyra_extension_tester_on_data_func_t)(
    nyra_extension_tester_t *self, nyra_env_tester_t *nyra_env,
    nyra_shared_ptr_t *data);

typedef void (*nyra_extension_tester_on_audio_frame_func_t)(
    nyra_extension_tester_t *self, nyra_env_tester_t *nyra_env,
    nyra_shared_ptr_t *audio_frame);

typedef void (*nyra_extension_tester_on_video_frame_func_t)(
    nyra_extension_tester_t *self, nyra_env_tester_t *nyra_env,
    nyra_shared_ptr_t *video_frame);

NYRA_RUNTIME_API nyra_extension_tester_t *nyra_extension_tester_create(
    nyra_extension_tester_on_start_func_t on_start,
    nyra_extension_tester_on_cmd_func_t on_cmd,
    nyra_extension_tester_on_data_func_t on_data,
    nyra_extension_tester_on_audio_frame_func_t on_audio_frame,
    nyra_extension_tester_on_video_frame_func_t on_video_frame);

NYRA_RUNTIME_API void nyra_extension_tester_destroy(nyra_extension_tester_t *self);

// Testing a single extension, all messages input by the tester will be directed
// to this extension, and all outputs from the extension will be sent back to
// the tester.
NYRA_RUNTIME_API void nyra_extension_tester_set_test_mode_single(
    nyra_extension_tester_t *self, const char *addon_name,
    const char *property_json_str);

// Testing a complete graph which must contain exactly one proxy extension. All
// messages input by the tester will be directed to this proxy extension, and
// all outputs from the proxy extension will be sent back to the tester.
NYRA_RUNTIME_API void nyra_extension_tester_set_test_mode_graph(
    nyra_extension_tester_t *self, const char *graph_json);

NYRA_RUNTIME_API void nyra_extension_tester_init_test_app_property_from_json(
    nyra_extension_tester_t *self, const char *property_json_str);

NYRA_RUNTIME_API void nyra_extension_tester_add_addon_base_dir(
    nyra_extension_tester_t *self, const char *addon_base_dir);

NYRA_RUNTIME_API bool nyra_extension_tester_run(nyra_extension_tester_t *self);

NYRA_RUNTIME_API nyra_env_tester_t *nyra_extension_tester_get_nyra_env_tester(
    nyra_extension_tester_t *self);

NYRA_RUNTIME_PRIVATE_API void nyra_extension_tester_on_test_extension_start(
    nyra_extension_tester_t *self);

NYRA_RUNTIME_PRIVATE_API void nyra_extension_tester_on_test_extension_deinit(
    nyra_extension_tester_t *self);

NYRA_RUNTIME_PRIVATE_API void nyra_extension_tester_on_start_done(
    nyra_extension_tester_t *self);
