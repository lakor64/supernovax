/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     Precompiled header
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#pragma once

// DXGI shared library
#include <dxgishared.h>

// C++
#include <vector>

#ifdef __REACTOS__
extern "C" BOOL WINAPI EnumDisplaySettingsExW(_In_opt_ LPCWSTR, _In_ DWORD, _Inout_ LPDEVMODEW, _In_ DWORD);
extern "C" BOOL WINAPI EnumDisplayDevicesW(_In_opt_ LPCWSTR, _In_ DWORD, _Inout_ PDISPLAY_DEVICEW, _In_ DWORD);
#endif

// Project
#include "impcb.h"
#include "dllcallbacks.h"
