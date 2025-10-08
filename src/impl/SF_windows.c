#include "sysfonts/sysfonts.h"

#ifdef SF_PLATFORM_WINDOWS

#include <Windows.h>

#define SYSTEM_FONT_REGISTRY_KEY "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts"
#define SYSTEM_FONT_PATH         "C:\\Windows\\Fonts\\"

static char sFontface[256];
static char sFontfile[1024];

static int StartsWith(const char* str, const char* prefix)
{
    if (!str || !prefix)
    {
        return 0;
    }

    while (*prefix)
    {
        if (*str++ != *prefix++)
        {
            return 0;
        }
    }

    return 1;
}

/**
 * Reference:
 * - https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regopenkeyexa
 * - https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regenumvaluea
 */
int SF_EnumFonts(SF_FontsEnumCallback callback)
{
    if (!callback)
    {
        return SF_SUCCESS;
    }

    HKEY hKey;

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, SYSTEM_FONT_REGISTRY_KEY, 0, KEY_READ, &hKey) != ERROR_SUCCESS)
    {
        SF_SetError("Failed to open registry key.");
        return SF_REGISTRY_ERROR;
    }

    const size_t PATH_PREFIX_SIZE = strlen(SYSTEM_FONT_PATH);

    DWORD index = 0;
    CHAR valueName[512];
    DWORD valueNameSize = sizeof(valueName) / sizeof(CHAR);
    DWORD type;

    CHAR path_buffer[1024] = SYSTEM_FONT_PATH;
    CHAR* valueData = path_buffer + PATH_PREFIX_SIZE;
    DWORD valueDataSize = sizeof(path_buffer) / sizeof(CHAR) - PATH_PREFIX_SIZE;

    SF_FontInfo info;

    LONG status = RegEnumValueA(hKey, index, valueName, &valueNameSize, NULL, &type, (LPBYTE)valueData, &valueDataSize);
    while (status == ERROR_SUCCESS)
    {
        if (type == REG_SZ)
        {
            info.family = valueName;
            info.style = ""; // Windows registry does not contain style info :(
            if (StartsWith(valueData, "C:\\"))
            {
                info.path = valueData;
            }
            else
            {
                info.path = path_buffer;
            }
            char* p = strstr(info.family, "(");
            if (p)
            {
                *(p - 1) = '\0'; // Remove the trailing space before '('
            }

            if (callback(&info) != SF_CONTINUE)
            {
                break;
            }
        }

        index++;
        valueNameSize = sizeof(valueName) / sizeof(CHAR);
        valueDataSize = sizeof(path_buffer) / sizeof(CHAR) - PATH_PREFIX_SIZE;

        status = RegEnumValueA(hKey, index, valueName, &valueNameSize, NULL, &type, (LPBYTE)valueData, &valueDataSize);
    }
    RegCloseKey(hKey);

    if ((status != ERROR_SUCCESS) && (status != ERROR_NO_MORE_ITEMS))
    {
        SF_SetError("Failed to enumerate registry values.");
        return SF_REGISTRY_ERROR;
    }

    return SF_SUCCESS;
}

#endif
