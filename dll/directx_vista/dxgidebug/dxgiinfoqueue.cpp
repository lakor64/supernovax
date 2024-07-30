/*
 * PROJECT:     ReactX Graphics Infrastructure Debug layer
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     Info queue
 * COPYRIGHT:   Copyright 2023 Christian Rendina <pizzaiolo100@proton.me>
 */
 
#include "pch.h"
#include "dxgiinfoqueue.h"

STDMETHODIMP CDXGIInfoQueue::AddApplicationMessage(_In_ DXGI_INFO_QUEUE_MESSAGE_SEVERITY Severity, _In_ LPCSTR pDescription)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDXGIInfoQueue::AddMessage(_In_ DXGI_DEBUG_ID Producer, _In_ DXGI_INFO_QUEUE_MESSAGE_CATEGORY Category, _In_ DXGI_INFO_QUEUE_MESSAGE_SEVERITY Severity, _In_ DXGI_INFO_QUEUE_MESSAGE_ID ID, _In_ LPCSTR pDescription)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDXGIInfoQueue::AddRetrievalFilterEntries(_In_ DXGI_DEBUG_ID Producer, _In_ DXGI_INFO_QUEUE_FILTER* pFilter)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDXGIInfoQueue::AddStorageFilterEntries(_In_ DXGI_DEBUG_ID Producer, _In_ DXGI_INFO_QUEUE_FILTER* pFilter)
{
	return E_NOTIMPL;
}

STDMETHODIMP_(void) CDXGIInfoQueue::CDXGIInfoQueue::ClearRetrievalFilter(_In_ DXGI_DEBUG_ID Producer)
{
}

STDMETHODIMP_(void) CDXGIInfoQueue::CDXGIInfoQueue::ClearStorageFilter(_In_ DXGI_DEBUG_ID Producer)
{
}

STDMETHODIMP_(BOOL) CDXGIInfoQueue::CDXGIInfoQueue::GetBreakOnCategory(_In_ DXGI_DEBUG_ID Producer, _In_ DXGI_INFO_QUEUE_MESSAGE_CATEGORY Category)
{
	return FALSE;
}

STDMETHODIMP_(BOOL) CDXGIInfoQueue::CDXGIInfoQueue::GetBreakOnID(_In_ DXGI_DEBUG_ID Producer, _In_ DXGI_INFO_QUEUE_MESSAGE_ID ID)
{
	return FALSE;
}

STDMETHODIMP_(BOOL) CDXGIInfoQueue::CDXGIInfoQueue::GetBreakOnSeverity(_In_ DXGI_DEBUG_ID Producer, _In_ DXGI_INFO_QUEUE_MESSAGE_SEVERITY Severity)
{
	return FALSE;
}

STDMETHODIMP CDXGIInfoQueue::GetMessage(_In_ DXGI_DEBUG_ID Producer, _In_ UINT64 MessageIndex, _Out_opt_ DXGI_INFO_QUEUE_MESSAGE* pMessage, _In_opt_ SIZE_T* pMessageByteLength)
{
	return E_NOTIMPL;
}

STDMETHODIMP_(UINT64) CDXGIInfoQueue::GetMessageCountLimit(_In_ DXGI_DEBUG_ID Producer)
{
	return 0;
}

STDMETHODIMP_(BOOL) CDXGIInfoQueue::GetMuteDebugOutput(_In_ DXGI_DEBUG_ID Producer)
{
	return FALSE;
}

STDMETHODIMP_(UINT64) CDXGIInfoQueue::GetNumMessagesAllowedByStorageFilter(_In_ DXGI_DEBUG_ID Producer)
{
	return 0;
}

STDMETHODIMP_(UINT64) CDXGIInfoQueue::GetNumMessagesDeniedByStorageFilter(_In_ DXGI_DEBUG_ID Producer)
{
	return 0;
}

STDMETHODIMP_(UINT64) CDXGIInfoQueue::GetNumStoredMessages(_In_ DXGI_DEBUG_ID Producer)
{
	return 0;
}

