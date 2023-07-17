#pragma once

#include <unordered_map>

class CDXGIObject : public IDXGIObject
{
public:
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

	virtual ULONG WINAPI AddRef(VOID);
	virtual ULONG WINAPI Release(VOID);
	virtual HRESULT WINAPI QueryInterface(_In_ REFIID id, _Inout_ void** ppObj);

	// IDXGIObject
	HRESULT WINAPI SetPrivateData(_In_ REFGUID Name, _In_ UINT DataSize, _In_ const void* pDataSize);
	HRESULT WINAPI GetPrivateData(_In_ REFGUID Name, _Inout_ UINT* DataSize, _Out_ void* pData);
	virtual HRESULT WINAPI GetParent(_In_ REFIID Id, _Out_ void** pParent);
	HRESULT WINAPI SetPrivateDataInterface(_In_ REFGUID Name, _In_ IUnknown* pUnknown);

protected:
	ULONG m_uRef;
	std::unordered_map<GUID, DXGIPrivateData> m_mData;

private:
	HRESULT DeletePD(_In_ REFGUID Name);

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
