/*
 * PROJECT:     ReactX Graphics Infrastructure
 * LICENSE:     LGPL-2.0-or-later (https://spdx.org/licenses/LGPL-2.0-or-later.html)
 * PURPOSE:     Shared code main inclusions
 * COPYRIGHT:   Copyright 2023 Christian Rendina <pizzaiolo100@proton.me>
 */
#ifndef __DXGISHARED_H__
#define __DXGISHARED_H__

#define STRICT 1
#define _ATL_APARTMENT_THREADED 1
#define _ATL_NO_AUTOMATIC_NAMESPACE 1
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS 1	// explicit CString
#define ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW 1

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x601 // Windows 7+
#endif

#if _WIN32_WINNT >= 0xA00
#define DXGKDDI_INTERFACE_VERSION DXGKDDI_INTERFACE_VERSION_WDDM3_1
#define DXGI_VERSION 6
#elif _WIN32_WINNT >= 0x602
#define DXGKDDI_INTERFACE_VERSION DXGKDDI_INTERFACE_VERSION_WIN8
#define DXGI_VERSION 3
#elif _WIN32_WINNT >= 0x601
#define DXGKDDI_INTERFACE_VERSION DXGKDDI_INTERFACE_VERSION_WIN7
#define DXGI_VERSION 2
#else
#define DXGKDDI_INTERFACE_VERSION DXGKDDI_INTERFACE_VERSION_VISTA
#define DXGI_VERSION 0
#endif

#ifdef __GNUC__
#define _ATL_DISABLE_NO_VTABLE 1 // fix error
#endif

 // ATL
#include <atlbase.h>
#include <atlcom.h>
#undef STATUS_NO_MEMORY

// Windows
#include <winuser.h>
#include <wingdi.h>
#include <shlwapi.h>

// NDK
#ifndef __REACTOS__
#include <winternl.h>
#else
#define NTOS_MODE_USER
#include <ndk/umtypes.h>
#endif

// DXGI
#include <dxgi.h>
#include <d3d9.h>
#include <d3d10_1.h>
#include <d3d11.h>

#if DXGI_VERSION >= 2
#include <dxgi1_2.h>
#endif

#if DXGI_VERSION >= 3
#include <dxgi1_3.h>
#endif

#if DXGI_VERSION >= 4
#include <dxgi1_4.h>
#endif

#if DXGI_VERSION >= 5
#include <dxgi1_5.h>
#endif

#if DXGI_VERSION >= 6
#include <dxgi1_6.h>
#endif

// DXGI DDK (the warning fixes some issues in the old ReactOS LongHorn branch, to be tested if they are still throwed)
#include <d3dkmthk.h>

#ifdef __WINE_D3DKMTHK_H
#error "Do not use wine d3dkmthk.h"
#endif

// Maximum enum outputs
#ifndef MAX_ENUM_OUTPUTS
#define MAX_ENUM_OUTPUTS 16
#endif

// NTSTATUS
#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS 0
#endif
#ifndef STATUS_NOT_SUPPORTED
#define STATUS_NOT_SUPPORTED 0xC00000BB
#endif
#ifndef STATUS_INVALID_PARAMETER
#define STATUS_INVALID_PARAMETER 0xC000000D 
#endif

/// ATL Object root typedef
using DXGIObjRoot = ATL::CComObjectRootEx<ATL::CComMultiThreadModelNoCS>;

// Project
#include "dxgitypes.h"
#include "dxgiternl.h"
#include "dxgidwm.h"
#include "dxgipartner.h"

#endif
