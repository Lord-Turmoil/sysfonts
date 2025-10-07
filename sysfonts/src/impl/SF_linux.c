#include "sysfonts/sysfonts.h"

#ifdef SF_PLATFORM_LINUX

#include <fontconfig/fontconfig.h>

int SF_EnumFonts(SF_FontsEnumCallback callback)
{
    if (!callback)
    {
        return 0;
    }

    if (!FcInit())
    {
        SF_SetError("Failed to initialize Font Config.");
        return 1;
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
        if (callback(&info))
        {
            break;
        }
    }

    FcFontSetDestroy(fonts);
    FcObjectSetDestroy(objects);
    FcPatternDestroy(pattern);
    FcFini();

    return 0;
}

#endif
