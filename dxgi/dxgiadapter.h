/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     GPU Adapter
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#pragma once

#include "dxgiobject.h"

class ATL_NO_VTABLE CDXGIAdapter : 
	public DXGIObjRoot,
	public CDXGIObject<DXGIAdapterType>
{
public:
	BEGIN_COM_MAP(CDXGIAdapter)
#if DXGI_VERSION >= 6
		COM_INTERFACE_ENTRY_IID(IID_IDXGIAdapter4, IDXGIAdapter4)
#endif
#if DXGI_VERSION >= 4
		COM_INTERFACE_ENTRY_IID(IID_IDXGIAdapter3, IDXGIAdapter3)
#endif
#if DXGI_VERSION >= 2
		COM_INTERFACE_ENTRY_IID(IID_IDXGIAdapter2, IDXGIAdapter2)
#endif
#if DXGI_VERSION >= 1
		COM_INTERFACE_ENTRY_IID(IID_IDXGIAdapter1, IDXGIAdapter1)
#endif
		COM_INTERFACE_ENTRY_IID(IID_IDXGIAdapter, IDXGIAdapter)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIObject, IDXGIObject)
	END_COM_MAP()

	CDXGIAdapter();
	~CDXGIAdapter();

	// IDXGIAdapter
	STDMETHODIMP CheckInterfaceSupport(_In_ REFGUID InterfaceName, _Out_ LARGE_INTEGER* pUMDVersion) override;
	STDMETHODIMP EnumOutputs(_In_ UINT Output, _COM_Outptr_ IDXGIOutput** ppOutput) override;
	STDMETHODIMP GetDesc(_Out_ DXGI_ADAPTER_DESC* pDesc) override;
#if DXGI_VERSION >= 1
	// IDXGIAdapter1
	STDMETHODIMP GetDesc1(_Out_ DXGI_ADAPTER_DESC1* pDesc) override;
#endif

	// custom
	STDMETHODIMP Initialize(IDXGIFactory1* parent, const DXGIAdapterDesc& desc);

private:
	/** adapter descriptor */
	DXGIAdapterDesc m_desc;

};
