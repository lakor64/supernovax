#pragma once

#include "dxgidevicesubobject.h"

class ATL_NO_VTABLE CDXGISurface :
	public DXGIObjRoot,
	public CDXGIDeviceSubObject<IDXGISurface1>
{
public:
	BEGIN_COM_MAP(CDXGISurface)
		COM_INTERFACE_ENTRY(IDXGISurface1)
		COM_INTERFACE_ENTRY(IDXGISurface)
		COM_INTERFACE_ENTRY(IDXGIDeviceSubObject)
		COM_INTERFACE_ENTRY(IDXGIObject)
	END_COM_MAP()

	// IDXGISurface
	STDMETHODIMP GetDesc(_Out_ DXGI_SURFACE_DESC* pDesc) override;
	STDMETHODIMP Map(_Out_ DXGI_MAPPED_RECT* pLockedRect, _In_ UINT MapFlags) override;
	STDMETHODIMP Unmap(void) override;
	// IDXGISurface1
	STDMETHODIMP GetDC(_In_ BOOL Discard, _Out_ HDC* pHdc) override;
	STDMETHODIMP ReleaseDC(_In_opt_ RECT* pDirtyRect) override;
};
