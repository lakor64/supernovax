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
	HMODULE GetGdi32() const { return hGdi; }

	DWORD GetGlobalThunkVersion() const { return thunKVer; }

	/** Gets a pointer to D3DKMTOpenAdapterFromGdiDisplayName */
	D3DKMTOpenAdapterFromGdiDisplayName_ GetOpenAdapterFromGdi() const { return fnc1; }
#if DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8
	/** Gets a pointer to D3DKMTEnumAdapters2 */
	D3DKMTEnumAdapters2_ GetEnumAdapters() const { return fnc2; }
#endif
	/** */
	D3DKMTQueryAdapterInfo_ GetQueryAdapterInfo() const { return fnc4; }
	/** */
	D3DKMTCloseAdapter_ GetCloseAdapter() const { return fnc5; }
	/** */
	D3DKMTGetDisplayModeList_ GetDisplayModeList() const { return fnc6; }
	
	D3DKMTWaitForVerticalBlankEvent_ GetWaitForVBlank() const { return fnc7; }

	D3DKMTGetDeviceState_ GetDeviceState() const { return fnc8; }

private:
	/** GDI32.DLL */
	HMODULE hGdi;
	DWORD thunKVer;

	D3DKMTOpenAdapterFromGdiDisplayName_ fnc1;
#if DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8
	D3DKMTEnumAdapters2_ fnc2;
#endif
	D3DKMTQueryAdapterInfo_ fnc4;
	D3DKMTCloseAdapter_ fnc5;
	D3DKMTGetDisplayModeList_ fnc6;
	D3DKMTWaitForVerticalBlankEvent_ fnc7;
	D3DKMTGetDeviceState_ fnc8;
	D3DKMTGetThunkVersion_ fnc9;
};

/** Global ATL module export */
extern CATLDXGIModule _AtlModule;
