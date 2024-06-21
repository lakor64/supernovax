/*
 * PROJECT:     ReactXDraw
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     IDirectDraw7 Implementation
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 *              Magnus Olsen (greatlrd)
 *              Maarten Bosma
 */

#include "pch.h"
#include "directdraw.h"
#include "directdrawsurface.h"
#include "directdrawclipper.h"
#include "directdrawpalette.h"

// TODO: Add win32k.sys mode change check and restore (DdQueryDisplaySettingsUniqueness)

// Gets HEL or HAL callback where supported
#define GET_DD_CALLBACK(name, nameu) \
    LPDDHAL_##nameu name##Cb = nullptr; \
    if (HaveHardware()) \
    { \
        if (lpLcl->lpDDCB->HALDD.dwFlags & DDHAL_CB32_##nameu) \
            name##Cb = lpLcl->lpDDCB->HALDD.##name; \
    } \
    if (HaveEmulation() && ! name##Cb) \
    { \
        if (lpLcl->lpDDCB->HELDD.dwFlags & DDHAL_CB32_##nameu) \
            name##Cb = lpLcl->lpDDCB->HELDD.##name; \
    } \
    if (!name##Cb) \
        return DDERR_UNSUPPORTED;

CDirectDraw::CDirectDraw() : m_gbl(nullptr), m_lcl(nullptr), m_bInit(false), m_lastLink(nullptr)
{

}

CDirectDraw::~CDirectDraw()
{
    if (m_gbl)
        m_gbl->Release();

    if (m_lcl)
        m_lcl->Release();
}

/*
*  According from ReactOS:
*  Microsoft says Compact is not implemented in ddraw.dll, but it returns  DDERR_NOEXCLUSIVEMODE or DD_OK
*/
STDMETHODIMP CDirectDraw::Compact()
{
    if (!m_bInit)
        return DDERR_NOTINITIALIZED;

    CDirectDrawScopedLock lock;

    if (m_gbl->lpExclusiveOwner != m_lcl)
        return DDERR_NOEXCLUSIVEMODE;

    return DD_OK;
}

STDMETHODIMP CDirectDraw::CreateClipper(_In_ DWORD dwFlags, _COM_Outptr_ LPDIRECTDRAWCLIPPER* lplpDDClipper, _In_ IUnknown* pUnkOuter)
{
    if (!lplpDDClipper)
        return DDERR_INVALIDPARAMS;

    *lplpDDClipper = nullptr;

    if (pUnkOuter)
        return CLASS_E_NOAGGREGATION;

    if (!m_bInit)
        return DDERR_NOTINITIALIZED;

    CDirectDrawScopedLock lock;

    ATL::CComObject<CDirectDrawClipper>* clipper;
    auto hr = ATL::CComObject<CDirectDrawClipper>::CreateInstance(&clipper);
    if (FAILED(hr))
        return hr;

    hr = clipper->Initialize(reinterpret_cast<LPDIRECTDRAW>(this), dwFlags);
    if (FAILED(hr))
    {
        delete clipper;
        return hr;
    }

    clipper->AddRef();
    *lplpDDClipper = clipper;

    return DD_OK;
}

STDMETHODIMP CDirectDraw::CreatePalette(_In_ DWORD dwFlags, _In_ LPPALETTEENTRY lpDDColorArray, _COM_Outptr_ LPDIRECTDRAWPALETTE* lplpDDPalette, _In_ IUnknown* pUnkOuter)
{
    if (!lplpDDPalette || !lpDDColorArray)
        return DDERR_INVALIDPARAMS;

    *lplpDDPalette = nullptr;

    if (pUnkOuter)
        return CLASS_E_NOAGGREGATION;

    if (!m_bInit)
        return DDERR_NOTINITIALIZED;

    CDirectDrawScopedLock lock;

    ATL::CComObject<CDirectDrawPalette>* pal;
    auto hr = ATL::CComObject<CDirectDrawPalette>::CreateInstance(&pal);

    if (FAILED(hr))
        return hr;

    hr = pal->Initialize(reinterpret_cast<LPDIRECTDRAW>(this), dwFlags, lpDDColorArray);

    if (FAILED(hr))
    {
        delete pal;
        return hr;
    }

    *lplpDDPalette = pal;
    return DD_OK;
}

STDMETHODIMP CDirectDraw::CreateSurface(_In_ LPDDSURFACEDESC2 lpDDSurfaceDesc2 , _COM_Outptr_ LPDIRECTDRAWSURFACE7* lplpDDSurface, _In_ IUnknown* pUnkOuter)
{
    if (!lpDDSurfaceDesc2 || !lplpDDSurface)
        return DDERR_INVALIDPARAMS;

    if (pUnkOuter)
        return CLASS_E_NOAGGREGATION;

    *lplpDDSurface = nullptr;

    if (!m_bInit)
        return DDERR_NOTINITIALIZED;

    CDirectDrawScopedLock lock;

    ATL::CComObject<CDirectDrawSurface>* surface;
    auto hr = ATL::CComObject<CDirectDrawSurface>::CreateInstance(&surface);
    if (FAILED(hr))
        return hr;

    hr = surface->CreateFromDesc(this, lpDDSurfaceDesc2);

    if (FAILED(hr))
    {
        delete surface;
        return hr;
    }
    
    surface->AddRef();
    *lplpDDSurface = surface;

    return DD_OK;
}

STDMETHODIMP CDirectDraw::DuplicateSurface(_In_ LPDIRECTDRAWSURFACE7 lpDDSurface, _COM_Outptr_ LPDIRECTDRAWSURFACE7* lplpDupDDSurface)
{
    if (!lpDDSurface || !lplpDupDDSurface)
        return DDERR_INVALIDPARAMS;

    *lplpDupDDSurface = nullptr;

    if (!m_bInit)
        return DDERR_NOTINITIALIZED;

    MessageBoxA(GetHwnd(), "CDirectDraw::DuplicateSurface", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDraw::EnumDisplayModes(_In_ DWORD dwFlags, _In_ LPDDSURFACEDESC2 lpDDSurfaceDesc2, _In_ LPVOID lpContext, _In_ LPDDENUMMODESCALLBACK2 lpEnumModesCallback)
{
    if (!lpDDSurfaceDesc2 || !lpEnumModesCallback)
        return DDERR_INVALIDPARAMS;

    if (!m_bInit)
        return DDERR_NOTINITIALIZED;

    if (lpDDSurfaceDesc2->dwSize != sizeof(DDSURFACEDESC2))
        return DDERR_INVALIDPARAMS;

    DEVMODEA DevMode = { 0 };
    DWORD iMode = 0;

    DevMode.dmSize = sizeof(DevMode);

    auto displayName = strcmp(m_gbl->cDriverName, "display") == 0 ? nullptr : m_gbl->cDriverName;

    while (EnumDisplaySettingsExA(displayName, iMode, &DevMode, 0))
    {
        DDSURFACEDESC2 SurfaceDesc = { 0 };
        iMode++;

        SurfaceDesc.dwSize = sizeof(SurfaceDesc);
        SurfaceDesc.dwFlags = DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT | DDSD_PITCH | DDSD_REFRESHRATE;
        SurfaceDesc.dwHeight = DevMode.dmPelsHeight;
        SurfaceDesc.dwWidth = DevMode.dmPelsWidth;
        SurfaceDesc.lPitch = DevMode.dmPelsWidth * DevMode.dmBitsPerPel / 8;
        SurfaceDesc.dwRefreshRate = DevMode.dmDisplayFrequency;

        SurfaceDesc.ddpfPixelFormat.dwSize = sizeof(SurfaceDesc.ddpfPixelFormat);
        SurfaceDesc.ddpfPixelFormat.dwFlags = DDPF_RGB;
        // FIXME: get these
        /*
            SurfaceDesc.ddpfPixelFormat.dwRBitMask =
            SurfaceDesc.ddpfPixelFormat.dwGBitMask =
            SurfaceDesc.ddpfPixelFormat.dwBBitMask =
            SurfaceDesc.ddpfPixelFormat.dwRGBAlphaBitMask =
        */
        SurfaceDesc.ddpfPixelFormat.dwRGBBitCount = DevMode.dmBitsPerPel;

        // FIXME1: This->m_gbl->dwMonitorFrequency is not set !
        if (dwFlags & DDEDM_REFRESHRATES && SurfaceDesc.dwRefreshRate != m_gbl->dwMonitorFrequency)
        {
            //continue;  // FIXME2: what is SurfaceDesc.dwRefreshRate supposed to be set to ?
        }

        // FIXME: Take case when DDEDM_STANDARDVGAMODES flag is not set in account

        if (lpDDSurfaceDesc2)
        {
            if (lpDDSurfaceDesc2->dwFlags & DDSD_HEIGHT && lpDDSurfaceDesc2->dwHeight != SurfaceDesc.dwHeight)
                continue;

            if (lpDDSurfaceDesc2->dwFlags & DDSD_WIDTH && lpDDSurfaceDesc2->dwWidth != SurfaceDesc.dwWidth)
                continue;

            if (lpDDSurfaceDesc2->dwFlags & DDSD_PITCH && lpDDSurfaceDesc2->lPitch != SurfaceDesc.lPitch)
                continue;

            if (lpDDSurfaceDesc2->dwFlags & DDSD_REFRESHRATE && lpDDSurfaceDesc2->dwRefreshRate != SurfaceDesc.dwRefreshRate)
                continue;

            if (lpDDSurfaceDesc2->dwFlags & DDSD_PIXELFORMAT && lpDDSurfaceDesc2->ddpfPixelFormat.dwRGBBitCount != SurfaceDesc.ddpfPixelFormat.dwRGBBitCount)
                continue;  // FIXME: test for the other members of ddpfPixelFormat as well
        }

        if ((*lpEnumModesCallback)(&SurfaceDesc, lpContext) == DDENUMRET_CANCEL)
            break;
    }

    return DD_OK;
}

STDMETHODIMP CDirectDraw::EnumSurfaces(_In_ DWORD dwFlags, _In_ LPDDSURFACEDESC2 lpDDS2, _In_ LPVOID lpContext, _In_ LPDDENUMSURFACESCALLBACK7 lpEnumSurfaceCallback)
{
    if (!lpDDS2 || !lpEnumSurfaceCallback)
        return DDERR_INVALIDPARAMS;

    if (!m_bInit)
        return DDERR_NOTINITIALIZED;


    MessageBoxA(GetHwnd(), "CDirectDraw::EnumSurfaces", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDraw::EvaluateMode(_In_ DWORD dwFlags, _Out_ DWORD* pSecondsUntilTimeout)
{
    if (!pSecondsUntilTimeout)
        return DDERR_INVALIDPARAMS;

    *pSecondsUntilTimeout = 0;

    if (!m_bInit)
        return DDERR_NOTINITIALIZED;

    MessageBoxA(GetHwnd(), "CDirectDraw::EvaluateMode", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDraw::FlipToGDISurface()
{
    if (!m_bInit)
        return DDERR_NOTINITIALIZED;

    auto surf = reinterpret_cast<CDirectDrawSurface*>(m_lcl->lpPrimary);

    if (!surf)
        return DDERR_NOTFOUND;

    // TODO: Implement attached flip support from LCL

    return surf->Flip(nullptr, DDFLIP_WAIT);
}

STDMETHODIMP CDirectDraw::GetAvailableVidMem(_In_ LPDDSCAPS2 lpDDSCaps2, _Out_ LPDWORD lpdwTotal, _Out_ LPDWORD lpdwFree)
{
    if (!lpDDSCaps2 || !lpdwTotal || !lpdwFree)
        return DDERR_INVALIDPARAMS;

    *lpdwTotal = 0;
    *lpdwFree = 0;

    if (!m_bInit)
        return DDERR_NOTINITIALIZED;

    MessageBoxA(GetHwnd(), "CDirectDraw::GetAvailableVidMem", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDraw::GetCaps(_Out_ LPDDCAPS lpDDDriverCaps, _Out_ LPDDCAPS lpDDHELCaps)
{
    if (!m_bInit)
        return DDERR_NOTINITIALIZED;

    MessageBoxA(GetHwnd(), "CDirectDraw::GetCaps", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDraw::GetDeviceIdentifier(_Out_ LPDDDEVICEIDENTIFIER2 lpdddi, _In_ DWORD dwFlags)
{
    if (!lpdddi)
        return DDERR_INVALIDPARAMS;

    memset(lpdddi, 0, sizeof(*lpdddi));

    if (!m_bInit)
        return DDERR_NOTINITIALIZED;

    if (dwFlags & ~(DDGDI_GETHOSTIDENTIFIER))
        return DDERR_INVALIDPARAMS;

    CDirectDrawScopedLock lock;

    DWORD iDevNum = 0;
    DISPLAY_DEVICEA dispDev = { 0 };
    dispDev.cb = sizeof(dispDev);

    while (EnumDisplayDevicesA(nullptr, iDevNum, &dispDev, 0))
    {
        if (strcmp(dispDev.DeviceName, m_gbl->cDriverName) == 0 ||
            (dispDev.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE && !strcmp(m_gbl->cDriverName, "display")))
        {
            // NOTE: According to my testing, Windows does not set the version and the version is dependant of the GUID check
            //  this needs to be better verified

            strncpy_s(lpdddi->szDescription, _countof(lpdddi->szDescription), dispDev.DeviceString, sizeof(dispDev.DeviceString));

            GDIDeviceID key;
            ParseGDIDeviceID(dispDev.DeviceID, key);
            lpdddi->dwDeviceId = key.DeviceId;
            lpdddi->dwRevision = key.Revision;
            lpdddi->dwSubSysId = key.SubSystemId;
            lpdddi->dwVendorId = key.VendorId;

            // Cannot use ATL because we use ansi
            HKEY hk;
            if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, &dispDev.DeviceKey[18], 0, KEY_QUERY_VALUE, &hk) == ERROR_SUCCESS)
            {
                DWORD type, keySize;
                if (RegQueryValueExA(hk, "InstalledDisplayDrivers", nullptr, &type, nullptr, &keySize) == ERROR_SUCCESS && type == REG_MULTI_SZ)
                {
                    BYTE* data = new BYTE[keySize];
                    if (RegQueryValueExA(hk, "InstalledDisplayDrivers", nullptr, &type, data, &keySize) == ERROR_SUCCESS)
                    {
                        size_t i;
                        for (i = 0; ; i++)
                        {
                            if ((i + 1) >= keySize)
                                break;

                            if (data[i] == '\0')
                                break;

                            lpdddi->szDriver[i] = static_cast<char>(data[i]);
                        }
                        lpdddi->szDriver[i] = '.';
                        lpdddi->szDriver[i + 1] = 'd';
                        lpdddi->szDriver[i + 2] = 'l';
                        lpdddi->szDriver[i + 3] = 'l';
                        lpdddi->szDriver[i + 4] = '\0';
                    }
                    delete[] data;
                }
                RegCloseKey(hk);
            }

            {
                char path[MAX_PATH + 1];
                auto len = GetSystemDirectoryA(path, MAX_PATH);
                strcat_s(path, _countof(path), "\\");
                strcat_s(path, _countof(path), lpdddi->szDriver);

                // Get the WHQL and driver version
                lpdddi->dwWHQLLevel = IsDriverWHQL(path);
            }

            // Generate the GUID, sadly we have to replicate what Windows did here
            {
                lpdddi->guidDeviceIdentifier = CLSID_DirectDraw;
                auto guidx = reinterpret_cast<DWORD*>(&lpdddi->guidDeviceIdentifier);
                guidx[0] ^= lpdddi->dwVendorId;
                guidx[1] ^= lpdddi->dwDeviceId;
                guidx[2] ^= lpdddi->dwSubSysId;
                guidx[3] ^= lpdddi->dwRevision;
                auto guidq = reinterpret_cast<LONGLONG*>(&lpdddi->guidDeviceIdentifier.Data4);
                *guidq ^= lpdddi->liDriverVersion.QuadPart;
            }
        }

        iDevNum++;
    }

    return DD_OK;
}

STDMETHODIMP CDirectDraw::GetDisplayMode(_In_ LPDDSURFACEDESC2 lpDDSurfaceDesc2)
{
    if (!lpDDSurfaceDesc2)
        return DDERR_INVALIDPARAMS;

    memset(lpDDSurfaceDesc2, 0, sizeof(*lpDDSurfaceDesc2));

    if (!m_bInit)
        return DDERR_NOTINITIALIZED;

    MessageBoxA(GetHwnd(), "CDirectDraw::GetDisplayMode", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDraw::GetFourCCCodes(_Inout_ LPDWORD lpNumCodes, _Inout_ LPDWORD lpCodes)
{
    if (!lpNumCodes)
        return DDERR_INVALIDPARAMS;

    *lpNumCodes = 0;

    if (!m_bInit)
        return DDERR_NOTINITIALIZED;

    *lpNumCodes = m_gbl->dwNumFourCC;

    if (lpCodes)
    {
        auto sz = min(*lpNumCodes, m_gbl->dwNumFourCC);
        memcpy_s(lpCodes, *lpNumCodes * sizeof(DWORD), m_gbl->lpdwFourCC, sz * sizeof(DWORD));
    }

    return DD_OK;
}

STDMETHODIMP CDirectDraw::GetGDISurface(_COM_Outptr_ LPDIRECTDRAWSURFACE7* lplpGDIDDSSurface)
{
    if (!lplpGDIDDSSurface)
        return DDERR_INVALIDPARAMS;

    *lplpGDIDDSSurface = nullptr;

    if (!m_bInit)
        return DDERR_NOTINITIALIZED;

    MessageBoxA(GetHwnd(), "CDirectDraw::GetGDISurface", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDraw::GetMonitorFrequency(_Out_ LPDWORD lpdwFrequency)
{
    if (!lpdwFrequency)
        return DDERR_INVALIDPARAMS;

    *lpdwFrequency = 0;

    if (!m_bInit)
        return DDERR_NOTINITIALIZED;

    *lpdwFrequency = m_gbl->dwMonitorFrequency;
    return DD_OK;
}

STDMETHODIMP CDirectDraw::GetScanLine(_Out_ LPDWORD lpdwScanLine)
{
    if (!lpdwScanLine)
        return DDERR_INVALIDPARAMS;

    *lpdwScanLine = 0;

    if (!m_bInit)
        return DDERR_NOTINITIALIZED;

    GET_DD_CALLBACK(GetScanLine, GETSCANLINE);
    DDHAL_GETSCANLINEDATA data = { 0 };
    data.lpDD = m_gbl;
    data.GetScanLine = m_lcl->lpDDCB->cbDDCallbacks.GetScanLine;

    if (GetScanLineCb(&data) == DDHAL_DRIVER_NOTHANDLED)
        return DDERR_UNSUPPORTED;

    if (FAILED(data.ddRVal))
        return data.ddRVal;

    *lpdwScanLine = data.dwScanLine;
    return DD_OK;
}

STDMETHODIMP CDirectDraw::GetSurfaceFromDC(_In_ HDC hdc, _COM_Outptr_ LPDIRECTDRAWSURFACE7* lpDDS)
{
    if (!lpDDS)
        return DDERR_INVALIDPARAMS;

    *lpDDS = nullptr;

    if (!m_bInit)
        return DDERR_NOTINITIALIZED;

    MessageBoxA(GetHwnd(), "CDirectDraw::GetSurfaceFromDC", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDraw::GetVerticalBlankStatus(_Out_ LPBOOL lpbIsInVB)
{
    if (!lpbIsInVB)
        return DDERR_INVALIDPARAMS;

    *lpbIsInVB = FALSE;

    if (!m_bInit)
        return DDERR_NOTINITIALIZED;

    MessageBoxA(GetHwnd(), "CDirectDraw::GetVerticalBlankStatus", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDraw::Initialize(_In_ GUID*)
{
    MessageBox(nullptr, _T("CDirectDraw::Initialize"), _T("WTF"), MB_OK);
    return DDERR_ALREADYINITIALIZED;
}

STDMETHODIMP CDirectDraw::RestoreAllSurfaces()
{
    if (!m_bInit)
        return DDERR_NOTINITIALIZED;

    MessageBoxA(GetHwnd(), "CDirectDraw::RestoreAllSurfaces", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDraw::RestoreDisplayMode()
{
    if (!m_bInit)
        return DDERR_NOTINITIALIZED;

    if (m_gbl->lpExclusiveOwner && m_gbl->lpExclusiveOwner != lpLcl)
        return DDERR_NOEXCLUSIVEMODE;

    // Add unique win32k.sys checks

    ChangeDisplaySettings(nullptr, 0);

    m_gbl->hDD = lpLcl->hDD;

    if (!(m_gbl->dwFlags & DDRAWI_NOHARDWARE))
    {
        BOOL modeChanged = FALSE;
        DdReenableDirectDrawObject(m_gbl, &modeChanged);
        // TODO: Reinit the DirectDraw structure (STARTUP)
    }

    return DD_OK;
}

STDMETHODIMP CDirectDraw::SetCooperativeLevel(_In_ HWND hWnd, _In_ DWORD dwFlags)
{
    if (!m_bInit)
        return DDERR_NOTINITIALIZED;

    if (hWnd && !IsWindow(hWnd))
        return DDERR_INVALIDPARAMS;

    if (dwFlags & (~(DDSCL_FPUPRESERVE | DDSCL_FPUSETUP | DDSCL_MULTITHREADED | DDSCL_CREATEDEVICEWINDOW |
        DDSCL_SETDEVICEWINDOW | DDSCL_SETFOCUSWINDOW | DDSCL_ALLOWMODEX | DDSCL_EXCLUSIVE |
        DDSCL_NORMAL | DDSCL_NOWINDOWCHANGES | DDSCL_ALLOWREBOOT | DDSCL_FULLSCREEN | DDSCL_HOOKWINDOW)))
        return DDERR_INVALIDPARAMS;

    if (!(dwFlags & (DDSCL_NORMAL | DDSCL_EXCLUSIVE | DDSCL_SETFOCUSWINDOW)))
        return DDERR_INVALIDPARAMS;

    if (dwFlags & (DDSCL_FPUSETUP | DDSCL_FPUPRESERVE))
        return DDERR_INVALIDPARAMS;

    if ((dwFlags & DDSCL_EXCLUSIVE) && (!(dwFlags & DDSCL_FULLSCREEN)))
        return DDERR_INVALIDPARAMS;

    if ((dwFlags & DDSCL_ALLOWMODEX) && (!(dwFlags & DDSCL_FULLSCREEN)))
        return DDERR_INVALIDPARAMS;

    if ((dwFlags & (DDSCL_CREATEDEVICEWINDOW | DDSCL_SETFOCUSWINDOW)))
        return DDERR_INVALIDPARAMS;

    if ((dwFlags & DDSCL_CREATEDEVICEWINDOW) && !(dwFlags & DDSCL_EXCLUSIVE))
        return DDERR_INVALIDPARAMS;

    if (dwFlags & (DDSCL_EXCLUSIVE | DDSCL_HOOKWINDOW))
        return DDERR_INVALIDPARAMS;

    if ((dwFlags & DDSCL_NORMAL) && ((dwFlags & DDSCL_ALLOWMODEX) || (dwFlags & DDSCL_EXCLUSIVE) || (dwFlags & DDSCL_FULLSCREEN)))
        return DDERR_INVALIDPARAMS;

    if (!dwFlags)
        return DDERR_INVALIDPARAMS;

    if (!(m_gbl->dwFlags & DDRAWI_ATTACHEDTODESKTOP))
        dwFlags |= DDSCL_NOWINDOWCHANGES; // We cannot update an HWND that's not attached to the desktop

    CDirectDrawScopedLock lock;

    m_lcl->dwLocalFlags |= DDRAWILCL_SETCOOPCALLED;

    /* Handle those levels first which set various hwnds */
    if ((dwFlags & DDSCL_SETFOCUSWINDOW) && !(dwFlags & DDSCL_CREATEDEVICEWINDOW))
    {
        /* This isn't compatible with a lot of flags */
        if (dwFlags & (DDSCL_MULTITHREADED
            | DDSCL_FPUSETUP
            | DDSCL_FPUPRESERVE
            | DDSCL_ALLOWREBOOT
            | DDSCL_ALLOWMODEX
            | DDSCL_SETDEVICEWINDOW
            | DDSCL_NORMAL
            | DDSCL_EXCLUSIVE
            | DDSCL_FULLSCREEN))
            return DDERR_INVALIDPARAMS;

        // TODO: Wine 9 talks about checks to see if it was already setted up the esclusive mode, but it's a fixme so

        m_lcl->hFocusWnd = reinterpret_cast<ULONG_PTR>(hWnd);
    }

    // TODO: Find what V1SCLBEHAVOUR is

    // NORMAL MODE
    if (dwFlags & DDSCL_NORMAL)
    {
        m_lcl->hWnd = reinterpret_cast<ULONG_PTR>(hWnd);
        m_lcl->hFocusWnd = reinterpret_cast<ULONG_PTR>(hWnd);
        m_gbl->lpExclusiveOwner = nullptr;
    }
    // FULLSCREEN MODE
    else
    {
        if (!hWnd && !(dwFlags & DDSCL_CREATEDEVICEWINDOW))
            return DDERR_INVALIDPARAMS;

        if (dwFlags & DDSCL_CREATEDEVICEWINDOW)
        {
            if (!m_lcl->hFocusWnd && !(dwFlags & DDSCL_SETFOCUSWINDOW))
                return DDERR_NOFOCUSWINDOW;

            // todo: implement createdevicewindow
        }
        else
        {
            if ((GetWindowLongPtr(hWnd, GWL_STYLE) & WS_CHILD))
                return DDERR_INVALIDPARAMS;
        }

        if ((m_gbl->lpExclusiveOwner != nullptr) &&
            (m_gbl->lpExclusiveOwner != m_lcl))
            return DDERR_INVALIDPARAMS;

        m_gbl->lpExclusiveOwner = m_lcl;
        m_lcl->dwLocalFlags = DDRAWILCL_SETCOOPCALLED | DDRAWILCL_HOOKEDHWND |
            DDRAWILCL_HASEXCLUSIVEMODE | DDRAWILCL_ISFULLSCREEN | DDRAWILCL_ACTIVEYES;

        if (dwFlags & DDSCL_ALLOWMODEX)
            m_lcl->dwLocalFlags |= DDRAWILCL_ALLOWMODEX;

        m_lcl->hWnd = reinterpret_cast<ULONG_PTR>(hWnd);
        m_lcl->hFocusWnd = reinterpret_cast<ULONG_PTR>(hWnd);

        // TODO: Implement cursor clipping
    }

    return DD_OK;
}

STDMETHODIMP CDirectDraw::SetDisplayMode(_In_ DWORD dwWidth, _In_ DWORD dwHeight, _In_ DWORD dwBPP, _In_ DWORD dwRefreshRate, _In_ DWORD dwFlags)
{
    if (!m_bInit)
        return DDERR_NOTINITIALIZED;

    MessageBoxA(GetHwnd(), "CDirectDraw::SetDisplayMode", "ddraw.dll", MB_OK);
    return DD_OK;
}

STDMETHODIMP CDirectDraw::StartModeTest(_In_ LPSIZE lpModesToTest, _In_ DWORD dwNumEntries, _In_ DWORD dwFlags)
{
    if (!m_bInit)
        return DDERR_NOTINITIALIZED;

    MessageBoxA(GetHwnd(), "CDirectDraw::StartModeTest", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDraw::TestCooperativeLevel()
{
    if (!m_bInit)
        return DDERR_NOTINITIALIZED;

    MessageBoxA(GetHwnd(), "CDirectDraw::TestCooperativeLevel", "ddraw.dll", MB_OK);
    return DDERR_GENERIC;
}

STDMETHODIMP CDirectDraw::WaitForVerticalBlank(_In_ DWORD dwFlags, _In_ HANDLE hEvent)
{
    if (!m_bInit)
        return DDERR_NOTINITIALIZED;

    GET_DD_CALLBACK(WaitForVerticalBlank, WAITFORVERTICALBLANK);

    DDHAL_WAITFORVERTICALBLANKDATA data = { 0 };
    data.dwFlags = dwFlags;
    data.lpDD = m_gbl;
    data.WaitForVerticalBlank = m_lcl->lpDDCB->cbDDCallbacks.WaitForVerticalBlank;

    // TODO: handle bIsInVB (hEvent is unused)

    if (WaitForVerticalBlankCb(&data) == DDHAL_DRIVER_NOTHANDLED)
        return DDERR_UNSUPPORTED;

    return data.ddRVal;
}

HRESULT CDirectDraw::Startup(LPGUID guid)
{
    m_gbl->hDDVxd = -1;
    m_gbl->lpDriverHandle = m_gbl;
    m_gbl->lpDDCBtmp = new DDHAL_CALLBACKS();
    m_lcl->lpDDCB = m_gbl->lpDDCBtmp;
    m_lcl->dwProcessId = GetCurrentProcessId();
    m_gbl->lpModeInfo = new DDHALMODEINFO();

    ZeroMemory(m_gbl->lpModeInfo, sizeof(*m_gbl->lpModeInfo));
    ZeroMemory(m_gbl->lpDDCBtmp, sizeof(*m_gbl->lpDDCBtmp));

    // Creat the default HDC for HAL and HEL
    m_lcl->hDC = reinterpret_cast<ULONG_PTR>(CreateDC(_T("display"), nullptr, nullptr, nullptr));

    if (!m_lcl->hDC)
        return DDERR_GENERIC;


    /* according to https ://github.com/reactos/reactos/blob/40955b447cc225a9df1f03980f6ccaa5cfbd0573/dll/directx/ddraw/startup.c#L243
     cObsolete needs to be setted up to the display name */
    strncpy_s(m_gbl->cObsolete, _countof(m_gbl->cObsolete), "display", 7);
    strncpy_s(m_gbl->cDriverName, _countof(m_gbl->cDriverName), "display", 7);

    DWORD dwFlags = DDRAWI_DISPLAYDRV | DDRAWI_GDIDRV;

    if ((DWORD)guid != DDCREATE_HARDWAREONLY)
    {
        auto hr = StartupHel();
        if (FAILED(hr))
        {
            dwFlags |= DDRAWI_NOEMULATION;

            if ((DWORD)guid == DDCREATE_EMULATIONONLY)
                return DDERR_NODIRECTDRAWSUPPORT;
        }
        else
            dwFlags |= DDRAWI_EMULATIONINITIALIZED;
    }
    
    if ((DWORD)guid != DDCREATE_EMULATIONONLY)
    {
        auto hr = StartupHal();

        if (FAILED(hr))
        {
            dwFlags |= DDRAWI_NOHARDWARE;
            if ((DWORD)guid == DDCREATE_HARDWAREONLY)
                return DDERR_NODIRECTDRAWSUPPORT;
        }
    }

    m_gbl->dwFlags |= dwFlags | DDRAWI_ATTACHEDTODESKTOP;
    m_lcl->hDD = m_gbl->hDD;
    m_lcl->hDDVxd = m_gbl->hDDVxd;

    // setup DISPLAY information
    m_gbl->rectDevice.top = 0;
    m_gbl->rectDevice.left = 0;
    m_gbl->rectDevice.right = m_gbl->vmiData.dwDisplayWidth;
    m_gbl->rectDevice.bottom = m_gbl->vmiData.dwDisplayHeight;

    // setup DESKTOP information
    m_gbl->rectDesktop.top = 0;
    m_gbl->rectDesktop.left = 0;
    m_gbl->rectDesktop.right = m_gbl->vmiData.dwDisplayWidth;
    m_gbl->rectDesktop.bottom = m_gbl->vmiData.dwDisplayHeight;

    // Setup Modeinfo
    m_gbl->dwMonitorFrequency = GetDeviceCaps(GetWindowDC(nullptr), VREFRESH);
    m_gbl->lpModeInfo->dwWidth = m_gbl->vmiData.dwDisplayWidth;
    m_gbl->lpModeInfo->dwHeight = m_gbl->vmiData.dwDisplayHeight;
    m_gbl->lpModeInfo->dwBPP = m_gbl->vmiData.ddpfDisplay.dwRGBBitCount;
    m_gbl->lpModeInfo->lPitch = m_gbl->vmiData.lDisplayPitch;
    m_gbl->lpModeInfo->wRefreshRate = WORD(m_gbl->dwMonitorFrequency);
    m_gbl->lpModeInfo->dwRBitMask = m_gbl->vmiData.ddpfDisplay.dwRBitMask;
    m_gbl->lpModeInfo->dwGBitMask = m_gbl->vmiData.ddpfDisplay.dwGBitMask;
    m_gbl->lpModeInfo->dwBBitMask = m_gbl->vmiData.ddpfDisplay.dwBBitMask;
    m_gbl->lpModeInfo->dwAlphaBitMask = m_gbl->vmiData.ddpfDisplay.dwRGBAlphaBitMask;

    return DD_OK;
}

HRESULT CDirectDraw::StartupHal()
{
    /*
     *  Startup DX HAL step one of three
     */
    if (!DdCreateDirectDrawObject(m_gbl, reinterpret_cast<HDC>(m_lcl->hDC)))
        return DDERR_GENERIC;

    /* Some card disable the dx after it have been created so
     * we are force reenabling it
     */
    BOOL newMode = FALSE;
    if (!DdReenableDirectDrawObject(m_gbl, &newMode))
    {
        DdDeleteDirectDrawObject(m_gbl);
        return DDERR_GENERIC;
    }

    LPD3DHAL_CALLBACKS pD3DCb = new D3DHAL_CALLBACKS();
    LPD3DHAL_GLOBALDRIVERDATA pD3DDrvData = new D3DHAL_GLOBALDRIVERDATA();
    DDHALINFO halInfo = { 0 };

    pD3DDrvData->dwSize = sizeof(D3DHAL_GLOBALDRIVERDATA);
    pD3DCb->dwSize = sizeof(D3DHAL_CALLBACKS);

    m_gbl->lpD3DHALCallbacks = reinterpret_cast<ULONG_PTR>(pD3DCb);
    m_gbl->lpD3DGlobalDriverData = reinterpret_cast<ULONG_PTR>(pD3DDrvData);

    if (!DdQueryDirectDrawObject(m_gbl, &halInfo, 
        &m_gbl->lpDDCBtmp->HALDD,
        &m_gbl->lpDDCBtmp->HALDDSurface,
        &m_gbl->lpDDCBtmp->HALDDPalette,
        pD3DCb, pD3DDrvData,
        &m_gbl->lpDDCBtmp->HALDDExeBuf, 
        nullptr, nullptr, nullptr))
    {
        return DDERR_GENERIC;
    }

    m_gbl->dwNumFourCC = halInfo.ddCaps.dwNumFourCCCodes;
    m_gbl->lpdwFourCC = new DWORD[m_gbl->dwNumFourCC];

    LPDDSURFACEDESC textureFormats = new DDSURFACEDESC[pD3DDrvData->dwNumTextureFormats];
    LPVIDMEM vidMem = new VIDMEM[halInfo.vmiData.dwNumHeaps];

    if (!DdQueryDirectDrawObject(m_gbl, &halInfo,
        &m_gbl->lpDDCBtmp->HALDD,
        &m_gbl->lpDDCBtmp->HALDDSurface,
        &m_gbl->lpDDCBtmp->HALDDPalette,
        pD3DCb, pD3DDrvData,
        &m_gbl->lpDDCBtmp->HALDDExeBuf,
        textureFormats, m_gbl->lpdwFourCC, vidMem))
    {
        delete[] textureFormats;
        delete[] vidMem;

        return DDERR_GENERIC;
    }

    // copy data from halinfo to gbl
    memcpy_s(&m_gbl->vmiData, sizeof(m_gbl->vmiData), &halInfo.vmiData, sizeof(halInfo.vmiData));
    memcpy_s(&m_gbl->ddCaps, sizeof(m_gbl->ddCaps), &halInfo.ddCaps, sizeof(halInfo.ddCaps));

    if (m_gbl->vmiData.pvmList != vidMem)
    {
        MessageBoxA(nullptr, "OPS MEMORY", "FAIL", MB_OK);
        return DDERR_GENERIC;
    }

    m_gbl->dwModeIndex = halInfo.dwModeIndex;

    if (halInfo.dwFlags & DDHALINFO_GETDRIVERINFOSET)
    {
        auto hr = GetDriverInfo(GUID_MiscellaneousCallbacks, &m_gbl->lpDDCBtmp->HALDDMiscellaneous, sizeof(m_gbl->lpDDCBtmp->HALDDMiscellaneous));
        if (FAILED(hr))
        {
            return hr;
        }
    }

    if (halInfo.dwFlags & DDHALINFO_GETDRIVERINFO2)
        m_gbl->dwFlags |= DDRAWI_DRIVERINFO2;

    delete[] textureFormats; // TODO: ???

    return DD_OK;
}

HRESULT CDirectDraw::StartupHel()
{
    SetupHELCallbacks(m_gbl);
    return DD_OK;
}

HRESULT CDirectDraw::InitializeByLink(CDirectDraw* link)
{
    m_gbl = link->m_gbl;
    m_lcl = link->m_lcl;
    m_bInit = true;
    lpLcl = m_lcl;

    if (link->m_lastLink)
        lpLink = link->m_lastLink;
    else
        lpLink = link;

    link->m_lastLink = this;

    if (m_gbl)
        m_gbl->AddRef();
    if (m_lcl)
        m_lcl->AddRef();

    return DD_OK;
}

HRESULT CDirectDraw::Initialize(const GUID& iid, LPGUID lpGuid)
{
    if (m_bInit)
        return DDERR_ALREADYINITIALIZED;

    if (!IsDirectDrawSupported())
        return DDERR_NODIRECTDRAWSUPPORT;

    // this is a root object! Create the LCL and GBL

    ATL::CComObject<CDirectDrawLCL>* lcl;

    auto hr = ATL::CComObject<CDirectDrawLCL>::CreateInstance(&lcl);
    if (FAILED(hr))
        return hr;

    ATL::CComObject<CDirectDrawGBL>* gbl;
    hr = ATL::CComObject<CDirectDrawGBL>::CreateInstance(&gbl);

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

    if (IsEqualGUID(iid, IID_IDirectDraw7))
        m_lcl->dwLocalFlags = DDRAWILCL_DIRECTDRAW7;

    hr = Startup(lpGuid);

    if (FAILED(hr))
        return hr;

    m_bInit = true;
    return DD_OK;
}

HRESULT CDirectDraw::GetDriverInfo(const GUID& guid, PVOID lpvData, DWORD expectedSize)
{
    
}
