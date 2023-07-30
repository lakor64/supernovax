/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     Factory class to access all graphics stuff
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#pragma once

#include "dxgiobject.h"
#include "dxgiadapterdesc.h"

class ATL_NO_VTABLE CDXGIFactory :
	public DXGIObjRoot,
	public CDXGIObject<IDXGIFactory1>
{
public:
	BEGIN_COM_MAP(CDXGIFactory)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIFactory1, IDXGIFactory1)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIFactory, IDXGIFactory)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIObject, IDXGIObject)
	END_COM_MAP()

	CDXGIFactory() = default;
	~CDXGIFactory() = default;

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

private:
	/*** Adapters container */
	std::vector<DXGIAdapterDesc> m_vAdapters;

	STDMETHODIMP EnumAdaptersReal(_In_ UINT Adapter, _In_ REFIID Iid, _Out_ void** ppAdapter);

#if DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8
	/** Enumerate adapters by using Windows8 D3DKMT function */
	STDMETHODIMP RunWin8AdapterEnumerator();
#endif

	/** Enumerate adapters by using Windows Vista GDI function */
	STDMETHODIMP RunGdiAdapterEnumator();

	/** Gets all the remaining info of the adapter */
	STDMETHODIMP GetRemainingDesc(DXGIAdapterDesc& desc);
};
