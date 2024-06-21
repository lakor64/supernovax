/*
 * PROJECT:     ReactX Graphics Infrastructure
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     Common types
 * COPYRIGHT:   Copyright 2023 Christian Rendina <pizzaiolo100@proton.me>
 */

#pragma once

/**
* @struct DXGIEnumInfo
* Holds the factory enumation results
*/
struct DXGIEnumInfo
{
	// from DISPLAY_DEVICEW
	WCHAR DeviceName[32];
	WCHAR DeviceString[128];

	// general output info
	UINT VendorId;
	UINT DeviceId;
	UINT Revision;
	UINT SubSystemId;

	LUID AdapterLuid;
	D3DKMT_HANDLE AdapterHandle;
	D3DDDI_VIDEO_PRESENT_SOURCE_ID VidPn;
};

struct DXGIOutputInfo
{
	D3DKMT_HANDLE AdapterHandle;
	D3DDDI_VIDEO_PRESENT_SOURCE_ID VidPn;
	WCHAR DeviceName[32];
};
