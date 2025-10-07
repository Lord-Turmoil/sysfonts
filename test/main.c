#include <sysfonts/sysfonts.h>

#include <stdio.h>
#include <string.h>

static int callback(const SF_FontInfo* info)
{
    printf("Font: %s\n", info->family);
    printf("  Style: %s\n", info->style);
    printf("   Path: %s\n", info->path);

    if (strstr(info->family, "Consolas"))
    {
        printf("\nFound Consolas!\n");
        return SF_STOP;
    }

    return SF_CONTINUE;
}

int main()
{
    if (SF_EnumFonts(callback) != SF_SUCCESS)
    {
        fprintf(stderr, SF_GetError());
    }

    return 0;
}
