#pragma once

#include "dxgidevicesubobject.h"

class CDXGISwapChain : public CDXGIDeviceSubObject, IDXGISwapChain
{
public:
	virtual HRESULT WINAPI QueryInterface(_In_ REFIID id, _Inout_ void** ppObj) override;

	HRESULT WINAPI GetBuffer(_In_ UINT Buffer, _In_ REFIID riid, _Out_ void** ppSurface);
	HRESULT WINAPI GetContainingOutput(_Out_ IDXGIOutput** ppOutput);
	HRESULT WINAPI GetDesc(_Out_ DXGI_SWAP_CHAIN_DESC* pDesc);
	HRESULT WINAPI GetFrameStatistics(_Out_ DXGI_FRAME_STATISTICS* pStats);
	HRESULT WINAPI GetFullscreenState(_Out_opt_ BOOL* pFullscreen, _Out_opt_ IDXGIOutput** ppTarget);
	HRESULT WINAPI GetLastPresentCount(_Out_ UINT* pLastPresentCount);
	HRESULT WINAPI Present(_In_ UINT SyncInterval, _In_ UINT Flags);
	HRESULT WINAPI ResizeBuffers(_In_ UINT BufferCount, _In_ UINT Width, _In_ UINT Height, _In_ DXGI_FORMAT NewFormat, _In_ UINT SwapChainFlags);
	HRESULT WINAPI ResizeTarget(_In_ const DXGI_MODE_DESC* pNewTargetParameters);
	HRESULT WINAPI SetFullscreenState(_In_ BOOL Fullscreen, _In_ IDXGIOutput* pTarget);
};

// TODO: SwapChain1
