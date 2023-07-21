#include "pch.h"
#include "dxgifactory.h"

class CATLDXGIModule : public ATL::CAtlDllModuleT< CATLDXGIModule >
{
public:

};

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

		*ppFactory = NULL;

		if (!IsEqualIID(riid, IID_IDXGIFactory) || !IsEqualIID(riid, IID_IDXGIFactory1))
			return E_NOINTERFACE;

		ATL::CComObject<CDXGIFactory>* factory;
		HRESULT hr = ATL::CComObject<CDXGIFactory>::CreateInstance(&factory);

		if (FAILED(hr))
			return hr;

		hr = factory->Initialize();

		if (FAILED(hr))
			return hr;

		hr = factory->QueryInterface(riid, ppFactory);

		if (FAILED(hr))
			return hr;

		factory->AddRef();
		return S_OK;
	}

	HRESULT WINAPI CreateDXGIFactory(REFIID riid, _COM_Outptr_ void** ppFactory)
	{
		if (!IsEqualIID(riid, IID_IDXGIFactory))
			return E_NOINTERFACE;

		return CreateDXGIFactory1(riid, ppFactory);
	}
}
