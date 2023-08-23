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
	: m_pDevice(nullptr), m_pAdapter(nullptr), m_DevVersion(0)
{
	m_uInternalDevice.D1 = nullptr;
}

CDXGISwapChain::~CDXGISwapChain()
{
	for (auto& buffer : m_vBuffers)
		buffer->Release();

	if (m_uInternalDevice.D1)
		m_uInternalDevice.D1->Release();

	if (m_pDevice)
		m_pDevice->Release();
}

 // IDXGISwapChain
STDMETHODIMP CDXGISwapChain::GetBuffer(_In_ UINT Buffer, _In_ REFIID riid, _Out_ void** ppSurface) 
{
	if (!ppSurface)
		return DXGI_ERROR_INVALID_CALL;

	*ppSurface = nullptr;

	if (Buffer >= m_vBuffers.size())
		return DXGI_ERROR_NOT_FOUND;

	return m_vBuffers.at(Buffer)->QueryInterface(riid, ppSurface);
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

	//if (m_desc.Windowed)
	{
		if (ApiCallback.DwmIsCompositionEnabled)
		{
			BOOL haveDwm = FALSE;
			auto hr = ApiCallback.DwmIsCompositionEnabled(&haveDwm);
			if (SUCCEEDED(hr) && haveDwm)
				return PresentToDWM(SyncInterval, Flags);
		}

		// assume we don't have DWM
		return PresentToGDI(SyncInterval, Flags);
	}

	// full screen presentation (D3DKMTPresent) not supported!
	//return DXGI_ERROR_UNSUPPORTED;
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

	hr = m_pDevice->QueryInterface(&m_uInternalDevice.D3);
	if (hr == E_NOINTERFACE)
	{
		// Windows 7 RTM
		hr = m_pDevice->QueryInterface(&m_uInternalDevice.D2);
		if (FAILED(hr))
		{
			// Vista RTM
			hr = m_pDevice->QueryInterface(&m_uInternalDevice.D1);
			if (FAILED(hr))
				return hr;

			m_DevVersion = 1;
		}
		else
			m_DevVersion = 2;
	}
	else
		m_DevVersion = 3;

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

	IDXGIResource* pBB = nullptr;
	if (m_DevVersion == 3)
	{
		/*
		* Creates the backbuffer (texture id = 0)
		* We must make this a Render target or we cannot draw inside it from a device
		*/
		hr = m_uInternalDevice.D3->CreateSurfaceInternal(this, nullptr, nullptr, &dsc, 1, 1, DXGI_RESOURCE_BIND_RENDER_TARGET, 0, nullptr, &pBB);
	}
	else
	{
		// TODO: Vista RTM/Windows 7 RTM support
		return E_NOTIMPL;
		//hr = m_pDevInt->CreateSurfaceInternal(nullptr, &dsc, 1, 0, nullptr, &pBB);
	}

	if (FAILED(hr))
		return hr;

	m_vBuffers.push_back(pBB);

	return S_OK;
}

STDMETHODIMP CDXGISwapChain::PresentToDWM(_In_ UINT SyncInterval, _In_ UINT Flags)
{
	DXGI_FORMAT fmt;
	UINT64 updId;
	HANDLE dxSurface;
	auto& bb = m_vBuffers.at(0);

	auto m = MonitorFromWindow(m_desc.OutputWindow, MONITOR_DEFAULTTONULL);

	auto hr = ApiCallback.DwmDxGetWindowSharedSurface(m_desc.OutputWindow, m_adapterDesc.AdapterLuid, m, DWM_REDIRECTION_FLAG_SUPPORT_PRESENT_TO_GDI_SURFACE | 8, &fmt, &dxSurface, &updId);
	if (FAILED(hr))
		return hr;

	IDXGIResource* pDwmSurface;
	hr = m_uInternalDevice.D3->OpenSharedResource(dxSurface, 1, __uuidof(pDwmSurface), (void**)&pDwmSurface);
	if (FAILED(hr))
		return hr;

	DXGI_PRESENT_SUBRESOURCES bltMap;
	DXGI_PRESENT_SUBRESOURCE test2[2];
	test2[0].SrcSubresource = 0;
	test2[0].DstSubresource = 0;
	test2[1].SrcSubresource = 1;
	test2[1].DstSubresource = 1;
	bltMap.Count = 1;
	bltMap.SubRes = test2;

	// destination rect
	RECT windowRect;
	if (!GetWindowRect(m_desc.OutputWindow, &windowRect))
		return DXGI_ERROR_NOT_CURRENTLY_AVAILABLE;

	RECT clientRect;
	if (!GetClientRect(m_desc.OutputWindow, &clientRect))
		return DXGI_ERROR_NOT_CURRENTLY_AVAILABLE;

	POINT borders;
	borders.y = (windowRect.bottom - windowRect.top) - clientRect.bottom;
	borders.x = (windowRect.right - windowRect.left) - clientRect.right;

	// destination rect with border fix applied
	clientRect.top = borders.y;
	clientRect.bottom += borders.y;
	clientRect.left += borders.x;
	clientRect.right += borders.x;

	hr = m_uInternalDevice.D3->Blt(bb, nullptr, nullptr, 0, pDwmSurface, nullptr, &bltMap, 0, 0, DXGI_DDI_MODE_ROTATION_IDENTITY);
	if (FAILED(hr))
	{
		pDwmSurface->Release();
		return hr;
	}

	hr = ApiCallback.DwmDxUpdateWindowSharedSurface(m_desc.OutputWindow, updId, DWM_REDIRECTION_FLAG_SUPPORT_PRESENT_TO_GDI_SURFACE, m, &windowRect);
	if (FAILED(hr))
	{
		pDwmSurface->Release();
		return hr;
	}

	pDwmSurface->Release();
	return S_OK;
}

STDMETHODIMP CDXGISwapChain::PresentToGDI(_In_ UINT SyncInterval, _In_ UINT Flags)
{
	return PresentToDWM(SyncInterval, Flags); // theory!

	auto& bb = m_vBuffers.at(0);

	// doesn't work on Windows Vista RTM!

	IDXGISurface1* bb1;
	auto hr = bb->QueryInterface(&bb1);
	if (FAILED(hr))
		return hr;

	RECT windowRect;
	if (!GetWindowRect(m_desc.OutputWindow, &windowRect))
		return DXGI_ERROR_NOT_CURRENTLY_AVAILABLE;

	RECT clientRect;
	if (!GetClientRect(m_desc.OutputWindow, &clientRect))
		return DXGI_ERROR_NOT_CURRENTLY_AVAILABLE;

	POINT borders;
	borders.y = (windowRect.bottom - windowRect.top) - clientRect.bottom;
	borders.x = (windowRect.right - windowRect.left) - clientRect.right;

	HDC hdc = nullptr;
	hdc = GetDC(m_desc.OutputWindow);
	if (!hdc)
		return DXGI_ERROR_NOT_CURRENTLY_AVAILABLE;

	HDC src = nullptr;
	hr = bb1->GetDC(FALSE, &src);
	if (FAILED(hr))
		return DXGI_ERROR_NOT_CURRENTLY_AVAILABLE;
	
	StretchBlt(hdc, borders.x, borders.y, clientRect.right + borders.x, clientRect.bottom + borders.y, src, 0, 0, m_desc.BufferDesc.Width, m_desc.BufferDesc.Height, SRCCOPY);

	ReleaseDC(m_desc.OutputWindow, hdc);
	bb1->ReleaseDC(nullptr);
	return S_OK;
}
