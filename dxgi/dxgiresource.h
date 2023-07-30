/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     GPU resource
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#pragma once

#include "dxgidevicesubobject.h"

class ATL_NO_VTABLE CDXGIResource :
	public DXGIObjRoot,
	public CDXGIDeviceSubObject<IDXGIResource>
{
public:
	BEGIN_COM_MAP(CDXGIResource)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIResource, IDXGIResource)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIDeviceSubObject, IDXGIDeviceSubObject)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIObject, IDXGIObject)
	END_COM_MAP()

	// IDXGIResource
	STDMETHODIMP GetEvictionPriority(_Out_ UINT* pEvictionPriority) override;
	STDMETHODIMP GetSharedHandle(_Out_ HANDLE* pSharedHandle) override;
	STDMETHODIMP GetUsage(_Out_ DXGI_USAGE* pUsage) override;
	STDMETHODIMP SetEvictionPriority(_In_ UINT EvictionPriority) override;
};
