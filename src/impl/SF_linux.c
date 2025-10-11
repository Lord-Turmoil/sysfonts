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

#ifdef SF_PLATFORM_LINUX

#include <fontconfig/fontconfig.h>

int SF_EnumFonts(SF_FontsEnumCallback callback, void* context)
{
    if (!callback)
    {
        return SF_SUCCESS;
    }

    if (!FcInit())
    {
        SF_SetError("Failed to initialize Font Config.");
        return SF_FONT_CONFIG_ERROR;
    }

    FcPattern* pattern = FcPatternCreate();
    FcObjectSet* objects = FcObjectSetBuild(FC_FAMILY, FC_FILE, FC_STYLE, NULL);
    FcFontSet* fonts = FcFontList(NULL, pattern, objects);
    for (int i = 0; i < fonts->nfont; i++)
    {
        FcPattern* font = fonts->fonts[i];

        FcChar8* family;
        FcChar8* path;
        FcChar8* style;
        if ((FcPatternGetString(font, FC_FAMILY, 0, &family) != FcResultMatch) ||
            (FcPatternGetString(font, FC_STYLE, 0, &style) != FcResultMatch) ||
            (FcPatternGetString(font, FC_FILE, 0, &path) != FcResultMatch))
        {
            // Skip silently if any of the required fields are missing.
            continue;
        }

        SF_FontInfo info;
        info.family = (const char*)family;
        info.style = (const char*)style;
        info.path = (const char*)path;
        if (callback(&info, context) != SF_CONTINUE)
        {
            break;
        }
    }

    FcFontSetDestroy(fonts);
    FcObjectSetDestroy(objects);
    FcPatternDestroy(pattern);
    FcFini();

    return SF_SUCCESS;
}

#endif
