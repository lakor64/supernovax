#include "pch.h"
#include "dxgiobject.h"


ULONG WINAPI CDXGIObject::AddRef(VOID)
{
	InterlockedIncrement(&m_uRef);
	return m_uRef;
}

ULONG WINAPI CDXGIObject::Release(VOID)
{
	InterlockedDecrement(&m_uRef);

	if (m_uRef == 0)
	{
		delete this;
		return 0;
	}

	return m_uRef;
}

// IDXGIObject
HRESULT WINAPI CDXGIObject::SetPrivateData(_In_ REFGUID Name, _In_ UINT DataSize, _In_ const void* pDataSize)
{

}

HRESULT WINAPI CDXGIObject::GetPrivateData(_In_ REFGUID Name, _Inout_ UINT* DataSize, _Out_ void* pData)
{

}

HRESULT WINAPI CDXGIObject::GetParent(_In_ REFIID Id, _Out_ void** pParent)
{

}

HRESULT WINAPI CDXGIObject::SetPrivateDataInterface(_In_ REFGUID Name, _In_ IUnknown* pUnknown)
{
	if (m_pPDI)
	{
		m_pPDI->Release();
	}

	m_pDataInterface = pUnknown;

	if (m_pDataInterface)
	{

	}

}
