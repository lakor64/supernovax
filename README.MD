# ReactX Graphics Infrastructure (formarly pff)
The following repository holds an open-source GPL 2.0 reimplementation of modern Microsoft DirectX Infrastructure for NT-based operative systems.

This repository currently targets what's found inside Windows 7 SP1. (DXGI 1.2 & D3D11 1.1)

## Implementation status
- [ ] dxgi 1.0
- [ ] dxgi 1.1
- [ ] dxgi 1.2
- [ ] dxgi 1.3
- [ ] dxgi 1.4
- [ ] dxgi 1.5
- [ ] dxgi 1.6
- [ ] dxgidebug
- [ ] d3d10 1.0
- [ ] d3d10 1.1
- [ ] D3D10core
- [ ] d3d10level9
- [ ] d3d10ref
- [ ] d3d10sdklayers
- [ ] d3d10warp
- [ ] d3d11 1.0
- [ ] d3d11 1.1
- [ ] d3d11 1.2
- [ ] d3d11 1.3
- [ ] d3d11 1.4
- [ ] d3d11_3SDKlayers
- [ ] d3d11on12
- [ ] d3d11ref
- [ ] d3d11sdklayers
- [ ] d3d12
- [ ] d3d12core
- [ ] d3d12sdklayers
- [ ] d3dcompiler

## What's missing
See [Issues](https://github.com/lakor64/pff/issues) for more information.

## Supported compilers
- Visual Studio 2019

## Will this code work under NT5?
Probably with special hacks and things there might be a way to allow this to work under XP-based environments, which does involve replacing GDI32.dll at most. I'm still in the process of thinking how specifically something like this could be implemented.

## Will this code work under ReactOS?
Once ReactOS gets WDDM mostly yes.

## Syncs
- [ReactOS Longhorn](https://github.com/Ring-0-Productions/reactos/tree/dxgi)
- [Retail ReactOS](https://github.com/lakor64/reactos/tree/dxgi)
