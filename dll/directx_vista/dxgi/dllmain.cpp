/*
 * PROJECT:     ReactX Graphics Infrastructure
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     DLL entrypoint
 * COPYRIGHT:   Copyright 2023 Christian Rendina <pizzaiolo100@proton.me>
 */

#include "pch.h"
#include "dllmain.h"
#include "dxgifactory.h"

/// Global ATL module
CATLDXGIModule _AtlModule;

/// GDI32.DLL pointer
HMODULE g_GDI32 = nullptr;

/// Global pointer to DwmDxGetWindowSharedSurface
DwmDxGetWindowSharedSurface_ DwmDxGetWindowSharedSurface = nullptr;

/// Global pointer to DwmDxUpdateWindowSharedSurface
DwmDxUpdateWindowSharedSurface_ DwmDxUpdateWindowSharedSurface = nullptr;

/// Global pointer to DwmIsCompositionEnabled
DwmIsCompositionEnabled_ DwmIsCompositionEnabled = nullptr;

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
	// Loads all WDDM callbacks

	g_GDI32 = LoadLibraryW(L"gdi32.dll");
	if (!g_GDI32)
		return FALSE;

	m_hDwm = LoadLibraryW(L"dwmapi.dll");
	if (m_hDwm)
	{
		DwmDxGetWindowSharedSurface = (DwmDxGetWindowSharedSurface_)GetProcAddress(m_hDwm, (LPCSTR)100);
		DwmDxUpdateWindowSharedSurface = (DwmDxUpdateWindowSharedSurface_)GetProcAddress(m_hDwm, (LPCSTR)101);
		DwmIsCompositionEnabled = (DwmIsCompositionEnabled_)GetProcAddress(m_hDwm, "DwmIsCompositionEnabled");

		// Some systems might not have dwmapi, this is not a problem
		// as we can fallback to WDDM present
	}

	return TRUE;
}

