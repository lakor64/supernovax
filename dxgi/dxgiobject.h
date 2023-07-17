#pragma once

class CDXGIObject : public IDXGIObject
{
public:
	virtual ULONG WINAPI AddRef(VOID);
	virtual ULONG WINAPI Release(VOID);
	virtual HRESULT WINAPI QueryInterface(_In_ REFIID id, _Inout_ void** ppObj);

	// IDXGIObject
	HRESULT WINAPI SetPrivateData(_In_ REFGUID Name, _In_ UINT DataSize, _In_ const void* pDataSize);
	HRESULT WINAPI GetPrivateData(_In_ REFGUID Name, _Inout_ UINT* DataSize, _Out_ void* pData);
	HRESULT WINAPI GetParent(_In_ REFIID Id, _Out_ void** pParent);
	HRESULT WINAPI SetPrivateDataInterface(_In_ REFGUID Name, _In_ IUnknown* pUnknown);

protected:
	ULONG m_uRef;
	IUnknown* m_pPDI;
	void* m_pPD;
};
