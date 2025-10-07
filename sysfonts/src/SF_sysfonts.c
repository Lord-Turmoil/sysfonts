#include "sysfonts/sysfonts.h"

#include <stdarg.h>
#include <stdio.h>

static char gErrorBuffer[256];

void SF_SetError(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    vsnprintf(gErrorBuffer, sizeof(gErrorBuffer), format, args);
    va_end(args);
}

const char* SF_GetError()
{
    return gErrorBuffer;
}

#ifdef SF_PLATFORM_WINDOWS
#    include "impl/SF_windows.c"
#elif defined(SF_PLATFORM_LINUX)
#    include "impl/SF_linux.c"
#elif defined(SF_PLATFORM_MACOS)
#    include "impl/SF_macos.c"
#else
#    error "Unsupported platform"
#endif
