/*
 * PROJECT:     ReactXDraw
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     IDirectDrawVideoPort object
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */

#pragma once


class ATL_NO_VTABLE CDirectDrawVideoPort :
    public IDirectDrawVideoPort,
    public DDObjRoot
{
public:
    BEGIN_COM_MAP(CDirectDrawVideoPort)
        COM_INTERFACE_ENTRY_IID(IID_IDirectDrawVideoPort, IDirectDrawVideoPort)
    END_COM_MAP()

    STDMETHODIMP Flip(_In_ LPDIRECTDRAWSURFACE lpDDSurface, _In_ DWORD dwFlags) override;
    STDMETHODIMP GetBandwidthInfo(_In_ LPDDPIXELFORMAT lpddpfFormat, _In_ DWORD dwWidth, _In_ DWORD dwHeight, _In_ DWORD dwFlags, _Out_ LPDDVIDEOPORTBANDWIDTH lpBandwidth) override;
    STDMETHODIMP GetColorControls(_Out_ LPDDCOLORCONTROL lpColorControl) override;
    STDMETHODIMP GetFieldPolarity(_Out_ LPBOOL lpbFieldPolarity) override;
    STDMETHODIMP GetInputFormats(_In_ LPDWORD lpNumFormats, _Out_ LPDDPIXELFORMAT lpFormats, _In_ DWORD dwFlags) override;
    STDMETHODIMP GetOutputFormats(_In_ LPDDPIXELFORMAT lpInputFormat, _Inout_ LPDWORD lpNumFormats, _Out_ LPDDPIXELFORMAT lpFormats, _In_ DWORD dwFlags) override;
    STDMETHODIMP GetVideoLine(_Out_ LPDWORD lpdwLine) override;
    STDMETHODIMP GetVideoSignalStatus(_Out_ LPDWORD lpdwStatus) override;
    STDMETHODIMP SetColorControls(_In_ LPDDCOLORCONTROL lpColorControl) override;
    STDMETHODIMP SetTargetSurface(_In_ LPDIRECTDRAWSURFACE lpDDSurface, _In_ DWORD dwFlags) override;
    STDMETHODIMP StartVideo(_In_ LPDDVIDEOPORTINFO lpVideoInfo) override;
    STDMETHODIMP StopVideo() override;
    STDMETHODIMP UpdateVideo(_In_ LPDDVIDEOPORTINFO lpVideoInfo) override;
    STDMETHODIMP WaitForSync(_In_ DWORD dwFlags, _In_ DWORD dwLine, _In_ DWORD dwTimeout) override;
};
