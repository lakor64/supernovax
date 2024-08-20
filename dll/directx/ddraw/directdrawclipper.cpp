/*
 * PROJECT:     SupernovaX 2D Draw
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     IDirectDrawClipper object
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */

#include "pch.h"
#include "directdrawclipper.h"

CDirectDrawClipper::CDirectDrawClipper() : m_bInit(false)
{}

STDMETHODIMP CDirectDrawClipper::GetClipList(_Inout_ LPRECT lpRect, _Inout_ LPRGNDATA lpClipList, _Inout_ LPDWORD lpdwSize)
{
    *lpdwSize = 0;
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawClipper::GetHWnd(_Out_ HWND* lphWnd)
{
    *lphWnd = nullptr;
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawClipper::Initialize(_In_ LPDIRECTDRAW lpDD, _In_ DWORD dwFlags)
{
    if (m_bInit)
        return DDERR_ALREADYINITIALIZED;

    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawClipper::IsClipListChanged(_Out_ BOOL* lpbChanged)
{
    *lpbChanged = FALSE;

    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawClipper::SetClipList(_In_ LPRGNDATA lpClipList, _In_ DWORD dwFlags)
{
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawClipper::SetHWnd(_In_ DWORD dwFlags, _In_ HWND hWnd)
{
    return DDERR_GENERIC;
}

