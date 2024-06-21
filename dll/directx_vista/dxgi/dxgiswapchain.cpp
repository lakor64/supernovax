/*
 * PROJECT:     ReactX Graphics Infrastructure
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     Device swapchain
 * COPYRIGHT:   Copyright 2023 Christian Rendina <pizzaiolo100@proton.me>
 */

#include "pch.h"
#include "dxgiswapchain.h"
#include "dllmain.h"

CDXGISwapChain::CDXGISwapChain()
	: m_pAdapter(nullptr), m_cDevice(this)
{
}

CDXGISwapChain::~CDXGISwapChain()
{
	for (auto& buffer : m_vBuffers)
		buffer->Release();
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

	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGISwapChain::GetContainingOutput", "DEBUG", MB_OK);
	return E_NOTIMPL;
}

STDMETHODIMP CDXGISwapChain::GetDesc(_Out_ DXGI_SWAP_CHAIN_DESC* pDesc) 
{
	if (!pDesc)
		return DXGI_ERROR_INVALID_CALL;

	*pDesc = m_desc;
	return S_OK;
}

STDMETHODIMP CDXGISwapChain::GetFrameStatistics(_Out_ DXGI_FRAME_STATISTICS* pStats) 
{
	if (!pStats)
		return DXGI_ERROR_INVALID_CALL;

	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGISwapChain::GetFrameStatistics", "DEBUG", MB_OK);
	return E_NOTIMPL;
}

STDMETHODIMP CDXGISwapChain::GetFullscreenState(_Out_opt_ BOOL* pFullscreen, _COM_Outptr_ IDXGIOutput** ppTarget) 
{
	if (!ppTarget)
		return DXGI_ERROR_INVALID_CALL;

	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGISwapChain::GetFullscreenState", "DEBUG", MB_OK);
	return E_NOTIMPL;
}

STDMETHODIMP CDXGISwapChain::GetLastPresentCount(_Out_ UINT* pLastPresentCount) 
{
	if (!pLastPresentCount)
		return DXGI_ERROR_INVALID_CALL;

	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGISwapChain::GetLastPresentCount", "DEBUG", MB_OK);
	return E_NOTIMPL;
}

STDMETHODIMP CDXGISwapChain::Present(_In_ UINT SyncInterval, _In_ UINT Flags)
{
	if (m_desc.Windowed)
	{
		if (DwmIsCompositionEnabled)
		{
			BOOL haveDwm = FALSE;
			auto hr = DwmIsCompositionEnabled(&haveDwm);
			if (SUCCEEDED(hr) && haveDwm)
				return PresentToDWM(SyncInterval, Flags);
		}

		// assume we don't have DWM
		return PresentToGDI(SyncInterval, Flags);
	}

	// full screen presentation not supported!
	return DXGI_ERROR_UNSUPPORTED;
}

STDMETHODIMP CDXGISwapChain::ResizeBuffers(_In_ UINT BufferCount, _In_ UINT Width, _In_ UINT Height, _In_ DXGI_FORMAT NewFormat, _In_ UINT SwapChainFlags) 
{
	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGISwapChain::ResizeBuffers", "DEBUG", MB_OK);
	return E_NOTIMPL;
}

STDMETHODIMP CDXGISwapChain::ResizeTarget(_In_ const DXGI_MODE_DESC* pNewTargetParameters) 
{
	if (!pNewTargetParameters)
		return DXGI_ERROR_INVALID_CALL;

	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGISwapChain::ResizeTarget", "DEBUG", MB_OK);
	return E_NOTIMPL;
}

STDMETHODIMP CDXGISwapChain::SetFullscreenState(_In_ BOOL Fullscreen, _In_ IDXGIOutput* pTarget)
{
	if (!pTarget)
		return DXGI_ERROR_INVALID_CALL;

	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGISwapChain::SetFullscreenState", "DEBUG", MB_OK);
	return E_NOTIMPL;
}

#if DXGI_VERSION >= 2
// IDXGISwapChain1
STDMETHODIMP CDXGISwapChain::GetDesc1(_Out_ DXGI_SWAP_CHAIN_DESC1* pDesc)
{
	if (!pDesc)
		return DXGI_ERROR_INVALID_CALL;

	pDesc->Width = m_desc.BufferDesc.Width;
	pDesc->Height = m_desc.BufferDesc.Height;
	pDesc->Format = m_desc.BufferDesc.Format;
	pDesc->Stereo = m_desc.Stereo;
	pDesc->SampleDesc = m_desc.SampleDesc;
	pDesc->BufferUsage = m_desc.BufferUsage;
	pDesc->Scaling = m_desc.WindowedScaling;
	pDesc->SwapEffect = m_desc.SwapEffect;
	pDesc->AlphaMode = m_desc.AlphaMode;
	pDesc->Flags = m_desc.Flags;

	return S_OK;
}

