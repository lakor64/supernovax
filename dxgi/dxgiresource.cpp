/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     GPU resource
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#include "pch.h"
#include "dxgiresource.h"

STDMETHODIMP CDXGIResource::GetEvictionPriority(_Out_ UINT* pEvictionPriority)
{
	if (!pEvictionPriority)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGIResource::GetSharedHandle(_Out_ HANDLE* pSharedHandle)
{
	if (!pSharedHandle)
		return DXGI_ERROR_INVALID_CALL;

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
