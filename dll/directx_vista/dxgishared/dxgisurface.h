/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     Render surface
 * COPYRIGHT:   Copyright 2023 Christian Rendina <pizzaiolo100@proton.me>
 */

#pragma once

#include "dxgidevicesubobject.h"

class ATL_NO_VTABLE CDXGISurface :
	public DXGIObjRoot,
	public CDXGIDeviceSubObject<DXGISurfaceType>
	//,public IDXGIKeyedMutex
{
public:
	BEGIN_COM_MAP(CDXGISurface)
#if DXGI_VERSION >= 2
		COM_INTERFACE_ENTRY_IID(IID_IDXGISurface2, IDXGISurface2)
#endif
#if DXGI_VERSION >= 1
		COM_INTERFACE_ENTRY_IID(IID_IDXGISurface1, IDXGISurface1)
#endif
		COM_INTERFACE_ENTRY_IID(IID_IDXGISurface, IDXGISurface)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIDeviceSubObject, IDXGIDeviceSubObject)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIObject, IDXGIObject)
	END_COM_MAP()

	// IDXGISurface
	STDMETHODIMP GetDesc(_Out_ DXGI_SURFACE_DESC* pDesc) override;
	STDMETHODIMP Map(_Out_ DXGI_MAPPED_RECT* pLockedRect, _In_ UINT MapFlags) override;
	STDMETHODIMP Unmap(void) override;
#if DXGI_VERSION >= 1
	// IDXGISurface1
	STDMETHODIMP GetDC(_In_ BOOL Discard, _Out_ HDC* pHdc) override;
	STDMETHODIMP ReleaseDC(_In_opt_ RECT* pDirtyRect) override;
#endif
#if DXGI_VERSION >= 2
	// IDXGISurface2
	STDMETHODIMP GetResource(_In_  REFIID riid, _COM_Outptr_ void** ppParentResource, _Out_ UINT* pSubresourceIndex) override;
#endif
};
