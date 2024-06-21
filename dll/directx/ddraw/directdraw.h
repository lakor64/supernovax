/*
 * PROJECT:     ReactXDraw
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     IDirectDraw7 object
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */

#pragma once

/**
* Main IDirectDraw7 ATL object
*/
class CDirectDraw :
    public CDirectDrawINT,
    public DDObjRoot
{
public:

    BEGIN_COM_MAP(CDirectDraw)
        COM_INTERFACE_ENTRY_IID(IID_IDirectDraw7, IDirectDraw7)
    END_COM_MAP()

    /**
    * Default ATL constructor
    */
    CDirectDraw();

    /**
    * Destructor which data is freed
    */
    ~CDirectDraw();

    /**
    * Extends the basic AddRef to include the reference counter of the internal object
    * @return Number of references after the increase
    */
    ULONG InternalAddRef()
    {
        CDirectDrawINT::InternalAddRef();
        return DDObjRoot::InternalAddRef();
    }

    /**
    * Extends the basic Release to include the reference counter of the internal object
    * @return Number of references after the decrease
    */
    ULONG InternalRelease()
    {
        CDirectDrawINT::InternalRelease();
        return DDObjRoot::InternalRelease();
    }

    /**
    * This function overrides the QueryInterface functionality to provide a link relationship used in DirectDraw
    * @param[in] pThis Pointer to the parent instance
    * @param[in] pEntries List of ATL IID entries
    * @param[in] iid Requested interface
    * @param[out] ppvObject Output object interface
    * @return S_OK or any error during creation
    */
    static HRESULT InternalQueryInterface(
        void* pThis,
        const ATL::_ATL_INTMAP_ENTRY* pEntries,
        REFIID iid,
        void** ppvObject)
    {
        for (; pEntries->pFunc != nullptr; pEntries++)
        {
            if (IsEqualIID(iid, *pEntries->piid) || IsEqualIID(iid, IID_IDirectDraw4)) // TODO: THIS IS AN HACK!!
            {
                ATL::CComObject<CDirectDraw>* ptr;
                auto hr = ATL::CComObject<CDirectDraw>::CreateInstance(&ptr);
                if (FAILED(hr))
                    return hr;

                hr = ptr->InitializeByLink(reinterpret_cast<CDirectDraw*>(pThis));
                if (FAILED(hr))
                {
                    delete ptr;
                    return hr;
                }

                ptr->AddRef();
                *ppvObject = ptr;
                return S_OK;
            }
        }

        return E_NOINTERFACE;
    }

    STDMETHODIMP Compact() override;
    STDMETHODIMP CreateClipper(_In_ DWORD dwFlags, _COM_Outptr_ LPDIRECTDRAWCLIPPER* lplpDDClipper, _In_ IUnknown* pUnkOuter) override;
    STDMETHODIMP CreatePalette(_In_ DWORD dwFlags, _In_ LPPALETTEENTRY lpDDColorArray, _COM_Outptr_ LPDIRECTDRAWPALETTE* lplpDDPalette, _In_ IUnknown* pUnkOuter) override;
    STDMETHODIMP CreateSurface(_In_ LPDDSURFACEDESC2 lpDDSurfaceDesc2 , _COM_Outptr_ LPDIRECTDRAWSURFACE7* lplpDDSurface, _In_ IUnknown* pUnkOuter) override;
    STDMETHODIMP DuplicateSurface(_In_ LPDIRECTDRAWSURFACE7 lpDDSurface, _COM_Outptr_ LPDIRECTDRAWSURFACE7* lplpDupDDSurface) override;
    STDMETHODIMP EnumDisplayModes(_In_ DWORD dwFlags, _In_ LPDDSURFACEDESC2 lpDDSurfaceDesc2, _In_ LPVOID lpContext, _In_ LPDDENUMMODESCALLBACK2 lpEnumModesCallback) override;
    STDMETHODIMP EnumSurfaces(_In_ DWORD dwFlags, _In_ LPDDSURFACEDESC2 lpDDS2, _In_ LPVOID lpContext, _In_ LPDDENUMSURFACESCALLBACK7 lpEnumSurfaceCallback) override;
    STDMETHODIMP EvaluateMode(_In_ DWORD dwFlags, _Out_ DWORD* pSecondsUntilTimeout) override;
    STDMETHODIMP FlipToGDISurface() override;
    STDMETHODIMP GetAvailableVidMem(_In_ LPDDSCAPS2 lpDDSCaps2, _Out_ LPDWORD lpdwTotal, _Out_ LPDWORD lpdwFree) override;
    STDMETHODIMP GetCaps(_Out_ LPDDCAPS lpDDDriverCaps, _Out_ LPDDCAPS lpDDHELCaps) override;
    STDMETHODIMP GetDeviceIdentifier(_Out_ LPDDDEVICEIDENTIFIER2 lpdddi, _In_ DWORD dwFlags) override;
    STDMETHODIMP GetDisplayMode(_In_ LPDDSURFACEDESC2 lpDDSurfaceDesc2) override;
    STDMETHODIMP GetFourCCCodes(_Inout_ LPDWORD lpNumCodes, _Inout_ LPDWORD lpCodes) override;
    STDMETHODIMP GetGDISurface(_COM_Outptr_ LPDIRECTDRAWSURFACE7* lplpGDIDDSSurface) override;
    STDMETHODIMP GetMonitorFrequency(_Out_ LPDWORD lpdwFrequency) override;
    STDMETHODIMP GetScanLine(_Out_ LPDWORD lpdwScanLine) override;
    STDMETHODIMP GetSurfaceFromDC(_In_ HDC hdc, _COM_Outptr_ LPDIRECTDRAWSURFACE7* lpDDS) override;
    STDMETHODIMP GetVerticalBlankStatus(_Out_ LPBOOL lpbIsInVB) override;
    STDMETHODIMP Initialize(_In_ GUID* lpGUID) override;
    STDMETHODIMP RestoreAllSurfaces() override;
    STDMETHODIMP RestoreDisplayMode() override;
    STDMETHODIMP SetCooperativeLevel(_In_ HWND hWnd, _In_ DWORD dwFlags) override;
    STDMETHODIMP SetDisplayMode(_In_ DWORD dwWidth, _In_ DWORD dwHeight, _In_ DWORD dwBPP, _In_ DWORD dwRefreshRate, _In_ DWORD dwFlags) override;
    STDMETHODIMP StartModeTest(_In_ LPSIZE lpModesToTest, _In_ DWORD dwNumEntries, _In_ DWORD dwFlags) override;
    STDMETHODIMP TestCooperativeLevel() override;
    STDMETHODIMP WaitForVerticalBlank(_In_ DWORD dwFlags, _In_ HANDLE hEvent) override;

    /**
    * Gets the focused HWND
    * @return Focused HWND
    */
    HWND GetHwnd() const { return reinterpret_cast<HWND>(lpLcl->hFocusWnd); }

    constexpr const bool HaveEmulation() const { return m_gbl->dwFlags & DDRAWI_EMULATIONINITIALIZED; }
    constexpr const bool HaveHardware() const { return (m_gbl->dwFlags & DDRAWI_NOHARDWARE) == 0; }

    HRESULT Initialize(const GUID& iid, LPGUID lpGuid);
    HRESULT InitializeByLink(CDirectDraw* link);

private:
    /**
    * Starts up the DirectDraw component. This function is responsable for the real initialization
    *  of DirectDraw, which includes setting up HEL and HAL callbacks.
    * @param[in] guid GPU guid or configuration
    * @return DD_OK or DD_ERROR*
    */
    HRESULT Startup(LPGUID guid);

    /**
    * Starts up DirectDraw Hardware Emulation Layer (HEL)
    * @return DD_OK or DD_ERROR*
    */
    HRESULT StartupHel();

    /**
    * Starts up DirectDraw Hardware Abstraction Layer (HAL)
    * @return DD_OK or DD_ERROR*
    */
    HRESULT StartupHal();

    /**
    * Gets information from the driver
    * @param guid GUID request
    * @param lpvData Data to send
    * @param expectedSize Size of the data to send
    * @return DD_OK or DD_ERROR*
    * @see https://learn.microsoft.com/en-us/windows/win32/api/ddrawint/ns-ddrawint-dd_getdriverinfodata
    */
    HRESULT GetDriverInfo(const GUID& guid, PVOID lpvData, DWORD expectedSize);

    /**
    * Getx extra information from the driver
    * <p>
    * Note: DirectX8+
    * </p>
    * @param type Request ID
    * @param lpvData Data to send
    * @param expectedSize Size of the data to send
    */
    HRESULT GetDriverInfo2(DWORD type, PVOID lpvData, DWORD expectedSize);
    
    /**
    * Global pointer to GBL
    */
    ATL::CComObject<CDirectDrawGBL>* m_gbl;

    /**
    * Global pointer to LCL
    */
    ATL::CComObject<CDirectDrawLCL>* m_lcl;

    /**
    * True if the object was initialized, otherwise false
    */
    bool m_bInit;

    /**
    * Last linked object
    */
    CDirectDraw* m_lastLink;
};
