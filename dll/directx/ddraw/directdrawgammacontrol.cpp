/*
 * PROJECT:     ReactXDraw
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     IDirectDrawGammaControl object
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */

#include "pch.h"
#include "directdrawgammacontrol.h"

STDMETHODIMP CDirectDrawGammaControl::GetGammaRamp(_In_ DWORD dwFlags, _Out_ LPDDGAMMARAMP lpRampData)
{
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawGammaControl::SetGammaRamp(_In_ DWORD dwFlags, _In_ LPDDGAMMARAMP lpRampData)
{
    return DDERR_GENERIC;
}