STDMETHODIMP CDXGISwapChain::GetFullscreenDesc(_Out_ DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pDesc)
{
	if (!pDesc)
		return DXGI_ERROR_INVALID_CALL;

	pDesc->RefreshRate = m_desc.BufferDesc.RefreshRate;
	pDesc->ScanlineOrdering = m_desc.BufferDesc.ScanlineOrdering;
	pDesc->Scaling = m_desc.BufferDesc.Scaling;
	pDesc->Windowed = m_desc.Windowed;

	return S_OK;
}

STDMETHODIMP CDXGISwapChain::GetHwnd(_Out_ HWND* pHwnd)
{
	if (!pHwnd)
		return DXGI_ERROR_INVALID_CALL;

	*pHwnd = m_desc.OutputWindow;
	return S_OK;
}

STDMETHODIMP CDXGISwapChain::GetCoreWindow(_In_ REFIID refiid, _COM_Outptr_ void** ppUnk)
{
	if (!ppUnk)
		return DXGI_ERROR_INVALID_CALL;

	*ppUnk = nullptr;

	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGISwapChain::GetCoreWindow", "DEBUG", MB_OK);
	return E_NOTIMPL;
}

STDMETHODIMP CDXGISwapChain::Present1(_In_ UINT SyncInterval, _In_ UINT PresentFlags, _In_ const DXGI_PRESENT_PARAMETERS* pPresentParameters)
{
	if (!pPresentParameters)
		return DXGI_ERROR_INVALID_CALL;

	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGISwapChain::Present1", "DEBUG", MB_OK);
	return E_NOTIMPL;
}

STDMETHODIMP_(BOOL) CDXGISwapChain::IsTemporaryMonoSupported(void)
{
	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGISwapChain::IsTemporaryMonoSupported", "DEBUG", MB_OK);
	return FALSE;
}

STDMETHODIMP CDXGISwapChain::GetRestrictToOutput(_Out_ IDXGIOutput** ppRestrictToOutput)
{
	if (!ppRestrictToOutput)
		return DXGI_ERROR_INVALID_CALL;

	*ppRestrictToOutput = nullptr;

	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGISwapChain::GetRestrictToOutput", "DEBUG", MB_OK);
	return E_NOTIMPL;
}

STDMETHODIMP CDXGISwapChain::SetBackgroundColor(_In_ const DXGI_RGBA* pColor)
{
	if (!pColor)
		return DXGI_ERROR_INVALID_CALL;

	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGISwapChain::SetBackgroundColor", "DEBUG", MB_OK);
	return E_NOTIMPL;
}

STDMETHODIMP CDXGISwapChain::GetBackgroundColor(_Out_ DXGI_RGBA* pColor)
{
	if (!pColor)
		return DXGI_ERROR_INVALID_CALL;

	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGISwapChain::GetBackgroundColor", "DEBUG", MB_OK);
	return E_NOTIMPL;
}

STDMETHODIMP CDXGISwapChain::SetRotation(_In_ DXGI_MODE_ROTATION Rotation)
{
	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGISwapChain::SetRotation", "DEBUG", MB_OK);
	return E_NOTIMPL;
}

STDMETHODIMP CDXGISwapChain::GetRotation(_Out_ DXGI_MODE_ROTATION* pRotation)
{
	if (!pRotation)
		return DXGI_ERROR_INVALID_CALL;

	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGISwapChain::GetRotation", "DEBUG", MB_OK);
	return E_NOTIMPL;
}

#endif

