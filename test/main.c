#include <sysfonts/sysfonts.h>

#include <stdio.h>
#include <string.h>

static int callback(const SF_FontInfo* info, void* context)
{
    printf("Font: %s\n", info->family);
    printf("  Style: %s\n", info->style);
    printf("   Path: %s\n", info->path);

    if (strstr(info->family, "Consolas"))
    {
        printf("\nFound Consolas!\n");
        return SF_STOP;
    }

    int* count = (int*)context;
    (*count)++;

    return SF_CONTINUE;
}

int main(void)
{
    int count = 0;

    if (SF_EnumFonts(callback, &count) != SF_SUCCESS)
    {
        fprintf(stderr, "%s", SF_GetError());
    }
    printf("Iterated %d fonts\n", count);

    return 0;
}
