# SupernovaX (formarly pff)

The following repository holds an open-source GPL/LGPL 2.1 reimplementation of Microsoft DirectX Infrastructure for NT-based operative systems.

***Modern DirectX:*** Targets what's found inside Windows 7 SP1. (DXGI 1.2 & D3D11 1.1)

***Legacy DirectX:*** Targets what's found inside Windows XP SP3. (D3D9)

**NOTE:** This project has no correlation or endorsement by ReactOS or similar project.

## What's missing
See [Issues](https://github.com/lakor64/pff/issues) for more information.

## Supported compilers
- Visual Studio 2022
- Visual Studio 2019
- Visual Studio 2017 (XP target)

## Will Modern DX work under NT5?
Probably with special hacks and things there might be a way to allow this to work under XP-based environments, which does involve replacing GDI32.dll at most. I'm still in the process of thinking how specifically something like this could be implemented.

## Special thanks
- ReactOS (as the whole repository structured is based upon them)
- ReactOS Longhorn fork
- Wine
- mingw-w64
