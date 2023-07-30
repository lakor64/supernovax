/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     Render surface
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#pragma once

#include "dxgidevicesubobject.h"

class ATL_NO_VTABLE CDXGISurface :
	public DXGIObjRoot,
	public CDXGIDeviceSubObject<IDXGISurface1>
{
public:
	BEGIN_COM_MAP(CDXGISurface)
		COM_INTERFACE_ENTRY_IID(IID_IDXGISurface1, IDXGISurface1)
		COM_INTERFACE_ENTRY_IID(IID_IDXGISurface, IDXGISurface)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIDeviceSubObject, IDXGIDeviceSubObject)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIObject, IDXGIObject)
	END_COM_MAP()

	// IDXGISurface
	STDMETHODIMP GetDesc(_Out_ DXGI_SURFACE_DESC* pDesc) override;
	STDMETHODIMP Map(_Out_ DXGI_MAPPED_RECT* pLockedRect, _In_ UINT MapFlags) override;
	STDMETHODIMP Unmap(void) override;
	// IDXGISurface1
	STDMETHODIMP GetDC(_In_ BOOL Discard, _Out_ HDC* pHdc) override;
	STDMETHODIMP ReleaseDC(_In_opt_ RECT* pDirtyRect) override;
};
