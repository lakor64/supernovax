/*
 * PROJECT:     ReactX Graphics Infrastructure
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
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
template <typename T>
inline bool DXGILoadThunkProcs(_In_ HMODULE hGdi, _In_ T& List, _Inout_ FARPROC Procs[])
{
	for (int i = 0; i < sizeof(List) / sizeof(const char*); i++)
	{
		if (!List[i])
			continue; // Two thunks are not discovered

		FARPROC x = GetProcAddress(hGdi, List[i]);

		// it looks like from software adapter that some of this are expected to fail
		/*if (!x)
		{
			x = GetProcAddress(g_GDI32, List[i]);
			if (!x)
				return false;
		}*/

		Procs[i + 1] = x;
	}

	return true;
}
