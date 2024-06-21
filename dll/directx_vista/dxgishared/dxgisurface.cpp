/*
 * PROJECT:     ReactX Graphics Infrastructure
 * LICENSE:     LGPL-2.0-or-later (https://spdx.org/licenses/LGPL-2.0-or-later.html)
 * PURPOSE:     Render surface
 * COPYRIGHT:   Copyright 2023 Christian Rendina <pizzaiolo100@proton.me>
 */

#include "dxgishared.h"
#include "dxgisurface.h"

 // IDXGISurface
STDMETHODIMP CDXGISurface::GetDesc(_Out_ DXGI_SURFACE_DESC* pDesc)
{
	if (!pDesc)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGISurface::Map(_Out_ DXGI_MAPPED_RECT* pLockedRect, _In_ UINT MapFlags)
{
	if (!pLockedRect)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGISurface::Unmap(void)
{
	return E_NOTIMPL;
}

#if DXGI_VERSION >= 1
// IDXGISurface1
STDMETHODIMP CDXGISurface::GetDC(_In_ BOOL Discard, _Out_ HDC* pHdc)
{
	if (!pHdc)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGISurface::ReleaseDC(_In_opt_ RECT* pDirtyRect)
{
	return E_NOTIMPL;
}
#endif

#if DXGI_VERSION >= 2
STDMETHODIMP CDXGISurface::GetResource(_In_  REFIID riid, _COM_Outptr_ void** ppParentResource, _Out_ UINT* pSubresourceIndex)
{
	if (!ppParentResource)
		return DXGI_ERROR_INVALID_CALL;

	*ppParentResource = nullptr;

	if (!pSubresourceIndex)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}

#endif
