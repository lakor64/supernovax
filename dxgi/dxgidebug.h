#pragma once

class CDXGIDebug : public IDXGIDebug
{
public:
	virtual HRESULT WINAPI QueryInterface(_In_ REFIID id, _Inout_ void** ppObj) override;

	HRESULT ReportLiveObjects(GUID apiid, DXGI_DEBUG_RLO_FLAGS flags);
};