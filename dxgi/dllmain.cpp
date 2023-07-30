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

	hNtDll = LoadLibraryW(L"ntdll.dll");
	if (!hNtDll)
		return FALSE;

	fnc1 = (D3DKMTOpenAdapterFromGdiDisplayName)GetProcAddress(hGdi, "D3DKMTOpenAdapterFromGdiDisplayName");

	if (!fnc1)
		return FALSE; // gdi32.dll is NOT from Vista+

#if DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8
	fnc2 = (D3DKMTEnumAdapters2)GetProcAddress(hGdi, "D3DKMTEnumAdapters2"); // Win8+
#endif

	fnc3 = (RtlNtStatusToDosError_)GetProcAddress(hNtDll, "RtlNtStatusToDosError");
	if (!fnc3)
		return FALSE;

	fnc4 = (D3DKMTQueryAdapterInfo)GetProcAddress(hGdi, "D3DKMTQueryAdapterInfo");
	if (!fnc4)
		return FALSE;

	return TRUE;
}

void CATLDXGIModule::MyTerm()
{
	if (hGdi)
		FreeLibrary(hGdi);
	if (hNtDll)
		FreeLibrary(hNtDll);

	hNtDll = nullptr;
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

	HRESULT WINAPI CreateDXGIFactory1(REFIID riid, _COM_Outptr_ void** ppFactory)
	{
		if (!ppFactory)
			return DXGI_ERROR_INVALID_CALL;

		*ppFactory = nullptr;

		if (!IsEqualIID(riid, IID_IDXGIFactory) && !IsEqualIID(riid, IID_IDXGIFactory1))
			return E_NOINTERFACE;

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

	HRESULT WINAPI CreateDXGIFactory(REFIID riid, _COM_Outptr_ void** ppFactory)
	{
		if (!IsEqualIID(riid, IID_IDXGIFactory))
			return E_NOINTERFACE;

		return CreateDXGIFactory1(riid, ppFactory);
	}
}
