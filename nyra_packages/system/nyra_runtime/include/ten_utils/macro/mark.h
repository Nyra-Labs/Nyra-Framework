//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#if !defined(VAR_UNUSED)
  #define VAR_UNUSED(var) (void)var
#endif  // !defined(VAR_UNUSED)

#define RETVAL_UNUSED(expr) \
  do {                      \
    while (expr) break;     \
  } while (0)

#if defined(_WIN32) && !defined(__clang__)

  #if !defined(NYRA_UNUSED)
    #define NYRA_UNUSED
  #endif  // !defined(NYRA_UNUSED)

  #if !defined(PURE)
    #define PURE
  #endif  // !defined(PURE)

  #ifndef LIKELY
    #define LIKELY(x) (x)
  #endif  // !LIKELY

  #ifndef UNLIKELY
    #define UNLIKELY(x) (x)
  #endif  // !UNLIKELY

#else  //  !defined(_WIN32)

  #if !defined(NYRA_UNUSED)
    #define NYRA_UNUSED __attribute__((unused))
  #endif  // !defined(NYRA_UNUSED)

  #if !defined(PURE)
    #define PURE __attribute__((const))
  #endif  // !defined(PURE)

  #ifndef LIKELY
    #define LIKELY(x) __builtin_expect(!!(x), 1)
  #endif  // !LIKELY

  #ifndef UNLIKELY
    #define UNLIKELY(x) __builtin_expect(!!(x), 0)
  #endif  // !UNLIKELY

  #if defined(__has_warning)
    #define NYRA_HAS_WARNING(x) __has_warning(x)
  #else
    #define NYRA_HAS_WARNING(x) 0
  #endif

#endif  // defined(_WIN32)
