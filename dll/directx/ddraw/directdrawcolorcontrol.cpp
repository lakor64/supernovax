/*
 * PROJECT:     SupernovaX 2D Draw
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     IDirectDrawColorControl object
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */

#include "pch.h"
#include "directdrawcolorcontrol.h"

STDMETHODIMP CDirectDrawColorControl::GetColorControls(_Out_ LPDDCOLORCONTROL lpColorControl)
{
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawColorControl::SetColorControls(_In_ LPDDCOLORCONTROL lpColorControl)
{
    return DDERR_GENERIC;
}

