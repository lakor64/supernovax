#pragma once

#include <unordered_map>

struct DXGIPrivateData
{
	LPVOID pData;
	UINT nSize;
	bool isCOM;

	DXGIPrivateData() : pData(nullptr), nSize(0), isCOM(false) {}
	~DXGIPrivateData() {
		if (pData)
		{
			if (isCOM)
				((IUnknown*)pData)->Release();
			else
				free(pData);

			pData = nullptr;
			nSize = 0;
		}
	}
	bool Set(IUnknown* pUnknown)
	{
		pData = pUnknown;
		nSize = sizeof(pUnknown);
		isCOM = true;
		pUnknown->AddRef();
		return true;
	}

	bool Set(LPCVOID pData, UINT nSize)
	{
		this->nSize = nSize;
		isCOM = false;

		this->pData = malloc(nSize);

		if (!this->pData)
			return false;

		memcpy_s(this->pData, nSize, pData, nSize);
		return true;
	}
};

template <typename T>
class ATL_NO_VTABLE CDXGIObject : 
	public virtual T
{
public:
	STDMETHODIMP SetPrivateData(_In_ REFGUID Name, _In_ UINT DataSize, _In_opt_ const void* pDataSize) override
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
		return S_OK;
	}

	STDMETHODIMP GetPrivateData(_In_ REFGUID Name, _Inout_ UINT* DataSize, _Out_ void* pData) override
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

	virtual STDMETHODIMP GetParent(_In_ REFIID Id, _Out_ void** pParent) override
	{
		return E_NOTIMPL;
	}

	STDMETHODIMP SetPrivateDataInterface(_In_ REFGUID Name, _In_opt_ const IUnknown* pUnknown) override
	{
		return SetPrivateData(Name, sizeof(pUnknown), pUnknown);
	}

protected:
	ULONG m_uRef;
	std::unordered_map<GUID, DXGIPrivateData> m_mData;

private:
	STDMETHODIMP DeletePD(_In_ REFGUID Name)
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

	inline void FreeCOMPD(_In_ REFGUID Name)
	{
		auto it = m_mData.find(Name);
		if (it != m_mData.end())
		{
			if (it->second.isCOM)
			{
				((IUnknown*)it->second.pData)->Release();
			}
		}
	}
};
