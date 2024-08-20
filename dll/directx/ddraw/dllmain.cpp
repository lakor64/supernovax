/*
 * PROJECT:     SupernovaX 2D Draw
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     ATL DLL entrypoint
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */
#include "pch.h"
#include "dllmain.h"
#include "directdraw.h"
#include "directdrawclipper.h"

/// Global ATL module
CATLDDRAWModule _AtlModule;

DdCreateDirectDrawObject_ DdCreateDirectDrawObject = nullptr;
DdDeleteDirectDrawObject_ DdDeleteDirectDrawObject = nullptr;
DdQueryDirectDrawObject_ DdQueryDirectDrawObject = nullptr;
DdQueryDisplaySettingsUniqueness_ DdQueryDisplaySettingsUniqueness = nullptr;
DdReenableDirectDrawObject_ DdReenableDirectDrawObject = nullptr;

HINSTANCE g_hDdraw = nullptr;
CRITICAL_SECTION g_dd_thread_lock = { 0 };

BOOL CATLDDRAWModule::MyInit()
{
    // Loads all WDDM callbacks

    InitializeCriticalSection(&g_dd_thread_lock);

    m_hGDI = LoadLibraryW(L"gdi32.dll");
    if (!m_hGDI)
        return FALSE;

    /*
        Callbacks required to talk to HAL.

        A ddraw workflow works as follows:
        ddraw.dll -> gdi32.dll -> ntdll.dll -> (end of user mode) -> win32k.sys -> dxg.sys
    */
    DdCreateDirectDrawObject = (DdCreateDirectDrawObject_)GetProcAddress(m_hGDI, "GdiEntry1");
    DdQueryDirectDrawObject = (DdQueryDirectDrawObject_)GetProcAddress(m_hGDI, "GdiEntry2");
    DdDeleteDirectDrawObject = (DdDeleteDirectDrawObject_)GetProcAddress(m_hGDI, "GdiEntry3");
    DdReenableDirectDrawObject = (DdReenableDirectDrawObject_)GetProcAddress(m_hGDI, "GdiEntry10");
    DdQueryDisplaySettingsUniqueness = (DdQueryDisplaySettingsUniqueness_)GetProcAddress(m_hGDI, "GdiEntry13");

    return DdCreateDirectDrawObject &&
        DdDeleteDirectDrawObject &&
        DdQueryDirectDrawObject &&
        DdReenableDirectDrawObject &&
        DdQueryDisplaySettingsUniqueness;
}

void CATLDDRAWModule::MyTerm()
{
    if (m_hGDI)
    {
        FreeLibrary(m_hGDI);
        m_hGDI = nullptr;
    }
}

BOOL WINAPI CATLDDRAWModule::DllMain(_In_ DWORD dwReason, _In_opt_ LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_DETACH:
        MyTerm();
        break;

    case DLL_PROCESS_ATTACH:
        return MyInit();
    default:
        break;
    }

    return TRUE;
}

extern "C"
{
    // TODO: Support DllGetClassObject

	BOOL WINAPI DllMain(_In_ HINSTANCE hInstance, _In_ DWORD dwReason, _In_opt_ LPVOID lpReserved)
	{
        g_hDdraw = hInstance;
        DisableThreadLibraryCalls(hInstance);
		return _AtlModule.DllMain(dwReason, lpReserved);
	}

    HRESULT WINAPI DirectDrawCreate(_In_ LPGUID lpGUID, LPDIRECTDRAW* lplpDD, IUnknown* pUnkOuter)
    {
        if (!lplpDD)
            return DDERR_INVALIDPARAMS;

        if (pUnkOuter)
            return CLASS_E_NOAGGREGATION;

        *lplpDD = nullptr;

        ATL::CComObject<CDirectDraw>* ddraw;
        HRESULT hr = ATL::CComObject<CDirectDraw>::CreateInstance(&ddraw);

        if (FAILED(hr))
            return hr;

        hr = ddraw->Initialize(IID_IDirectDraw4, lpGUID);

        if (FAILED(hr))
        {
            delete ddraw;
            return hr;
        }

        ddraw->AddRef();
        *lplpDD = reinterpret_cast<LPDIRECTDRAW>(ddraw);
        return S_OK;
    }

    HRESULT WINAPI DirectDrawCreateEx(_In_ LPGUID lpGUID, _In_ LPVOID* lplpDD, _In_ REFIID iid, _COM_Outptr_ IUnknown* pUnkOuter)
    {
        if (iid != IID_IDirectDraw7 || !lplpDD)
            return DDERR_INVALIDPARAMS;

        if (pUnkOuter)
            return CLASS_E_NOAGGREGATION;
        
        *lplpDD = nullptr;

        ATL::CComObject<CDirectDraw>* ddraw;
        HRESULT hr = ATL::CComObject<CDirectDraw>::CreateInstance(&ddraw);

        if (FAILED(hr))
            return hr;
        
        hr = ddraw->Initialize(iid, lpGUID);

        if (FAILED(hr))
        {
            delete ddraw;
            return hr;
        }

        ddraw->AddRef();
        *lplpDD = ddraw;

        return S_OK;
    }

    HRESULT WINAPI DirectDrawCreateClipper(_In_ DWORD dwFlags, _COM_Outptr_ LPDIRECTDRAWCLIPPER* lplpDDClipper, IUnknown* pUnkOuter)
    {
        if (dwFlags != 0)
            return DDERR_INVALIDPARAMS;

        if (pUnkOuter)
            return CLASS_E_NOAGGREGATION;
        
        *lplpDDClipper = nullptr;

        ATL::CComObject<CDirectDrawClipper>* clipper;
        HRESULT hr = ATL::CComObject<CDirectDrawClipper>::CreateInstance(&clipper);

        if (FAILED(hr))
            return hr;

        hr = clipper->Initialize(nullptr, dwFlags);

        if (FAILED(hr))
        {
            delete clipper;
            return hr;
        }

        hr = clipper->QueryInterface(IID_IDirectDrawClipper, reinterpret_cast<void**>(& lplpDDClipper));
        if (FAILED(hr))
        {
            delete clipper;
            return hr;
        }

        return S_OK;
    }
}
