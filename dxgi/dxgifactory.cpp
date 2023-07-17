#include "pch.h"
#include "dxgifactory.h"

// IUnknown

HRESULT WINAPI CDXGIFactory::QueryInterface(_In_ REFIID id, _Inout_ void** ppObj)
{
	if (!IsEqualIID(id, IID_IDXGIFactory) && !IsEqualIID(id, IID_IDXGIObject) && !IsEqualIID(id, IID_IUnknown))
	{
		*ppObj = NULL;
		return E_NOINTERFACE;
	}

	AddRef();
	*ppObj = this;
	return S_OK;
}

// IDXGIFactory
HRESULT WINAPI CDXGIFactory::CreateSoftwareAdapter(_In_ HMODULE Module, _Out_ IDXGIAdapter** ppAdapter)
{

}

HRESULT WINAPI CDXGIFactory::CreateSwapChain(_In_ const IUnknown* pDevice, _In_ const DXGI_SWAP_CHAIN_DESC* pDesc, _Out_ IDXGISwapChain** ppSwapChain)
{

}

HRESULT WINAPI CDXGIFactory::EnumAdapters(_In_ UINT Adapter, _Out_ IDXGIAdapter** ppAdapter)
{

}

HRESULT WINAPI CDXGIFactory::GetWindowAssocation(_Out_ HWND* pWindowHandle)
{

}

HRESULT WINAPI CDXGIFactory::MakeWindowAssociation(_In_ HWND WindowHandle, _In_ UINT Flags)
{

}
