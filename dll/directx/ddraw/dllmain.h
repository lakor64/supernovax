/*
 * PROJECT:     ReactXDraw
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     ATL DLL module
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */
#pragma once

class CATLDDRAWModule : public ATL::CAtlDllModuleT<CATLDDRAWModule>
{
public:
	CATLDDRAWModule() = default;
	~CATLDDRAWModule() = default;

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
	HMODULE m_hGDI;
};
