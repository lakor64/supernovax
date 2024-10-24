#define STRICT 1
#define _ATL_APARTMENT_THREADED 1
#define _ATL_NO_AUTOMATIC_NAMESPACE 1
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS 1	// explicit CString
#define ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW 1
#define USE_STATIC_ATL 1
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING 1 // kys

#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>
#include <dxdiag.h>
#include <dxdiagternl.h>
#include <string>
#include <locale>
#include <codecvt>
#include <sstream>
#include <proxy_i.h>

typedef HRESULT(WINAPI* DllGetClassObjectCb)(_In_ IID* rclsid, _In_ IID* riid, _Out_ LPVOID* ppv);

static void MYLOG_A(HWND hwnd, LPCSTR text, LPCSTR title, DWORD style);
static void MYLOG_W(HWND hwnd, LPCWSTR text, LPCWSTR title, DWORD style);

class CDxDiagProviderModule :
	public ATL::CAtlDllModuleT<CDxDiagProviderModule>
{
public:
	DECLARE_LIBID(LIBID_DxDiagProviderModule)

	explicit CDxDiagProviderModule() : m_hDll(nullptr), m_pProc(nullptr) {}
	~CDxDiagProviderModule() = default;

    static FILE* ayo_log;

	BOOL WINAPI DllMain(_In_ DWORD dwReason, _In_opt_ LPVOID lpReserved)
	{
        if (!ATL::CAtlDllModuleT<CDxDiagProviderModule>::DllMain(dwReason, lpReserved))
            return FALSE;

		switch (dwReason)
		{
		case DLL_PROCESS_DETACH:
            MYLOG_A(nullptr, "proxy dxdiag offline", "dxdiagn proxy", MB_OK);

            if (ayo_log)
            {
                fflush(ayo_log);
                fclose(ayo_log);
            }

			if (m_hDll)
				FreeLibrary(m_hDll);

			m_pProc = nullptr;
			m_hDll = nullptr;
			break;

		case DLL_PROCESS_ATTACH:

            fopen_s(&ayo_log, "ayoo_log.txt", "wb");
            if (!ayo_log)
            {
                MessageBoxW(nullptr, L"CANNOT MAKE LOG !!!!", L"FATAL ERROR", MB_OK | MB_ICONERROR);
                return FALSE;
            }

            fwrite("\xff\xfe", 2, 1, ayo_log);

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

            MYLOG_A(nullptr, "proxy dxdiag online", "dxdiagn proxy", MB_OK);
			break;
		}

		return TRUE;
	}

	HRESULT CreateDxDiagProvider(IDxDiagProvider** ptr)
	{
		if (!m_pProc)
			return E_NOINTERFACE;

        //MYLOG_A(nullptr, "Test create dxprovider", "dxdiagn proxy", MB_OK);
        IClassFactory* caf = nullptr;
		auto x = m_pProc((IID*) & CLSID_DxDiagProvider, (IID*)&IID_IClassFactory, (LPVOID*)&caf);
        if (FAILED(x))
            return x;
        x = caf->CreateInstance(nullptr, IID_IDxDiagProvider, (void**)ptr);
        caf->Release();
        //MYLOG_A(nullptr, "Test create dxprovider ok", "dxdiagn proxy", MB_OK);
        return x;
    }

private:
	HMODULE m_hDll;
	DllGetClassObjectCb m_pProc;
};

FILE* CDxDiagProviderModule::ayo_log = nullptr;

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
        break;
    case VT_LPSTR:
    {
        std::string inp = (LPCSTR)val.byref;
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        q += converter.from_bytes(inp);
        break;
    }
    case VT_LPWSTR:
    case VT_BSTR:
        q += (LPWSTR)val.byref;
        break;
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

