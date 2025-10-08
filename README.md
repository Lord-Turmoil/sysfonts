# sysfonts

> A lightweight cross-platform C library to list installed system fonts.

---

> [!NOTE]
>
> This is a side project of [DungineX](https://github.com/Lord-Turmoil/DungineX), which needs to know all available system fonts.

[![Multi-platform Build](https://github.com/Lord-Turmoil/sysfonts/actions/workflows/build.yml/badge.svg?branch=main)](https://github.com/Lord-Turmoil/sysfonts/actions/workflows/build.yml)

The goal of sysfonts is to list all installed system fonts with 

- font name
- font style
- path to the font file

Although it works as long as there is font installed, it is intended to be used by programs with graphical interface. On Linux, it requires `libfontconfig` installed.

```bash
sudo apt install -y libfontconfig1-dev
```

## Usage

This is a standard CMake project, simply copy it to your project and add the following command to your project.

```cmake
target_link_libraries(${YOUR_TARGET} PRIVATE sysfonts::sysfonts)
```

sysfonts provides an API to iterate through all installed system fonts. All you need is to define a callback to handle each font. The order of the fonts is not guaranteed.

```c
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
```

> [!WARNING]
>
> The `FontInfo` is only valid inside the callback. Copy the data if you want to use it later.

You can find this example in [test/main.c](./test/main.c).

## Cross-platform support

- [x] Windows
- [x] Linux
- [x] MacOS

### Note for Windows

It works as expected on Linux and MacOS, but fonts on windows is a little messy.

In order to be light-weighted, sysfonts only reads the registry, which does not contain precise font name and style. The `style` in `FontInfo` is **always an empty string**, and `family` may contain text from font style. Although one can try to parse the registry entry name to get font family and style, but it may not apply to all cases. Therefore sysfonts leaves it as it is.

However, the path to the font file is always accurate, so one solution is to actually load the file to get the font family and style information.
