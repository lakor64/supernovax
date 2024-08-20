/*
 * PROJECT:     SupernovaX 2D Draw
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     IDirectDrawVideoPort object
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */

#include "pch.h"
#include "directdrawvideoport.h"

STDMETHODIMP CDirectDrawVideoPort::Flip(_In_ LPDIRECTDRAWSURFACE lpDDSurface, _In_ DWORD dwFlags)
{
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawVideoPort::GetBandwidthInfo(_In_ LPDDPIXELFORMAT lpddpfFormat, _In_ DWORD dwWidth, _In_ DWORD dwHeight, _In_ DWORD dwFlags, _Out_ LPDDVIDEOPORTBANDWIDTH lpBandwidth)
{
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawVideoPort::GetColorControls(_Out_ LPDDCOLORCONTROL lpColorControl)
{
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawVideoPort::GetFieldPolarity(_Out_ LPBOOL lpbFieldPolarity)
{
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawVideoPort::GetInputFormats(_In_ LPDWORD lpNumFormats, _Out_ LPDDPIXELFORMAT lpFormats, _In_ DWORD dwFlags)
{
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawVideoPort::GetOutputFormats(_In_ LPDDPIXELFORMAT lpInputFormat, _Inout_ LPDWORD lpNumFormats, _Out_ LPDDPIXELFORMAT lpFormats, _In_ DWORD dwFlags)
{
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawVideoPort::GetVideoLine(_Out_ LPDWORD lpdwLine)
{
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawVideoPort::GetVideoSignalStatus(_Out_ LPDWORD lpdwStatus)
{
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawVideoPort::SetColorControls(_In_ LPDDCOLORCONTROL lpColorControl)
{
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawVideoPort::SetTargetSurface(_In_ LPDIRECTDRAWSURFACE lpDDSurface, _In_ DWORD dwFlags)
{
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawVideoPort::StartVideo(_In_ LPDDVIDEOPORTINFO lpVideoInfo)
{
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawVideoPort::StopVideo()
{
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawVideoPort::UpdateVideo(_In_ LPDDVIDEOPORTINFO lpVideoInfo)
{
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawVideoPort::WaitForSync(_In_ DWORD dwFlags, _In_ DWORD dwLine, _In_ DWORD dwTimeout)
{
    return DDERR_GENERIC;
}
