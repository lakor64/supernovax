/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     Thunk loader
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#pragma once

#include "dxgithunks.h"

inline HRESULT DXGILoadThunkFunction(_In_ HMODULE hGdi, _In_ const char* Address, _Out_ FARPROC* Data)
{
	//NOTE: remove this code once I figure all the thunks!!!!
	if (!Address)
	{
		*Data = nullptr;
		return S_OK;
	}
	//NOTE: ^^^^^^

	*Data = GetProcAddress(hGdi, Address);
	if (!*Data)
		return E_NOINTERFACE; // NOTE: DX9 on DX10 device should not complain about lot of this things...

	return S_OK;
}

template <typename T, size_t L>
inline HRESULT DXGILoadThunk(_In_ HMODULE hGdi, _In_ const char** List, _Inout_ T* procs)
{
	HRESULT hs;
	FARPROC* pStart = (FARPROC*)procs; // super unsafe code yeah...
	pStart++; // skip the length

	for (int i = 0; i < L; i++, pStart++)
	{
		hs = DXGILoadThunkFunction(hGdi, List[i], pStart);

		if (FAILED(hs))
			hs = S_OK; // NOTE: SUPER TEMP HACK! FIX
	}

	return hs;
}

#define DEF_THUNK_FUN(n) \
	inline HRESULT DXGILoadThunk(_In_ HMODULE hGdi, _Inout_ DXGI_THUNKS_V##n * procs) { \
		return DXGILoadThunk<DXGI_THUNKS_V##n, DXGI_THUNKS_NAMES_V##n##_LENGTH>(hGdi, (const char**)DXGI_THUNKS_NAMES_V##n##, procs);\
	}

DEF_THUNK_FUN(1)
DEF_THUNK_FUN(2)
DEF_THUNK_FUN(3)
DEF_THUNK_FUN(4)
