#include <sysfonts/sysfonts.h>

#include <stdio.h>

static int callback(const SF_FontInfo* info)
{
    printf("Font: %s\n\tStyle: %s\n\tPath: %s\n\n", info->family, info->style, info->path);
    return 0;
}

int main()
{
    SF_EnumFonts(callback);

    return 0;
}
