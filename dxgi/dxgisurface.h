#pragma once

#include "dxgidevicesubobject.h"

class CDXGISurface : public CDXGIDeviceSubObject, IDXGISurface
{
public:
	virtual HRESULT WINAPI QueryInterface(_In_ REFIID id, _Inout_ void** ppObj) override;

	HRESULT WINAPI GetDesc(_Out_ DXGI_SURFACE_DESC* pDesc);
	HRESULT WINAPI Map(_Out_ DXGI_MAPPED_RECT* pLockedRect, _In_ UINT MapFlags);
	HRESULT WINAPI Unmap(void);
};

// TODO: Surface1
// TODO: Surface2
