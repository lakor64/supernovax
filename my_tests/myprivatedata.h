#pragma once

class MyPrivateData : public IUnknown
{
public:
	MyPrivateData() : m_nRef(1) {}

	virtual ULONG WINAPI AddRef(VOID);
	virtual ULONG WINAPI Release(VOID);
	virtual HRESULT WINAPI QueryInterface(_In_ REFIID id, _Inout_ void** ppObj);
	ULONG GetRefCount() const { return m_nRef; }

protected:
	ULONG m_nRef;
};