STDMETHODIMP_(UINT64) CDXGIInfoQueue::GetNumStoredMessagesAllowedByRetrievalFilters(_In_ DXGI_DEBUG_ID Producer)
{
	return 0;
}

STDMETHODIMP CDXGIInfoQueue::GetRetrievalFilter(_In_ DXGI_DEBUG_ID Producer, _Out_opt_ DXGI_INFO_QUEUE_FILTER* pFilter, _In_opt_ SIZE_T* pFilterByteLength)
{
	return E_NOTIMPL;
}

STDMETHODIMP_(UINT) CDXGIInfoQueue::GetRetrievalFilterStackSize(_In_ DXGI_DEBUG_ID Producer)
{
	return 0;
}

STDMETHODIMP CDXGIInfoQueue::GetStorageFilter(_In_ DXGI_DEBUG_ID Producer, _Out_opt_ DXGI_INFO_QUEUE_FILTER* pFilter, _In_opt_ SIZE_T* pFilterByteLength)
{
	return E_NOTIMPL;
}

STDMETHODIMP_(UINT) CDXGIInfoQueue::GetStorageFilterStackSize(_In_ DXGI_DEBUG_ID Producer)
{
	return 0;
}

STDMETHODIMP_(void) CDXGIInfoQueue::PopRetrievalFilter(_In_ DXGI_DEBUG_ID Producer)
{

}

STDMETHODIMP_(void) CDXGIInfoQueue::PopStorageFilter(_In_ DXGI_DEBUG_ID Producer)
{

}

STDMETHODIMP CDXGIInfoQueue::PushCopyOfRetrievalFilter(_In_ DXGI_DEBUG_ID Producer)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDXGIInfoQueue::PushCopyOfStorageFilter(_In_ DXGI_DEBUG_ID Producer)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDXGIInfoQueue::PushDenyAllRetrievalFilter(_In_ DXGI_DEBUG_ID Producer)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDXGIInfoQueue::PushDenyAllStorageFilter(_In_ DXGI_DEBUG_ID Producer)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDXGIInfoQueue::PushEmptyRetrievalFilter(_In_ DXGI_DEBUG_ID Producer)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDXGIInfoQueue::PushEmptyStorageFilter(_In_ DXGI_DEBUG_ID Producer)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDXGIInfoQueue::PushRetrievalFilter(_In_ DXGI_DEBUG_ID Producer, _In_ DXGI_INFO_QUEUE_FILTER* pFilter)
{
	return E_NOTIMPL;
}
STDMETHODIMP CDXGIInfoQueue::PushStorageFilter(_In_ DXGI_DEBUG_ID Producer, _In_ DXGI_INFO_QUEUE_FILTER* pFilter)
{
	return E_NOTIMPL;
}
STDMETHODIMP CDXGIInfoQueue::SetBreakOnCategory(_In_ DXGI_DEBUG_ID Producer, _In_ DXGI_INFO_QUEUE_MESSAGE_CATEGORY Category, _In_ BOOL bEnable)
{
	return E_NOTIMPL;
}
STDMETHODIMP CDXGIInfoQueue::SetBreakOnID(_In_ DXGI_DEBUG_ID SetBreakOnID, _In_ DXGI_INFO_QUEUE_MESSAGE_ID ID, _In_ BOOL bEnable)
{
	return E_NOTIMPL;
}
STDMETHODIMP CDXGIInfoQueue::SetBreakOnSeverity(_In_ DXGI_DEBUG_ID Producer, _In_ DXGI_INFO_QUEUE_MESSAGE_SEVERITY Severity, _In_ BOOL bEnable)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDXGIInfoQueue::SetMessageCountLimit(_In_ DXGI_DEBUG_ID Producer, _In_ UINT64 MessageCountLimit)
{
	return E_NOTIMPL;
}

STDMETHODIMP_(void) CDXGIInfoQueue::SetMuteDebugOutput(_In_ DXGI_DEBUG_ID Producer, _In_ BOOL bMute)
{
	
}