class ATL_NO_VTABLE CDxDiagContainer :
    public IDxDiagContainer,
    public ATL::CComObjectRootEx<ATL::CComSingleThreadModel>
{
public:
    BEGIN_COM_MAP(CDxDiagContainer)
        COM_INTERFACE_ENTRY_IID(IID_IDxDiagContainer, IDxDiagContainer)
    END_COM_MAP()

    DECLARE_NO_REGISTRY()
    DECLARE_NOT_AGGREGATABLE(CDxDiagContainer)

    CDxDiagContainer() : m_pcnt(nullptr) {}

    ~CDxDiagContainer() {
        if (m_pcnt)
            m_pcnt->Release();
    }

    void SetContainer(IDxDiagContainer* cnt) { m_pcnt = cnt;  }

    void SetWhoIs(LPCWSTR who) { wcscpy_s(m_who, _countof(m_who), who); }

    STDMETHODIMP GetNumberOfChildContainers(DWORD* pdwCount) override
    {
        auto hr = m_pcnt->GetNumberOfChildContainers(pdwCount);

        std::wstring p = L"HR: ";
        p += std::to_wstring(hr);

        if (pdwCount)
        {
            p += L" count: ";
            p += std::to_wstring(*pdwCount);
        }

        MYLOG_W(nullptr, p.c_str(), L"GetNumberOfChildContainers", MB_OK);
        return hr;
    }

    STDMETHODIMP EnumChildContainerNames(
        /* [in] */ DWORD dwIndex,
        /* [out] */ LPWSTR pwszContainer,
        /* [in] */ DWORD cchContainer) override
    {
        std::wstring aa = L"index: ";
        aa += std::to_wstring(dwIndex);

        auto hr = m_pcnt->EnumChildContainerNames(dwIndex, pwszContainer, cchContainer);

        if (pwszContainer && cchContainer > 0)
        {
            aa += L" buffer: ";
            aa += pwszContainer;
        }

        aa += L" hr:";
        aa += std::to_wstring(hr);

        MYLOG_W(nullptr, aa.c_str(), L"EnumchildContainerNames", MB_OK);
        return hr;
    }

    STDMETHODIMP GetChildContainer(
        /* [in] */ LPCWSTR pwszConainer,
        /* [out] */ IDxDiagContainer** ppInstance) override
    {
        *ppInstance = nullptr;

        IDxDiagContainer* origcont = nullptr;
        auto hr = m_pcnt->GetChildContainer(pwszConainer, &origcont);
        if (FAILED(hr))
        {
            std::wstring ops = L"Fail ";
            ops += pwszConainer;
            ops += L" HR: ";
            ops += std::to_wstring(hr);
            MYLOG_W(nullptr, ops.c_str(), L"GetChildContainer", MB_OK);
            return hr;
        }

        ATL::CComObject<CDxDiagContainer>* conta;
        hr = ATL::CComObject<CDxDiagContainer>::CreateInstance(&conta);
        if (FAILED(hr))
        {
            MYLOG_W(nullptr, L"Create CDxDiagContainer fail, wtf", L"GetChildContainer", MB_OK);
            origcont->Release();
            return hr;
        }

        conta->SetContainer(origcont);
        conta->SetWhoIs(pwszConainer);
        conta->AddRef();

        *ppInstance = conta;
        return S_OK;
    }

    STDMETHODIMP GetNumberOfProps(
        /* [out] */ DWORD* pdwCount)
    {
        auto hr = m_pcnt->GetNumberOfProps(pdwCount);

        std::wstring p = L"HR: ";
        p += std::to_wstring(hr);

        if (pdwCount)
        {
            p += L" count: ";
            p += std::to_wstring(*pdwCount);
        }
        MYLOG_W(nullptr, p.c_str(), L"GetNumberOfProps", MB_OK);

        return hr;
    }

    STDMETHODIMP EnumPropNames(
        /* [in] */ DWORD dwIndex,
        /* [out] */ LPWSTR pwszPropName,
        /* [in] */ DWORD cchPropName)
    {
        auto hr = m_pcnt->EnumPropNames(dwIndex, pwszPropName, cchPropName);
        std::wstring aa = L"index: ";
        aa += std::to_wstring(dwIndex);

        if (pwszPropName && cchPropName > 0)
        {
            aa += L" data: ";
            aa += pwszPropName;
        }

        aa += L" hr:";
        aa += std::to_wstring(hr);

        MYLOG_W(nullptr, aa.c_str(), L"EnumPropNames", MB_OK);
        return hr;
    }

    STDMETHODIMP GetProp(
        /* [in] */ LPCWSTR pwszPropName,
        /* [out] */ VARIANT* pvarProp) override
    {
        std::wstring prop = L"prop: ";
        prop += pwszPropName;
        prop += L" from: ";
        prop += m_who;

        auto hr = m_pcnt->GetProp(pwszPropName, pvarProp);
        prop += L" hr: ";
        prop += std::to_wstring(hr);

        if (pvarProp)
        {
            prop += L" val: ";
            add_variant_val(*pvarProp, prop, pwszPropName);
            prop += L"(";
            prop += val_type(*pvarProp);
            prop += L")";
        }

        MYLOG_W(nullptr, prop.c_str(), L"GetProp", MB_OK);
        return hr;
    }

private:
    IDxDiagContainer* m_pcnt;
    WCHAR m_who[256];
};

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
        MYLOG_A(nullptr, "create provider", "dxdiagn proxy", MB_OK);
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
        MYLOG_A(nullptr, "Create base DxDiag Provider", "dxdiagn proxy", MB_OK);

        auto hr = _AtlModule.CreateDxDiagProvider(&m_pms);
        if (FAILED(hr))
        {
            std::stringstream sss;
            sss << "CreateDxDiagProvider fail: ";
            sss << std::hex << hr;

            MYLOG_A(nullptr, sss.str().c_str(), "dxdiagn proxy", MB_OK);
            return hr;
        }

        MYLOG_A(nullptr, "Initialize base DxDiag Provider", "dxdiagn proxy", MB_OK);

		hr = m_pms->Initialize(pParams);
        if (FAILED(hr))
        {
            std::stringstream sss;
            sss << "Initialize fail: ";
            sss << std::hex << hr;

            MYLOG_A(nullptr, sss.str().c_str(), "dxdiagn proxy", MB_OK);
            return hr;
        }

        hr = m_pms->QueryInterface(IID_IDxDiagProviderPrivate, (LPVOID*)&m_ppms);
        if (FAILED(hr))
        {
            std::stringstream sss;
            sss << "QueryInterface private fail: ";
            sss << std::hex << hr;

            MYLOG_A(nullptr, sss.str().c_str(), "dxdiagn proxy", MB_OK);
            return hr;
        }

        return S_OK;
	}

	STDMETHODIMP GetRootContainer(IDxDiagContainer** ppInstance) override
	{
        *ppInstance = nullptr;

        IDxDiagContainer* cnt2 = nullptr;
		auto hr = m_pms->GetRootContainer(&cnt2);

        if (FAILED(hr))
        {
            std::string aa = "HR: ";
            aa += std::to_string(hr);
            MYLOG_A(nullptr, aa.c_str(), "GetRootContainer", MB_OK);
            return hr;
        }

        ATL::CComObject<CDxDiagContainer>* cnt;
        hr = ATL::CComObject<CDxDiagContainer>::CreateInstance(&cnt);
        if (FAILED(hr))
        {
            MYLOG_A(nullptr, "Cannot create atl obj", "GetRootContainer", MB_OK);
            cnt2->Release();
            return hr;
        }

        cnt->SetContainer(cnt2);
        cnt->SetWhoIs(L"___ROOT___");
        cnt->AddRef();

        MYLOG_A(nullptr, "Called by ?", "GetRootContainer", MB_OK);

        *ppInstance = cnt;
        return S_OK;
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

        MYLOG_W(nullptr, qo.c_str(), L"dxdiagn proxy", MB_OK);
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

    MYLOG_W(nullptr, p.c_str(), L"dxdiagn proxy", MB_OK);
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
                MYLOG_A(nullptr, "Provider CreateInstance fail", "dxdiagn proxy", MB_OK);
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

void MYLOG_A(HWND hwnd, LPCSTR text, LPCSTR title, DWORD style)
{
    std::string inp = title;
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    auto q = converter.from_bytes(inp);
    q += L"::";

    inp = text;
    q += converter.from_bytes(inp);
    q += L"\n";

    fwrite(q.data(), q.size() * 2, 1, CDxDiagProviderModule::ayo_log);
}

void MYLOG_W(HWND hwnd, LPCWSTR text, LPCWSTR title, DWORD style)
{
    std::wstring q = title;
    q += L"::";
    q += text;
    q += L"\n";
    fwrite(q.data(), q.size() * 2, 1, CDxDiagProviderModule::ayo_log);
}
