# SupernovaX
SupernovaX is an open-source reimplementation of the Microsoft DirectX Infrastructure that targets NT compatible operative systems.

**WARNING ⚠️:** The project is currently at an early stage (and is undergoing a rewrite) and may not work at all.

## Goal of the project
The goal of the project is to eventually provide a reimplementation of some of the Microsoft DirectX user-land and tools distributed as part of the DirectX SDK/Runtime/Windows itself.

The project is divided into two separate parts:
* XDDM
* WDDM

### XDDM
[XDDM](https://learn.microsoft.com/en-us/previous-versions/windows/drivers/display/windows-2000-display-driver-model-design-guide) is the previous Display Driver Model used up to Windows XP.

The following model supports several "legacy" Windows components like DirectDraw, Direct3D9.

This project aims to target Windows XP SP3 XDDM userland implementation. (Direct3D9)

### XDDM
[XDDM](https://learn.microsoft.com/en-us/windows-hardware/drivers/display/windows-vista-and-later-display-driver-model-architecture) is the current Display Driver Model used in modern versions of Windows.

The following model supports the modern Windows components like Direct3D10, Direct2D.

This project aims to target Windows Vista WDDM userland implementation. (Direct3D10 with DXGI 1.0)

## What's missing
Everything, see [Issues](https://github.com/lakor64/supernovax/issues) for more information.

## Supported compilers
Generally any compiler that supports C++14 or greater like.

Does it build on Linux/MinGW? No, feel free to send a PR if interested.

The reference compiler for this project is `Visual Studio 2017 with Windows XP target (v141_xp)` with MIDL.

## How to build
Fetch [this](https://github.com/lakor64/xmake) version of XMake until PR#6301 is merged inside xmake dev branch and rolled out.

Install Visual Studio 2017 with Windows XP triplet.

Run `xmake config -m debug -a x86`, this command will switch to a debug build for 32-bit computers.

Run `xmake` to build the project.

## Special thanks
The following are the basis in which this project was possible, this project is **NOT ENDORSED OR SPONSORED** by any of the project/companies that appears in this list:
- ReactOS
- ReactOS Longhorn fork
- Wine
- mingw-w64
- Various Microsoft repos open-sourced trough the years
