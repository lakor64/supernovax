#pragma once

#include "dxgidevicesubobject.h"

class ATL_NO_VTABLE CDXGIResource :
	public DXGIObjRoot,
	public CDXGIDeviceSubObject<IDXGIResource>
{
public:
	BEGIN_COM_MAP(CDXGIResource)
		COM_INTERFACE_ENTRY(IDXGIResource)
		COM_INTERFACE_ENTRY(IDXGIDeviceSubObject)
		COM_INTERFACE_ENTRY(IDXGIObject)
	END_COM_MAP()

	// IDXGIResource
	STDMETHODIMP GetEvictionPriority(_Out_ UINT* pEvictionPriority) override;
	STDMETHODIMP GetSharedHandle(_Out_ HANDLE* pSharedHandle) override;
	STDMETHODIMP GetUsage(_Out_ DXGI_USAGE* pUsage) override;
	STDMETHODIMP SetEvictionPriority(_In_ UINT EvictionPriority) override;
};
