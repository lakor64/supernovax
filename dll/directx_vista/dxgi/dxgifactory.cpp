/*
 * PROJECT:     ReactX Graphics Infrastructure
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     Factory class to access all graphics stuff
 * COPYRIGHT:   Copyright 2023 Christian Rendina <pizzaiolo100@proton.me>
 */

#include "pch.h"
#include "dxgifactory.h"
#include "dxgiadapter.h"
#include "dllmain.h"
#include "utils.h"
#include "dxgiswapchain.h"

CDXGIFactory::~CDXGIFactory()
{
	D3DKMT_CLOSEADAPTER ca;
	D3DKMTCloseAdapter_ close = (D3DKMTCloseAdapter_)GetProcAddress(g_GDI32, "D3DKMTCloseAdapter");

	if (!close)
		return;

	// close all the real adapters 
	for (auto& p : m_vEnums)
	{
		if (p.AdapterHandle == D3DGPU_NULL)
			continue;

		ca.hAdapter = p.AdapterHandle;
		close(&ca);
	}
}

STDMETHODIMP CDXGIFactory::CreateSoftwareAdapter(_In_ HMODULE Module, _Out_ IDXGIAdapter** ppAdapter)
{
	if (!ppAdapter)
		return DXGI_ERROR_INVALID_CALL;

	*ppAdapter = nullptr;

	if (!Module)
		return DXGI_ERROR_INVALID_CALL;

	ATL::CComObject<CDXGIAdapter>* adapter;
	auto hr = ATL::CComObject<CDXGIAdapter>::CreateInstance(&adapter);

	if (FAILED(hr))
		return hr;

	for (const auto& x : m_vEnums)
	{
		// add all the outputs regardless, we don't care if they are alive or not
		//  as a software adapter will have all custom handles anyway
		adapter->AddOutput(x);
	}

	hr = adapter->Initialize(this, Module);
	if (FAILED(hr))
	{
		delete adapter;
		return hr;
	}

	adapter->AddRef();
	*ppAdapter = adapter;

	return S_OK;
}

/**
* @brief This function creates a swapchain
* @param[in] pDevice Device context
* @param[in] pDesc Swap chain descriptor
* @param[out] ppSwapChain Swap chain output
* @remarks pDevice types:
* - Direct3D10 context -> IDXGIDevice
* - Direct3D11 context -> ID3D11Device
* - Direct3D12 context -> ID3D12CommandQueue
*/
STDMETHODIMP CDXGIFactory::CreateSwapChain(_In_ IUnknown* pDevice, _In_ DXGI_SWAP_CHAIN_DESC* pDesc, _Out_ IDXGISwapChain** ppSwapChain)
{
	if (!ppSwapChain)
		return DXGI_ERROR_INVALID_CALL;

	*ppSwapChain = nullptr;

	if (!pDevice || !pDesc)
		return DXGI_ERROR_INVALID_CALL;

	ATL::CComObject<CDXGISwapChain>* swapChain;
	HRESULT hr = ATL::CComObject<CDXGISwapChain>::CreateInstance(&swapChain);

	if (FAILED(hr))
		return hr;

	hr = swapChain->Initialize(this, pDevice, pDesc);

	if (FAILED(hr))
	{
		delete swapChain;
		return hr;
	}

	swapChain->AddRef();
	*ppSwapChain = swapChain;

	return S_OK;
}

