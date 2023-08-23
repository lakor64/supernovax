/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     DLL module
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */
#pragma once

class CATLDXGIModule : public ATL::CAtlDllModuleT< CATLDXGIModule >
{
public:
	CATLDXGIModule() = default;
	~CATLDXGIModule() = default;

	/** Custom ATL DllMain */
	BOOL WINAPI DllMain(_In_ DWORD dwReason, _In_opt_ LPVOID lpReserved);

	/** Custom DLL init */
	BOOL MyInit();

	/** Custom DLL shutdown */
	void MyTerm();

	/** Gets GDI32.DLL */
	HMODULE GetGdi32() const { return m_hGdi; }

	/** Get the global thunk version */
	ULONG GetGlobalThunkVersion() const { return m_thunkVer; }

private:
	/** GDI32.DLL */
	HMODULE m_hGdi;
	/** DWMAPI.DLL */
	HMODULE m_hDwm;
	/** D3D10.DLL */
	HMODULE m_hD3d10;
	/** Thunk version */
	ULONG m_thunkVer;
};

/** Global ATL module export */
extern CATLDXGIModule _AtlModule;

/** Api callback, left here because it's easier to manage */
extern DXGI_WAPI_CALLBACKS ApiCallback;
