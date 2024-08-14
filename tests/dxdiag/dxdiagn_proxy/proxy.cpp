#define STRICT 1
#define _ATL_APARTMENT_THREADED 1
#define _ATL_NO_AUTOMATIC_NAMESPACE 1
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS 1	// explicit CString
#define ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW 1

#include <atlbase.h>
#include <atlcom.h>
#include <dxdiag.h>
#include <dxdiag_private.h>
#include <string>

typedef HRESULT(WINAPI* DllGetClassObjectCb)(_In_ REFCLSID rclsid, _In_ REFIID riid, _Out_ LPVOID* ppv);

class ATL_NO_VTABLE CDxDiagProviderModule :
	public ATL::CAtlDllModuleT<CDxDiagProviderModule>
{
public:
	DECLARE_LIBID(CLSID_DxDiagProvider)

	explicit CDxDiagProviderModule() : m_hDll(nullptr), m_pProc(nullptr) {}
	~CDxDiagProviderModule() = default;

	BOOL WINAPI DllMain(_In_ DWORD dwReason, _In_opt_ LPVOID lpReserved)
	{
		switch (dwReason)
		{
		case DLL_PROCESS_DETACH:
			if (m_hDll)
				FreeLibrary(m_hDll);

			m_pProc = nullptr;
			m_hDll = nullptr;
			break;

		case DLL_PROCESS_ATTACH:

			m_hDll = LoadLibraryW(L"dxdiagn2.dll");
            if (!m_hDll)
            {
                MessageBoxA(nullptr, "Cannot load dxdiagn2.dll", "dxdiagn proxy", MB_ICONERROR | MB_OK);
                return FALSE;
            }

			m_pProc = (DllGetClassObjectCb)GetProcAddress(m_hDll, "DllGetClassObject");
			if (!m_pProc)
			{
                MessageBoxA(nullptr, "cannot get DllGetClassObject from dxdiagn ms", "dxdiagn proxy", MB_ICONERROR | MB_OK);
				FreeLibrary(m_hDll);
				m_hDll = nullptr;
				return FALSE;
			}

            MessageBoxA(nullptr, "proxy dxdiag online", "dxdiagn proxy", MB_OK);
			break;
		}

		return TRUE;
	}

	HRESULT CreateDxDiagProvider(IDxDiagProvider* ptr)
	{
		if (!m_pProc)
			return E_NOINTERFACE;

		return m_pProc(CLSID_DxDiagProvider, IID_IDxDiagProvider, (LPVOID*) & ptr);
	}

private:
	HMODULE m_hDll;
	DllGetClassObjectCb m_pProc;
};

static CDxDiagProviderModule _AtlModule;

static const wchar_t* val_type(const VARIANT& v)
{
    switch (v.vt)
    {
    case VT_EMPTY:
        return L"empty";
    case VT_NULL:
        return L"null";
    case VT_I2:
        return L"i2";
    case VT_I4:
        return L"i4";
    case VT_R4:
        return L"r4";
    case VT_R8:
        return L"r8";
    case VT_CY:
        return L"cy";
    case VT_DATE:
        return L"date";
    case VT_BSTR:
        return L"bstr";
    case VT_DISPATCH:
        return L"dispatch";
    case VT_ERROR:
        return L"error";
    case VT_BOOL:
        return L"bool";
    case VT_VARIANT:
        return L"variant";
    case VT_UNKNOWN:
        return L"unknown";
    case VT_DECIMAL:
        return L"decimal";
    case VT_I1:
        return L"i1";
    case VT_UI1:
        return L"ui1";
    case VT_UI2:
        return L"ui2";
    case VT_UI4:
        return L"ui4";
    case VT_I8:
        return L"i8";
    case VT_UI8:
        return L"ui8";
    case VT_INT:
        return L"int";
    case VT_UINT:
        return L"uint";
    case VT_VOID:
        return L"void";
    case VT_HRESULT:
        return L"hresult";
    case VT_PTR:
        return L"ptr";
    case VT_SAFEARRAY:
        return L"safearray";
    case VT_CARRAY:
        return L"carray";
    case VT_USERDEFINED:
        return L"userdefined";
    case VT_LPSTR:
        return L"lpstr";
    case VT_LPWSTR:
        return L"lpwstr";
    case VT_RECORD:
        return L"record";
    case VT_INT_PTR:
        return L"intptr";
    case VT_UINT_PTR:
        return L"uintptr";
    case VT_FILETIME:
        return L"filetime";
    case VT_BLOB:
        return L"blob";
    case VT_STREAM:
        return L"stream";
    case VT_STORAGE:
        return L"storage";
    case VT_STREAMED_OBJECT:
        return L"streamedobject";
    case VT_STORED_OBJECT:
        return L"storedobject";
    case VT_BLOB_OBJECT:
        return L"blobobject";
    case VT_CF:
        return L"cf";
    case VT_CLSID:
        return L"clsid";
    case VT_VERSIONED_STREAM:
        return L"versionedstream";
    case VT_BSTR_BLOB:
        return L"bstrblob";
    case VT_VECTOR:
        return L"vector";
    case VT_ARRAY:
        return L"array";
    case VT_BYREF:
        return L"byref";
    case VT_RESERVED:
        return L"reserved";
    case VT_ILLEGAL:
        return L"illegal";
    default:
        break;
    }

    return L"???";
}

