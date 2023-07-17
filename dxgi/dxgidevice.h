#pragma once

#include "dxgiobject.h"

class CDXGIDevice : public CDXGIObject, IDXGIDevice
{
public:
	virtual HRESULT WINAPI QueryInterface(_In_ REFIID id, _Inout_ void** ppObj) override;
	
	HRESULT WINAPI CreateSurface(_In_ const DXGI_SURFACE_DESC* pDesc, _In_ UINT NumSurfaces, _In_ DXGI_USAGE Usage, _In_opt_ const DXGI_SHARED_RESOURCE* pSharedResource, _Out_ IDXGISurface** ppSurface);
	HRESULT WINAPI GetAdapter(_Out_ IDXGIAdapter** pAdapter);
	HRESULT WINAPI GetGPUThreadPriority(_Out_ INT* pPriority);
	HRESULT WINAPI QueryResourceResidency(_In_ IUnknown* const* ppResources, _Out_ DXGI_RESIDENCY *pResidencyStatus, _In_ UINT NumResources);
	HRESULT WINAPI SetGPUThreadPriority(_In_ INT Priority);
};

// TODO: Device1
// TODO: Device2
