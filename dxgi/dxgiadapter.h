#pragma once

#include "dxgiobject.h"

class CDXGIAdapter : public CDXGIObject, public IDXGIAdapter
{
public:
	// IUnknown
	virtual HRESULT WINAPI QueryInterface(_In_ REFIID id, _Inout_ void** ppObj) override;
	// IDXGIObject
	virtual HRESULT WINAPI GetParent(_In_ REFIID Id, _Out_ void** pParent) override;
	// IDXGIAdapter
	HRESULT WINAPI CheckInterfaceSupport(_In_ REFGUID InterfaceName, _Out_ LARGE_INTEGER* pUMDVersion);
	HRESULT WINAPI EnumOutputs(_In_ UINT Output, _Out_ IDXGIOutput** ppOutput);
	HRESULT WINAPI GetDesc(_Out_ DXGI_ADAPTER_DESC* pDesc);
};

// TODO: Adapter1
// TODO: Adapter2