void CATLDXGIModule::MyTerm()
{
	if (g_GDI32)
	{
		FreeLibrary(g_GDI32);
		g_GDI32 = nullptr;
	}

	if (m_hDwm)
	{
		DwmDxGetWindowSharedSurface = nullptr;
		DwmDxUpdateWindowSharedSurface = nullptr;
		DwmIsCompositionEnabled = nullptr;

		FreeLibrary(m_hDwm);
		m_hDwm = nullptr;
	}
}

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

	/**
	* @brief This function creates the actual IDXGIFactory
	* @param riid IID to create
	* @param ppFactory Output factory
	* @return S_OK in case of success, otherwise specific errors
	*/
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

	/**
	* @brief This function creates the a IDXGIFactory up to 1.2
	* @param Flags creation flags
	* @param riid IID to create
	* @param ppFactory Output factory
	* @return S_OK in case of success, otherwise specific errors
	*/
	HRESULT WINAPI CreateDXGIFactory2(UINT Flags, REFIID riid, _COM_Outptr_ void** ppFactory)
	{
		*ppFactory = nullptr;

#if DXGI_VERSION >= 2
		if (!IsEqualIID(riid, IID_IDXGIFactory) && !IsEqualIID(riid, IID_IDXGIFactory1) && !IsEqualIID(riid, IID_IDXGIFactory2))
			return E_NOINTERFACE;

		return CreateDXGIFactoryReal(riid, ppFactory);
#else
		// DXGI 1.1 doesn't have IDXGIFactory2
		return CreateDXGIFactory1(riid, ppFactory);
#endif

	}

	/**
	* @brief This function creates the a IDXGIFactory up to 1.1
	* @param riid IID to create
	* @param ppFactory Output factory
	* @return S_OK in case of success, otherwise specific errors
	*/
	HRESULT WINAPI CreateDXGIFactory1(REFIID riid, _COM_Outptr_ void** ppFactory)
	{
		*ppFactory = nullptr;

		if (!IsEqualIID(riid, IID_IDXGIFactory) && !IsEqualIID(riid, IID_IDXGIFactory1))
			return E_NOINTERFACE;

		return CreateDXGIFactoryReal(riid, ppFactory);
	}

	/**
	* @brief This function creates the a IDXGIFactory 1.0
	* @param riid IID to create
	* @param ppFactory Output factory
	* @return S_OK in case of success, otherwise specific errors
	*/
	HRESULT WINAPI CreateDXGIFactory(REFIID riid, _COM_Outptr_ void** ppFactory)
	{
		*ppFactory = nullptr;

		if (!IsEqualIID(riid, IID_IDXGIFactory))
			return E_NOINTERFACE;

		return CreateDXGIFactoryReal(riid, ppFactory);
	}

	/**
	* @brief This function creates a Direct3D10 device
	* @param[in] hD3D10 pointer to a D3D10.DLL
	* @param[in] pFactory pointer to a DXGI factory
	* @param[in] pAdapter pointer to an adapter to use for the device
	* @param Flags creation flags
	* @param[in] pLevels Feature levels to use for the device creation
	* @param levelsCount Number of feature levels
	* @param device Output device
	* @return S_OK in case of success, otherwise specific errors
	* @remarks Currently unimplemented as we don't have a custom D3D10 module 
	*/
	HRESULT WINAPI DXGID3D10CreateDevice(_In_ HMODULE hD3d10, _In_ IDXGIFactory* pFactory, _In_ IDXGIAdapter* pAdapter,
		UINT Flags, _In_ const D3D_FEATURE_LEVEL* pLevels, UINT levelsCount, _COM_Outptr_ void** device)
	{
		*device = nullptr;

#ifdef PFF_PROJ_DEBUG
		printf("DXGID3D10CreateDevice: %#llx %p %p %#x %p %u %p\n", (uint64_t)hD3d10, pFactory, pAdapter, Flags, pLevels, levelsCount, device);
		_CrtDbgBreak();
#endif
		return DXGI_ERROR_UNSUPPORTED;
	}

	/**
	* @brief Register one or more custom layers to the Direct3D 10 runtime
	* @param[in] pLayers layers to register
	* @param nLayerCount Number of layers to register
	* @return S_OK in case of success, otherwise specific errors
	* @remarks Currently unimplemented as we don't have a custom D3D10 module 
	*/
	HRESULT WINAPI DXGID3D10RegisterLayers(_In_ const void* pLayers, UINT nLayerCount)
	{
#ifdef PFF_PROJ_DEBUG
		printf("DXGID3D10RegisterLayers: %p %u\n", pLayers, nLayerCount);
		_CrtDbgBreak();
#endif
		return DXGI_ERROR_UNSUPPORTED;
	}


	/**
	* @brief Creates a Direct3D 10 device with a specific layer
	* @param[in] pAdapter pointer to an adapter to use for the device
	* @param Flags creation flags
	* @param pUnknown (Unknown)
	* @param rii (Unknown)
	* @param device Output device
	* @return S_OK in case of success, otherwise specific errors
	* @remarks Currently unimplemented as we don't have a custom D3D10 module
	*/
	HRESULT WINAPI DXGID3D10CreateLayeredDevice(_In_ IDXGIAdapter* pAdapter, UINT Flags, void* pUnknown, _In_ REFIID riid, _COM_Outptr_ void** device)
	{
		*device = nullptr;

#ifdef PFF_PROJ_DEBUG
		printf("DXGID3D10CreateLayeredDevice: %p %#x %p %p\n", pAdapter, Flags, pUnknown, device);
		_CrtDbgBreak();
#endif
		return DXGI_ERROR_UNSUPPORTED;
	}


	/**
	* @brief Gets the size of the layered device
	* @param[in] pLayers Layers to get the size
	* @param numLayers number of layers
	* @return S_OK in case of success, otherwise specific errors
	* @remarks Currently unimplemented as we don't have a custom D3D10 module
	*/
	HRESULT WINAPI DXGID3D10GetLayeredDeviceSize(_In_ const void* pLayers, UINT numLayers)
	{
#ifdef PFF_PROJ_DEBUG
		printf("DXGID3D10GetLayeredDeviceSize: layers %p num %u.\n", pLayers, numLayers);
		_CrtDbgBreak();
#endif
		return DXGI_ERROR_UNSUPPORTED;
	}

	/**
	* @brief Gets the debug interface for DXGI operations
	* @param flags Creation flags
	* @param iid IID of the debug interface to create
	* @param debug Output debug interface
	* @return S_OK in case of success, otherwise specific errors
	* @remarks Currently unimplemented as we don't have a DXGIDebug.dll, this function is for DXGI 1.3+
	*/
	HRESULT WINAPI DXGIGetDebugInterface1(UINT flags, REFIID iid, _COM_Outptr_ void** debug)
	{
		*debug = nullptr;

#if DXGI_VERSION >= 3

#ifdef PFF_PROJ_DEBUG
		printf("DXGIGetDebugInterface1: flags %#x, debug %p.\n", flags, debug);
		_CrtDbgBreak();
#endif
		return E_NOINTERFACE;
#else
		return E_NOINTERFACE; // Trick the system into thinking we don't have the debug runtime installed
#endif
	}
}
