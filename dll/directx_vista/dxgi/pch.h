/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     Precompiled header
 * COPYRIGHT:   Copyright 2023 Christian Rendina <pizzaiolo100@proton.me>
 */

#pragma once

// DXGI shared library
#include <dxgishared.h>
#include <strsafe.h>

// C++
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

#ifdef __REACTOS__
extern "C" BOOL WINAPI EnumDisplaySettingsExW(_In_opt_ LPCWSTR, _In_ DWORD, _Inout_ LPDEVMODEW, _In_ DWORD);
extern "C" BOOL WINAPI EnumDisplayDevicesW(_In_opt_ LPCWSTR, _In_ DWORD, _Inout_ PDISPLAY_DEVICEW, _In_ DWORD);
#endif

// project files
#include "dxgitypes2.h"
#include "dllimports.h"
