/*
 * PROJECT:     SupernovaX Graphics Infrastructure
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     Keyed mutex
 * COPYRIGHT:   Copyright 2023 Christian Rendina <pizzaiolo100@proton.me>
 */

#include "dxgishared.h"
#include "dxgikeyedmutex.h"

STDMETHODIMP CDXGIKeyedMutex::AcquireSync(_In_ UINT64 Key, _In_ DWORD dwMilliseconds)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDXGIKeyedMutex::ReleaseSync(_In_ UINT64 Key)
{
	return E_NOTIMPL;
}
