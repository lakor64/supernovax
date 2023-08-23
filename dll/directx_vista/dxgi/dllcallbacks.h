/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     Windows DLL callbacks
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */
#pragma once

typedef struct _DXGI_WAPI_CALLBACKS
{
	// gdi32.dll
	D3DKMTOpenAdapterFromGdiDisplayName_ D3DKMTOpenAdapterFromGdiDisplayName;
	D3DKMTQueryAdapterInfo_ D3DKMTQueryAdapterInfo;
	D3DKMTCloseAdapter_ D3DKMTCloseAdapter;
	D3DKMTGetDisplayModeList_ D3DKMTGetDisplayModeList;
	D3DKMTWaitForVerticalBlankEvent_ D3DKMTWaitForVerticalBlankEvent;
	D3DKMTGetDeviceState_ D3DKMTGetDeviceState;
	D3DKMTGetThunkVersion_ D3DKMTGetThunkVersion;
#if DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN7
	D3DKMTCheckSharedResourceAccess_ D3DKMTCheckSharedResourceAccess;
#endif
#if DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8
	D3DKMTEnumAdapters2_ D3DKMTEnumAdapters2;
#endif

	// dwmapi.dll
	DwmDxGetWindowSharedSurface_ DwmDxGetWindowSharedSurface;
	DwmDxUpdateWindowSharedSurface_ DwmDxUpdateWindowSharedSurface;
	DwmIsCompositionEnabled_ DwmIsCompositionEnabled;

} DXGI_WAPI_CALLBACKS;
