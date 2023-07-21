#pragma once

#include "dxgiobject.h"

class ATL_NO_VTABLE CDXGIFactory :
	public DXGIObjRoot,
	public CDXGIObject<IDXGIFactory1>
{
public:
	BEGIN_COM_MAP(CDXGIFactory)
		COM_INTERFACE_ENTRY(IDXGIFactory1)
		COM_INTERFACE_ENTRY(IDXGIFactory)
		COM_INTERFACE_ENTRY(IDXGIObject)
	END_COM_MAP()

	// IDXGIFactory
	STDMETHODIMP CreateSoftwareAdapter(_In_ HMODULE Module, _COM_Outptr_ IDXGIAdapter** ppAdapter) override;
	STDMETHODIMP CreateSwapChain(_In_ IUnknown* pDevice, _In_ DXGI_SWAP_CHAIN_DESC* pDesc, _COM_Outptr_ IDXGISwapChain** ppSwapChain) override;
	STDMETHODIMP EnumAdapters(_In_ UINT Adapter, _COM_Outptr_ IDXGIAdapter** ppAdapter) override;
	STDMETHODIMP GetWindowAssociation(_Out_ HWND* pWindowHandle) override;
	STDMETHODIMP MakeWindowAssociation(_In_ HWND WindowHandle, _In_ UINT Flags) override;
	// IDXGIFactory1
	STDMETHODIMP EnumAdapters1(_In_ UINT Adapter, _COM_Outptr_ IDXGIAdapter1** ppAdapter) override;
	STDMETHODIMP_(BOOL) IsCurrent(void) override;
	// Custom
	STDMETHODIMP Initialize(void);
};
