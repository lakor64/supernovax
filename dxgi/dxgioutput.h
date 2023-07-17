#pragma once

#include "dxgiobject.h"

class CDXGIOutput : public CDXGIObject, public IDXGIOutput
{
public:
	virtual HRESULT WINAPI QueryInterface(_In_ REFIID id, _Inout_ void** ppObj) override;

	HRESULT WINAPI FindClosestMatchingMode(_In_ const DXGI_MODE_DESC* pModeToMatch, _Out_ DXGI_MODE_DESC* pClosestMatch, _In_opt_ IUnknown* pConcernedDevice);
	HRESULT WINAPI GetDesc(_Out_ DXGI_OUTPUT_DESC* pDesc);
	HRESULT WINAPI GetDisplayModeList(_In_ DXGI_FORMAT EnumFormat, _In_ UINT Flags, _In_opt_ UINT* pNumModes, _Out_opt_ DXGI_MODE_DESC* pDesc);
	HRESULT WINAPI GetDisplaySurfaceData(_In_ IDXGISurface *pDestination);
	HRESULT WINAPI GetFrameStatistics(_Out_ DXGI_FRAME_STATISTICS* pStats);
	HRESULT WINAPI GetGammeControl(_Out_ DXGI_GAMMA_CONTROL* pArray);
	HRESULT WINAPI GetGammaControlCapabilities(_Out_ DXGI_GAMMA_CONTROL_CAPABILITIES* pGammaCaps);
	void WINAPI ReleaseOwnership(void);
	HRESULT WINAPI SetDisplaySurface(_In_ IDXGISurface* pScanoutSurface);
	HRESULT WINAPI SetGammaControl(_In_ const DXGI_GAMMA_CONTROL* pArray);
	HRESULT WINAPI TakeOwnership(_In_ IUnknown* pDevice, _In_ BOOL Exclusive);
	HRESULT WINAPI WaitForVBlank(void);
};

// TODO: Output1
