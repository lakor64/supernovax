/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     Keyed mutex
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#include "pch.h"
#include "dxgikeyedmutex.h"

STDMETHODIMP CDXGIKeyedMutex::AcquireSync(_In_ UINT64 Key, _In_ DWORD dwMilliseconds)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDXGIKeyedMutex::ReleaseSync(_In_ UINT64 Key)
{
	return E_NOTIMPL;
}