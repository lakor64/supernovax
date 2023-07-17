#pragma once

class CDXGIDeviceSubObject : public IDXGIDeviceSubObject
{
public:
	virtual HRESULT WINAPI QueryInterface(_In_ REFIID id, _Inout_ void** ppObj) override;

	HRESULT WINAPI GetDevice(_In_ REFIID riid, _Out_ void** ppDevice);
};

