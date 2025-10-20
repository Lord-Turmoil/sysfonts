/*
  sysfonts - A cross-platform C library to list installed system fonts

  Copyright (C) 2025 Tony Lewis <swift-phantom@outlook.com>

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
 */

#pragma once

#include <stddef.h> // NULL

#define SF_VERSION_MAJOR    0
#define SF_VERSION_MINOR    1
#define SF_VERSION_PATCH    1
#define SF_VERSION_REVISION 0

// clang-format off

// platform detection
#if (defined(_WIN32) || defined(_WIN64))
#    define SF_PLATFORM_WINDOWS
#elif (defined(__linux__))
#    define SF_PLATFORM_LINUX
#elif (defined(__APPLE__) || defined(__MACH__))
#    define SF_PLATFORM_MACOS
#else
#    error "Unsupported platform"
#endif

// shared library macros
#ifdef SF_PLATFORM_WINDOWS
#    ifdef SF_EXPORT
#        define SF_API __declspec(dllexport)
#    elif defined(SF_IMPORT)
#        define SF_API
#    else
#        define SF_API
#    endif
#elif __GNUC__ >= 4
#    define SF_API __attribute__((visibility("default")))
#else
#    define SF_API
#endif

// C/C++ compatibility
#ifdef __cplusplus
#    define SF_EXTERN_C extern "C"
#    define SF_EXTERN_C_BEGIN                                                                                          \
        extern "C"                                                                                                     \
        {
#    define SF_EXTERN_C_END }
#else
#    define SF_EXTERN_C
#    define SF_EXTERN_C_BEGIN
#    define SF_EXTERN_C_END
#endif

// clang-format on
