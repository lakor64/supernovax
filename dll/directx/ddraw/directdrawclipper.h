/*
 * PROJECT:     SupernovaX 2D Draw
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     IDirectDrawClipper object
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */

#pragma once

class ATL_NO_VTABLE CDirectDrawClipper :
    public IDirectDrawClipper,
    public DDObjRoot
{
public:
    BEGIN_COM_MAP(CDirectDrawClipper)
        COM_INTERFACE_ENTRY_IID(IID_IDirectDrawClipper, IDirectDrawClipper)
    END_COM_MAP()

    CDirectDrawClipper();

    STDMETHODIMP GetClipList(_Inout_ LPRECT lpRect, _Inout_ LPRGNDATA lpClipList, _Inout_ LPDWORD lpdwSize) override;
    STDMETHODIMP GetHWnd(_Out_ HWND* lphWnd) override;
    STDMETHODIMP Initialize(_In_ LPDIRECTDRAW lpDD, _In_ DWORD dwFlags) override;
    STDMETHODIMP IsClipListChanged(_Out_ BOOL* lpbChanged) override;
    STDMETHODIMP SetClipList(_In_ LPRGNDATA lpClipList, _In_ DWORD dwFlags) override;
    STDMETHODIMP SetHWnd(_In_ DWORD dwFlags, _In_ HWND hWnd) override;

private:
    bool m_bInit;
};
