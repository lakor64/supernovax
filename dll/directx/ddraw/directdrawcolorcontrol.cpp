/*
 * PROJECT:     ReactXDraw
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
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

