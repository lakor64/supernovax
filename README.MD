# ReactX Graphics Infrastructure (formarly pff)

The following repository holds an open-source GPL 2.0/LGPL 2.1 reimplementation of Microsoft DirectX Infrastructure for NT-based operative systems.

***Modern DirectX:*** Targets what's found inside Windows 7 SP1. (DXGI 1.2 & D3D11 1.1)

***Legacy DirectX:*** Targets what's found inside Windows XP SP3.

**NOTE:** Despite the names, this project has no correlation or endorsement by ReactOS or similar project.

## What's missing
See [Issues](https://github.com/lakor64/pff/issues) for more information.

## Supported compilers
- Visual Studio 2019
- Visual Studio 2017 (XP target)

## Will this code work under NT5?
Probably with special hacks and things there might be a way to allow this to work under XP-based environments, which does involve replacing GDI32.dll at most. I'm still in the process of thinking how specifically something like this could be implemented.

## Repository syncs
- ReactOS: a532a68d40feee2422baac4d092ce8ce829e293b (https://github.com/reactos/reactos)
- Wine: 1dfac2a252d0036c3bae08bf47f00582343a80fb (https://github.com/wine-mirror/wine)
- mingw-w64: 11.0

## Code parts
- sdk/include: mingw-w64 and reactos
- sdk/include/reactos/wine: wine
- win32ss_vista\include: reactos ring-0
- dll/directx/ddraw: partial fork from reactos
- dll/directx/dxutils: partial sync from reactos ddraw/d3d9
- base/applications/dxdiag: forked from wine with sync from reactos
