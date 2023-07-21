#include "pch.h"

class CATLDXGIDebugModule : public ATL::CAtlDllModuleT<CATLDXGIDebugModule>
{
public:

};

//! Global ATL module
CATLDXGIDebugModule _AtlModule;

extern "C"
{
	/*
	* DXGIDEBUG.DLL is not a registrable server object
	* by fact, there's no CLSID exported by this module
	* so we don't have to bother about implementing anything
	* of that regards (such as DllRegisterServer)
	*/ 

	BOOL WINAPI DllMain(_In_ HINSTANCE hInstance, _In_ DWORD dwReason, _In_opt_ LPVOID lpReserved)
	{
		hInstance;
		return _AtlModule.DllMain(dwReason, lpReserved);
	}
}
