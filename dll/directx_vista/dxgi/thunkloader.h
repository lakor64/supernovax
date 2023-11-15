/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     Thunk loader
 * COPYRIGHT:   Copyright 2023 Christian Rendina <pizzaiolo100@proton.me>
 */

#pragma once

#include "dxgithunks.h"

/**
* @brief Loads relative thunk procedures
* @param[in] hGdi GDI32.DLL reference
* @param[in] List lists of functions to load
* @param[out] Procs output procedures
* @return true in case of success, otherwise false
*/
inline bool DXGILoadThunkProcs(_In_ HMODULE hGdi, _In_ const char* const* List, _Inout_ FARPROC Procs[])
{
	for (int i = 0; i < sizeof(List); i++)
	{
		if (!List[i])
			continue; // Two thunks are not discovered

		FARPROC x = GetProcAddress(hGdi, List[i]);

		if (!x)
			return false;

		Procs[i + 1] = x;
	}

	return true;
}
