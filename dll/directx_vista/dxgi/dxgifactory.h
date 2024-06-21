/*
 * PROJECT:     ReactX Graphics Infrastructure
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     Factory class to access all graphics stuff
 * COPYRIGHT:   Copyright 2023 Christian Rendina <pizzaiolo100@proton.me>
 */

#pragma once

#include "dxgiobject.h"
#include <lockedowner.h>

class ATL_NO_VTABLE CDXGIFactory :
	public DXGIObjRoot,
	public CDXGIObject<DXGIFactoryType>,
	public IDXGIFactoryInternal,
#if DXGI_VERSION >= 2
	public IDXGIDisplayControl,
#endif
	public IDXGIDebugProducer,
	public CLockedOwner
{
public:
	using AdapterLUIDStorage = std::vector<LUID>;

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
		COM_INTERFACE_ENTRY_IID(IID_IDXGIDisplayControl, IDXGIDisplayControl)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIFactory2, IDXGIFactory2)
#endif
#if DXGI_VERSION >= 1
		COM_INTERFACE_ENTRY_IID(IID_IDXGIFactory1, IDXGIFactory1)
#endif
		COM_INTERFACE_ENTRY_IID(IID_IDXGIDebugProducer, IDXGIDebugProducer)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIFactoryInternal, IDXGIFactoryInternal)
		COM_INTERFACE_ENTRY_IID(IID_ILockOwner, ILockOwner)
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
#if DXGI_VERSION >= 2
	// IDXGIFactory2
	STDMETHODIMP_(BOOL) IsWindowedStereoEnabled(void) override;
    STDMETHODIMP CreateSwapChainForHwnd(_In_ IUnknown* pDevice, _In_ HWND hWnd, _In_ const DXGI_SWAP_CHAIN_DESC1* pDesc, _In_opt_ const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pFullscreenDesc, _In_opt_ IDXGIOutput* pRestrictToOutput, _COM_Outptr_  IDXGISwapChain1** ppSwapChain) override;
    STDMETHODIMP CreateSwapChainForCoreWindow(_In_ IUnknown* pDevice,_In_ IUnknown* pWindow, _In_ const DXGI_SWAP_CHAIN_DESC1* pDesc, _In_opt_ IDXGIOutput* pRestrictToOutput, _COM_Outptr_ IDXGISwapChain1** ppSwapChain) override;
    STDMETHODIMP GetSharedResourceAdapterLuid(_In_ HANDLE hResource, _Out_ LUID* pLuid) override;
    STDMETHODIMP RegisterStereoStatusWindow(_In_ HWND WindowHandle, _In_ UINT wMsg, _Out_ DWORD* pdwCookie) override;
    STDMETHODIMP RegisterStereoStatusEvent(_In_ HANDLE hEvent, _Out_ DWORD* pdwCookie) override;
    STDMETHODIMP_(void) UnregisterStereoStatus(_In_ DWORD dwCookie) override;
    STDMETHODIMP RegisterOcclusionStatusWindow(_In_ HWND WindowHandle, _In_ UINT wMsg, _Out_  DWORD* pdwCookie) override;
    STDMETHODIMP RegisterOcclusionStatusEvent(_In_ HANDLE hEvent, _Out_ DWORD* pdwCookie) override;
    STDMETHODIMP_(void) UnregisterOcclusionStatus(_In_ DWORD dwCookie) override;
    STDMETHODIMP CreateSwapChainForComposition(_In_ IUnknown* pDevice, _In_ const DXGI_SWAP_CHAIN_DESC1* pDesc, _In_opt_ IDXGIOutput* pRestrictToOutput, _COM_Outptr_  IDXGISwapChain1** ppSwapChain) override;
	// IDXGIDisplayControl
	STDMETHODIMP_(BOOL) IsStereoEnabled(void) override;
	STDMETHODIMP_(void) SetStereoEnabled(BOOL enabled) override;
#endif

	// IDXGIFactoryInternal
	STDMETHODIMP CreateSwapPoolInternal(IUnknown*, const DXGI_SWAP_POOL_DESC* pDesc) override;
	STDMETHODIMP RegisterStereoStatusWinRTDisplayPropertiesCB(void* pCB) override;
	STDMETHODIMP UnregisterStereoStatusWinRTDisplayPropertiesCB();

	// IDXGIDebugProducer
	STDMETHODIMP DumpProducer() override;
	STDMETHODIMP DumpObject(IUnknown*) override;
	STDMETHODIMP GetSummaryInfoQueueMessageID(int*) override;

	// Custom
	STDMETHODIMP Initialize(void);

private:

	/// Basic DXGI factory enumerations
	std::vector<DXGIEnumInfo> m_vEnums;

	/// General adapter LUID set
	AdapterLUIDStorage m_vGpuLuids;

	/**
	* @brief Real implementation of EnumAdapter, which creates a real adapter
	* @param Adapter Adapter ID
	* @param[in] Iid Adapter IID to create
	* @param[out] ppAdapter Output adapter
	* @return S_OK if the enumeration succeeded, otherwise an HRESULT error
	*/
	STDMETHODIMP EnumAdaptersReal(_In_ UINT Adapter, _In_ REFIID Iid, _COM_Outptr_ IDXGIAdapter** ppAdapter);

	/**
	* @brief Enumates display outputs by GDI32, if any
	*/
	STDMETHODIMP_(void) RunGdiOutputEnumeration();

	/**
	* @brief Enumerates all real adapters
	* @param[in] hSoft Software adapter to use for enum
	* @param Luids Found adapter LUIDs
	* @return S_OK if the enumeration succeeded, otherwise an HRESULT error
	* @remarks default adapter is GDI32.DLL, which counts as a real one
	*/
	STDMETHODIMP RunD3DKMTAdapterEnumeration(_In_ HMODULE hSoft, AdapterLUIDStorage& Luids);

	/**
	* @brief Formats a GDI Device ID into factory enum
	* @param id DeviceID to format
	* @param en Factory enum to store the results
	*/
	static STDMETHODIMP_(void) FormatGdiDeviceIdToFactoryEnum(const std::wstring& str, DXGIEnumInfo& en);
};
