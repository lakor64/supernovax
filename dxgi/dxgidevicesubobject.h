/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     Device sub object
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#pragma once

#include "dxgiobject.h"

/*** Template definition of a subobject */
template <typename T>
class ATL_NO_VTABLE CDXGIDeviceSubObject :
	public CDXGIObject<T>
{
public:
	// IDXGIDeviceSubObject
	STDMETHODIMP GetDevice(_In_ REFIID riid, _Out_ void** ppDevice) override
	{
		if (!ppDevice)
			return DXGI_ERROR_INVALID_CALL;

		return E_NOTIMPL;
	}
};
