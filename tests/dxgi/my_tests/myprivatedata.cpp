#include "pch.h"
#include "myprivatedata.h"

ULONG WINAPI MyPrivateData::AddRef(VOID)
{
	InterlockedIncrement(&m_nRef);
	return m_nRef;
}

ULONG WINAPI MyPrivateData::Release(VOID)
{
	InterlockedDecrement(&m_nRef);

	if (!m_nRef)
	{
		delete this;
		return 0;
	}

	return m_nRef;
}

HRESULT WINAPI MyPrivateData::QueryInterface(_In_ REFIID id, _Inout_ void** ppObj)
{
	if (IsEqualIID(IID_IUnknown, id) || IsEqualIID(IID_MyPrivateData, id))
	{
		*ppObj = this;
		AddRef();
		return S_OK;
	}

	*ppObj = NULL;
	return E_NOINTERFACE;
}
