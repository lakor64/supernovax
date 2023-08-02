/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     Device swapchain
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#include "pch.h"
#include "dxgiswapchain.h"

 // IDXGISwapChain
STDMETHODIMP CDXGISwapChain::GetBuffer(_In_ UINT Buffer, _In_ REFIID riid, _Out_ void** ppSurface) 
{
	if (!ppSurface)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
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

