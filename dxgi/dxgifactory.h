/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     Factory class to access all graphics stuff
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#pragma once

#include "dxgiobject.h"

class ATL_NO_VTABLE CDXGIFactory :
	public DXGIObjRoot,
	public CDXGIObject<DXGIFactoryType>
{
public:
	BEGIN_COM_MAP(CDXGIFactory)

#if DXGI_VERSION >= 6
		COM_INTERFACE_ENTRY_IID(IID_IDXGIFactory7, IDXGIFactory7)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIFactory6, IDXGIFactory6)
#endif
#if DXGI_VERSION >= 5
		COM_INTERFACE_ENTRY_IID(IID_IDXGIFactory5, IDXGIFactory5)
#endif
#if DXGI_VERSION >= 4
		COM_INTERFACE_ENTRY_IID(IID_IDXGIFactory4, IDXGIFactory4)
#endif
#if DXGI_VERSION >= 3
		COM_INTERFACE_ENTRY_IID(IID_IDXGIFactory3, IDXGIFactory3)
#endif
#if DXGI_VERSION >= 2
		COM_INTERFACE_ENTRY_IID(IID_IDXGIFactory2, IDXGIFactory2)
#endif
#if DXGI_VERSION >= 1
		COM_INTERFACE_ENTRY_IID(IID_IDXGIFactory1, IDXGIFactory1)
#endif
		COM_INTERFACE_ENTRY_IID(IID_IDXGIFactory, IDXGIFactory)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIObject, IDXGIObject)
	END_COM_MAP()

	CDXGIFactory() = default;
	~CDXGIFactory();

	// IDXGIFactory
	STDMETHODIMP CreateSoftwareAdapter(_In_ HMODULE Module, _COM_Outptr_ IDXGIAdapter** ppAdapter) override;
	STDMETHODIMP CreateSwapChain(_In_ IUnknown* pDevice, _In_ DXGI_SWAP_CHAIN_DESC* pDesc, _COM_Outptr_ IDXGISwapChain** ppSwapChain) override;
	STDMETHODIMP EnumAdapters(_In_ UINT Adapter, _COM_Outptr_ IDXGIAdapter** ppAdapter) override;
	STDMETHODIMP GetWindowAssociation(_Out_ HWND* pWindowHandle) override;
	STDMETHODIMP MakeWindowAssociation(_In_ HWND WindowHandle, _In_ UINT Flags) override;
#if DXGI_VERSION >= 1
	// IDXGIFactory1
	STDMETHODIMP EnumAdapters1(_In_ UINT Adapter, _COM_Outptr_ IDXGIAdapter1** ppAdapter) override;
	STDMETHODIMP_(BOOL) IsCurrent(void) override;
#endif
	// Custom
	STDMETHODIMP Initialize(void);

private:
	/*** Adapters container */
	std::vector<DXGIAdapterDesc> m_vAdapters;

	STDMETHODIMP EnumAdaptersReal(_In_ UINT Adapter, _In_ REFIID Iid, _Out_ void** ppAdapter);

	/** Enumerate adapters by using Windows Vista GDI function */
	STDMETHODIMP RunGdiAdapterEnumator();
};
