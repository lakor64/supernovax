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

	CDXGIObject::AddRef();
	*ppObj = this;
	return S_OK;
}

// IDXGIObject
HRESULT WINAPI CDXGIFactory::GetParent(_In_ REFIID Id, _Out_ void** pParent)
{
	return E_NOINTERFACE;
}

// IDXGIFactory
HRESULT WINAPI CDXGIFactory::CreateSoftwareAdapter(_In_ HMODULE Module, _Out_ IDXGIAdapter** ppAdapter)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CDXGIFactory::CreateSwapChain(_In_ const IUnknown* pDevice, _In_ const DXGI_SWAP_CHAIN_DESC* pDesc, _Out_ IDXGISwapChain** ppSwapChain)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CDXGIFactory::EnumAdapters(_In_ UINT Adapter, _Out_ IDXGIAdapter** ppAdapter)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CDXGIFactory::GetWindowAssocation(_Out_ HWND* pWindowHandle)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CDXGIFactory::MakeWindowAssociation(_In_ HWND WindowHandle, _In_ UINT Flags)
{
	return E_NOTIMPL;
}
