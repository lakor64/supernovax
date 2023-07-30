/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     DLL module
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */
#pragma once

#include "impcb.h"

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

	/** Gets a pointer to D3DKMTOpenAdapterFromGdiDisplayName */
	D3DKMTOpenAdapterFromGdiDisplayName GetOpenAdapterFromGdi() const { return fnc1; }

#if DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8
	/** Gets a pointer to D3DKMTEnumAdapters2 */
	D3DKMTEnumAdapters2 GetEnumAdapters() const { return fnc2; }
#endif

	/** Gets a pointer to RtlNtStatusToDosError */
	RtlNtStatusToDosError_ GetNtStatusToDosError() const { return fnc3; }
	/** */
	D3DKMTQueryAdapterInfo GetQueryAdapterInfo() const { return fnc4; }
private:
	/** GDI32.DLL */
	HMODULE hGdi;
	/** NTDLL.DLL */
	HMODULE hNtDll;

	D3DKMTOpenAdapterFromGdiDisplayName fnc1;
#if DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8
	D3DKMTEnumAdapters2 fnc2;
#endif
	RtlNtStatusToDosError_ fnc3;
	D3DKMTQueryAdapterInfo fnc4;
};

/** Global ATL module export */
extern CATLDXGIModule _AtlModule;
