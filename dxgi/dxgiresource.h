#pragma once

#include "dxgidevicesubobject.h"

class CDXGIResource : public CDXGIDeviceSubObject, public IDXGIResource
{
public:
	virtual HRESULT WINAPI QueryInterface(_In_ REFIID id, _Inout_ void** ppObj) override;

	HRESULT WINAPI GetEvictionPriority(_Out_ UINT* pEvictionPriority);
	HRESULT WINAPI GetSharedHandle(_Out_ HANDLE* pSharedHandle);
	HRESULT WINAPI GetUsage(_Out_ DXGI_USAGE* pUsage);
	HRESULT WINAPI SetEvictionPriority(_In_ UINT EvictionPriority);
};

// TODO: Resource1
