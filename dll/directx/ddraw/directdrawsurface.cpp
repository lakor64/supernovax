/*
 * PROJECT:     SupernovaX 2D Draw
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     Accelerated 2D surface
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */
#include "pch.h"
#include "directdrawsurface.h"
#include "directdraw.h"

 // Gets HEL or HAL callback where supported
#define GET_DD_CALLBACK(name, nameu) \
    LPDDHAL_##nameu name##Cb = nullptr; \
    if (HaveHardware()) \
    { \
        if (m_ddraw->lpLcl->lpDDCB->HALDD.dwFlags & DDHAL_CB32_##nameu) \
            name##Cb = m_ddraw->lpLcl->lpDDCB->HALDD.##name; \
    } \
    if (HaveEmulation() && ! name##Cb) \
    { \
        if (m_ddraw->lpLcl->lpDDCB->HELDD.dwFlags & DDHAL_CB32_##nameu) \
            name##Cb = m_ddraw->lpLcl->lpDDCB->HELDD.##name; \
    } \
    if (!name##Cb) \
        return DDERR_UNSUPPORTED;


CDirectDrawSurface::CDirectDrawSurface() : m_gbl(nullptr), m_lcl(nullptr), m_bInit(false), m_lastLink(nullptr)
{

}

CDirectDrawSurface::~CDirectDrawSurface()
{
    if (m_gbl)
        m_gbl->Release();

    if (m_lcl)
        m_lcl->Release();
}

STDMETHODIMP CDirectDrawSurface::AddAttachedSurface(_In_ LPDIRECTDRAWSURFACE7 lpDDSAttachedSurface)
{
    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::AddAttachedSurface", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::AddOverlayDirtyRect(_In_ LPRECT lpRect)
{
    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::AddOverlayDirtyRect", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::Blt(_In_ LPRECT lpDestRect, _In_ LPDIRECTDRAWSURFACE7 lpDDSrcSurface, _In_ LPRECT lpSrcRect, _In_ DWORD dwFlags, _In_ LPDDBLTFX lpDDBltFx)
{
    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::Blt", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::BltBatch(_In_ LPDDBLTBATCH lpDDBltBatch, _In_ DWORD dwCount, _In_ DWORD dwFlags)
{
    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::BltBatch", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::BltFast(_In_ DWORD dwX, _In_ DWORD dwY, _In_ LPDIRECTDRAWSURFACE7 lpDDSrcSurface, _In_ LPRECT lpSrcRect, _In_ DWORD dwTrans)
{
    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::BltFast", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::DeleteAttachedSurface(_In_ DWORD dwFlags, _In_ LPDIRECTDRAWSURFACE7 lpDDSAttachedSurface)
{
    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::DeleteAttachedSurface", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::EnumAttachedSurfaces(_In_ LPVOID lpContext, _In_ LPDDENUMSURFACESCALLBACK7 lpEnumSurfacesCallback)
{
    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::EnumAttachedSurfaces", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::EnumOverlayZOrders(_In_ DWORD dwFlags, _In_ LPVOID lpContext, _In_ LPDDENUMSURFACESCALLBACK7 lpfnCallback)
{
    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::EnumOverlayZOrders", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::Flip(_In_ LPDIRECTDRAWSURFACE7 lpDDSurfaceTargetOverride, _In_ DWORD dwFlags)
{
    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::Flip", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::GetAttachedSurface(_In_ LPDDSCAPS2 lpDDSCaps, _COM_Outptr_ LPDIRECTDRAWSURFACE7* lplpDDAttachedSurface)
{
    *lplpDDAttachedSurface = nullptr;

    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::GetAttachedSurface", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::GetBltStatus(_In_ DWORD dwFlags)
{
    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::GetBltStatus", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::GetCaps(_Out_ LPDDSCAPS2 lpDDSCaps)
{
    memset(lpDDSCaps, 0, sizeof(*lpDDSCaps));

    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::GetCaps", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::GetClipper(_COM_Outptr_ LPDIRECTDRAWCLIPPER* lplpDDClipper)
{
    *lplpDDClipper = nullptr;

    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::GetClipper", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::GetColorKey(_In_ DWORD dwFlags, _Out_ LPDDCOLORKEY lpDDColorKey)
{
    memset(lpDDColorKey, 0, sizeof(*lpDDColorKey));

    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::GetColorKey", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::GetDC(_Out_ HDC* lphDC)
{
    *lphDC = nullptr;

    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::GetDC", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::GetFlipStatus(_In_ DWORD dwFlags)
{
    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::GetFlipStatus", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::GetOverlayPosition(_Out_ LPLONG lplX, _Out_ LPLONG lplY)
{
    *lplX = 0;
    *lplY = 0;

    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::GetOverlayPosition", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::GetPalette(_COM_Outptr_ LPDIRECTDRAWPALETTE* lplpDDPalette)
{
    *lplpDDPalette = nullptr;

    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::GetPalette", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::GetPixelFormat(_Out_ LPDDPIXELFORMAT lpDDPixelFormat)
{
    memset(lpDDPixelFormat, 0, sizeof(*lpDDPixelFormat));

    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::GetPixelFormat", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::GetSurfaceDesc(_Out_ LPDDSURFACEDESC2 lpDDSurfaceDesc)
{
    memset(lpDDSurfaceDesc, 0, sizeof(*lpDDSurfaceDesc));

    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::GetSurfaceDesc", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::Initialize(_In_ LPDIRECTDRAW, _Out_ LPDDSURFACEDESC2)
{
    MessageBox(nullptr, _T("CDirectDrawSurface::Initialize"), _T("WTF"), MB_OK);
    return DDERR_ALREADYINITIALIZED;
}

STDMETHODIMP CDirectDrawSurface::IsLost()
{
    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::IsLost", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::Lock(_In_ LPRECT lpDestRect, _Out_ LPDDSURFACEDESC2 lpDDSurfaceDesc, _In_ DWORD dwFlags, _In_ HANDLE hEvent)
{
    memset(lpDDSurfaceDesc, 0, sizeof(*lpDDSurfaceDesc));

    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::Lock", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::ReleaseDC(_In_ HDC hDC)
{
    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::ReleaseDC", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::Restore()
{
    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::Restore", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::SetClipper(_In_ LPDIRECTDRAWCLIPPER lpDDClipper)
{
    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::SetClipper", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::SetColorKey(_In_ DWORD dwFlags, _In_ LPDDCOLORKEY lpDDColorKey)
{
    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::SetColorKey", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::SetOverlayPosition(_In_ LONG lX, _In_ LONG lY)
{
    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::SetOverlayPosition", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::SetPalette(_In_ LPDIRECTDRAWPALETTE lpDDPalette)
{
    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::SetPalette", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::Unlock(_In_ LPRECT lpRect)
{
    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::Unlock", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::UpdateOverlay(_In_ LPRECT lpSrcRect, _In_ LPDIRECTDRAWSURFACE7 lpDDDestSurface, _In_ LPRECT lpDestRect, _In_ DWORD dwFlags, _In_ LPDDOVERLAYFX lpDDOverlayFx)
{
    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::UpdateOverlay", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::UpdateOverlayDisplay(_In_ DWORD dwFlags)
{
    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::UpdateOverlayDisplay", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::UpdateOverlayZOrder(_In_ DWORD dwflags, _In_ LPDIRECTDRAWSURFACE7 lpDDSReference)
{
    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::UpdateOverlayZOrder", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::GetDDInterface(_Out_ LPVOID* lplpDD)
{
    *lplpDD = nullptr;

    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::GetDDInterface", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::PageLock(_In_ DWORD dwFlags)
{
    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::PageLock", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::PageUnlock(_In_ DWORD dwFlags)
{
    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::PageUnlock", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::SetSurfaceDesc(_In_ LPDDSURFACEDESC2 lpddsd2, _In_ DWORD dwFlags)
{
    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::SetSurfaceDesc", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::SetPrivateData(_In_ REFGUID guidTag, _In_ LPVOID lpData, _In_ DWORD cbSize, _In_ DWORD dwFlags)
{
    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::SetPrivateData", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::GetPrivateData(_In_ REFGUID guidTag, _Out_ LPVOID lpBuffer, _Inout_ LPDWORD lpcbBufferSize)
{
    *lpcbBufferSize = 0;

    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::GetPrivateData", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::FreePrivateData(_In_ REFGUID guidTag)
{
    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::FreePrivateData", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::GetUniquenessValue(_Out_ LPDWORD lpValue)
{
    *lpValue = 0;

    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::GetUniquenessValue", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::ChangeUniquenessValue()
{
    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::ChangeUniquenessValue", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::SetPriority(_In_ DWORD dwPriority)
{
    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::SetPriority", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::GetPriority(_Out_ LPDWORD lpdwPriority)
{
    *lpdwPriority = 0;

    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::GetPriority", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::SetLOD(_In_ DWORD dwMaxLOD)
{
    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::SetLOD", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDrawSurface::GetLOD(_Out_ LPDWORD lpdwMaxLOD)
{
    *lpdwMaxLOD = 0;

    MessageBoxA(m_ddraw->GetHwnd(), "CDirectDrawSurface::GetLOD", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

HRESULT CDirectDrawSurface::CreateFromDesc(_In_ CDirectDraw* lpDD, _In_ LPDDSURFACEDESC2 lpDDSurfaceDesc)
{
    m_ddraw = reinterpret_cast<CDirectDraw*>(lpDD);


    // this is a root object! Create the LCL and GBL

    ATL::CComObject<CDirectDrawSurfaceLCL>* lcl;

    auto hr = ATL::CComObject<CDirectDrawSurfaceLCL>::CreateInstance(&lcl);
    if (FAILED(hr))
        return hr;

    ATL::CComObject<CDirectDrawSurfaceGBL>* gbl;
    hr = ATL::CComObject<CDirectDrawSurfaceGBL>::CreateInstance(&gbl);

    if (FAILED(hr))
    {
        delete lcl;
        return hr;
    }

    lcl->AddRef();
    gbl->AddRef();

    lpLcl = lcl;
    m_lcl = lcl;
    m_gbl = gbl;
    m_lcl->lpGbl = gbl;

    DDHAL_CREATESURFACEDATA data = { 0 };
    data.lpDD = m_ddraw->lpLcl->lpGbl;
    data.lpDDSurfaceDesc = (LPDDSURFACEDESC)lpDDSurfaceDesc;
    data.lplpSList = nullptr;
    data.dwSCnt = 0;
    data.CreateSurface = m_ddraw->lpLcl->lpDDCB->cbDDCallbacks.CreateSurface;

    LPDDHAL_CREATESURFACE CreateSurfaceCB;

    if (m_ddraw->lpLcl->lpDDCB->HALDD.dwFlags & DDHAL_CB32_CREATESURFACE)
        CreateSurfaceCB = m_ddraw->lpLcl->lpDDCB->HALDD.CreateSurface;

    if (m_ddraw->lpLcl->lpDDCB->HELDD.dwFlags & DDHAL_CB32_CREATESURFACE && !CreateSurfaceCB)
    {
        CreateSurfaceCB = m_ddraw->lpLcl->lpDDCB->HELDD.CreateSurface;
        lpLcl->dwFlags |= DDRAWISURF_HELCB;
    }

    if (!CreateSurfaceCB)
        return DDERR_UNSUPPORTED;

    if (CreateSurfaceCB(&data) != DDHAL_DRIVER_NOTHANDLED)
        return DDERR_UNSUPPORTED;

    return data.ddRVal;
}

HRESULT CDirectDrawSurface::CreateFromSystemInfo(CDirectDraw* lpDD)
{
    DDSURFACEDESC2 desc = { 0 };
    desc.dwSize = sizeof(desc);
    auto hr = lpDD->GetDisplayMode(&desc);
    if (FAILED(hr))
        return hr;

    hr = CreateFromDesc(lpDD, &desc);
    if (FAILED(hr))
        return hr;


}