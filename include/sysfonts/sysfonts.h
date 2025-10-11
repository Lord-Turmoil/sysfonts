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

#include "sysfonts/SF_defines.h"

SF_EXTERN_C_BEGIN

/**
 * @brief Information about a font.
 */
typedef struct _SF_FontInfo
{
    const char* family; // font family name, e.g. "Arial"
    const char* path;   // full path to the font file
    const char* style;  // font style, e.g. "Regular", "Bold Italic"
} SF_FontInfo;

/**
 * @brief Callback function type for enumerating fonts.
 *
 * @warning
 * The content of the FontInfo structure is only valid during the callback.
 * You must copy any data you need if you want to use it after the callback returns.
 *
 * @note
 * On Windows, the `style` field is always an empty string, as Windows registry does not
 * contain style information. Also, the `family` may not be the precise font family name.
 * You may need to parse it or load the font file to get accurate information.
 *
 * @param font    Pointer to SF_FontInfo structure containing font details.
 * @param context Custom user context passed to the enumeration function.
 * @return Return `SF_CONTINUE` to continue enumeration, `SF_STOP` to stop.
 */
typedef int (*SF_FontsEnumCallback)(const SF_FontInfo* font, void* context);

#define SF_CONTINUE 0
#define SF_STOP     1

/**
 * @brief Enumerate all system fonts.
 *
 * This function calls the provided callback for each font found on the system.
 * Use `SF_GetError()` to retrieve error messages if the function fails.
 *
 * @param callback The callback function for each font, see `SF_FontsEnumCallback`.
 * @param context  Custom user context passed to the callback.
 * @return `SF_SUCCESS` on success, or an error code on failure.
 */
SF_API int SF_EnumFonts(SF_FontsEnumCallback callback, void* context);

#define SF_SUCCESS           0
#define SF_REGISTRY_ERROR    1 // Windows registry error
#define SF_FONT_CONFIG_ERROR 2 // Linux font config error
#define SF_DESCRIPTOR_ERROR  3 // MacOS font descriptor error

/**
 * @brief Set the last error message.
 *
 * @param format The format string (printf-style).
 */
SF_API void SF_SetError(const char* format, ...);

/**
 * @brief Get the last error message.
 *
 * @return The last error message.
 */
SF_API const char* SF_GetError(void);

SF_EXTERN_C_END
