#pragma once

#include "dxgiobject.h"

template <typename T>
class ATL_NO_VTABLE CDXGIDeviceSubObject :
	public CDXGIObject<T>
{
public:
	// IDXGIDeviceSubObject
	STDMETHODIMP GetDevice(_In_ REFIID riid, _Out_ void** ppDevice) override
	{
		return E_NOTIMPL;
	}
};
