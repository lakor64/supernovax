/*
 * PROJECT:     SupernovaX Graphics Infrastructure
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     Monitor output
 * COPYRIGHT:   Copyright 2023 Christian Rendina <pizzaiolo100@proton.me>
 */

#pragma once

#include "dxgiobject.h"

class CDXGIAdapter;

class ATL_NO_VTABLE CDXGIOutput :
	public DXGIObjRoot,
	public CDXGIObject<DXGIOutputType>
{
public:
	BEGIN_COM_MAP(CDXGIOutput)
#if DXGI_VERSION >= 6
		COM_INTERFACE_ENTRY_IID(IID_IDXGIOutput6, IDXGIOutput6)
#endif
#if DXGI_VERSION >= 5
		COM_INTERFACE_ENTRY_IID(IID_IDXGIOutput5, IDXGIOutput5)
#endif
#if DXGI_VERSION >= 4
		COM_INTERFACE_ENTRY_IID(IID_IDXGIOutput4, IDXGIOutput4)
#endif
#if DXGI_VERSION >= 3
		COM_INTERFACE_ENTRY_IID(IID_IDXGIOutput3, IDXGIOutput3)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIOutput2, IDXGIOutput2)
#endif
#if DXGI_VERSION >= 2
		COM_INTERFACE_ENTRY_IID(IID_IDXGIOutput1, IDXGIOutput1)
#endif
		COM_INTERFACE_ENTRY_IID(IID_IDXGIOutput, IDXGIOutput)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIObject, IDXGIObject)
	END_COM_MAP()

	CDXGIOutput();
	~CDXGIOutput() = default;

	// IDXGIOutput
	STDMETHODIMP FindClosestMatchingMode(_In_ const DXGI_MODE_DESC* pModeToMatch, _Out_ DXGI_MODE_DESC* pClosestMatch, _In_opt_ IUnknown* pConcernedDevice) override;
	STDMETHODIMP GetDesc(_Out_ DXGI_OUTPUT_DESC* pDesc) override;
	STDMETHODIMP GetDisplayModeList(_In_ DXGI_FORMAT EnumFormat, _In_ UINT Flags, _In_opt_ UINT* pNumModes, _Out_opt_ DXGI_MODE_DESC* pDesc) override;
	STDMETHODIMP GetDisplaySurfaceData(_In_ IDXGISurface *pDestination) override;
	STDMETHODIMP GetFrameStatistics(_Out_ DXGI_FRAME_STATISTICS* pStats) override;
	STDMETHODIMP GetGammaControl(_Out_ DXGI_GAMMA_CONTROL* pArray) override;
	STDMETHODIMP GetGammaControlCapabilities(_Out_ DXGI_GAMMA_CONTROL_CAPABILITIES* pGammaCaps) override;
	STDMETHODIMP_(void) ReleaseOwnership(void) override;
	STDMETHODIMP SetDisplaySurface(_In_ IDXGISurface* pScanoutSurface) override;
	STDMETHODIMP SetGammaControl(_In_ const DXGI_GAMMA_CONTROL* pArray) override;
	STDMETHODIMP TakeOwnership(_In_ IUnknown* pDevice, _In_ BOOL Exclusive) override;
	STDMETHODIMP WaitForVBlank(void) override;
#if DXGI_VERSION >= 2
	STDMETHODIMP GetDisplayModeList1(_In_ DXGI_FORMAT EnumFormat, _In_ UINT Flags, _Inout_  UINT* pNumModes, _Out_writes_to_opt_(*pNumModes, *pNumModes)  DXGI_MODE_DESC1* pDesc) override;
	STDMETHODIMP FindClosestMatchingMode1(_In_  const DXGI_MODE_DESC1* pModeToMatch, _Out_  DXGI_MODE_DESC1* pClosestMatch, _In_opt_  IUnknown* pConcernedDevice) override;
	STDMETHODIMP GetDisplaySurfaceData1(_In_  IDXGIResource* pDestination) override;
	STDMETHODIMP DuplicateOutput(_In_ IUnknown* pDevice, _COM_Outptr_  IDXGIOutputDuplication** ppOutputDuplication) override;
#endif

	/**
	* @brief Initializes a DXGI Output
	* @param[in] hSoft Software adapter
	* @param[in] parent Parent adapter
	* @param dsc Information desc to use
	* @return S_OK in case of success, or any HRESULT
	*/
	STDMETHODIMP Initialize(_In_ HMODULE hSoft, _In_ CDXGIAdapter* parent, const DXGIOutputInfo& dsc);


	/**
	* Sets the monitor info
	* @param desktopCoord Desktop coordinated
	* @param hm Handle to the monitor
	* @param attachedToDesk If the output is attached to the desktop
	* @remarks SHOULD BE ONLY USED INTERNALLY!!!
	*/
	STDMETHODIMP_(void) SetMonitorInfo(RECT desktopCoord, HMONITOR hm, BOOL attachedToDesk)
	{
		m_desc.AttachedToDesktop = attachedToDesk;
		m_desc.Monitor = hm;
		m_desc.DesktopCoordinates = desktopCoord;
	}


	/**
	* @brief Gets the device name
	* @return Name of the output device
	*/
	LPCWSTR GetDeviceName() const { return m_desc.DeviceName; }

private:
	/**
	* @brief Checks if the DDI format is ok for this output
	* @param ddi Display mode to check
	* @return true in case it's ok, otherwise false
	*/
	STDMETHODIMP_(bool) CheckIfDDIFormatIsOk(const D3DKMT_DISPLAYMODE& ddi, DXGI_FORMAT fmt, UINT flags);

	/**
	* @brief Sets up output descriptor
	*/
	STDMETHODIMP_(void) GetOutputDesc();

	/**
	* @brief Tries to load D3DKMT APIs
	* @return S_OK in case of success, or DXGI_ERROR_UNSUPPORTED in case of error
	*/
	STDMETHODIMP LoadD3DKMTApi();

	/// output desc type
	DXGIOutputDescType m_desc;

	/// adapter handle
	D3DKMT_HANDLE m_hHandle;

	/// vid pn
	D3DDDI_VIDEO_PRESENT_SOURCE_ID m_VidPn;

	/// software adapter
	HMODULE m_hDll;

	/// if the output is valid or not
	bool m_bValid;

	// D3DKMT APIs
	D3DKMTGetDisplayModeList_ D3DKMTGetDisplayModeList;
	D3DKMTGetDeviceState_ D3DKMTGetDeviceState;
	D3DKMTWaitForVerticalBlankEvent_ D3DKMTWaitForVerticalBlankEvent;
};
