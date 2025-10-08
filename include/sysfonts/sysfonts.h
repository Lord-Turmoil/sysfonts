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
 * @param font Pointer to SF_FontInfo structure containing font details.
 * @return Return `SF_CONTINUE` to continue enumeration, `SF_STOP` to stop.
 */
typedef int (*SF_FontsEnumCallback)(const SF_FontInfo* font);

#define SF_CONTINUE 0
#define SF_STOP     1

/**
 * @brief Enumerate all system fonts.
 *
 * This function calls the provided callback for each font found on the system.
 *
 * @param callback The callback function for each font, see `SF_FontsEnumCallback`.
 * @return `SF_SUCCESS` on success, or an error code on failure.
 */
SF_API int SF_EnumFonts(SF_FontsEnumCallback callback);

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
