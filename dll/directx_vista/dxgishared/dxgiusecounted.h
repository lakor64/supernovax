/*
 * PROJECT:     SupernovaX Graphics Infrastructure
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     Use counted object
 * COPYRIGHT:   Copyright 2023 Christian Rendina <pizzaiolo100@proton.me>
 */

#pragma once

/*** Definition of a UseCounted type */
class ATL_NO_VTABLE CDXGIUseCounted :
	public DXGIUseCountedType
{
public:
	// IUseCounted
	STDMETHODIMP_(ULONG) UCAddUse(void) override
	{
		MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGISwapChain::UCAddUse", "DEBUG", MB_OK);
		return 0;
	}

	STDMETHODIMP_(ULONG) UCReleaseUse(void) override
	{
		MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGISwapChain::UCReleaseUse", "DEBUG", MB_OK);
		return 0;
	}

	STDMETHODIMP UCBreakCyclicReferences(void) override
	{
		MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGISwapChain::UCBreakCyclicReferences", "DEBUG", MB_OK);
		return E_NOTIMPL;
	}

	STDMETHODIMP UCEnstablishCyclicReferences(void) override
	{
		MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGISwapChain::UCEnstablishCyclicReferences", "DEBUG", MB_OK);
		return E_NOTIMPL;
	}

	STDMETHODIMP UCDestroy(void) override
	{
		MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGISwapChain::UCDestroy", "DEBUG", MB_OK);
		return E_NOTIMPL;
	}

#if DXGI_VERSION >= 2
	// IUseCounted2
	STDMETHODIMP UCQueryInterface(_In_ UINT flags, _In_ REFIID riid, _COM_Outptr_ void** ppObj) override
	{
		if (!ppObj)
			return DXGI_ERROR_INVALID_CALL;

		*ppObj = nullptr;

		MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGISwapChain::UCQueryInterface", "DEBUG", MB_OK);
		return E_NOTIMPL;
	}
#endif
};
