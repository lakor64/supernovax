/*
 * PROJECT:     SupernovaX Graphics Infrastructure
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     GPU resource
 * COPYRIGHT:   Copyright 2023 Christian Rendina <pizzaiolo100@proton.me>
 */

#include "dxgishared.h"
#include "dxgiresource.h"

STDMETHODIMP CDXGIResource::GetEvictionPriority(_Out_ UINT* pEvictionPriority)
{
	if (!pEvictionPriority)
		return DXGI_ERROR_INVALID_CALL;

	*pEvictionPriority = 0;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGIResource::GetSharedHandle(_Out_ HANDLE* pSharedHandle)
{
	if (!pSharedHandle)
		return DXGI_ERROR_INVALID_CALL;

	*pSharedHandle = nullptr;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGIResource::GetUsage(_Out_ DXGI_USAGE* pUsage)
{
	if (!pUsage)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGIResource::SetEvictionPriority(_In_ UINT EvictionPriority)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDXGIResource::CreateSubresourceSurface(_In_ UINT index, _COM_Outptr_ IDXGISurface2** ppSurface)
{
	if (!ppSurface)
		return DXGI_ERROR_INVALID_CALL;

	*ppSurface = nullptr;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGIResource::CreateSharedHandle(_In_opt_ const SECURITY_ATTRIBUTES* pAttributes, _In_ DWORD dwAccess, _In_opt_ LPCWSTR lpName, _Out_ HANDLE* pHandle)
{
	if (!pHandle)
		return DXGI_ERROR_INVALID_CALL;

	*pHandle = nullptr;

	return E_NOTIMPL;
}