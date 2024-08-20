/*
 * PROJECT:     SupernovaX Graphics Infrastructure
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     DLL module
 * COPYRIGHT:   Copyright 2023 Christian Rendina <pizzaiolo100@proton.me>
 */
#pragma once

#include "dllimports.h"

class CATLDXGIModule : public ATL::CAtlDllModuleT< CATLDXGIModule >
{
public:
	CATLDXGIModule() : m_hDwm(nullptr) {}
	~CATLDXGIModule() = default;

	/**
	* @brief ATL Dll entrypoint
	* @param[in] dwReason
	* Reason why the callback was called
	* @param[in,opt] lpReserved
	* Reserved parameter
	* @return TRUE in case of success, FALSE otherwise.
	* @see Normal Winapi DLL Main
	*/
	BOOL WINAPI DllMain(_In_ DWORD dwReason, _In_opt_ LPVOID lpReserved);

	/**
	* @brief Loads all required callbacks and modules
	* @return TRUE in case of success, FALSE otherwise.
	*/
	BOOL MyInit();

	/**
	* @brief Unloads all required callbacks and modules
	*/
	void MyTerm();

private:
	/** DWMAPI.DLL */
	HMODULE m_hDwm;
};
