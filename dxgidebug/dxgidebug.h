#pragma once

class ATL_NO_VTABLE CDXGIDebug : 
	public IDXGIDebug,
	public DXGIObjRoot
{
public:
	BEGIN_COM_MAP(CDXGIDebug)
		COM_INTERFACE_ENTRY(IDXGIDebug)
	END_COM_MAP()

	STDMETHODIMP ReportLiveObjects(GUID apiid, DXGI_DEBUG_RLO_FLAGS flags) override;
};
