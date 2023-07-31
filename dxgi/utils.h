/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     Utility functions
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */
#pragma once

#include "dllmain.h"

inline bool IsInSession0()
{
	return false; // TODO
}

inline bool IsEqualLUID(const LUID& a, const LUID& b)
{
	return b.HighPart == a.HighPart && b.LowPart == a.LowPart;
}

/** Closes an open adapter kernel handle */
inline void CloseKMTAdapter(D3DKMT_HANDLE h)
{
	D3DKMT_CLOSEADAPTER ad;
	ad.hAdapter = h;
	_AtlModule.GetCloseAdapter()(&ad);
}

inline void WcsMaxCpy(const wchar_t* src, wchar_t* dst, size_t max)
{
	auto as = wcslen(src);

	if (as > max)
	{
		wcsncpy(dst, src, max);
		dst[max] = L'\0';
	}
	else
	{
		wcsncpy(dst, src, as);
		dst[as] = L'\0';
	}
}

extern DXGI_FORMAT WINAPI DXGI_MFMapDX9FormatToDXGIFormat(D3DDDIFORMAT format);
extern D3DDDIFORMAT WINAPI DXGI_MFMapDXGIFormatToDX9Format(DXGI_FORMAT dxgi_format);