STDMETHODIMP CDXGISwapChain::Initialize(_In_ IDXGIFactory* pFactory, _In_ IUnknown* pDevice, _In_ DXGI_SWAP_CHAIN_DESC* pDesc)
{
	SetParent(pFactory);

	auto hr = m_cDevice.Initialize(pDevice);
	if (FAILED(hr))
		return hr;

	hr = m_cDevice.GetAdapter(&m_pAdapter);
	if (FAILED(hr))
		return hr;

	hr = m_pAdapter->GetDesc(&m_adapterDesc);
	if (FAILED(hr))
		return hr;

	m_desc.BufferDesc = pDesc->BufferDesc;
	m_desc.SampleDesc = pDesc->SampleDesc;
	m_desc.BufferUsage = pDesc->BufferUsage;
	m_desc.BufferCount = pDesc->BufferCount;
	m_desc.OutputWindow = pDesc->OutputWindow;
	m_desc.Windowed = pDesc->Windowed;
	m_desc.SwapEffect = pDesc->SwapEffect;
	m_desc.Flags = pDesc->Flags;

#if DXGI_VERSION >= 2
	// TODO!
	m_desc.Stereo = FALSE;
	m_desc.WindowedScaling = DXGI_SCALING_NONE;
	m_desc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
#endif

	DXGI_SURFACE_DESC dsc;
	dsc.Width = m_desc.BufferDesc.Width;
	dsc.Height = m_desc.BufferDesc.Height;
	dsc.Format = m_desc.BufferDesc.Format;
	dsc.SampleDesc = m_desc.SampleDesc;

	IDXGIResource* pBB = nullptr;

	/*
	* Create back buffer
	*/
	hr = m_cDevice.CreateSurfaceInternal(&dsc, 1, 1, DXGI_RESOURCE_BIND_RENDER_TARGET | DXGI_RESOURCE_BIND_SHADER_RESOURCE, 0, &pBB);

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

	auto hr = DwmDxGetWindowSharedSurface(m_desc.OutputWindow, m_adapterDesc.AdapterLuid, m, 0, &fmt, &dxSurface, &updId);
	if (FAILED(hr))
		return hr;

	IDXGIResource* pDwmSurface;
	hr = m_cDevice.OpenSharedResource(dxSurface, __uuidof(pDwmSurface), &pDwmSurface);
	if (FAILED(hr))
	{
		DwmDxUpdateWindowSharedSurface(m_desc.OutputWindow, updId, 0, m, nullptr);
		return hr;
	}

	DXGI_PRESENT_SUBRESOURCES bltMap;
	DXGI_PRESENT_SUBRESOURCE test2[1];
	test2[0].SrcSubresource = 0;
	test2[0].DstSubresource = 0;
	bltMap.Count = 1;
	bltMap.SubRes = test2;

	// destination rect
	RECT windowRect;
	if (!GetWindowRect(m_desc.OutputWindow, &windowRect))
	{
		DwmDxUpdateWindowSharedSurface(m_desc.OutputWindow, updId, 0, m, nullptr);
		return DXGI_ERROR_NOT_CURRENTLY_AVAILABLE;
	}

	RECT clientRect;
	if (!GetClientRect(m_desc.OutputWindow, &clientRect))
	{
		DwmDxUpdateWindowSharedSurface(m_desc.OutputWindow, updId, 0, m, nullptr);
		return DXGI_ERROR_NOT_CURRENTLY_AVAILABLE;
	}

	POINT borders;
	borders.y = (windowRect.bottom - windowRect.top) - clientRect.bottom;
	borders.x = (windowRect.right - windowRect.left) - clientRect.right;

	// destination rect with border fix applied
	clientRect.top = borders.y;
	clientRect.bottom += borders.y;
	clientRect.left += borders.x;
	clientRect.right += borders.x;

	hr = m_cDevice.Blt(bb, nullptr, nullptr, 0, pDwmSurface, nullptr, &bltMap, 0, DXGI_DDI_MODE_ROTATION_IDENTITY);
	if (FAILED(hr))
	{
		DwmDxUpdateWindowSharedSurface(m_desc.OutputWindow, updId, 0, m, nullptr);

		pDwmSurface->Release();
		return hr;
	}

	hr = DwmDxUpdateWindowSharedSurface(m_desc.OutputWindow, updId, DWM_REDIRECTION_FLAG_SUPPORT_PRESENT_TO_GDI_SURFACE, m, &windowRect);
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
	auto& bb = m_vBuffers.at(0);

	D3DKMT_PRESENT context = { 0 };
	context.SrcRect.right = m_desc.BufferDesc.Width;
	context.SrcRect.bottom = m_desc.BufferDesc.Height;
	context.pSrcSubRects = &context.SrcRect;
	context.SubRectCnt = 1;
	context.hWindow = m_desc.OutputWindow;
	context.VidPnSourceId = -1;

	if (SyncInterval > 4)
		SyncInterval = 0;

	context.FlipInterval = (D3DDDI_FLIPINTERVAL_TYPE)SyncInterval;
	context.Flags.Blt = 1;
	context.Flags.SrcRectValid = 1;

	DXGI_DDI_PRESENT_FLAGS presentFlags = { 0 };
	presentFlags.Blt = 1;

	auto hr = m_cDevice.Present(bb, nullptr, &context, presentFlags, DXGI_DDI_FLIP_INTERVAL_IMMEDIATE);

	return hr;
}
