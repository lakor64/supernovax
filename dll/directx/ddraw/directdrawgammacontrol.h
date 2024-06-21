/*
 * PROJECT:     ReactXDraw
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     IDirectDrawGammaControl object
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */

#pragma once

class ATL_NO_VTABLE CDirectDrawGammaControl :
    public IDirectDrawGammaControl,
    public DDObjRoot
{
public:
    BEGIN_COM_MAP(CDirectDrawGammaControl)
        COM_INTERFACE_ENTRY_IID(IID_IDirectDrawGammaControl, IDirectDrawGammaControl)
    END_COM_MAP()

    STDMETHODIMP GetGammaRamp(_In_ DWORD dwFlags, _Out_ LPDDGAMMARAMP lpRampData) override;
    STDMETHODIMP SetGammaRamp(_In_ DWORD dwFlags, _In_ LPDDGAMMARAMP lpRampData) override;
};
