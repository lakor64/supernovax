/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     GPU Adapter
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#pragma once

#include "dxgiobject.h"

class ATL_NO_VTABLE CDXGIAdapter : 
	public DXGIObjRoot,
	public CDXGIObject<DXGIAdapterType>,
	public DXGIAdapterInternalType
{
public:
	BEGIN_COM_MAP(CDXGIAdapter)
#if DXGI_VERSION >= 6
		COM_INTERFACE_ENTRY_IID(IID_IDXGIAdapter4, IDXGIAdapter4)
#endif
#if DXGI_VERSION >= 4
		COM_INTERFACE_ENTRY_IID(IID_IDXGIAdapter3, IDXGIAdapter3)
#endif
#if DXGI_VERSION >= 2
		COM_INTERFACE_ENTRY_IID(IID_IDXGIAdapter2, IDXGIAdapter2)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIAdapterInternal2, IDXGIAdapterInternal2)
#endif
#if DXGI_VERSION >= 1
		COM_INTERFACE_ENTRY_IID(IID_IDXGIAdapter1, IDXGIAdapter1)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIAdapterInternal1, IDXGIAdapterInternal1)
#endif
		COM_INTERFACE_ENTRY_IID(IID_IDXGIAdapter, IDXGIAdapter)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIAdapterInternal, IDXGIAdapterInternal)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIObject, IDXGIObject)
	END_COM_MAP()

	CDXGIAdapter();
	~CDXGIAdapter();

	// IDXGIAdapter
	STDMETHODIMP CheckInterfaceSupport(_In_ REFGUID InterfaceName, _Out_ LARGE_INTEGER* pUMDVersion) override;
	STDMETHODIMP EnumOutputs(_In_ UINT Output, _COM_Outptr_ IDXGIOutput** ppOutput) override;
	STDMETHODIMP GetDesc(_Out_ DXGI_ADAPTER_DESC* pDesc) override;
#if DXGI_VERSION >= 1
	// IDXGIAdapter1
	STDMETHODIMP GetDesc1(_Out_ DXGI_ADAPTER_DESC1* pDesc) override;
#endif
#if DXGI_VERSION >= 2
	// IDXGIAdapter2
	STDMETHODIMP GetDesc2(_Out_ DXGI_ADAPTER_DESC2* pDesc) override;
#endif
	// IDXGIAdapterInternal
	STDMETHODIMP GetUMDDeviceSize(_In_ UINT unk, _In_ UINT unk2, _In_ UINT unk3) override;
#if DXGI_VERSION >= 1
	// IDXGIAdapterInternal1
#endif
#if DXGI_VERSION >= 2
	// IDXGIAdapterInternal2
	STDMETHODIMP LoadUMD(_In_ KMTUMDVERSION Version, _Out_ HINSTANCE* hUMD) override;
	STDMETHODIMP InstanceThunks(_In_ DXGI_THUNKS_VERSION Version, _Out_ D3DKMT_HANDLE* pAdapter, _In_ UINT ThunkSize, _Out_opt_ void* Thunks) override;
	STDMETHODIMP RetireUsage(_In_ D3DKMT_HANDLE Adapter) override;
	STDMETHODIMP SetAdapterCapabilities(_In_ DXGI_ADAPTER_CAPABILITIES* cap) override;
	STDMETHODIMP GetAdapterCapabilities(_Inout_ DXGI_ADAPTER_CAPABILITIES* cap) override;
	STDMETHODIMP_(BOOL) IsWARP(void) override;
	STDMETHODIMP_(D3DDDI_VIDEO_PRESENT_SOURCE_ID) GetPrimaryVidPnSourceId(void) override;
	STDMETHODIMP_(UINT) WddmVersion(void) override;
	STDMETHODIMP_(BOOL) MismatchedVendorLda(void) override;
	STDMETHODIMP_(BOOL) IsLda(void) override;
#endif
	// custom
	STDMETHODIMP Initialize(IDXGIFactory* parent, const DXGIAdapterDesc& desc);

private:
	STDMETHODIMP_(void) GetAdapterDesc();

	/** adapter descriptor */
	DXGIAdapterDesc m_desc;

};
