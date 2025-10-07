#pragma once

#include <stddef.h>

#define SF_VERSION_MAJOR    0
#define SF_VERSION_MINOR    1
#define SF_VERSION_PATCH    0
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

// utility macros
#define SF_USED(x) (void)(x)
