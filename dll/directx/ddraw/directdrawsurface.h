/*
 * PROJECT:     ReactXDraw
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Accelerated 2D surface
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */

#pragma once

class CDirectDraw;

class ATL_NO_VTABLE CDirectDrawSurface :
    public CDirectDrawSurfaceINT,
    public DDObjRoot
{
public:
    BEGIN_COM_MAP(CDirectDrawSurface)
        COM_INTERFACE_ENTRY_IID(IID_IDirectDrawSurface7, IDirectDrawSurface7)
    END_COM_MAP()

    // this fixes compilation issues with COM_MAP macros
    void Lock() { DDObjRoot::Lock(); }
    void Unlock() { DDObjRoot::Unlock(); }

    HRESULT CreateFromDesc(CDirectDraw* lpDD, LPDDSURFACEDESC2 lpSurface);
    HRESULT CreateFromSystemInfo(CDirectDraw* lpDD);

    STDMETHODIMP AddAttachedSurface(_In_ LPDIRECTDRAWSURFACE7 lpDDSAttachedSurface) override;
    STDMETHODIMP AddOverlayDirtyRect(_In_ LPRECT lpRect) override;
    STDMETHODIMP Blt(_In_ LPRECT lpDestRect, _In_ LPDIRECTDRAWSURFACE7 lpDDSrcSurface, _In_ LPRECT lpSrcRect, _In_ DWORD dwFlags, _In_ LPDDBLTFX lpDDBltFx) override;
    STDMETHODIMP BltBatch(_In_ LPDDBLTBATCH lpDDBltBatch, _In_ DWORD dwCount, _In_ DWORD dwFlags) override;
    STDMETHODIMP BltFast(_In_ DWORD dwX, _In_ DWORD dwY, _In_ LPDIRECTDRAWSURFACE7 lpDDSrcSurface, _In_ LPRECT lpSrcRect, _In_ DWORD dwTrans) override;
    STDMETHODIMP DeleteAttachedSurface(_In_ DWORD dwFlags, _In_ LPDIRECTDRAWSURFACE7 lpDDSAttachedSurface) override;
    STDMETHODIMP EnumAttachedSurfaces(_In_ LPVOID lpContext, _In_ LPDDENUMSURFACESCALLBACK7 lpEnumSurfacesCallback) override;
    STDMETHODIMP EnumOverlayZOrders(_In_ DWORD dwFlags, _In_ LPVOID lpContext, _In_ LPDDENUMSURFACESCALLBACK7 lpfnCallback) override;
    STDMETHODIMP Flip(_In_ LPDIRECTDRAWSURFACE7 lpDDSurfaceTargetOverride, _In_ DWORD dwFlags) override;
    STDMETHODIMP GetAttachedSurface(_In_ LPDDSCAPS2 lpDDSCaps, _COM_Outptr_ LPDIRECTDRAWSURFACE7* lplpDDAttachedSurface) override;
    STDMETHODIMP GetBltStatus(_In_ DWORD dwFlags) override;
    STDMETHODIMP GetCaps(_Out_ LPDDSCAPS2 lpDDSCaps) override;
    STDMETHODIMP GetClipper(_COM_Outptr_ LPDIRECTDRAWCLIPPER* lplpDDClipper) override;
    STDMETHODIMP GetColorKey(_In_ DWORD dwFlags, _Out_ LPDDCOLORKEY lpDDColorKey) override;
    STDMETHODIMP GetDC(_Out_ HDC* lphDC) override;
    STDMETHODIMP GetFlipStatus(_In_ DWORD dwFlags) override;
    STDMETHODIMP GetOverlayPosition(_Out_ LPLONG lplX, _Out_ LPLONG lplY) override;
    STDMETHODIMP GetPalette(_COM_Outptr_ LPDIRECTDRAWPALETTE* lplpDDPalette) override;
    STDMETHODIMP GetPixelFormat(_Out_ LPDDPIXELFORMAT lpDDPixelFormat) override;
    STDMETHODIMP GetSurfaceDesc(_Out_ LPDDSURFACEDESC2 lpDDSurfaceDesc) override;
    STDMETHODIMP Initialize(_In_ LPDIRECTDRAW lpDD, _Out_ LPDDSURFACEDESC2 lpDDSurfaceDesc) override;
    STDMETHODIMP IsLost() override;
    STDMETHODIMP Lock(_In_ LPRECT lpDestRect, _Out_ LPDDSURFACEDESC2 lpDDSurfaceDesc, _In_ DWORD dwFlags, _In_ HANDLE hEvent) override;
    STDMETHODIMP ReleaseDC(_In_ HDC hDC) override;
    STDMETHODIMP Restore() override;
    STDMETHODIMP SetClipper(_In_ LPDIRECTDRAWCLIPPER lpDDClipper) override;
    STDMETHODIMP SetColorKey(_In_ DWORD dwFlags, _In_ LPDDCOLORKEY lpDDColorKey) override;
    STDMETHODIMP SetOverlayPosition(_In_ LONG lX, _In_ LONG lY) override;
    STDMETHODIMP SetPalette(_In_ LPDIRECTDRAWPALETTE lpDDPalette) override;
    STDMETHODIMP Unlock(_In_ LPRECT lpRect) override;
    STDMETHODIMP UpdateOverlay(_In_ LPRECT lpSrcRect, _In_ LPDIRECTDRAWSURFACE7 lpDDDestSurface, _In_ LPRECT lpDestRect, _In_ DWORD dwFlags, _In_ LPDDOVERLAYFX lpDDOverlayFx) override;
    STDMETHODIMP UpdateOverlayDisplay(_In_ DWORD dwFlags) override;
    STDMETHODIMP UpdateOverlayZOrder(_In_ DWORD dwflags, _In_ LPDIRECTDRAWSURFACE7 lpDDSReference) override;
    STDMETHODIMP GetDDInterface(_Out_ LPVOID* lplpDD) override;
    STDMETHODIMP PageLock(_In_ DWORD dwFlags) override;
    STDMETHODIMP PageUnlock(_In_ DWORD dwFlags) override;
    STDMETHODIMP SetSurfaceDesc(_In_ LPDDSURFACEDESC2 lpddsd2, _In_ DWORD dwFlags) override;
    STDMETHODIMP SetPrivateData(_In_ REFGUID guidTag, _In_ LPVOID lpData, _In_ DWORD cbSize, _In_ DWORD dwFlags) override;
    STDMETHODIMP GetPrivateData(_In_ REFGUID guidTag, _Out_ LPVOID lpBuffer, _Inout_ LPDWORD lpcbBufferSize) override;
    STDMETHODIMP FreePrivateData(_In_ REFGUID guidTag) override;
    STDMETHODIMP GetUniquenessValue(_Out_ LPDWORD lpValue) override;
    STDMETHODIMP ChangeUniquenessValue() override;
    STDMETHODIMP SetPriority(_In_ DWORD dwPriority) override;
    STDMETHODIMP GetPriority(_Out_ LPDWORD lpdwPriority) override;
    STDMETHODIMP SetLOD(_In_ DWORD dwMaxLOD) override;
    STDMETHODIMP GetLOD(_Out_ LPDWORD lpdwMaxLOD) override;

private:

    constexpr const bool HaveEmulation() const { return m_ddraw->lpLcl->lpGbl->dwFlags & DDRAWI_EMULATIONINITIALIZED; }
    constexpr const bool HaveHardware() const { return (m_ddraw->lpLcl->lpGbl->dwFlags & DDRAWI_NOHARDWARE) == 0; }

    /**
    * Pointer to DDRAW interface
    */
    CDirectDraw* m_ddraw;

    /**
    * Global pointer to GBL
    */
    ATL::CComObject<CDirectDrawSurfaceGBL>* m_gbl;

    /**
    * Global pointer to LCL
    */
    ATL::CComObject<CDirectDrawSurfaceLCL>* m_lcl;

    /**
    * True if the object was initialized, otherwise false
    */
    bool m_bInit;

    /**
    * Last linked object
    */
    CDirectDrawSurface* m_lastLink;
};