STDMETHODIMP CDXGIFactory::EnumAdaptersReal(_In_ UINT Adapter, _In_ REFIID Iid, _COM_Outptr_ IDXGIAdapter** ppAdapter)
{
	if (!ppAdapter)
		return DXGI_ERROR_INVALID_CALL;

	*ppAdapter = nullptr;

	if ((Adapter + 1) > m_vGpuLuids.size())
		return DXGI_ERROR_NOT_FOUND;

	ATL::CComObject<CDXGIAdapter>* adapter;
	HRESULT hr = ATL::CComObject<CDXGIAdapter>::CreateInstance(&adapter);

	if (FAILED(hr))
		return hr;

	auto luid = m_vGpuLuids.at(Adapter);

	for (const auto& x : m_vEnums)
	{
		// add all the outputs associated to this adapter

		if (IsEqualLUID(x.AdapterLuid, luid))
		{
			adapter->AddOutput(x);
		}
	}

	hr = adapter->Initialize(this);
	if (FAILED(hr))
	{
		delete adapter;
		return hr;
	}

	adapter->AddRef();
	*ppAdapter = adapter;

	return S_OK;
}

STDMETHODIMP CDXGIFactory::EnumAdapters(_In_ UINT Adapter, _COM_Outptr_ IDXGIAdapter** ppAdapter)
{
	return EnumAdaptersReal(Adapter, IID_IDXGIAdapter, ppAdapter);
}

STDMETHODIMP CDXGIFactory::GetWindowAssociation(_Out_ HWND* pWindowHandle)
{
	if (!pWindowHandle)
		return DXGI_ERROR_INVALID_CALL;

	if (IsInSession0())
		return DXGI_ERROR_NOT_CURRENTLY_AVAILABLE;

	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGIFactory::GetWindowAssociation", "DEBUG", MB_OK);

	return E_NOTIMPL;
}

STDMETHODIMP CDXGIFactory::MakeWindowAssociation(_In_ HWND WindowHandle, _In_ UINT Flags)
{
	if (!WindowHandle)
		return DXGI_ERROR_INVALID_CALL;

	if (IsInSession0())
		return DXGI_ERROR_NOT_CURRENTLY_AVAILABLE;

	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGIFactory::MakeWindowAssociation", "DEBUG", MB_OK);

	return E_NOTIMPL;
}

STDMETHODIMP CDXGIFactory::Initialize(void)
{
	// enumerate all outputs
	RunGdiOutputEnumeration();

	// enumerate all real GPUs

	auto hr = RunD3DKMTAdapterEnumeration(g_GDI32, m_vGpuLuids);
	if (FAILED(hr))
		return hr; // if you want to have XDDM XP support / something without GDI32.DLL WDDM then modify here

	return S_OK;
}

STDMETHODIMP_(void) CDXGIFactory::RunGdiOutputEnumeration()
{
	for (auto i = 0U; i < MAX_ENUM_OUTPUTS; i++)
	{
		DXGIEnumInfo dxgienum = { 0 };

		DISPLAY_DEVICEW dd = { 0 };
		dd.cb = sizeof(dd);

		if (!EnumDisplayDevicesW(nullptr, i, &dd, 0))
			break; // found the last device

		if (!(dd.StateFlags & DISPLAY_DEVICE_ACTIVE))
			continue; // skip devices that are NOT active, tested via DXGI behavour

		StringCchCopyN(dxgienum.DeviceName, 32, dd.DeviceName, 32);
		StringCchCopyN(dxgienum.DeviceString, 128, dd.DeviceString, 128);

		FormatGdiDeviceIdToFactoryEnum(dd.DeviceID, dxgienum);

		m_vEnums.push_back(dxgienum);
	}
}

