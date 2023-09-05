/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     Device swapchain
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#pragma once

#include "dxgidevicesubobject.h"
#include "deviceptr.h"
#include "dxgiusecounted.h"

struct DXGI_SWAP_CHAIN_DESC_INTERNAL : DXGI_SWAP_CHAIN_DESC
{
#if DXGI_VERSION >= 2
	BOOL Stereo;
	DXGI_ALPHA_MODE AlphaMode;
	DXGI_SCALING WindowedScaling;
#endif
};

class ATL_NO_VTABLE CDXGISwapChain :
	public DXGIObjRoot,
	public CDXGIDeviceSubObject<DXGISwapChainType>,
#if DXGI_VERSION >= 3
	public IDXGISwapChainMedia,
	public IDXGIDecodeSwapChain,
#endif
	public CDXGIUseCounted
{
public:
	BEGIN_COM_MAP(CDXGISwapChain)
#if DXGI_VERSION >= 5
		COM_INTERFACE_ENTRY_IID(IID_IDXGISwapChain4, IDXGISwapChain4)
#endif
#if DXGI_VERSION >= 4
		COM_INTERFACE_ENTRY_IID(IID_IDXGISwapChain3, IDXGISwapChain3)
#endif
#if DXGI_VERSION >= 3
		COM_INTERFACE_ENTRY_IID(IID_IDXGISwapChain2, IDXGISwapChain2)
		COM_INTERFACE_ENTRY_IID(IID_IDXGISwapChainMedia, IDXGISwapChainMedia)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIDecodeSwapChain, IDXGIDecodeSwapChain)
#endif
#if DXGI_VERSION >= 2
		COM_INTERFACE_ENTRY_IID(IID_IDXGISwapChain1, IDXGISwapChain1)
		COM_INTERFACE_ENTRY_IID(IID_IUseCounted2, IUseCounted2)
#endif
		COM_INTERFACE_ENTRY_IID(IID_IUseCounted, IUseCounted)
		COM_INTERFACE_ENTRY_IID(IID_IDXGISwapChain, IDXGISwapChain)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIDeviceSubObject, IDXGIDeviceSubObject)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIObject, IDXGIObject)
	END_COM_MAP()

	CDXGISwapChain();
	~CDXGISwapChain();

	// IDXGISwapChain
	STDMETHODIMP GetBuffer(_In_ UINT Buffer, _In_ REFIID riid, _Out_ void** ppSurface) override;
	STDMETHODIMP GetContainingOutput(_COM_Outptr_ IDXGIOutput** ppOutput) override;
	STDMETHODIMP GetDesc(_Out_ DXGI_SWAP_CHAIN_DESC* pDesc) override;
	STDMETHODIMP GetFrameStatistics(_Out_ DXGI_FRAME_STATISTICS* pStats) override;
	STDMETHODIMP GetFullscreenState(_Out_opt_ BOOL* pFullscreen, _COM_Outptr_ IDXGIOutput** ppTarget) override;
	STDMETHODIMP GetLastPresentCount(_Out_ UINT* pLastPresentCount) override;
	STDMETHODIMP Present(_In_ UINT SyncInterval, _In_ UINT Flags) override;
	STDMETHODIMP ResizeBuffers(_In_ UINT BufferCount, _In_ UINT Width, _In_ UINT Height, _In_ DXGI_FORMAT NewFormat, _In_ UINT SwapChainFlags) override;
	STDMETHODIMP ResizeTarget(_In_ const DXGI_MODE_DESC* pNewTargetParameters) override;
	STDMETHODIMP SetFullscreenState(_In_ BOOL Fullscreen, _In_ IDXGIOutput* pTarget) override;


#if DXGI_VERSION >= 2
	// IDXGISwapChain1
    STDMETHODIMP GetDesc1(_Out_ DXGI_SWAP_CHAIN_DESC1* pDesc) override;
    STDMETHODIMP GetFullscreenDesc( _Out_ DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pDesc) override;
    STDMETHODIMP GetHwnd(_Out_ HWND* pHwnd) override;
    STDMETHODIMP GetCoreWindow(_In_ REFIID refiid, _COM_Outptr_ void** ppUnk) override;
    STDMETHODIMP Present1(_In_ UINT SyncInterval, _In_ UINT PresentFlags, _In_ const DXGI_PRESENT_PARAMETERS* pPresentParameters) override;
	STDMETHODIMP_(BOOL) IsTemporaryMonoSupported(void) override;
    STDMETHODIMP GetRestrictToOutput(_Out_ IDXGIOutput** ppRestrictToOutput) override;
    STDMETHODIMP SetBackgroundColor(_In_ const DXGI_RGBA* pColor) override;
    STDMETHODIMP GetBackgroundColor(_Out_ DXGI_RGBA* pColor) override;
    STDMETHODIMP SetRotation(_In_ DXGI_MODE_ROTATION Rotation) override;
    STDMETHODIMP GetRotation(_Out_ DXGI_MODE_ROTATION* pRotation) override;
#endif

	/*!
	* Initializes the swapchain
	* @param pFactory Factory pointer
	* @param pDevice D3D device
	* @param pDesc Swapchain desc
	* @return HResult
	*/
	STDMETHODIMP Initialize(_In_ IDXGIFactory* pFactory, _In_ IUnknown* pDevice, _In_ DXGI_SWAP_CHAIN_DESC* pDesc);

private:

	/*!
	* Present the current screen to DWM
	* @param SyncInterval Syncronization interval
	* @param Flags Present flags
	*/
	STDMETHODIMP PresentToDWM(_In_ UINT SyncInterval, _In_ UINT Flags);

	/*!
	* Present the current screen to GDI
	* @param SyncInterval Syncronization interval
	* @param Flags Present flags
	* @note Selected when DWM is disabled
	*/
	STDMETHODIMP PresentToGDI(_In_ UINT SyncInterval, _In_ UINT Flags);

	/* Associated adapter */
	IDXGIAdapter* m_pAdapter;

	/* Associated adapter desc */
	DXGI_ADAPTER_DESC m_adapterDesc;

	/* Swapchain desc */
	DXGI_SWAP_CHAIN_DESC_INTERNAL m_desc;

	/* Swapchain buffers */
	std::vector<IDXGIResource*> m_vBuffers;

	/* Device pointer */
	CDevicePtr m_cDevice;
};
