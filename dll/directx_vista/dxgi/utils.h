/*
 * PROJECT:     SupernovaX Graphics Infrastructure
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     Utility functions
 * COPYRIGHT:   Copyright 2023 Christian Rendina <pizzaiolo100@proton.me>
 */
#pragma once

#include "dllmain.h"

/**
* @brief Checks if the current function is executed
*  during session 0
* @return true if it is executed, otherwise false
*/
inline bool IsInSession0()
{
	DWORD sid = 0;
	DWORD pid = GetCurrentProcessId();
	ProcessIdToSessionId(pid, &sid);
	return sid == 0;
}

/**
* @brief Checks if two LUIDs are equal
* @param a First LUID
* @param b Second LUID
* @return true if they are equal, otherwise false
*/
constexpr bool IsEqualLUID(const LUID& a, const LUID& b)
{
	return b.HighPart == a.HighPart && b.LowPart == a.LowPart;
}

/**
* @brief Converts a WDDM format to DXGI format
* @param format WDDM Format to convert
* @return Converted DXGI format
*/
extern DXGI_FORMAT WINAPI DXGI_MFMapDX9FormatToDXGIFormat(D3DDDIFORMAT format);

/**
* @brief Converts a DXGI format to WDDM format
* @param dxgi_format DXGI Format to convert
* @return Converted WDDM format
*/
extern D3DDDIFORMAT WINAPI DXGI_MFMapDXGIFormatToDX9Format(DXGI_FORMAT dxgi_format);

/**
* @brief Converts NTSTATUS errors to DXGI errors
* @param status NTSTATUS error
* @return HRESULT (DXGI_ERROR_*) error
*/
extern HRESULT WINAPI NtErrorToDxgiError(NTSTATUS status);
