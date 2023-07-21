#pragma once

#include "dxgidevicesubobject.h"

class ATL_NO_VTABLE CDXGIKeyedMutex : 
	public CDXGIDeviceSubObject<IDXGIKeyedMutex>,
	public DXGIObjRoot
{
public:

	BEGIN_COM_MAP(CDXGIKeyedMutex)
		COM_INTERFACE_ENTRY(IDXGIKeyedMutex)
		COM_INTERFACE_ENTRY(IDXGIDeviceSubObject)
		COM_INTERFACE_ENTRY(IDXGIObject)
	END_COM_MAP()

	// IDXGIKeyedMutex
	STDMETHODIMP AcquireSync(_In_ UINT64 Key, _In_ DWORD dwMilliseconds) override;
	STDMETHODIMP ReleaseSync(_In_ UINT64 Key) override;
};