STDMETHODIMP_(void) CDXGIFactory::FormatGdiDeviceIdToFactoryEnum(const std::wstring& id, DXGIEnumInfo& en)
{
	en.DeviceId = 0;
	en.Revision = 0;
	en.VendorId = 0;
	en.SubSystemId = 0;

	// Format is: PCI/VEN_#####&DEV_#####&SUBSYS_######&REV_###

	if (memcmp(id.c_str(), L"PCI\\", 8) != 0)
		return; // invalid string

	auto src = id.substr(4);
	size_t e;
	size_t tmp = 0;

	while (true)
	{
		e = src.find('&');
		if (e == std::wstring::npos)
			e = src.length();

		std::wstring prefix = L"0x";

		if (memcmp(src.c_str(), L"VEN_", 4) == 0)
		{
			prefix += src.substr(4, e - 4);
			en.VendorId = UINT(wcstoul(prefix.c_str(), nullptr, 16));
		}
		else if (memcmp(src.c_str(), L"DEV_", 4) == 0)
		{
			prefix += src.substr(4, e - 4);
			en.DeviceId = UINT(wcstoul(prefix.c_str(), nullptr, 16));
		}
		else if (memcmp(src.c_str(), L"REV_", 4) == 0)
		{
			prefix += src.substr(4, e - 4);
			en.Revision = UINT(wcstoul(prefix.c_str(), nullptr, 16));
		}
		else if (memcmp(src.c_str(), L"SUBSYS_", 7) == 0)
		{
			prefix += src.substr(7, e - 7);
			en.SubSystemId = UINT(wcstoul(prefix.c_str(), nullptr, 16));
		}
		else
			return;

		if (src.length() == e)
			break;

		src = src.substr(e + 1);
	}
}

STDMETHODIMP CDXGIFactory::RunD3DKMTAdapterEnumeration(_In_ HMODULE hSoft, AdapterLUIDStorage& Luids)
{
	D3DKMTOpenAdapterFromGdiDisplayName_ openAdapter = (D3DKMTOpenAdapterFromGdiDisplayName_)GetProcAddress(hSoft, "D3DKMTOpenAdapterFromGdiDisplayName");

	if (!openAdapter)
		return DXGI_ERROR_UNSUPPORTED;

	NTSTATUS err;

	for (auto i = 0U; i < m_vEnums.size(); i++)
	{
		auto& x = m_vEnums.at(i);

		D3DKMT_OPENADAPTERFROMGDIDISPLAYNAME gdi = { 0 };
		StringCchCopyN(gdi.DeviceName, 32, x.DeviceName, 32);
		err = openAdapter(&gdi);

		if (FAILED(err))
			break; // might not have an adapter on this device, exit

		x.AdapterLuid = gdi.AdapterLuid;
		x.AdapterHandle = gdi.hAdapter;
		x.VidPn = gdi.VidPnSourceId;

		bool found = false;

		// add the gpu to the list of GPUs if the LUID was not found

		for (const auto& p : Luids)
		{
			found |= IsEqualLUID(p, x.AdapterLuid);
		}

		if (!found)
			Luids.push_back(x.AdapterLuid);
	}

	return S_OK;
}

STDMETHODIMP CDXGIFactory::CreateSwapPoolInternal(IUnknown*, const DXGI_SWAP_POOL_DESC* pDesc)
{
	MessageBoxA(nullptr, "Call CreateSwapPoolInternal", "dxgi.dll", MB_OK);
	return E_FAIL;
}

STDMETHODIMP CDXGIFactory::RegisterStereoStatusWinRTDisplayPropertiesCB(void* pCB)
{
	MessageBoxA(nullptr, "Call RegisterStereoStatusWinRTDisplayPropertiesCB", "dxgi.dll", MB_OK);
	return S_OK;
}

STDMETHODIMP CDXGIFactory::UnregisterStereoStatusWinRTDisplayPropertiesCB()
{
	MessageBoxA(nullptr, "Call UnregisterStereoStatusWinRTDisplayPropertiesCB", "dxgi.dll", MB_OK);
	return S_OK;
}
STDMETHODIMP CDXGIFactory::DumpProducer()
{
	MessageBoxA(nullptr, "Call DumpProducer", "dxgi.dll", MB_OK);
	return E_FAIL;
}

STDMETHODIMP CDXGIFactory::DumpObject(IUnknown*)
{
	MessageBoxA(nullptr, "Call DumpObject", "dxgi.dll", MB_OK);
	return E_FAIL;
}

