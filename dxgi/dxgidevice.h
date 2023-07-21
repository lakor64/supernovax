#pragma once

#include "dxgiobject.h"

class ATL_NO_VTABLE CDXGIDevice : 
	public DXGIObjRoot,
	public CDXGIObject<IDXGIDevice1>
{
public:
	BEGIN_COM_MAP(CDXGIDevice)
		COM_INTERFACE_ENTRY(IDXGIDevice1)
		COM_INTERFACE_ENTRY(IDXGIDevice)
		COM_INTERFACE_ENTRY(IDXGIObject)
	END_COM_MAP()

	// IDXGIDevice	
	STDMETHODIMP CreateSurface(_In_ const DXGI_SURFACE_DESC* pDesc, _In_ UINT NumSurfaces, _In_ DXGI_USAGE Usage, _In_opt_ const DXGI_SHARED_RESOURCE* pSharedResource, _COM_Outptr_ IDXGISurface** ppSurface) override;
	STDMETHODIMP GetAdapter(_COM_Outptr_ IDXGIAdapter** pAdapter) override;
	STDMETHODIMP GetGPUThreadPriority(_Out_ INT* pPriority) override;
	STDMETHODIMP QueryResourceResidency(_In_ IUnknown* const* ppResources, _Out_ DXGI_RESIDENCY *pResidencyStatus, _In_ UINT NumResources) override;
	STDMETHODIMP SetGPUThreadPriority(_In_ INT Priority) override;
	// IDXGIDevice1
	STDMETHODIMP GetMaximumFrameLatency(_Out_ UINT* pMaxLatency) override;
};