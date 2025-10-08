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

#ifdef SF_PLATFORM_MACOS

#include <CoreFoundation/CoreFoundation.h>
#include <CoreText/CoreText.h>

#include <stdio.h>

int SF_EnumFonts(SF_FontsEnumCallback callback)
{
    if (!callback)
    {
        return SF_SUCCESS;
    }

    // Get all available font descriptors
    CFArrayRef fontDescriptors = CTFontManagerCopyAvailableFontFamilyNames();
    if (!fontDescriptors)
    {
        SF_SetError("Failed to get font descriptors.");
        return SF_DESCRIPTOR_ERROR;
    }

    int finished = 0;

    char family[256];
    char style[256];
    char path[1024];
    SF_FontInfo info;
    CFIndex count = CFArrayGetCount(fontDescriptors);
    for (CFIndex i = 0; i < count && !finished; i++)
    {
        CFStringRef familyName = (CFStringRef)CFArrayGetValueAtIndex(fontDescriptors, i);
        if (!CFStringGetCString(familyName, family, sizeof(family), kCFStringEncodingUTF8))
        {
            continue;
        }
        info.family = family;

        printf("Family: %s\n", family);

        CTFontDescriptorRef descriptor = CTFontDescriptorCreateWithNameAndSize(familyName, 0);
        CFArrayRef matchedDescriptors = CTFontDescriptorCreateMatchingFontDescriptors(descriptor, NULL);
        CFRelease(descriptor);
        if (!matchedDescriptors)
        {
            continue;
        }

        CFIndex styleCount = CFArrayGetCount(matchedDescriptors);
        for (CFIndex j = 0; j < styleCount && !finished; j++)
        {
            CTFontDescriptorRef desc = (CTFontDescriptorRef)CFArrayGetValueAtIndex(matchedDescriptors, j);
            CFStringRef styleName = (CFStringRef)CTFontDescriptorCopyAttribute(desc, kCTFontStyleNameAttribute);
            if (!styleName || !CFStringGetCString(styleName, style, sizeof(style), kCFStringEncodingUTF8))
            {
                if (styleName)
                {
                    CFRelease(styleName);
                }
                continue;
            }

            CFURLRef url = (CFURLRef)CTFontDescriptorCopyAttribute(desc, kCTFontURLAttribute);
            if (!url || !CFURLGetFileSystemRepresentation(url, true, (UInt8*)path, sizeof(path)))
            {
                if (styleName)
                {
                    CFRelease(styleName);
                }
                if (url)
                {
                    CFRelease(url);
                }
                continue;
            }

            info.style = style;
            info.path = path;

            if (callback(&info) != SF_CONTINUE)
            {
                finished = 1;
            }

            CFRelease(styleName);
            CFRelease(url);
        }
        CFRelease(matchedDescriptors);
    }
    CFRelease(fontDescriptors);

    return SF_SUCCESS;
}

#endif
