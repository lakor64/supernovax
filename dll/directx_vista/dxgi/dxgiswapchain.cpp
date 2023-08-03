/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     Device swapchain
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#include "pch.h"
#include "dxgiswapchain.h"

CDXGISwapChain::CDXGISwapChain()
	: m_pBaseDev(nullptr), m_pDevInt(nullptr), m_pBB(nullptr)
{}

CDXGISwapChain::~CDXGISwapChain()
{
	if (m_pBB)
		m_pBB->Release();

	if (m_pDevInt)
		m_pDevInt->Release();

	if (m_pBaseDev)
		m_pBaseDev->Release();
}

 // IDXGISwapChain
STDMETHODIMP CDXGISwapChain::GetBuffer(_In_ UINT Buffer, _In_ REFIID riid, _Out_ void** ppSurface) 
{
	if (!ppSurface)
		return DXGI_ERROR_INVALID_CALL;

	*ppSurface = nullptr;

	if (Buffer > 0)
		return DXGI_ERROR_NOT_FOUND;

	return m_pBB->QueryInterface(riid, ppSurface);
}

STDMETHODIMP CDXGISwapChain::GetContainingOutput(_COM_Outptr_ IDXGIOutput** ppOutput) 
{
	if (!ppOutput)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGISwapChain::GetDesc(_Out_ DXGI_SWAP_CHAIN_DESC* pDesc) 
{
	if (!pDesc)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGISwapChain::GetFrameStatistics(_Out_ DXGI_FRAME_STATISTICS* pStats) 
{
	if (!pStats)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGISwapChain::GetFullscreenState(_Out_opt_ BOOL* pFullscreen, _COM_Outptr_ IDXGIOutput** ppTarget) 
{
	if (!ppTarget)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGISwapChain::GetLastPresentCount(_Out_ UINT* pLastPresentCount) 
{
	if (!pLastPresentCount)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGISwapChain::Present(_In_ UINT SyncInterval, _In_ UINT Flags) 
{
	return E_NOTIMPL;
}

STDMETHODIMP CDXGISwapChain::ResizeBuffers(_In_ UINT BufferCount, _In_ UINT Width, _In_ UINT Height, _In_ DXGI_FORMAT NewFormat, _In_ UINT SwapChainFlags) 
{
	return E_NOTIMPL;
}

STDMETHODIMP CDXGISwapChain::ResizeTarget(_In_ const DXGI_MODE_DESC* pNewTargetParameters) 
{
	if (!pNewTargetParameters)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGISwapChain::SetFullscreenState(_In_ BOOL Fullscreen, _In_ IDXGIOutput* pTarget)
{
	if (!pTarget)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}

// IUseCounted
STDMETHODIMP_(ULONG) CDXGISwapChain::UCAddUse(void)
{
	return 0;
}

STDMETHODIMP_(ULONG) CDXGISwapChain::UCReleaseUse(void)
{
	return 0;
}

STDMETHODIMP CDXGISwapChain::UCBreakCyclicReferences(void)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDXGISwapChain::UCEnstablishCyclicReferences(void)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDXGISwapChain::UCDestroy(void)
{
	return E_NOTIMPL;
}

#if DXGI_VERSION >= 2
// IDXGISwapChain1
STDMETHODIMP CDXGISwapChain::GetDesc1(_Out_ DXGI_SWAP_CHAIN_DESC1* pDesc)
{
	if (!pDesc)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGISwapChain::GetFullscreenDesc(_Out_ DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pDesc)
{
	if (!pDesc)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGISwapChain::GetHwnd(_Out_ HWND* pHwnd)
{
	if (!pHwnd)
		return DXGI_ERROR_INVALID_CALL;

	*pHwnd = nullptr;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGISwapChain::GetCoreWindow(_In_ REFIID refiid, _COM_Outptr_ void** ppUnk)
{
	if (!ppUnk)
		return DXGI_ERROR_INVALID_CALL;

	*ppUnk = nullptr;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGISwapChain::Present1(_In_ UINT SyncInterval, _In_ UINT PresentFlags, _In_ const DXGI_PRESENT_PARAMETERS* pPresentParameters)
{
	if (!pPresentParameters)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}

STDMETHODIMP_(BOOL) CDXGISwapChain::IsTemporaryMonoSupported(void)
{
	return FALSE;
}

STDMETHODIMP CDXGISwapChain::GetRestrictToOutput(_Out_ IDXGIOutput** ppRestrictToOutput)
{
	if (!ppRestrictToOutput)
		return DXGI_ERROR_INVALID_CALL;

	*ppRestrictToOutput = nullptr;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGISwapChain::SetBackgroundColor(_In_ const DXGI_RGBA* pColor)
{
	if (!pColor)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGISwapChain::GetBackgroundColor(_Out_ DXGI_RGBA* pColor)
{
	if (!pColor)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGISwapChain::SetRotation(_In_ DXGI_MODE_ROTATION Rotation)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDXGISwapChain::GetRotation(_Out_ DXGI_MODE_ROTATION* pRotation)
{
	if (!pRotation)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}

// IUseCounted2
STDMETHODIMP CDXGISwapChain::UCQueryInterface(UINT flags, REFIID riid, void** ppObj)
{
	if (!ppObj)
		return DXGI_ERROR_INVALID_CALL;

	*ppObj = nullptr;

	return E_NOTIMPL;
}
#endif

STDMETHODIMP CDXGISwapChain::Initialize(_In_ IUnknown* pDevice, _In_ DXGI_SWAP_CHAIN_DESC* pDesc)
{
	m_pBaseDev = pDevice;
	m_pBaseDev->AddRef();

	auto hr = m_pBaseDev->QueryInterface(&m_pDevInt3);
	if (hr == E_NOINTERFACE)
	{
		// Windows 7 RTM
		hr = m_pBaseDev->QueryInterface(&m_pDevInt2);
		if (FAILED(hr))
		{
			// Vista RTM
			auto hr = m_pBaseDev->QueryInterface(&m_pDevInt);
			if (FAILED(hr))
				return hr;
		}
		else
		{
			m_pDevInt = m_pDevInt2;
		}
	}

	m_desc = *pDesc;

	DXGI_SURFACE_DESC dsc;
	dsc.Width = m_desc.BufferDesc.Width;
	dsc.Height = m_desc.BufferDesc.Height;
	dsc.Format = m_desc.BufferDesc.Format;
	dsc.SampleDesc = m_desc.SampleDesc;

	if (m_pDevInt3)
		hr = m_pDevInt3->CreateSurfaceInternal(this, nullptr, nullptr, &dsc, 1, 1, 0, 0, nullptr, (IDXGIResource**) &m_pBB);
	else
		hr = m_pDevInt->CreateSurfaceInternal(nullptr, &dsc, 1, 0, nullptr, &m_pBB);

	if (FAILED(hr))
		return hr;

	return S_OK;
}
