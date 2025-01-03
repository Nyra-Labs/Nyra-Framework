//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#ifdef __cplusplus
  #define NYRA_EXTERN_C extern "C"
#else
  #define NYRA_EXTERN_C extern
#endif

#if defined(_WIN32)

  #if defined(NYRA_RUNTIME_EXPORT)
    #if !defined(NYRA_RUNTIME_API)
      #define NYRA_RUNTIME_API NYRA_EXTERN_C __declspec(dllexport)
    #endif
  #else
    #if !defined(NYRA_RUNTIME_API)
      #define NYRA_RUNTIME_API NYRA_EXTERN_C __declspec(dllimport)
    #endif
  #endif

  #if !defined(NYRA_RUNTIME_PRIVATE_API)
    #define NYRA_RUNTIME_PRIVATE_API NYRA_EXTERN_C
  #endif

#elif defined(__APPLE__)

  #include <TargetConditionals.h>

  #if !defined(NYRA_RUNTIME_API)
    #define NYRA_RUNTIME_API __attribute__((visibility("default"))) NYRA_EXTERN_C
  #endif

  #if !defined(NYRA_RUNTIME_PRIVATE_API)
    #define NYRA_RUNTIME_PRIVATE_API \
      __attribute__((visibility("hidden"))) NYRA_EXTERN_C
  #endif

#elif defined(__linux__)

  #if !defined(NYRA_RUNTIME_API)
    #define NYRA_RUNTIME_API NYRA_EXTERN_C __attribute__((visibility("default")))
  #endif

  #if !defined(NYRA_RUNTIME_PRIVATE_API)
    #define NYRA_RUNTIME_PRIVATE_API \
      NYRA_EXTERN_C __attribute__((visibility("hidden")))
  #endif

#else

  #if !defined(NYRA_RUNTIME_API)
    #define NYRA_RUNTIME_API NYRA_EXTERN_C
  #endif

  #if !defined(NYRA_RUNTIME_PRIVATE_API)
    #define NYRA_RUNTIME_PRIVATE_API NYRA_EXTERN_C
  #endif

#endif
