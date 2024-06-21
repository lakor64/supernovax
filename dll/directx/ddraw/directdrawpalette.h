/*
 * PROJECT:     ReactXDraw
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     IDirectDrawPalette object
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */

#pragma once

class ATL_NO_VTABLE CDirectDrawPalette :
    public IDirectDrawPalette,
    public DDObjRoot
{
public:
    BEGIN_COM_MAP(CDirectDrawPalette)
        COM_INTERFACE_ENTRY_IID(IID_IDirectDrawPalette, IDirectDrawPalette)
    END_COM_MAP()

    STDMETHODIMP GetCaps(_Out_ LPDWORD lpdwCaps) override;
    STDMETHODIMP GetEntries(_In_ DWORD dwFlags, _In_ DWORD dwBase, _In_ DWORD dwNumEntries, _Out_ LPPALETTEENTRY lpEntries) override;
    STDMETHODIMP Initialize(_In_ LPDIRECTDRAW lpDD, _In_ DWORD dwFlags, _In_ LPPALETTEENTRY lpDDColorTable) override;
    STDMETHODIMP SetEntries(_In_ DWORD dwFlags, _In_ DWORD dwStartingEntry, _In_ DWORD dwCount, _In_ LPPALETTEENTRY lpEntries) override;
};
