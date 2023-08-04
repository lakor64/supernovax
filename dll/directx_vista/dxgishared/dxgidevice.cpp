/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     Render device
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#include "pch.h"
#include "dxgidevice.h"

 // IDXGIDevice	
STDMETHODIMP CDXGIDevice::CreateSurface(_In_ const DXGI_SURFACE_DESC* pDesc, _In_ UINT NumSurfaces, _In_ DXGI_USAGE Usage, _In_opt_ const DXGI_SHARED_RESOURCE* pSharedResource, _COM_Outptr_ IDXGISurface** ppSurface) 
{
	if (!ppSurface)
		return DXGI_ERROR_INVALID_CALL;

	*ppSurface = nullptr;

	if (!pDesc)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGIDevice::GetAdapter(_COM_Outptr_ IDXGIAdapter** pAdapter) 
{
	if (!pAdapter)
		return DXGI_ERROR_INVALID_CALL;

	*pAdapter = nullptr;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGIDevice::GetGPUThreadPriority(_Out_ INT* pPriority) 
{
	if (!pPriority)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGIDevice::QueryResourceResidency(_In_ IUnknown* const* ppResources, _Out_ DXGI_RESIDENCY* pResidencyStatus, _In_ UINT NumResources) 
{
	if (!ppResources)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGIDevice::SetGPUThreadPriority(_In_ INT Priority) 
{
	return E_NOTIMPL;
}

#if DXGI_VERSION >= 1
// IDXGIDevice1
STDMETHODIMP CDXGIDevice::GetMaximumFrameLatency(_Out_ UINT* pMaxLatency)
{
	if (!pMaxLatency)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}
#endif
