/*
 * PROJECT:     ReactX Graphics Infrastructure Debug layer
 * LICENSE:     LGPL-2.0-or-later (https://spdx.org/licenses/LGPL-2.0-or-later.html)
 * PURPOSE:   	Debug layer
 * COPYRIGHT:   Copyright 2023 Christian Rendina <pizzaiolo100@proton.me>
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
