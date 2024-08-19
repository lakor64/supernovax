#define STRICT 1
#define _ATL_APARTMENT_THREADED 1
#define _ATL_NO_AUTOMATIC_NAMESPACE 1
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS 1	// explicit CString
#define ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW 1
#define USE_STATIC_ATL 1

#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>
#include <dxdiag.h>
#include <dxdiag_private.h>
#include <string>
#include <sstream>
#include <proxy_i.h>

typedef HRESULT(WINAPI* DllGetClassObjectCb)(_In_ IID* rclsid, _In_ IID* riid, _Out_ LPVOID* ppv);

class CDxDiagProviderModule :
	public ATL::CAtlDllModuleT<CDxDiagProviderModule>
{
public:
	DECLARE_LIBID(LIBID_DxDiagProviderModule)

	explicit CDxDiagProviderModule() : m_hDll(nullptr), m_pProc(nullptr) {}
	~CDxDiagProviderModule() = default;

	BOOL WINAPI DllMain(_In_ DWORD dwReason, _In_opt_ LPVOID lpReserved)
	{
        if (!ATL::CAtlDllModuleT<CDxDiagProviderModule>::DllMain(dwReason, lpReserved))
            return FALSE;

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

	HRESULT CreateDxDiagProvider(IDxDiagProvider** ptr)
	{
		if (!m_pProc)
			return E_NOINTERFACE;

        //MessageBoxA(nullptr, "Test create dxprovider", "dxdiagn proxy", MB_OK);
        IClassFactory* caf = nullptr;
		auto x = m_pProc((IID*) & CLSID_DxDiagProvider, (IID*)&IID_IClassFactory, (LPVOID*)&caf);
        if (FAILED(x))
            return x;
        x = caf->CreateInstance(nullptr, IID_IDxDiagProvider, (void**)ptr);
        caf->Release();
        //MessageBoxA(nullptr, "Test create dxprovider ok", "dxdiagn proxy", MB_OK);
        return x;
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

static void add_variant_val(const VARIANT& val, std::wstring& q, LPCWSTR key)
{
    switch (val.vt)
    {
    case VT_I1:
    case VT_UI1:
        q += std::to_wstring((UINT)val.bVal);
        break;
    case VT_I2:
    case VT_UI2:
        q += std::to_wstring(val.uiVal);
        break;
    case VT_I4:
    case VT_UI4:
    case VT_UINT:
        q += std::to_wstring(val.uintVal);
        break;
    case VT_I8:
    case VT_UI8:
        q += std::to_wstring(val.ullVal);
    case VT_BYREF:
        if (wcscmp(key, L"TestDD") == 0 ||
            wcscmp(key, L"TestD3D") == 0 ||
            wcscmp(key, L"TestSnd") == 0)
        {
            struct TESTDD_DATA
            {
                HWND hwnd;
                int32_t result;
            };

            TESTDD_DATA* ddq = (TESTDD_DATA*)val.byref;
            q += L"hwnd->";
            q += std::to_wstring((intptr_t)ddq->hwnd);
            q += L" result->";
            q += std::to_wstring(ddq->result);
        }
        else if (wcscmp(key, L"TestMusic") == 0)
        {
            struct TESTMUSIC_DATA
            {
                HWND hwnd;
                GUID g;
            };
            TESTMUSIC_DATA* ddq = (TESTMUSIC_DATA*)val.byref;
            q += L"hwnd->";
            q += std::to_wstring((intptr_t)ddq->hwnd);
            q += L"guid->";
            wchar_t myptr[255] = { 0 };
            StringFromGUID2(ddq->g, myptr, 254);
            q += myptr;
        }
        else if (wcscmp(key, L"TestNetwork"))
        {
            q += L"hwnd->";
            q += std::to_wstring((intptr_t)(HWND)val.byref);
        }
        else
        {
            q += std::to_wstring((UINT)val.byref);
        }
        break;
    default:
        break;
    }
}

class ATL_NO_VTABLE CDxDiagProvider : 
    public IDxDiagProvider,
	public IDxDiagProviderPrivate,
    public ATL::CComObjectRootEx<ATL::CComSingleThreadModel>
{
public:
	BEGIN_COM_MAP(CDxDiagProvider)
		COM_INTERFACE_ENTRY_IID(IID_IDxDiagProvider, IDxDiagProvider)
		COM_INTERFACE_ENTRY_IID(IID_IDxDiagProviderPrivate, IDxDiagProviderPrivate)
	END_COM_MAP()

    DECLARE_NO_REGISTRY()
    DECLARE_NOT_AGGREGATABLE(CDxDiagProvider)

	CDxDiagProvider() : m_pms(nullptr), m_ppms(nullptr)
    {
#ifdef BIG_DEBUG
        MessageBoxA(nullptr, "create provider", "dxdiagn proxy", MB_OK);
#endif
    }

	~CDxDiagProvider()
	{
		if (m_ppms)
			m_ppms->Release();
		if (m_pms)
			m_pms->Release();
	}

	STDMETHODIMP Initialize(DXDIAG_INIT_PARAMS* pParams) override
	{
#ifdef BIG_DEBUG
        MessageBoxA(nullptr, "Create base DxDiag Provider", "dxdiagn proxy", MB_OK);
#endif

        auto hr = _AtlModule.CreateDxDiagProvider(&m_pms);
        if (FAILED(hr))
        {
            std::stringstream sss;
            sss << "CreateDxDiagProvider fail: ";
            sss << std::hex << hr;

            MessageBoxA(nullptr, sss.str().c_str(), "dxdiagn proxy", MB_OK);
            return hr;
        }

#ifdef BIG_DEBUG
        MessageBoxA(nullptr, "Initialize base DxDiag Provider", "dxdiagn proxy", MB_OK);
#endif

		hr = m_pms->Initialize(pParams);
        if (FAILED(hr))
        {
            std::stringstream sss;
            sss << "Initialize fail: ";
            sss << std::hex << hr;

            MessageBoxA(nullptr, sss.str().c_str(), "dxdiagn proxy", MB_OK);
            return hr;
        }

        hr = m_pms->QueryInterface(IID_IDxDiagProviderPrivate, (LPVOID*)&m_ppms);
        if (FAILED(hr))
        {
            std::stringstream sss;
            sss << "QueryInterface private fail: ";
            sss << std::hex << hr;

            MessageBoxA(nullptr, sss.str().c_str(), "dxdiagn proxy", MB_OK);
            return hr;
        }

        return S_OK;
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
            qo += L"(";
            add_variant_val(*lpValue, qo, lpActionName);
            qo += L")";
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

static void print_no_interface(REFIID rclsid, REFIID riid)
{
    std::wstring p = L"";
    LPOLESTR clsidlp = nullptr;
    StringFromCLSID(rclsid, &clsidlp);
    LPOLESTR riidlp = nullptr;
    StringFromIID(riid, &riidlp);
    p = L"Cannot find clsid: ";
    p += clsidlp;
    p += L" iid: ";
    p += riidlp;
    CoTaskMemFree(riidlp);
    CoTaskMemFree(clsidlp);

    MessageBoxW(nullptr, p.c_str(), L"dxdiagn proxy", MB_OK);
}

class ATL_NO_VTABLE CDxDiagProviderFactory :
    public ATL::CComClassFactory
{
public:
    STDMETHOD(CreateInstance)(LPUNKNOWN pUnkOuter, REFIID riid, void** ppvObj)
    {
        if (IsEqualIID(riid, IID_IDxDiagProvider) ||
            IsEqualIID(riid, IID_IDxDiagProviderPrivate) ||
            IsEqualIID(riid, IID_IUnknown))
        {
            ATL::CComObject<CDxDiagProvider>* prov;
            auto hr = ATL::CComObject<CDxDiagProvider>::CreateInstance(&prov);
            if (FAILED(hr))
            {
                MessageBoxA(nullptr, "Provider CreateInstance fail", "dxdiagn proxy", MB_OK);
                return hr;
            }

            prov->AddRef();
            *ppvObj = prov;

            return S_OK;
        }

        print_no_interface(CLSID_DxDiagProvider, riid);
        return E_NOINTERFACE;
    }
};

class ATL_NO_VTABLE CDxDiagProviderClass :
    public ATL::CComObjectRootEx<ATL::CComSingleThreadModel>,
    public ATL::CComCoClass<CDxDiagProviderClass, &CLSID_DxDiagProvider>
{
public:
    DECLARE_CLASSFACTORY_EX(CDxDiagProviderFactory)
    DECLARE_NO_REGISTRY()

    BEGIN_COM_MAP(CDxDiagProviderClass)
    END_COM_MAP()
};

OBJECT_ENTRY_AUTO(CLSID_DxDiagProvider, CDxDiagProviderClass);

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
