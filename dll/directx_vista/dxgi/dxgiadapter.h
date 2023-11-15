/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     GPU Adapter
 * COPYRIGHT:   Copyright 2023 Christian Rendina <pizzaiolo100@proton.me>
 */

#pragma once

#include "dxgiobject.h"

enum class DXGIAdapterModuleType
{
	Invalid,
	Hardware,
	Software,
	Warp
};

class ATL_NO_VTABLE CDXGIAdapter : 
	public DXGIObjRoot,
	public CDXGIObject<DXGIAdapterType>,
	public DXGIAdapterInternalType,
	public IDXGIAdapterUnknownInternal
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
#endif
		COM_INTERFACE_ENTRY_IID(IID_IDXGIAdapterUnknownInternal, IDXGIAdapterUnknownInternal)
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

	STDMETHODIMP CloseKernelHandle(_In_ D3DKMT_HANDLE* pHandle) override;

	
	/**
	* @brief Initializes the DXGI Adapter as a hardware adapter
	* @param[in] parent Parent factory
	*/
	STDMETHODIMP Initialize(_In_ IDXGIFactory* parent);

	/**
	* @brief Initializes the DXGI Adapter as a software adapter
	* @param[in] parent Parent factory
	* @param[in] hSoft Software module
	*/
	STDMETHODIMP Initialize(_In_ IDXGIFactory* parent, _In_ HMODULE hSoft);

	/**
	* @brief Adds an output to the adapter
	* @param e Output to add
	*/
	STDMETHODIMP_(void) AddOutput(const DXGIEnumInfo& e);

private:

	/**
	* @brief Attempts to load D3DKMT API
	* @return S_OK in case of success, or DXGI_ERROR_UNSUPPORTED in case a required API is not supported
	*/
	STDMETHODIMP LoadD3DKMTApi();

	/**
	* @brief Sets up the adapter description
	*/
	STDMETHODIMP_(void) GetAdapterDesc();

	/**
	* @brief Query the supported adapter version
	* @param uv version to query
	* @return S_OK in case it's supported ,or DXGI_ERROR*
	*/
	STDMETHODIMP QueryUMDVersion(KMTUMDVERSION uv);

	/**
	* @brief Changes adapter info for DirectX9-only adapters
	*/
	STDMETHODIMP_(void) ChangeDataToSoftAdapter();

	/// Module DLL
	HMODULE m_hDll;

	/// Check if the adapter was enumated
	bool m_bValid;

	/// One generic handle of the specified GPU
	D3DKMT_HANDLE m_hHandle;

	// Exports from D3DKMT
	D3DKMTQueryAdapterInfo_ D3DKMTQueryAdapterInfo;
	// ----------

	/// Adapter desc type
	DXGIAdapterDescType m_desc;

	/// Outputs
	std::vector <DXGIOutputInfo> m_vOutputs;

	/// Module type
	DXGIAdapterModuleType m_modType;
};
