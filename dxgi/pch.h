/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     Precompiled header
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#pragma once

#define WIN32_LEAN_AND_MEAN

#ifndef STRICT
#define STRICT 1
#endif

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// explicit CString
#define ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x600 // Vista+
#endif

#ifdef __GNUC__
#define _ATL_DISABLE_NO_VTABLE 1 // fix error
#endif

// ATL
#include <atlbase.h>
#include <atlcom.h>

#ifndef __REACTOS__
#include <winternl.h>
#endif

// DXGI
#include <dxgi.h>

#if _WIN32_WINNT >= 0xA00
#define DXGKDDI_INTERFACE_VERSION DXGKDDI_INTERFACE_VERSION_WDDM3_1
#elif _WIN32_WINNT >= 0x602
#define DXGKDDI_INTERFACE_VERSION DXGKDDI_INTERFACE_VERSION_WIN8
#elif _WIN32_WINNT >= 0x601
#define DXGKDDI_INTERFACE_VERSION DXGKDDI_INTERFACE_VERSION_WIN7
#else
#define DXGKDDI_INTERFACE_VERSION VERSION_WDDM_REACTOS
#endif

#include <d3dkmthk.h>

/** ATL Object root typedef */
using DXGIObjRoot = ATL::CComObjectRootEx<ATL::CComMultiThreadModelNoCS>;
