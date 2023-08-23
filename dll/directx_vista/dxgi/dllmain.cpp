/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     DLL entrypoint
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#include "pch.h"
#include "dllmain.h"
#include "dxgifactory.h"

DXGI_WAPI_CALLBACKS ApiCallback = { 0 };

BOOL WINAPI CATLDXGIModule::DllMain(_In_ DWORD dwReason, _In_opt_ LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_DETACH:
		MyTerm();
		break;

	case DLL_PROCESS_ATTACH:
		return MyInit();
	default:
		break;
	}

	return TRUE;
}

BOOL CATLDXGIModule::MyInit()
{
	m_hGdi = LoadLibraryW(L"gdi32.dll");
	if (!m_hGdi)
		return FALSE;

	ApiCallback.D3DKMTOpenAdapterFromGdiDisplayName = (D3DKMTOpenAdapterFromGdiDisplayName_)GetProcAddress(m_hGdi, "D3DKMTOpenAdapterFromGdiDisplayName");
	ApiCallback.D3DKMTQueryAdapterInfo = (D3DKMTQueryAdapterInfo_)GetProcAddress(m_hGdi, "D3DKMTQueryAdapterInfo");
	ApiCallback.D3DKMTCloseAdapter = (D3DKMTCloseAdapter_)GetProcAddress(m_hGdi, "D3DKMTCloseAdapter");
	ApiCallback.D3DKMTGetDisplayModeList = (D3DKMTGetDisplayModeList_)GetProcAddress(m_hGdi, "D3DKMTGetDisplayModeList");
	ApiCallback.D3DKMTWaitForVerticalBlankEvent = (D3DKMTWaitForVerticalBlankEvent_)GetProcAddress(m_hGdi, "D3DKMTWaitForVerticalBlankEvent");
	ApiCallback.D3DKMTGetDeviceState = (D3DKMTGetDeviceState_)GetProcAddress(m_hGdi, "D3DKMTGetDeviceState");
	ApiCallback.D3DKMTGetThunkVersion = (D3DKMTGetThunkVersion_)GetProcAddress(m_hGdi, "D3DKMTGetThunkVersion");

#if DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN7
	ApiCallback.D3DKMTCheckSharedResourceAccess = (D3DKMTCheckSharedResourceAccess_)GetProcAddress(m_hGdi, "D3DKMTCheckSharedResourceAccess");
#endif

#if DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8
	ApiCallback.ApiCallback = (D3DKMTEnumAdapters2_)GetProcAddress(m_hGdi, "D3DKMTEnumAdapters2"); // Win8+
#endif

	if (!ApiCallback.D3DKMTOpenAdapterFromGdiDisplayName || !ApiCallback.D3DKMTQueryAdapterInfo ||
		!ApiCallback.D3DKMTCloseAdapter || !ApiCallback.D3DKMTGetDisplayModeList ||
		!ApiCallback.D3DKMTWaitForVerticalBlankEvent || !ApiCallback.D3DKMTGetDeviceState)
		return FALSE;

	if (ApiCallback.D3DKMTGetThunkVersion)
		m_thunkVer = ApiCallback.D3DKMTGetThunkVersion();
	else
		m_thunkVer = 1; // Thunk default version

	m_hDwm = LoadLibraryW(L"dwmapi.dll");
	if (m_hDwm)
	{
		ApiCallback.DwmDxGetWindowSharedSurface = (DwmDxGetWindowSharedSurface_)GetProcAddress(m_hDwm, (LPCSTR)100);
		ApiCallback.DwmDxUpdateWindowSharedSurface = (DwmDxUpdateWindowSharedSurface_)GetProcAddress(m_hDwm, (LPCSTR)101);
		ApiCallback.DwmIsCompositionEnabled = (DwmIsCompositionEnabled_)GetProcAddress(m_hDwm, "DwmIsCompositionEnabled");

		// We don't mind if we can't load dwm stuff actually
	}

	return TRUE;
}

void CATLDXGIModule::MyTerm()
{
	if (m_hGdi)
		FreeLibrary(m_hGdi);
	if (m_hDwm)
		FreeLibrary(m_hDwm);

	m_hDwm = nullptr;
	m_hGdi = nullptr;
}

//! Global ATL module
CATLDXGIModule _AtlModule;