STDMETHODIMP CDXGIFactory::GetSummaryInfoQueueMessageID(int*)
{
	MessageBoxA(nullptr, "Call GetSummaryInfoQueueMessageID", "dxgi.dll", MB_OK);
	return E_FAIL;
}


#if DXGI_VERSION >= 1
STDMETHODIMP CDXGIFactory::EnumAdapters1(_In_ UINT Adapter, _Out_ IDXGIAdapter1** ppAdapter)
{
	return EnumAdaptersReal(Adapter, IID_IDXGIAdapter1, (IDXGIAdapter**)ppAdapter);
}

STDMETHODIMP_(BOOL) CDXGIFactory::IsCurrent(void)
{
	return FALSE;
}
#endif

#if DXGI_VERSION >= 2
STDMETHODIMP_(BOOL) CDXGIFactory::IsStereoEnabled(void)
{
	return FALSE;
}

STDMETHODIMP_(void) CDXGIFactory::SetStereoEnabled(BOOL enabled)
{

}

STDMETHODIMP_(BOOL) CDXGIFactory::IsWindowedStereoEnabled(void)
{
	return FALSE;
}

STDMETHODIMP CDXGIFactory::CreateSwapChainForHwnd(_In_ IUnknown* pDevice, _In_ HWND hWnd, _In_ const DXGI_SWAP_CHAIN_DESC1* pDesc, _In_opt_ const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pFullscreenDesc, _In_opt_ IDXGIOutput* pRestrictToOutput, _COM_Outptr_  IDXGISwapChain1** ppSwapChain)
{
	return DXGI_ERROR_UNSUPPORTED;
}

STDMETHODIMP CDXGIFactory::CreateSwapChainForCoreWindow(_In_ IUnknown* pDevice, _In_ IUnknown* pWindow, _In_ const DXGI_SWAP_CHAIN_DESC1* pDesc, _In_opt_ IDXGIOutput* pRestrictToOutput, _COM_Outptr_ IDXGISwapChain1** ppSwapChain)
{
	return DXGI_ERROR_UNSUPPORTED;
}

STDMETHODIMP CDXGIFactory::GetSharedResourceAdapterLuid(_In_ HANDLE hResource, _Out_ LUID* pLuid)
{
	return DXGI_ERROR_UNSUPPORTED;
}

STDMETHODIMP CDXGIFactory::RegisterStereoStatusWindow(_In_ HWND WindowHandle, _In_ UINT wMsg, _Out_ DWORD* pdwCookie)
{
	return DXGI_ERROR_UNSUPPORTED;
}

STDMETHODIMP CDXGIFactory::RegisterStereoStatusEvent(_In_ HANDLE hEvent, _Out_ DWORD* pdwCookie)
{
	return DXGI_ERROR_UNSUPPORTED;
}

STDMETHODIMP_(void) CDXGIFactory::UnregisterStereoStatus(_In_ DWORD dwCookie)
{

}

STDMETHODIMP CDXGIFactory::RegisterOcclusionStatusWindow(_In_ HWND WindowHandle, _In_ UINT wMsg, _Out_  DWORD* pdwCookie)
{
	return DXGI_ERROR_UNSUPPORTED;
}

STDMETHODIMP CDXGIFactory::RegisterOcclusionStatusEvent(_In_ HANDLE hEvent, _Out_ DWORD* pdwCookie)
{
	return DXGI_ERROR_UNSUPPORTED;
}

STDMETHODIMP_(void) CDXGIFactory::UnregisterOcclusionStatus(_In_ DWORD dwCookie)
{

}
STDMETHODIMP CDXGIFactory::CreateSwapChainForComposition(_In_ IUnknown* pDevice, _In_ const DXGI_SWAP_CHAIN_DESC1* pDesc, _In_opt_ IDXGIOutput* pRestrictToOutput, _COM_Outptr_  IDXGISwapChain1** ppSwapChain)
{
	return DXGI_ERROR_UNSUPPORTED;
}
#endif
