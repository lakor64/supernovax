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
#include "utils.h"

CDXGIFactory::~CDXGIFactory()
{
	D3DKMT_CLOSEADAPTER ca;
	for (auto it = m_vAdapters.begin(); it != m_vAdapters.end(); it++)
	{
		for (auto it2 = it->Outputs.begin(); it2 != it->Outputs.end(); it2++)
		{
#ifdef PFF_PROJ_DEBUG
			printf("CDXGIFactory->CloseAdapter this:%p handle:%u\n", this, it->Handle);
#endif

			ca.hAdapter = it2->Handle;
			_AtlModule.GetCloseAdapter()(&ca);
		}
	}
}

STDMETHODIMP CDXGIFactory::CreateSoftwareAdapter(_In_ HMODULE Module, _Out_ IDXGIAdapter** ppAdapter)
{
	if (!ppAdapter)
		return DXGI_ERROR_INVALID_CALL;

	*ppAdapter = nullptr;

	if (!Module)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGIFactory::CreateSwapChain(_In_ IUnknown* pDevice, _In_ DXGI_SWAP_CHAIN_DESC* pDesc, _Out_ IDXGISwapChain** ppSwapChain)
{
	if (!ppSwapChain)
		return DXGI_ERROR_INVALID_CALL;

	*ppSwapChain = nullptr;

	if (!pDevice || !pDesc)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGIFactory::EnumAdaptersReal(_In_ UINT Adapter, _In_ REFIID Iid, _Out_ void** ppAdapter)
{
	if (!ppAdapter)
		return DXGI_ERROR_INVALID_CALL;

	*ppAdapter = nullptr;

	if ((Adapter + 1) > m_vAdapters.size())
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
	if (!pWindowHandle)
		return DXGI_ERROR_INVALID_CALL;

	if (IsInSession0())
		return DXGI_ERROR_NOT_CURRENTLY_AVAILABLE;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGIFactory::MakeWindowAssociation(_In_ HWND WindowHandle, _In_ UINT Flags)
{
	if (!WindowHandle)
		return DXGI_ERROR_INVALID_CALL;

	if (IsInSession0())
		return DXGI_ERROR_NOT_CURRENTLY_AVAILABLE;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGIFactory::Initialize(void)
{
	return RunGdiAdapterEnumator();
}

STDMETHODIMP CDXGIFactory::RunGdiAdapterEnumator()
{
	DWORD ids = 0;
	NTSTATUS err;

	for (; ids < MAX_ENUM_ADAPTERS; ids++) // attempt to enumate ALL adapters
	{
		DISPLAY_DEVICEW dd = { 0 };
		dd.cb = sizeof(dd);

		if (!EnumDisplayDevicesW(nullptr, ids, &dd, 0))
			break; // found the last device

		if (!(dd.StateFlags & DISPLAY_DEVICE_ACTIVE))
			continue; // skip devices that are NOT active, tested via dxgi behavour

		D3DKMT_OPENADAPTERFROMGDIDISPLAYNAME gdi = { 0 };

		memcpy(gdi.DeviceName, dd.DeviceName, sizeof(dd.DeviceName));

		err = _AtlModule.GetOpenAdapterFromGdi()(&gdi);

		if (FAILED(err))
			break; // might not have an adapter on this device, exit

#ifdef PFF_PROJ_DEBUG
		printf("CDXGIFactory->OpenAdapter this:%p handle:%u vidpn:%u\n", this, gdi.hAdapter, gdi.VidPnSourceId);
#endif

		bool skipThis = false;

		for (auto it = m_vAdapters.begin(); it != m_vAdapters.end(); it++)
		{
			if (IsEqualLUID(gdi.AdapterLuid, it->AdapterLuid))
			{
				// fill the new monitor info and skip adapter enumeration

				DXGIOutputDescBasic b;
				b.Handle = gdi.hAdapter;
				b.VidPn = gdi.VidPnSourceId;
				WcsMaxCpy(gdi.DeviceName, b.DeviceName, 31);

				it->Outputs.push_back(b);
				skipThis = true;
				break;
			}
		}

		if (skipThis)
		{
			continue;
		}

		DXGIAdapterDesc desc;
		memset(&desc, 0, sizeof(desc));

		desc.Handle = gdi.hAdapter;
		desc.AdapterLuid = gdi.AdapterLuid;
		WcsMaxCpy(dd.DeviceName, desc.Description, 127);

		DXGIOutputDescBasic b;
		b.Handle = gdi.hAdapter;
		b.VidPn = gdi.VidPnSourceId;
		WcsMaxCpy(gdi.DeviceName, b.DeviceName, 31);

		desc.Outputs.push_back(b);

		desc.DeviceId = 0;
		desc.VendorId = 0;
		desc.Revision = 0;
		desc.SubSysId = 0;

		wchar_t tmp[128] = { '0', 'x', '\0' };

		// Format is: PCI/VEN_#####&DEV_#####&SUBSYS_######&REV_###

		/*
			THIS CODE IS HORRIBLE, PLEASE REFACTOR AND MODIFY THIS
			INTO SOMETHING THAT ACTUALLY MAKES SENSE!!!!
		*/

		auto x = wcschr(dd.DeviceID + 8, L'&');
		auto z = wcslen(dd.DeviceID);
		int i;

		if (x)
		{
			wcsncpy(tmp + 2, dd.DeviceID + 8, x - dd.DeviceID - 8);
			
			if (StrToIntEx(tmp, STIF_SUPPORT_HEX, &i))
				desc.VendorId = (UINT)i;

			auto y = wcschr(x + 5, L'&');
			if (y)
			{
				wcsncpy(tmp + 2, x + 5, y - x - 5);
				if (StrToIntEx(tmp, STIF_SUPPORT_HEX, &i))
					desc.DeviceId = (UINT)i;

				x = wcschr(y + 8, L'&');
				if (x)
				{
					wcsncpy(tmp + 2, y + 8, x - y - 8);
					if (StrToIntEx(tmp, STIF_SUPPORT_HEX, &i))
						desc.SubSysId = (UINT)i;
					
					wcsncpy(tmp + 2, x + 5, z - (x - dd.DeviceID) - 5);
					tmp[z - (x - dd.DeviceID) - 5 + 2] = L'\0';
					if (StrToIntEx(tmp, STIF_SUPPORT_HEX, &i))
						desc.Revision = (UINT)i;
				}
				else
				{
					wcsncpy(tmp + 2, y + 8, z - (y - dd.DeviceID) - 8);
					if (StrToIntEx(tmp, STIF_SUPPORT_HEX, &i))
						desc.SubSysId = (UINT)i;
				}
			}
			else
			{
				wcsncpy(tmp + 2, x + 5, z - (x - dd.DeviceID) - 5);
				if (StrToIntEx(tmp, STIF_SUPPORT_HEX, &i))
					desc.DeviceId = (UINT)i;
			}
		}
		else
		{
			wcsncpy(tmp + 2, dd.DeviceID + 8, z - 8);
			if (StrToIntEx(tmp, STIF_SUPPORT_HEX, &i))
				desc.VendorId = (UINT)i;
		}

		m_vAdapters.push_back(desc);
	}

	return S_OK;
}

#if DXGI_VERSION >= 1
STDMETHODIMP CDXGIFactory::EnumAdapters1(_In_ UINT Adapter, _Out_ IDXGIAdapter1** ppAdapter)
{
	return EnumAdaptersReal(Adapter, IID_IDXGIAdapter1, (void**)ppAdapter);
}

STDMETHODIMP_(BOOL) CDXGIFactory::IsCurrent(void)
{
	return FALSE;
}
#endif

#if DXGI_VERSION >= 2
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
