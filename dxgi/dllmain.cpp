/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     DLL entrypoint
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#include "pch.h"
#include "dllmain.h"
#include "dxgifactory.h"

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
	hGdi = LoadLibraryW(L"gdi32.dll");
	if (!hGdi)
		return FALSE;

	fnc1 = (D3DKMTOpenAdapterFromGdiDisplayName_)GetProcAddress(hGdi, "D3DKMTOpenAdapterFromGdiDisplayName");

	if (!fnc1)
		return FALSE; // gdi32.dll is NOT from Vista+

#if DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8
	fnc2 = (D3DKMTEnumAdapters2_)GetProcAddress(hGdi, "D3DKMTEnumAdapters2"); // Win8+
#endif

	fnc4 = (D3DKMTQueryAdapterInfo_)GetProcAddress(hGdi, "D3DKMTQueryAdapterInfo");
	if (!fnc4)
		return FALSE;

	fnc5 = (D3DKMTCloseAdapter_)GetProcAddress(hGdi, "D3DKMTCloseAdapter");
	if (!fnc5)
		return FALSE;

	fnc6 = (D3DKMTGetDisplayModeList_)GetProcAddress(hGdi, "D3DKMTGetDisplayModeList");
	if (!fnc6)
		return FALSE;

	fnc7 = (D3DKMTWaitForVerticalBlankEvent_)GetProcAddress(hGdi, "D3DKMTWaitForVerticalBlankEvent");
	if (!fnc7)
		return FALSE;

	fnc8 = (D3DKMTGetDeviceState_)GetProcAddress(hGdi, "D3DKMTGetDeviceState");
	if (!fnc8)
		return FALSE;

	return TRUE;
}

void CATLDXGIModule::MyTerm()
{
	if (hGdi)
		FreeLibrary(hGdi);

	hGdi = nullptr;
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
		if (!IsEqualIID(riid, IID_IDXGIFactory) && !IsEqualIID(riid, IID_IDXGIFactory1) || !IsEqualIID(riid, IID_IDXGIFactory2))
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
		printf("DXGID3D10CreateDevice: %#x %p %p %#x %p %u %p\n", hD3d10, pFactory, pAdapter, Flags, pLevels, levelsCount, device);
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

	HRESULT WINAPI	OpenAdapter10(void* pOpenData)
	{
#ifdef PFF_PROJ_DEBUG
		printf("OpenAdapter10: data %p\n", pOpenData);
		_CrtDbgBreak();
#endif
		return DXGI_ERROR_UNSUPPORTED;
	}

	HRESULT WINAPI	OpenAdapter10_2(void* pOpenData)
	{
#ifdef PFF_PROJ_DEBUG
		printf("OpenAdapter10_2: data %p\n", pOpenData);
		_CrtDbgBreak();
#endif
		return DXGI_ERROR_UNSUPPORTED;
	}
}
