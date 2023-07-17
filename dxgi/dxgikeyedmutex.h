#pragma once

#include "dxgidevicesubobject.h"

class CDXGIKeyedMutex : public CDXGIDeviceSubObject, IDXGIKeyedMutex
{
public:
	virtual HRESULT WINAPI QueryInterface(_In_ REFIID id, _Inout_ void** ppObj) override;

	HRESULT WINAPI AcquireSync(_In_ UINT64 Key, _In_ DWORD dwMilliseconds);
	HRESULT WINAPI ReleaseSync(_In_ UINT64 Key);
};
