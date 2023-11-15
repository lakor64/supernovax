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