extern "C"
{
	/*
	* DXGI.DLL is not a registrable server object
	* by fact, there's no CLSID exported by this module
	* so we don't have to bother about implementing anything
	* of that regards (such as DllRegisterServer)
	*/ 

	BOOL WINAPI DllMain(_In_ HINSTANCE hInstance, _In_ DWORD dwReason, _In_opt_ LPVOID lpReserved)
	{
		hInstance;
		return _AtlModule.DllMain(dwReason, lpReserved);
	}

	static HRESULT WINAPI CreateDXGIFactoryReal(REFIID riid, _COM_Outptr_ void** ppFactory)
	{
		if (!ppFactory)
			return DXGI_ERROR_INVALID_CALL;

		*ppFactory = nullptr;

		ATL::CComObject<CDXGIFactory>* factory;
		HRESULT hr = ATL::CComObject<CDXGIFactory>::CreateInstance(&factory);

		if (FAILED(hr))
			return hr;

		hr = factory->Initialize();

		if (FAILED(hr))
		{
			delete factory;
			return hr;
		}

		hr = factory->QueryInterface(riid, ppFactory);

		if (FAILED(hr))
		{
			delete factory;
			return hr;
		}

		return S_OK;
	}

	HRESULT WINAPI CreateDXGIFactory2(UINT Flags, REFIID riid, _COM_Outptr_ void** ppFactory)
	{
#if DXGI_VERSION >= 2
		if (!IsEqualIID(riid, IID_IDXGIFactory) && !IsEqualIID(riid, IID_IDXGIFactory1) && !IsEqualIID(riid, IID_IDXGIFactory2))
			return E_NOINTERFACE;

		return CreateDXGIFactoryReal(riid, ppFactory);
#else
		// DXGI 1.1 doesn't have IDXGIFactory2
		return CreateDXGIFactory1(riid, ppFactory);
#endif

	}

	HRESULT WINAPI CreateDXGIFactory1(REFIID riid, _COM_Outptr_ void** ppFactory)
	{
		if (!IsEqualIID(riid, IID_IDXGIFactory) && !IsEqualIID(riid, IID_IDXGIFactory1))
			return E_NOINTERFACE;

		return CreateDXGIFactoryReal(riid, ppFactory);
	}

	HRESULT WINAPI CreateDXGIFactory(REFIID riid, _COM_Outptr_ void** ppFactory)
	{
		if (!IsEqualIID(riid, IID_IDXGIFactory))
			return E_NOINTERFACE;

		return CreateDXGIFactoryReal(riid, ppFactory);
	}

	HRESULT WINAPI DXGID3D10CreateDevice(_In_ HMODULE hD3d10, _In_ IDXGIFactory* pFactory, _In_ IDXGIAdapter* pAdapter,
		_In_ UINT Flags, _In_ const D3D_FEATURE_LEVEL* pLevels, _In_ UINT levelsCount, _COM_Outptr_ void** device)
	{
#ifdef PFF_PROJ_DEBUG
		printf("DXGID3D10CreateDevice: %#llx %p %p %#x %p %u %p\n", (uint64_t)hD3d10, pFactory, pAdapter, Flags, pLevels, levelsCount, device);
		_CrtDbgBreak();
#endif
		return DXGI_ERROR_UNSUPPORTED;
	}

	HRESULT WINAPI DXGID3D10RegisterLayers(const void* pLayers, _In_ UINT nLayerCount)
	{
#ifdef PFF_PROJ_DEBUG
		printf("DXGID3D10RegisterLayers: %p %u\n", pLayers, nLayerCount);
		_CrtDbgBreak();
#endif
		return DXGI_ERROR_UNSUPPORTED;
	}

	HRESULT WINAPI DXGID3D10CreateLayeredDevice(_In_ IDXGIAdapter* pAdapter, _In_ UINT Flags, void* pUnknown, _In_ REFIID riid, _COM_Outptr_ void** device)
	{
#ifdef PFF_PROJ_DEBUG
		printf("DXGID3D10CreateLayeredDevice: %p %#x %p %p\n", pAdapter, Flags, pUnknown, device);
		_CrtDbgBreak();
#endif
		return DXGI_ERROR_UNSUPPORTED;
	}

	HRESULT WINAPI DXGIGetDebugInterface1(UINT flags, REFIID iid, void** debug)
	{
#ifdef PFF_PROJ_DEBUG
		printf("DXGIGetDebugInterface1: flags %#x, debug %p.\n", flags, debug);
		_CrtDbgBreak();
#endif
		return DXGI_ERROR_UNSUPPORTED;
	}

	HRESULT WINAPI DXGID3D10GetLayeredDeviceSize(_In_ const void* pLayers, UINT numLayers)
	{
#ifdef PFF_PROJ_DEBUG
		printf("DXGID3D10GetLayeredDeviceSize: layers %p num %u.\n", pLayers, numLayers);
		_CrtDbgBreak();
#endif
		return DXGI_ERROR_UNSUPPORTED;
	}

}
