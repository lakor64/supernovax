/*
 * PROJECT:     ReactX Utilities
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     Utilities for ReactX implementations
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */
#pragma once

#include <Windows.h>
#include <string>

struct GDIDeviceID
{
	DWORD VendorId;
	DWORD DeviceId;
	DWORD Revision;
	DWORD SubSystemId;
};

/**
* Default GUID for the primary display device
*/
static const GUID DISPLAY_GUID = { 0x67685559, 0x3106, 0x11D0, { 0xB9, 0x71, 0x00, 0xAA, 0x00, 0x34, 0x2F, 0x9F } };

/**
* Checks if DirectDraw is supported in the system
* @return true in case of success, otherwise false
*/
bool IsDirectDrawSupported();

/**
* Formats a GDI DeviceKey to numbers
* @param id DeviceKey to parse
* @param en Output structure
*/
void ParseGDIDeviceID(const std::wstring& id, GDIDeviceID& en);

/**
* Parses a GDI string device id
* @param id DeviceID to parse
* @param en Output structure
*/
void ParseGDIDeviceID(const std::string& id, GDIDeviceID& en);

/**
* Checks if a specified driver passes WHQL
* @param driverPath Path of the driver
* @return true in case it passess, otherwise false
*/
bool IsDriverWHQL(LPCWSTR szFileName);

/**
* Checks if a specified driver passes WHQL
* @param driverPath Path of the driver
* @return true in case it passess, otherwise false
*/
bool IsDriverWHQL(LPCSTR szFileName);