class ATL_NO_VTABLE CDxDiagProvider
	: public IDxDiagProvider,
	public IDxDiagProviderPrivate,
    public ATL::CComObjectRootEx<ATL::CComMultiThreadModelNoCS>
{
public:
	BEGIN_COM_MAP(CDxDiagProvider)
		COM_INTERFACE_ENTRY_IID(IID_IDxDiagProvider, IDxDiagProvider)
		COM_INTERFACE_ENTRY_IID(IID_IDxDiagProviderPrivate, IDxDiagProviderPrivate)
	END_COM_MAP()

	CDxDiagProvider() : m_pms(nullptr), m_ppms(nullptr) {}
	~CDxDiagProvider()
	{
		if (m_ppms)
			m_ppms->Release();
		if (m_pms)
			m_pms->Release();
	}

	STDMETHODIMP Initialize(DXDIAG_INIT_PARAMS* pParams) override
	{
		return m_pms->Initialize(pParams);
	}

	STDMETHODIMP GetRootContainer(IDxDiagContainer** ppInstance) override
	{
		// TODO: Proxy this!
		return m_pms->GetRootContainer(ppInstance);
	}

    STDMETHODIMP_(int) ExecMethod(
        /* [in] */ LPCWSTR lpActionName,
        /* [in] */ VARIANT* lpValue) override
    {
        auto r = m_ppms->ExecMethod(lpActionName, lpValue);

        std::wstring qo = L"ExecMethod ActionName->";
        qo += lpActionName;
        qo += L" lpValue->";
        if (lpValue)
        {
            qo += val_type(*lpValue);
        }
        else
        {
            qo += L"(null)";
        }
        qo += L" return->";
        qo += std::to_wstring(r);

        MessageBoxW(nullptr, qo.c_str(), L"dxdiagn proxy", MB_OK);
        return r;
	}

private:
	IDxDiagProvider* m_pms;
	IDxDiagProviderPrivate* m_ppms;
};


extern "C"
{
	BOOL WINAPI DllMain(_In_ HINSTANCE hInstance, _In_ DWORD dwReason, _In_opt_ LPVOID lpReserved)
	{
		hInstance;
		return _AtlModule.DllMain(dwReason, lpReserved);
	}

	HRESULT WINAPI DllGetClassObject(
		_In_  REFCLSID rclsid,
		_In_  REFIID   riid,
		_Out_ LPVOID* ppv
	)
	{
		return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
	}

	HRESULT WINAPI DllCanUnloadNow()
	{
		return _AtlModule.DllCanUnloadNow();
	}

	HRESULT WINAPI DllRegisterServer()
	{
		return _AtlModule.DllRegisterServer();
	}

	HRESULT WINAPI DllUnregisterServer()
	{
		return _AtlModule.DllUnregisterServer();
	}
}
