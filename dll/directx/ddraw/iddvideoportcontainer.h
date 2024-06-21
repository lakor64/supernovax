/*
 * PROJECT:     ReactXDraw
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     IDDVideoPortContainer container
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */

#pragma once

class ATL_NO_VTABLE CIDDVideoPortContainer :
    public IDDVideoPortContainer,
    public DDObjRoot
{
public:
    BEGIN_COM_MAP(CIDDVideoPortContainer)
        COM_INTERFACE_ENTRY_IID(IID_IDDVideoPortContainer, IDDVideoPortContainer)
    END_COM_MAP()

    STDMETHODIMP CreateVideoPort(_In_ DWORD dwFlags, _In_ LPDDVIDEOPORTDESC lpDDVideoPortDesc, _COM_Outptr_ LPDIRECTDRAWVIDEOPORT* lplpDDVideoPort, _In_ IUnknown* pUnkOuter) override;
    STDMETHODIMP EnumVideoPorts(_In_ DWORD dwFlags, _In_ LPDDVIDEOPORTCAPS lpDDVideoPortCaps, _In_ LPVOID lpContext, _In_ LPDDENUMVIDEOCALLBACK lpEnumVideoCallback) override;
    STDMETHODIMP GetVideoPortConnectInfo(_In_ DWORD dwPortId, _Inout_ LPDWORD lpNumEntries, _Out_ LPDDVIDEOPORTCONNECT lpConnectInfo) override;
    STDMETHODIMP QueryVideoPortStatus(_In_ DWORD dwPortId, _Out_ LPDDVIDEOPORTSTATUS lpVPStatus) override;
};
