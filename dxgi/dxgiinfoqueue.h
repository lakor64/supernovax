#pragma once

class CDXGIInfoQueue : public IDXGIInfoQueue
{
public:
	virtual HRESULT WINAPI QueryInterface(_In_ REFIID id, _Inout_ void** ppObj) override;

	// TODO
};
