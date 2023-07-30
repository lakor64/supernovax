/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     GPU Adapter
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#pragma once

#include "dxgiobject.h"
#include "dxgiadapterdesc.h"

class ATL_NO_VTABLE CDXGIAdapter : 
	public DXGIObjRoot,
	public CDXGIObject<IDXGIAdapter1>
{
public:
	BEGIN_COM_MAP(CDXGIAdapter)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIAdapter1, IDXGIAdapter1)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIAdapter, IDXGIAdapter)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIObject, IDXGIObject)
	END_COM_MAP()

	CDXGIAdapter() = default;
	~CDXGIAdapter() = default;

	// IDXGIAdapter
	STDMETHODIMP CheckInterfaceSupport(_In_ REFGUID InterfaceName, _Out_ LARGE_INTEGER* pUMDVersion) override;
	STDMETHODIMP EnumOutputs(_In_ UINT Output, _COM_Outptr_ IDXGIOutput** ppOutput) override;
	STDMETHODIMP GetDesc(_Out_ DXGI_ADAPTER_DESC* pDesc) override;
	// IDXGIAdapter1
	STDMETHODIMP GetDesc1(_Out_ DXGI_ADAPTER_DESC1* pDesc) override;

	// custom
	STDMETHODIMP Initialize(IDXGIFactory1* parent, const DXGIAdapterDesc& desc);

private:
	/** adapter descriptor */
	DXGIAdapterDesc m_desc;
};
