/*
 * PROJECT:     SupernovaX 2D Draw
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
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
