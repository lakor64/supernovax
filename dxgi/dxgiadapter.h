#pragma once

#include "dxgiobject.h"

class ATL_NO_VTABLE CDXGIAdapter : 
	public DXGIObjRoot,
	public CDXGIObject<IDXGIAdapter1>
{
public:
	BEGIN_COM_MAP(CDXGIAdapter)
		COM_INTERFACE_ENTRY(IDXGIAdapter1)
		COM_INTERFACE_ENTRY(IDXGIAdapter)
		COM_INTERFACE_ENTRY(IDXGIObject)
	END_COM_MAP()

	// IDXGIAdapter
	STDMETHODIMP CheckInterfaceSupport(_In_ REFGUID InterfaceName, _Out_ LARGE_INTEGER* pUMDVersion) override;
	STDMETHODIMP EnumOutputs(_In_ UINT Output, _COM_Outptr_ IDXGIOutput** ppOutput) override;
	STDMETHODIMP GetDesc(_Out_ DXGI_ADAPTER_DESC* pDesc) override;
	// IDXGIAdapter1
	STDMETHODIMP GetDesc1(_Out_ DXGI_ADAPTER_DESC1* pDesc) override;
};
