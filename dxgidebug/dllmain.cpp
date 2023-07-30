/*
 * PROJECT:     ReactX Graphics Infrastructure Debug layer
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     DLL entrypoint
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */
 
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

#ifdef __REACTOS__
		return TRUE;
#else
		return _AtlModule.DllMain(dwReason, lpReserved); // ReactOS...
#endif
	}
}
