/*
 * PROJECT:     ReactX Graphics Infrastructure Debug layer
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:   	Debug layer
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */
 
#pragma once

class ATL_NO_VTABLE CDXGIDebug : 
	public IDXGIDebug,
	public DXGIObjRoot
{
public:
	BEGIN_COM_MAP(CDXGIDebug)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIDebug, IDXGIDebug)
	END_COM_MAP()

	STDMETHODIMP ReportLiveObjects(GUID apiid, DXGI_DEBUG_RLO_FLAGS flags) override;
};
