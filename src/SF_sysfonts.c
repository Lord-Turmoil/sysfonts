#include "sysfonts/sysfonts.h"

#include <stdarg.h>
#include <stdio.h>

static char sErrorBuffer[256];

void SF_SetError(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    vsnprintf(sErrorBuffer, sizeof(sErrorBuffer), format, args);
    va_end(args);
}

const char* SF_GetError(void)
{
    return sErrorBuffer;
}
