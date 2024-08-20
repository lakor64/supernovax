/*
 * PROJECT:     ReactX Utilities
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     Helper functions
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */
#include "dxutils.h"

bool IsDirectDrawSupported()
{
    HDC hDC;
    DWORD Planes;
    DWORD Bpp;

    hDC = GetDC(nullptr);
    Planes = GetDeviceCaps(hDC, PLANES);
    Bpp = GetDeviceCaps(hDC, BITSPIXEL);
    ReleaseDC(nullptr, hDC);

    return (Planes * Bpp) >= 8;
}

void ParseGDIDeviceID(const std::wstring& id, GDIDeviceID& en)
{
	en.DeviceId = 0;
	en.Revision = 0;
	en.VendorId = 0;
	en.SubSystemId = 0;

	// Format is: PCI/VEN_#####&DEV_#####&SUBSYS_######&REV_###

	if (id.rfind(L"PCI\\") != 0)
		return; // invalid string

	auto src = id.substr(4);
	size_t e;
	size_t tmp = 0;

	while (true)
	{
		e = src.find(L'&');
		if (e == std::wstring::npos)
			e = src.length();

		std::wstring prefix = L"0x";

		if (src.rfind(L"VEN_") == 0)
		{
			prefix += src.substr(4, e - 4);
			en.VendorId = UINT(wcstoul(prefix.c_str(), nullptr, 16));
		}
		else if (src.rfind(L"DEV_") == 0)
		{
			prefix += src.substr(4, e - 4);
			en.DeviceId = UINT(wcstoul(prefix.c_str(), nullptr, 16));
		}
		else if (src.rfind(L"REV_") == 0)
		{
			prefix += src.substr(4, e - 4);
			en.Revision = UINT(wcstoul(prefix.c_str(), nullptr, 16));
		}
		else if (src.rfind(L"SUBSYS_") == 0)
		{
			prefix += src.substr(7, e - 7);
			en.SubSystemId = UINT(wcstoul(prefix.c_str(), nullptr, 16));
		}
		else
			return;

		if (src.length() == e)
			break;

		src = src.substr(e + 1);
	}
}

void ParseGDIDeviceID(const std::string& id, GDIDeviceID& en)
{
	en.DeviceId = 0;
	en.Revision = 0;
	en.VendorId = 0;
	en.SubSystemId = 0;

	// Format is: PCI/VEN_#####&DEV_#####&SUBSYS_######&REV_###

	if (id.rfind("PCI\\") != 0)
		return; // invalid string

	auto src = id.substr(4);
	size_t e;
	size_t tmp = 0;

	while (true)
	{
		e = src.find('&');
		if (e == std::string::npos)
			e = src.length();

		std::string prefix = "0x";

		if (src.rfind("VEN_") == 0)
		{
			prefix += src.substr(4, e - 4);
			en.VendorId = UINT(strtoul(prefix.c_str(), nullptr, 16));
		}
		else if (src.rfind("DEV_") == 0)
		{
			prefix += src.substr(4, e - 4);
			en.DeviceId = UINT(strtoul(prefix.c_str(), nullptr, 16));
		}
		else if (src.rfind("REV_") == 0)
		{
			prefix += src.substr(4, e - 4);
			en.Revision = UINT(strtoul(prefix.c_str(), nullptr, 16));
		}
		else if (src.rfind("SUBSYS_") == 0)
		{
			prefix += src.substr(7, e - 7);
			en.SubSystemId = UINT(strtoul(prefix.c_str(), nullptr, 16));
		}
		else
			return;

		if (src.length() == e)
			break;

		src = src.substr(e + 1);
	}
}
