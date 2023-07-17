#include "pch.h"
#include "dxgiobject.h"

// IUnknown
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

HRESULT WINAPI CDXGIObject::QueryInterface(_In_ REFIID id, _Inout_ void** ppObj)
{
	if (IsEqualIID(id, IID_IUnknown) || IsEqualIID(id, IID_IDXGIObject))
	{
		*ppObj = this;
		AddRef();
		return S_OK;
	}

	return E_NOINTERFACE;
}

// IDXGIObject
HRESULT WINAPI CDXGIObject::SetPrivateData(_In_ REFGUID Name, _In_ UINT DataSize, _In_ const void* pDataSize)
{
	if (!pDataSize)
	{
		return DeletePD(Name);
	}

	FreeCOMPD(Name);

	DXGIPrivateData data;
	if (!data.Set(pDataSize, DataSize))
		return E_OUTOFMEMORY;

	m_mData.insert_or_assign(Name, data);
}

HRESULT WINAPI CDXGIObject::GetPrivateData(_In_ REFGUID Name, _Inout_ UINT* DataSize, _Out_ void* pData)
{
	auto it = m_mData.find(Name);
	if (it == m_mData.end())
		return DXGI_ERROR_NOT_FOUND;

	if (*DataSize < it->second.nSize)
		return DXGI_ERROR_MORE_DATA;

	memcpy_s(pData, *DataSize, it->second.pData, it->second.nSize);

	if (it->second.isCOM)
		((IUnknown*)it->second.pData)->AddRef();

	return S_OK;
}

HRESULT WINAPI CDXGIObject::GetParent(_In_ REFIID Id, _Out_ void** pParent)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CDXGIObject::SetPrivateDataInterface(_In_ REFGUID Name, _In_ IUnknown* pUnknown)
{
	return SetPrivateData(Name, sizeof(pUnknown), pUnknown);
}

HRESULT CDXGIObject::DeletePD(_In_ REFGUID Name)
{
	auto it = m_mData.find(Name);
	if (it == m_mData.end())
		return S_OK;

	if (it->second.isCOM)
	{
		((IUnknown*)it->second.pData)->Release();
	}

	m_mData.erase(it);
	return S_OK;
}
