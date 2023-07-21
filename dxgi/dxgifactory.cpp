#include "pch.h"
#include "dxgifactory.h"

STDMETHODIMP CDXGIFactory::CreateSoftwareAdapter(_In_ HMODULE Module, _Out_ IDXGIAdapter** ppAdapter)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDXGIFactory::CreateSwapChain(_In_ IUnknown* pDevice, _In_ DXGI_SWAP_CHAIN_DESC* pDesc, _Out_ IDXGISwapChain** ppSwapChain)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDXGIFactory::EnumAdapters(_In_ UINT Adapter, _Out_ IDXGIAdapter** ppAdapter)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDXGIFactory::GetWindowAssociation(_Out_ HWND* pWindowHandle)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDXGIFactory::MakeWindowAssociation(_In_ HWND WindowHandle, _In_ UINT Flags)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDXGIFactory::EnumAdapters1(_In_ UINT Adapter, _Out_ IDXGIAdapter1** ppAdapter)
{
	return E_NOTIMPL;
}

STDMETHODIMP_(BOOL) CDXGIFactory::IsCurrent(void)
{
	return FALSE;
}

STDMETHODIMP CDXGIFactory::Initialize(void)
{
	return E_NOTIMPL;
}
