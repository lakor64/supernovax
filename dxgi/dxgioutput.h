#pragma once

#include "dxgiobject.h"

class ATL_NO_VTABLE CDXGIOutput :
	public DXGIObjRoot,
	public CDXGIObject<IDXGIOutput>
{
public:
	BEGIN_COM_MAP(CDXGIOutput)
		COM_INTERFACE_ENTRY(IDXGIOutput)
		COM_INTERFACE_ENTRY(IDXGIObject)
	END_COM_MAP()

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
};
