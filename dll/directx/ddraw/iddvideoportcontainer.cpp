/*
 * PROJECT:     SupernovaX 2D Draw
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     IDDVideoPortContainer object
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */

#include "pch.h"
#include "iddvideoportcontainer.h"

STDMETHODIMP CIDDVideoPortContainer::CreateVideoPort(_In_ DWORD dwFlags, _In_ LPDDVIDEOPORTDESC lpDDVideoPortDesc, _COM_Outptr_ LPDIRECTDRAWVIDEOPORT* lplpDDVideoPort, _In_ IUnknown* pUnkOuter)
{
    return DDERR_GENERIC;
}

STDMETHODIMP CIDDVideoPortContainer::EnumVideoPorts(_In_ DWORD dwFlags, _In_ LPDDVIDEOPORTCAPS lpDDVideoPortCaps, _In_ LPVOID lpContext, _In_ LPDDENUMVIDEOCALLBACK lpEnumVideoCallback)
{
    return DDERR_GENERIC;
}

STDMETHODIMP CIDDVideoPortContainer::GetVideoPortConnectInfo(_In_ DWORD dwPortId, _Inout_ LPDWORD lpNumEntries, _Out_ LPDDVIDEOPORTCONNECT lpConnectInfo)
{
    *lpNumEntries = 0;

    return DDERR_GENERIC;
}

STDMETHODIMP CIDDVideoPortContainer::QueryVideoPortStatus(_In_ DWORD dwPortId, _Out_ LPDDVIDEOPORTSTATUS lpVPStatus)
{
    memset(lpVPStatus, 0, sizeof(*lpVPStatus));

    return DDERR_GENERIC;
}
