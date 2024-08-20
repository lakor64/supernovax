/*
 * PROJECT:     SupernovaX 2D Draw
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     IDirectDrawPalette object
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */

#include "pch.h"
#include "directdrawpalette.h"

STDMETHODIMP CDirectDrawPalette::GetCaps(_Out_ LPDWORD lpdwCaps)
{
    *lpdwCaps = 0;

    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawPalette::GetEntries(_In_ DWORD dwFlags, _In_ DWORD dwBase, _In_ DWORD dwNumEntries, _Out_ LPPALETTEENTRY lpEntries)
{
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawPalette::Initialize(_In_ LPDIRECTDRAW lpDD, _In_ DWORD dwFlags, _In_ LPPALETTEENTRY lpDDColorTable)
{
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawPalette::SetEntries(_In_ DWORD dwFlags, _In_ DWORD dwStartingEntry, _In_ DWORD dwCount, _In_ LPPALETTEENTRY lpEntries)
{
    return DDERR_GENERIC;
}
