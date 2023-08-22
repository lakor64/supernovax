/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     Device swapchain
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#include "pch.h"
#include "dxgiswapchain.h"
#include "dllmain.h"

CDXGISwapChain::CDXGISwapChain()
	: m_pDevice(nullptr), m_pDevIntrnl1(nullptr), m_pDevIntrnl2(nullptr),
	m_pDevIntrnl3(nullptr)
{}

CDXGISwapChain::~CDXGISwapChain()
{
	if (m_pBB)
		m_pBB->Release();

	if (m_pDevIntrnl3)
		m_pDevIntrnl3->Release();

	if (m_pDevIntrnl2)
		m_pDevIntrnl2->Release();
	else if (m_pDevIntrnl1)
		m_pDevIntrnl1->Release();

	if (m_pDevice)
		m_pDevice->Release();
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
#if 0 // IIRC we cannot call this because it's for offline?
	D3DKMT_PRESENT pp = { 0 };
	pp.hWindow = m_desc.OutputWindow;
	pp.VidPnSourceId = -1;
	pp.SrcRect.bottom = m_desc.BufferDesc.Height;
	pp.SrcRect.right = m_desc.BufferDesc.Width;
	pp.DstRect.bottom = m_desc.BufferDesc.Height;
	pp.DstRect.right = m_desc.BufferDesc.Width;
	pp.pSrcSubRects = &pp.SrcRect;
	pp.SubRectCnt = 1;
	pp.Flags.SrcRectValid = 1;
	pp.Flags.DstRectValid = 1;

	auto hr = m_pDevInt3->Present((IDXGIDebugProducer*)m_pBB, nullptr, &pp, 0, 0);
#endif

	DXGI_FORMAT fmt = DXGI_FORMAT_UNKNOWN;
	UINT64 updId;
	HANDLE dxSurface;
	auto hr = _AtlModule.GetDwmDxGetWindowSharedSurface()(m_desc.OutputWindow, m_adapterDesc.AdapterLuid, nullptr, 0, &fmt, &dxSurface, &updId);
	if (FAILED(hr))
		return hr;

	IDXGIResource* pDwmSurface;
	hr = m_pDevIntrnl3->OpenSharedResource(dxSurface, 0, __uuidof(pDwmSurface), (void**)&pDwmSurface);
	if (FAILED(hr))
		return hr;

	RECT rc;
	GetClientRect(m_desc.OutputWindow, &rc);

	// pls is this ok?
	struct SUBRESOURCE_BLT_MAP_RES
	{
		DWORD dstSubId;
		DWORD srcSubid;
	};

	struct SUBRESOURCE_BLT_MAP
	{
		DWORD subResCount;
		SUBRESOURCE_BLT_MAP_RES res[2];
	};

	SUBRESOURCE_BLT_MAP bltMap = { 0 };
	
	hr = m_pDevIntrnl3->Blt((IDXGIResource*)m_pBB, nullptr, nullptr, 0, pDwmSurface, nullptr, &bltMap, updId, 1, 0);
	if (FAILED(hr))
	{
		pDwmSurface->Release();
		return hr;
	}

	hr = _AtlModule.GetDwmDxUpdateWindowSharedSurface()(m_desc.OutputWindow, updId, 0, nullptr, &rc);
	if (FAILED(hr))
	{
		pDwmSurface->Release();
		return hr;
	}

	pDwmSurface->Release();
	return hr;
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

STDMETHODIMP CDXGISwapChain::Initialize(_In_ IDXGIFactory* pFactory, _In_ IUnknown* pDevice, _In_ DXGI_SWAP_CHAIN_DESC* pDesc)
{
	SetParent(pFactory);

	auto hr = pDevice->QueryInterface(&m_pDevice);
	if (FAILED(hr))
		return hr; // cannot fail!

	// TODO: Make the shitty hack for Windows 10 IDXGIDeviceInternal3
	hr = m_pDevice->QueryInterface(&m_pDevIntrnl3);
	if (hr == E_NOINTERFACE)
	{
#if 0
		// Windows 7 RTM
		hr = m_pDevice->QueryInterface(&m_pDevIntrnl2);
		if (FAILED(hr))
		{
			// Vista RTM
			hr = m_pDevice->QueryInterface(&m_pDevIntrnl1);
			if (FAILED(hr))
				return hr;
		}
		else
		{
			m_pDevIntrnl1 = m_pDevIntrnl2;
		}
#else
		return E_NOTIMPL;
#endif
	}

	hr = m_pDevice->GetAdapter(&m_pAdapter);
	if (FAILED(hr))
		return hr;

	hr = m_pAdapter->GetDesc(&m_adapterDesc);
	if (FAILED(hr))
		return hr;

	m_desc = *pDesc;

	DXGI_SURFACE_DESC dsc;
	dsc.Width = m_desc.BufferDesc.Width;
	dsc.Height = m_desc.BufferDesc.Height;
	dsc.Format = m_desc.BufferDesc.Format;
	dsc.SampleDesc = m_desc.SampleDesc;

	if (m_pDevIntrnl3)
	{
		// backbuffer (ID: 0)
		hr = m_pDevIntrnl3->CreateSurfaceInternal(this, nullptr, nullptr, &dsc, 1, 1, D3D11_BIND_RENDER_TARGET, 0, nullptr, (IDXGIResource**)&m_pBB);
	}
#if 0
	else
	{
		// TODO: Vista RTM/Windows 7 RTM support
		return E_NOTIMPL;
		//hr = m_pDevInt->CreateSurfaceInternal(nullptr, &dsc, 1, 0, nullptr, &m_pBB);
	}
#endif

	if (FAILED(hr))
		return hr;

	return S_OK;
}
