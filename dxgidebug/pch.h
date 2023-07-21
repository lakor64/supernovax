#pragma once

#define WIN32_LEAN_AND_MEAN

#ifndef STRICT
#define STRICT 1
#endif

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// explicit CString
#define ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW

#define _WIN32_WINNT 0x600 // Vista+

// ATL
#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>

// bugfix of IDXGIInfoQueue::GetMessage
#ifdef GetMessage
#undef GetMessage
#endif

// DXGI
#include <dxgi.h>
#include <dxgidebug.h>

// Project
#include "resource.h"

//! ATL Object root typedef
using DXGIObjRoot = ATL::CComObjectRootEx<ATL::CComMultiThreadModelNoCS>;
