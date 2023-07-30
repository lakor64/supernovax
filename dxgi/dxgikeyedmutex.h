/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     Keyed mutex
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#pragma once

#include "dxgidevicesubobject.h"

class ATL_NO_VTABLE CDXGIKeyedMutex : 
	public CDXGIDeviceSubObject<IDXGIKeyedMutex>,
	public DXGIObjRoot
{
public:

	BEGIN_COM_MAP(CDXGIKeyedMutex)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIKeyedMutex, IDXGIKeyedMutex)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIDeviceSubObject, IDXGIDeviceSubObject)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIObject, IDXGIObject)
	END_COM_MAP()

	// IDXGIKeyedMutex
	STDMETHODIMP AcquireSync(_In_ UINT64 Key, _In_ DWORD dwMilliseconds) override;
	STDMETHODIMP ReleaseSync(_In_ UINT64 Key) override;
};
