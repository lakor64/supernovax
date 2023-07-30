/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     Factory class to access all graphics stuff
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#include "pch.h"
#include "dxgifactory.h"
#include "dxgiadapter.h"
#include "dllmain.h"

STDMETHODIMP CDXGIFactory::CreateSoftwareAdapter(_In_ HMODULE Module, _Out_ IDXGIAdapter** ppAdapter)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDXGIFactory::CreateSwapChain(_In_ IUnknown* pDevice, _In_ DXGI_SWAP_CHAIN_DESC* pDesc, _Out_ IDXGISwapChain** ppSwapChain)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDXGIFactory::EnumAdaptersReal(_In_ UINT Adapter, _In_ REFIID Iid, _Out_ void** ppAdapter)
{
	if (!ppAdapter)
		return DXGI_ERROR_INVALID_CALL;

	*ppAdapter = nullptr;

	if (Adapter > m_vAdapters.size())
		return DXGI_ERROR_NOT_FOUND;

	ATL::CComObject<CDXGIAdapter>* adapter;
	HRESULT hr = ATL::CComObject<CDXGIAdapter>::CreateInstance(&adapter);

	if (FAILED(hr))
		return hr;

	hr = adapter->Initialize(this, m_vAdapters.at(Adapter));
	if (FAILED(hr))
	{
		delete adapter;
		return hr;
	}

	hr = adapter->QueryInterface(Iid, ppAdapter);
	if (FAILED(hr))
	{
		delete adapter;
		return hr;
	}

	return S_OK;
}

STDMETHODIMP CDXGIFactory::EnumAdapters(_In_ UINT Adapter, _COM_Outptr_ IDXGIAdapter** ppAdapter)
{
	return EnumAdaptersReal(Adapter, IID_IDXGIAdapter, (void**) ppAdapter);
}

STDMETHODIMP CDXGIFactory::GetWindowAssociation(_Out_ HWND* pWindowHandle)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDXGIFactory::MakeWindowAssociation(_In_ HWND WindowHandle, _In_ UINT Flags)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDXGIFactory::EnumAdapters1(_In_ UINT Adapter, _Out_ IDXGIAdapter1** ppAdapter)
{
	return EnumAdaptersReal(Adapter, IID_IDXGIAdapter1, (void**)ppAdapter);
}

STDMETHODIMP_(BOOL) CDXGIFactory::IsCurrent(void)
{
	return FALSE;
}

STDMETHODIMP CDXGIFactory::Initialize(void)
{
	HRESULT hr;

#if DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8
	// Compatibily for Windows 7 or lesser gdi32.dll
	if (_AtlModule.GetEnumAdapters() != nullptr)
		hr = RunWin8AdapterEnumerator();
	else
		hr = RunGdiAdapterEnumator();
#else
	hr = RunGdiAdapterEnumator();
#endif

	return hr;
}

#if DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8
STDMETHODIMP CDXGIFactory::RunWin8AdapterEnumerator()
{
	return E_NOTIMPL;
}
#endif

STDMETHODIMP CDXGIFactory::RunGdiAdapterEnumator()
{
	DWORD ids = 0;
	NTSTATUS err;
	HRESULT hr;

	for (; ids < UINT_MAX; ids++) // attempt to enumate ALL adapters
	{
		DISPLAY_DEVICEW dd = { 0 };
		dd.cb = sizeof(dd);

		if (!EnumDisplayDevicesW(nullptr, ids, &dd, 0))
			break; // found the last device

		D3DKMT_OPENADAPTERFROMGDIDISPLAYNAME gdi = { 0 };

		memcpy(gdi.DeviceName, dd.DeviceName, sizeof(dd.DeviceName));

		err = _AtlModule.GetOpenAdapterFromGdi()(&gdi);

		if (FAILED(err))
			break;

		// TODO: Check if LUIDs are the same and skip...

		DXGIAdapterDesc desc;
		desc.Handle = gdi.hAdapter;
		desc.AdapterLuid = gdi.AdapterLuid;
		
		hr = GetRemainingDesc(desc);
		if (FAILED(hr))
			return hr;

		m_vAdapters.push_back(desc);
	}

	return S_OK;
}

STDMETHODIMP CDXGIFactory::GetRemainingDesc(DXGIAdapterDesc& desc)
{
	D3DKMT_QUERYADAPTERINFO qa;
	D3DKMT_SEGMENTSIZEINFO segInfo;

	qa.hAdapter = desc.Handle;
	qa.Type = KMTQAITYPE_GETSEGMENTSIZE;
	qa.PrivateDriverDataSize = sizeof(segInfo);
	qa.pPrivateDriverData = &segInfo;

	NTSTATUS s = _AtlModule.GetQueryAdapterInfo()(&qa);

	if (NT_ERROR(s))
		return _AtlModule.GetNtStatusToDosError()(s);

	desc.DedicatedSystemMemory = segInfo.DedicatedSystemMemorySize;
	desc.DedicatedVideoMemory = segInfo.DedicatedVideoMemorySize;
	desc.SharedSystemMemory = segInfo.SharedSystemMemorySize;

	D3DKMT_ADAPTERREGISTRYINFO reg;
	qa.Type = KMTQAITYPE_ADAPTERREGISTRYINFO;
	qa.PrivateDriverDataSize = sizeof(reg);
	qa.pPrivateDriverData = &reg;

	s = _AtlModule.GetQueryAdapterInfo()(&qa);

	if (NT_ERROR(s))
		return _AtlModule.GetNtStatusToDosError()(s);

	auto as = wcslen(reg.AdapterString);

	if (as >= 128)
	{
		wcsncpy(desc.Description, reg.AdapterString, 127);
		desc.Description[127] = L'\0';
	}
	else
	{
		wcsncpy(desc.Description, reg.AdapterString, as);
		desc.Description[as] = L'\0';
	}

	desc.Flags = DXGI_ADAPTER_FLAG_NONE;

#if _WIN32_WINNT > 0x601 && DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8 
	// Windows 8 SDK
	D3DKMT_ADAPTERTYPE at;
	qa.Type = KMTQAITYPE_ADAPTERTYPE;
	qa.PrivateDriverDataSize = sizeof(at);
	qa.pPrivateDriverData = &at;

	s = _AtlModule.GetQueryAdapterInfo()(&qa);

	if (SUCCEEDED(s))
	{
		desc.Flags |= at.SoftwareDevice ? DXGI_ADAPTER_FLAG_SOFTWARE : DXGI_ADAPTER_FLAG_NONE;
	}
#endif

	// TODO
	desc.DeviceId = 0;
	desc.Revision = 0;
	desc.VendorId = 0;

	return S_OK;
}
