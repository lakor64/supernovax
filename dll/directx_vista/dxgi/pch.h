/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     Precompiled header
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#pragma once

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
#define DXGKDDI_INTERFACE_VERSION VERSION_WDDM_REACTOS
#define DXGI_VERSION 0
#endif

#ifdef __GNUC__
#define _ATL_DISABLE_NO_VTABLE 1 // fix error
#endif

 // ATL
#include <atlbase.h>
#include <atlcom.h>
#undef STATUS_NO_MEMORY

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

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4200)
#endif
#include <d3dkmthk.h>
#ifdef _MSC_VER
#pragma warning(pop)
#endif

#ifdef __WINE_D3DKMTHK_H
#error "Do not use wine d3dkmthk.h"
#endif

#ifndef MAX_ENUM_ADAPTERS
#define MAX_ENUM_ADAPTERS 16
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

/** ATL Object root typedef */
using DXGIObjRoot = ATL::CComObjectRootEx<ATL::CComMultiThreadModelNoCS>;

// Project
#include "impcb.h"
#include "dxgitypes.h"
#include "dxgi_internal_h.h"
