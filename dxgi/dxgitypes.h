/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     DXGI types
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#pragma once

#include <vector>

#define DXGIOutputDescType DXGI_OUTPUT_DESC
#define DXGIAdapterDescType DXGI_ADAPTER_DESC
#define DXGISwapChainDescType DXGI_SWAP_CHAIN_DESC
#define DXGIFactoryType IDXGIFactory
#define DXGIAdapterType IDXGIAdapter
#define DXGIOutputType IDXGIOutput
#define DXGIDeviceType IDXGIDevice
#define DXGISurfaceType IDXGISurface
#define DXGIResourceType IDXGIResource
#define DXGISwapChainType IDXGISwapChain

#if DXGI_VERSION >= 1
#undef  DXGIAdapterDescType
#define DXGIAdapterDescType DXGI_ADAPTER_DESC1
#undef  DXGIFactoryType
#define DXGIFactoryType IDXGIFactory1
#undef  DXGIAdapterType
#define DXGIAdapterType IDXGIAdapter1
#undef  DXGIDeviceType
#define DXGIDeviceType IDXGIDevice1
#undef  DXGISurfaceType
#define DXGISurfaceType IDXGISurface1
#endif

#if DXGI_VERSION >= 2
#undef  DXGIAdapterDescType
#define DXGIAdapterDescType DXGI_ADAPTER_DESC2
#undef  DXGISwapChainDescType
#define DXGISwapChainDescType DXGI_SWAP_CHAIN_DESC1
#undef  DXGIFactoryType
#define DXGIFactoryType IDXGIFactory2
#undef  DXGIAdapterType
#define DXGIAdapterType IDXGIAdapter2
#undef  DXGIOutputType
#define DXGIOutputType IDXGIOutput1
#undef  DXGIDeviceType
#define DXGIDeviceType IDXGIDevice2
#undef  DXGISurfaceType
#define DXGISurfaceType IDXGISurface2
#undef  DXGIResourceType
#define DXGIResourceType IDXGIResource1
#undef  DXGISwapChainType
#define DXGISwapChainType IDXGISwapChain1
#endif

#if DXGI_VERSION >= 3
#undef  DXGIFactoryType
#define DXGIFactoryType IDXGIFactory3
#undef  DXGIOutputType
#define DXGIOutputType IDXGIOutput3
#undef  DXGIDeviceType
#define DXGIDeviceType IDXGIDevice3
#undef  DXGISwapChainType
#define DXGISwapChainType IDXGISwapChain2
#endif

#if DXGI_VERSION >= 4
#undef  DXGIFactoryType
#define DXGIFactoryType IDXGIFactory4
#undef  DXGIOutputType
#define DXGIOutputType IDXGIOutput4
#undef  DXGIAdapterType
#define DXGIAdapterType IDXGIAdapter3
#undef  DXGIDeviceType
#define DXGIDeviceType IDXGIDevice3
#undef  DXGISwapChainType
#define DXGISwapChainType IDXGISwapChain3
#endif

#if DXGI_VERSION >= 5
#undef  DXGIFactoryType
#define DXGIFactoryType IDXGIFactory5
#undef  DXGIDeviceType
#define DXGIDeviceType IDXGIDevice4
#undef  DXGIOutputType
#define DXGIOutputType IDXGIOutput5
#undef  DXGISwapChainType
#define DXGISwapChainType IDXGISwapChain4
#endif

#if DXGI_VERSION >= 6
#undef  DXGIAdapterDescType
#define DXGIAdapterDescType DXGI_ADAPTER_DESC3
#undef  DXGIAdapterType
#define DXGIAdapterType IDXGIAdapter4
#undef  DXGIFactoryType
#define DXGIFactoryType IDXGIFactory7
#undef  DXGIOutputType
#define DXGIOutputType IDXGIOutput6
#undef  DXGIOutputDescType
#define DXGIOutputDescType DXGI_OUTPUT_DESC1
#endif

struct DXGIOutputDescBasic
{
	/** device name */
	WCHAR DeviceName[32];
	/** associated adapter handle */
	D3DKMT_HANDLE Handle;
	/** display handle */
	D3DDDI_VIDEO_PRESENT_SOURCE_ID VidPn;
};

struct DXGIOutputDesc : public DXGIOutputDescType
{
	/** associated adapter handle */
	D3DKMT_HANDLE Handle;
	/** display handle */
	D3DDDI_VIDEO_PRESENT_SOURCE_ID VidPn;
	/** has been enumerated */
	bool IsValid;
};

/** Structure that holds adapter info */
struct DXGIAdapterDesc : public DXGIAdapterDescType
{
	/** kernel handle */
	D3DKMT_HANDLE Handle;

	/** has been enumerated */
	bool IsValid;

	/** outputs */
	std::vector<DXGIOutputDescBasic> Outputs;
};
