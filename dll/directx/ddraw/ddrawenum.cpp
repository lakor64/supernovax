/*
 * PROJECT:     ReactXDraw
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     ReactXDraw devices enumerator
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */

#include "pch.h"
#include "resource.h"
#include "dllmain.h"

extern HINSTANCE g_hDdraw;

struct DDrawEnumCbData
{
    union
    {
        LPDDENUMCALLBACKA a;
        LPDDENUMCALLBACKW w;
    } cb;
    LPVOID ctx;
};

static inline bool CheckForSecondaryDeviceEnum(_In_ DWORD dwFlags)
{
    bool queryForSecondaryDevices = (dwFlags & DDENUM_ATTACHEDSECONDARYDEVICES || dwFlags & DDENUM_DETACHEDSECONDARYDEVICES);

    HKEY swhk;
    if (RegOpenKey(HKEY_LOCAL_MACHINE, _T(REGISTER_PATH_DDSW), &swhk) == ERROR_SUCCESS)
    {
        DWORD type = 0, data = 0, size = sizeof(data);
        if (RegQueryValueEx(swhk, _T("EnumerateAttachedSecondaries"), nullptr, &type, reinterpret_cast<LPBYTE>(&data), &size) == ERROR_SUCCESS)
        {
            queryForSecondaryDevices |= data > 0;
        }

        RegCloseKey(swhk);
    }

    return queryForSecondaryDevices;
}

static inline bool CanEnumSecondaryDevice(DWORD StateFlags, DWORD dwFlags)
{
    return StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER && !(StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE) // secondary device which is not a primary device
        &&
        (
            (dwFlags & DDENUM_ATTACHEDSECONDARYDEVICES && StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) // only enum attached to desktop secondary devices
            || (dwFlags & DDENUM_DETACHEDSECONDARYDEVICES) // enum any kind of secondary device
            );
}

static BOOL WINAPI DDrawEnumExACallback(_In_ LPGUID lpGUID, _In_ LPSTR lpDriverDescription, _In_ LPSTR lpDriverName, _In_ LPVOID lpContext, _In_ HMONITOR hm)
{
    DDrawEnumCbData* data = static_cast<DDrawEnumCbData*>(lpContext);
    return data->cb.a(lpGUID, lpDriverDescription, lpDriverName, data->ctx);
}

static BOOL WINAPI DDrawEnumExWCallback(_In_ LPGUID lpGUID, _In_ LPWSTR lpDriverDescription, _In_ LPWSTR lpDriverName, _In_ LPVOID lpContext, _In_ HMONITOR hm)
{
    DDrawEnumCbData* data = static_cast<DDrawEnumCbData*>(lpContext);
    return data->cb.w(lpGUID, lpDriverDescription, lpDriverName, data->ctx);
}

extern "C"
{
    HRESULT WINAPI DirectDrawEnumerateA(_In_ LPDDENUMCALLBACKA lpCallback, _In_ LPVOID lpContext)
    {
        if (!lpCallback)
            return DDERR_INVALIDPARAMS;

        DDrawEnumCbData data;
        data.cb.a = lpCallback;
        data.ctx = lpContext;

        return DirectDrawEnumerateExA(DDrawEnumExACallback, &data, DDENUM_NONDISPLAYDEVICES);
    }

    HRESULT WINAPI DirectDrawEnumerateW(_In_ LPDDENUMCALLBACKW lpCallback, _In_ LPVOID lpContext)
    {
        if (!lpCallback)
            return DDERR_INVALIDPARAMS;

        DDrawEnumCbData data;
        data.cb.w = lpCallback;
        data.ctx = lpContext;

        return DirectDrawEnumerateExW(DDrawEnumExWCallback, &data, DDENUM_NONDISPLAYDEVICES);
    }

    HRESULT WINAPI DirectDrawEnumerateExA(_In_ LPDDENUMCALLBACKEXA lpCallback, _In_ LPVOID lpContext, _In_ DWORD dwFlags)
    {
        if (!lpCallback || (dwFlags & ~(DDENUM_NONDISPLAYDEVICES |
            DDENUM_DETACHEDSECONDARYDEVICES |
            DDENUM_ATTACHEDSECONDARYDEVICES)) != 0)
            return DDERR_INVALIDPARAMS;

        char strMsg[RC_STRING_MAX_SIZE];
        LoadStringA(g_hDdraw, STR_PRIMARY_DISPLAY, reinterpret_cast<LPSTR>(&strMsg), RC_STRING_MAX_SIZE);

        if (lpCallback(nullptr, strMsg, PRIMARY_DISPLAY_NAME, lpContext, nullptr) == DDENUMRET_CANCEL)
            return DD_OK;

        /*
            Enumeration code functionality:

            1. We use EnumDisplayDevices to get the informations on all the attached monitors on the primary device
            2. Based from the flag we can either enumerate the secondary monitors connected or not

            NOTE: If HKLM\Software\Microsoft\DirectDraw\EnumerateAttachedSecondaries (REG_DWORD) is 1,
                then we must enumerate the secondary devices regardless of the flags passed.

        */

        if (CheckForSecondaryDeviceEnum(dwFlags))
        {
            DWORD devId = 0;

            DISPLAY_DEVICEA dispdevice = { 0 };
            dispdevice.cb = sizeof(dispdevice);

            while (EnumDisplayDevicesA(nullptr, devId, &dispdevice, 0))
            {
                if (CanEnumSecondaryDevice(dispdevice.StateFlags, dwFlags))
                {
                    // TODO: Implement HMONITOR fetch
                    if (lpCallback(const_cast<LPGUID>(&DISPLAY_GUID), dispdevice.DeviceString, dispdevice.DeviceName, lpContext, nullptr) == DDENUMRET_CANCEL)
                        return DD_OK;
                }

                devId++;
            }
        }

        return DD_OK;
    }

    HRESULT WINAPI DirectDrawEnumerateExW(_In_ LPDDENUMCALLBACKEXW lpCallback, _In_ LPVOID lpContext, _In_ DWORD dwFlags)
    {
        if (!lpCallback || (dwFlags & ~(DDENUM_NONDISPLAYDEVICES |
            DDENUM_DETACHEDSECONDARYDEVICES |
            DDENUM_ATTACHEDSECONDARYDEVICES)) != 0)
            return DDERR_INVALIDPARAMS;

        wchar_t strMsg[RC_STRING_MAX_SIZE];
        LoadStringW(g_hDdraw, STR_PRIMARY_DISPLAY, reinterpret_cast<LPWSTR>(&strMsg), RC_STRING_MAX_SIZE);

        if (lpCallback(nullptr, strMsg, _T(PRIMARY_DISPLAY_NAME), lpContext, nullptr) == DDENUMRET_CANCEL)
            return DD_OK;

        if (CheckForSecondaryDeviceEnum(dwFlags))
        {
            DWORD devId = 0;

            DISPLAY_DEVICEW dispdevice = { 0 };
            dispdevice.cb = sizeof(dispdevice);

            while (EnumDisplayDevicesW(nullptr, devId, &dispdevice, 0))
            {
                if (CanEnumSecondaryDevice(dispdevice.StateFlags, dwFlags))
                {
                    // TODO: Implement HMONITOR fetch
                    if (lpCallback(const_cast<LPGUID>(&DISPLAY_GUID), dispdevice.DeviceString, dispdevice.DeviceName, lpContext, nullptr) == DDENUMRET_CANCEL)
                        return DD_OK;
                }

                devId++;
            }
        }

        return DD_OK;
    }
}
