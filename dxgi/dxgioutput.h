/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     Monitor output
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
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

	CDXGIOutput() = default;
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
	// custom
	STDMETHODIMP Initialize(CDXGIAdapter* parent, DXGIOutputDesc& dsc);

private:
	STDMETHODIMP_(bool) CheckIfDDIFormatIsOk(D3DKMT_DISPLAYMODE* ddi, DXGI_FORMAT fmt, UINT flags);

	DXGIOutputDesc m_desc;
};
