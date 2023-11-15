/*
 * PROJECT:     ReactX Graphics Infrastructure Debug layer
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     Info queue
 * COPYRIGHT:   Copyright 2023 Christian Rendina <pizzaiolo100@proton.me>
 */
 
#pragma once

class ATL_NO_VTABLE CDXGIInfoQueue :
	public DXGIObjRoot,
	public IDXGIInfoQueue
{
public:
	BEGIN_COM_MAP(CDXGIInfoQueue)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIInfoQueue, IDXGIInfoQueue)
	END_COM_MAP()

	// IDXGIInfoQueue
	STDMETHODIMP AddApplicationMessage(_In_ DXGI_INFO_QUEUE_MESSAGE_SEVERITY Severity, _In_ LPCSTR pDescription) override;
	STDMETHODIMP AddMessage(_In_ DXGI_DEBUG_ID Producer, _In_ DXGI_INFO_QUEUE_MESSAGE_CATEGORY Category, _In_ DXGI_INFO_QUEUE_MESSAGE_SEVERITY Severity, _In_ DXGI_INFO_QUEUE_MESSAGE_ID ID, _In_ LPCSTR pDescription) override;
	STDMETHODIMP AddRetrievalFilterEntries(_In_ DXGI_DEBUG_ID Producer, _In_ DXGI_INFO_QUEUE_FILTER* pFilter) override;
	STDMETHODIMP AddStorageFilterEntries(_In_ DXGI_DEBUG_ID Producer, _In_ DXGI_INFO_QUEUE_FILTER* pFilter) override;
	STDMETHODIMP_(void) ClearRetrievalFilter(_In_ DXGI_DEBUG_ID Producer) override;
	STDMETHODIMP_(void) ClearStorageFilter(_In_ DXGI_DEBUG_ID Producer) override;
	STDMETHODIMP_(BOOL) GetBreakOnCategory(_In_ DXGI_DEBUG_ID Producer, _In_ DXGI_INFO_QUEUE_MESSAGE_CATEGORY Category) override;
	STDMETHODIMP_(BOOL) GetBreakOnID(_In_ DXGI_DEBUG_ID Producer, _In_ DXGI_INFO_QUEUE_MESSAGE_ID ID) override;
	STDMETHODIMP_(BOOL) GetBreakOnSeverity(_In_ DXGI_DEBUG_ID Producer, _In_ DXGI_INFO_QUEUE_MESSAGE_SEVERITY Severity) override;
	STDMETHODIMP GetMessage(_In_ DXGI_DEBUG_ID Producer, _In_ UINT64 MessageIndex, _Out_opt_ DXGI_INFO_QUEUE_MESSAGE* pMessage, _In_opt_ SIZE_T* pMessageByteLength) override;
	STDMETHODIMP_(UINT64) GetMessageCountLimit(_In_ DXGI_DEBUG_ID Producer) override;
	STDMETHODIMP_(BOOL) GetMuteDebugOutput(_In_ DXGI_DEBUG_ID Producer) override;
	STDMETHODIMP_(UINT64) GetNumMessagesAllowedByStorageFilter(_In_ DXGI_DEBUG_ID Producer) override;
	STDMETHODIMP_(UINT64) GetNumMessagesDeniedByStorageFilter(_In_ DXGI_DEBUG_ID Producer) override;
	STDMETHODIMP_(UINT64) GetNumStoredMessages(_In_ DXGI_DEBUG_ID Producer) override;
	STDMETHODIMP_(UINT64) GetNumStoredMessagesAllowedByRetrievalFilters(_In_ DXGI_DEBUG_ID Producer) override;
	STDMETHODIMP GetRetrievalFilter(_In_ DXGI_DEBUG_ID Producer, _Out_opt_ DXGI_INFO_QUEUE_FILTER* pFilter, _In_opt_ SIZE_T* pFilterByteLength) override;
	STDMETHODIMP_(UINT) GetRetrievalFilterStackSize(_In_ DXGI_DEBUG_ID Producer) override;
	STDMETHODIMP GetStorageFilter(_In_ DXGI_DEBUG_ID Producer, _Out_opt_ DXGI_INFO_QUEUE_FILTER* pFilter, _In_opt_ SIZE_T* pFilterByteLength) override;
	STDMETHODIMP_(UINT) GetStorageFilterStackSize(_In_ DXGI_DEBUG_ID Producer) override;
	STDMETHODIMP_(void) PopRetrievalFilter(_In_ DXGI_DEBUG_ID Producer) override;
	STDMETHODIMP_(void) PopStorageFilter(_In_ DXGI_DEBUG_ID Producer) override;
	STDMETHODIMP PushCopyOfRetrievalFilter(_In_ DXGI_DEBUG_ID Producer) override;
	STDMETHODIMP PushCopyOfStorageFilter(_In_ DXGI_DEBUG_ID Producer) override;
	STDMETHODIMP PushDenyAllRetrievalFilter(_In_ DXGI_DEBUG_ID Producer) override;
	STDMETHODIMP PushDenyAllStorageFilter(_In_ DXGI_DEBUG_ID Producer) override;
	STDMETHODIMP PushEmptyRetrievalFilter(_In_ DXGI_DEBUG_ID Producer) override;
	STDMETHODIMP PushEmptyStorageFilter(_In_ DXGI_DEBUG_ID Producer) override;
	STDMETHODIMP PushRetrievalFilter(_In_ DXGI_DEBUG_ID Producer, _In_ DXGI_INFO_QUEUE_FILTER* pFilter) override;
	STDMETHODIMP PushStorageFilter(_In_ DXGI_DEBUG_ID Producer, _In_ DXGI_INFO_QUEUE_FILTER* pFilter) override;
	STDMETHODIMP SetBreakOnCategory(_In_ DXGI_DEBUG_ID Producer, _In_ DXGI_INFO_QUEUE_MESSAGE_CATEGORY Category, _In_ BOOL bEnable) override;
	STDMETHODIMP SetBreakOnID(_In_ DXGI_DEBUG_ID SetBreakOnID, _In_ DXGI_INFO_QUEUE_MESSAGE_ID ID, _In_ BOOL bEnable) override;
	STDMETHODIMP SetBreakOnSeverity(_In_ DXGI_DEBUG_ID Producer, _In_ DXGI_INFO_QUEUE_MESSAGE_SEVERITY Severity, _In_ BOOL bEnable) override;
	STDMETHODIMP SetMessageCountLimit(_In_ DXGI_DEBUG_ID Producer, _In_ UINT64 MessageCountLimit) override;
	STDMETHODIMP_(void) SetMuteDebugOutput(_In_ DXGI_DEBUG_ID Producer, _In_ BOOL bMute) override;
};
