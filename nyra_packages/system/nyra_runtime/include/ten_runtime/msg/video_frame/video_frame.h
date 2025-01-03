//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_runtime/nyra_config.h"

#include <stddef.h>
#include <stdint.h>

#include "nyra_utils/lib/error.h"
#include "nyra_utils/lib/smart_ptr.h"

// Note: To achieve the best compatibility, any new enum item, should be added
// to the end to avoid changing the value of previous enum items.
typedef enum NYRA_PIXEL_FMT {
  NYRA_PIXEL_FMT_INVALID,

  NYRA_PIXEL_FMT_RGB24,
  NYRA_PIXEL_FMT_RGBA,

  NYRA_PIXEL_FMT_BGR24,
  NYRA_PIXEL_FMT_BGRA,

  NYRA_PIXEL_FMT_I422,
  NYRA_PIXEL_FMT_I420,

  NYRA_PIXEL_FMT_NV21,
  NYRA_PIXEL_FMT_NV12,
} NYRA_PIXEL_FMT;

typedef struct nyra_video_frame_t nyra_video_frame_t;

NYRA_RUNTIME_API nyra_shared_ptr_t *nyra_video_frame_create(const char *name,
                                                         nyra_error_t *err);

NYRA_RUNTIME_API int32_t nyra_video_frame_get_width(nyra_shared_ptr_t *self);
NYRA_RUNTIME_API bool nyra_video_frame_set_width(nyra_shared_ptr_t *self,
                                               int32_t width);

NYRA_RUNTIME_API int32_t nyra_video_frame_get_height(nyra_shared_ptr_t *self);
NYRA_RUNTIME_API bool nyra_video_frame_set_height(nyra_shared_ptr_t *self,
                                                int32_t height);

NYRAAAA_RUNTIME_API int64_t nyra_video_frame_get_timestamp(nyra_shared_ptr_t *self);
NYRA_RUNTIME_API bool nyra_video_frame_set_timestamp(nyra_shared_ptr_t *self,
                                                   int64_t timestamp);

NYRA_RUNTIME_API bool nyra_video_frame_is_eof(nyra_shared_ptr_t *self);
NYRA_RUNTIME_API bool nyra_video_frame_set_eof(nyra_shared_ptr_t *self,
                                             bool is_eof);

NYRA_RUNTIME_API NYRA_PIXEL_FMT
nyra_video_frame_get_pixel_fmt(nyra_shared_ptr_t *self);

NYRA_RUNTIME_API bool nyra_video_frame_set_pixel_fmt(nyra_shared_ptr_t *self,
                                                   NYRA_PIXEL_FMT type);

NYRA_RUNTIME_API uint8_t *nyra_video_frame_alloc_data(nyra_shared_ptr_t *self,
                                                    size_t size);

NYRA_RUNTIME_API nyra_buf_t *nyra_video_frame_peek_data(nyra_shared_ptr_t *self);
