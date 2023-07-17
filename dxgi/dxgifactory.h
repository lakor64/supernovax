#pragma once

#include "dxgiobject.h"

class CDXGIFactory : public IDXGIFactory, public CDXGIObject
{
public:
	// IUnknown
	virtual HRESULT WINAPI QueryInterface(_In_ REFIID id, _Inout_ void** ppObj);

	// IDXGIFactory
	HRESULT WINAPI CreateSoftwareAdapter(_In_ HMODULE Module, _Out_ IDXGIAdapter** ppAdapter);
	HRESULT WINAPI CreateSwapChain(_In_ const IUnknown* pDevice, _In_ const DXGI_SWAP_CHAIN_DESC* pDesc, _Out_ IDXGISwapChain** ppSwapChain);
	HRESULT WINAPI EnumAdapters(_In_ UINT Adapter, _Out_ IDXGIAdapter** ppAdapter);
	HRESULT WINAPI GetWindowAssocation(_Out_ HWND* pWindowHandle);
	HRESULT WINAPI MakeWindowAssociation(_In_ HWND WindowHandle, _In_ UINT Flags);
};

