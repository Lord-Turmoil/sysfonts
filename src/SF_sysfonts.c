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

#include "sysfonts/sysfonts.h"

#include <stdarg.h>
#include <stdio.h>

static char sErrorBuffer[256];

void SF_SetError(const char* format, ...)
{
    va_list args;
    va_start(args, format);

#ifdef SF_PLATFORM_WINDOWS
    vsnprintf_s(sErrorBuffer, sizeof(sErrorBuffer), _TRUNCATE, format, args);
#else
    vsnprintf(sErrorBuffer, sizeof(sErrorBuffer), format, args);
#endif

    va_end(args);
}

const char* SF_GetError(void)
{
    return sErrorBuffer;
}
