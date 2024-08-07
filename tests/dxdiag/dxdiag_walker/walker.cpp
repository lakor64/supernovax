#define WINBOOL BOOL

#include <dxdiag.h>
#include <unordered_map>
#include <string>
#include <fstream>
#include <dxdiag_private.h>

BOOL g_filesInfo = FALSE, g_networkInfo = FALSE, g_musicInfo = FALSE, g_dshowInfo = FALSE, g_inputInfo = FALSE;

#define EXEC_METHOD2(m, vt) \
    hr = pddpp->ExecMethod(m, vt); \
    if (FAILED(hr)) { \
        std::wstring q = L"ExecMethod " m L" failed with "; \
        q += std::to_wstring(uint32_t(hr)); \
        MessageBox(nullptr, q.c_str(), L"ERROR", MB_OK | MB_ICONERROR); \
        return hr; \
    }

#define EXEC_METHOD(m) EXEC_METHOD2(m, NULL)
#define EXEC_METHOD_NOFAIL(m, vt) hr = pddpp->ExecMethod(m, vt);

constexpr const auto MAX_WCHAR_BUFFER = 1024;

struct container
{
    std::wstring name;
    std::unordered_map<std::wstring, VARIANT> props;
    std::unordered_map<std::wstring, container> childs;
    std::unordered_map<std::wstring, HRESULT> prop_in_error;
    std::unordered_map<std::wstring, HRESULT> child_in_error;
};

static void walk(IDxDiagContainer* root, container& ptr_c)
{
    HRESULT hr;
    WCHAR tmp[MAX_WCHAR_BUFFER];
    std::vector<std::wstring> tmpx;
    std::vector<IDxDiagContainer*> dxdiagc;
    DWORD il = 0;

    // 1. get all props
    hr = root->GetNumberOfProps(&il);
    if (SUCCEEDED(hr))
    {
        for (DWORD i = 0; i < il; i++)
        {
            hr = root->EnumPropNames(i, tmp, MAX_WCHAR_BUFFER);
            if (FAILED(hr))
                break;

            tmpx.push_back(tmp);
        }

        for (size_t i = 0; i < tmpx.size(); i++)
        {
            VARIANT var;
            ZeroMemory(&var, sizeof(var));
            hr = root->GetProp(tmpx[i].c_str(), &var);
            if (FAILED(hr))
            {
                ptr_c.child_in_error.insert_or_assign(tmpx[i], hr);
                continue;
            }

            ptr_c.props.insert_or_assign(tmpx[i], var);
        }
    }

    // 2. get all childs
    tmpx.clear();

    if ((ptr_c.name == L"DxDiag_DirectMusicPorts" && !g_musicInfo) ||
        ((ptr_c.name == L"DxDiag_DirectInputDevices" ||
            ptr_c.name == L"DxDiag_DirectInputGameports" ||
            ptr_c.name == L"DxDiag_DirectInputUSBRoot" ||
            ptr_c.name == L"DxDiag_DirectInputPS2Devices") && !g_inputInfo) ||
        ((ptr_c.name == L"DxDiag_DirectPlayApps" ||
            ptr_c.name == L"DxDiag_DirectPlaySPs" ||
            ptr_c.name == L"DxDiag_DirectPlayAdapters" ||
            ptr_c.name == L"DxDiag_DirectPlayVoiceCodecs") && !g_networkInfo) ||
        (ptr_c.name == L"DxDiag_DirectXFiles" && !g_filesInfo))
        return;

    hr = root->GetNumberOfChildContainers(&il);
    if (SUCCEEDED(hr))
    {
        for (DWORD i = 0; i < il; i++)
        {
            hr = root->EnumChildContainerNames(i, tmp, MAX_WCHAR_BUFFER);
            if (FAILED(hr))
                break;

            tmpx.push_back(tmp);
        }

        for (size_t i = 0; i < tmpx.size(); i++)
        {
            IDxDiagContainer* pcon = nullptr;
            container kon;

            if (tmpx[i] == L"DxDiag_DirectShowFilters" && !g_dshowInfo)
                continue;

            hr = root->GetChildContainer(tmpx[i].c_str(), &pcon);
            if (FAILED(hr))
            {
                ptr_c.child_in_error.insert_or_assign(tmpx[i], hr);
                continue;
            }

            kon.name = tmpx[i];
            walk(pcon, kon);
            ptr_c.childs.insert_or_assign(tmpx[i], kon);
        }
    }
}


static const char* val_type(const VARIANT& v)
{
    switch (v.vt)
    {
    case VT_EMPTY:
        return "empty";
    case VT_NULL:
        return "null";
    case VT_I2:
        return "i2";
    case VT_I4:
        return "i4";
    case VT_R4:
        return "r4";
    case VT_R8:
        return "r8";
    case VT_CY:
        return "cy";
    case VT_DATE:
        return "date";
    case VT_BSTR:
        return "bstr";
    case VT_DISPATCH:
        return "dispatch";
    case VT_ERROR:
        return "error";
    case VT_BOOL:
        return "bool";
    case VT_VARIANT:
        return "variant";
    case VT_UNKNOWN:
        return "unknown";
    case VT_DECIMAL:
        return "decimal";
    case VT_I1:
        return "i1";
    case VT_UI1:
        return "ui1";
    case VT_UI2:
        return "ui2";
    case VT_UI4:
        return "ui4";
    case VT_I8:
        return "i8";
    case VT_UI8:
        return "ui8";
    case VT_INT:
        return "int";
    case VT_UINT:
        return "uint";
    case VT_VOID:
        return "void";
    case VT_HRESULT:
        return "hresult";
    case VT_PTR:
        return "ptr";
    case VT_SAFEARRAY:
        return "safearray";
    case VT_CARRAY:
        return "carray";
    case VT_USERDEFINED:
        return "userdefined";
    case VT_LPSTR:
        return "lpstr";
    case VT_LPWSTR:
        return "lpwstr";
    case VT_RECORD:
        return "record";
    case VT_INT_PTR:
        return "intptr";
    case VT_UINT_PTR:
        return "uintptr";
    case VT_FILETIME:
        return "filetime";
    case VT_BLOB:
        return "blob";
    case VT_STREAM:
        return "stream";
    case VT_STORAGE:
        return "storage";
    case VT_STREAMED_OBJECT:
        return "streamedobject";
    case VT_STORED_OBJECT:
        return "storedobject";
    case VT_BLOB_OBJECT:
        return "blobobject";
    case VT_CF:
        return "cf";
    case VT_CLSID:
        return "clsid";
    case VT_VERSIONED_STREAM:
        return "versionedstream";
    case VT_BSTR_BLOB:
        return "bstrblob";
    case VT_VECTOR:
        return "vector";
    case VT_ARRAY:
        return "array";
    case VT_BYREF:
        return "byref";
    case VT_RESERVED:
        return "reserved";
    case VT_ILLEGAL:
        return "illegal";
    default:
        break;
    }

    return "???";
}

static void print_val(std::wofstream& of, const VARIANT& v)
{
    of << "type: " << val_type(v) << " val: ";

    switch (v.vt)
    {
    case VT_I1:
    case VT_UI1:
        of << int(v.bVal);
        break;
    case VT_I2:
    case VT_UI2:
        of << v.iVal;
        break;
    case VT_I4:
    case VT_UINT:
    case VT_INT:
    case VT_UI4:
    case VT_VARIANT:
    case VT_HRESULT:
    case VT_FILETIME:
        of << v.lVal;
        break;
    case VT_BOOL:
        of << v.boolVal;
        break;
    case VT_I8:
    case VT_UI8:
    case VT_DECIMAL:
        of << v.llVal;
        break;
    case VT_CY:
        of << v.cyVal.int64;
        break;
    case VT_DATE:
        of << v.date;
        break;
    case VT_PTR:
        of << uint64_t(v.punkVal);
        break;
    case VT_SAFEARRAY:
        of << "elements: " << v.parray->cbElements << " dims: " << v.parray->cDims << " locks: " << v.parray->cLocks << " features: " << v.parray->fFeatures;
        break;
    case VT_LPSTR:
        of << v.pcVal;
        break;
    case VT_BSTR:
        of << "len: " << SysStringLen(v.bstrVal) << " val: " << v.bstrVal;
        break;
    case VT_LPWSTR:
        of << (LPWSTR)v.pcVal;
        break;
    case VT_INT_PTR:
    case VT_UINT_PTR:
        of << *v.puintVal;
        break;
    default:
        break;
    }

    of << "\n";
}

static void print(std::wofstream& of, const container& kon)
{
#if 0
    for (const auto& k : kon.props)
    {
        of << "prop: " << k.first << "\nvalue: ";
        print_val(of, k.second);
        of << "\n";
    }
#endif

    for (const auto& k : kon.childs)
    {
        of << "child: " << k.first << "\n";
        print(of, k.second);
        of << "\n";
    }

    for (const auto& k : kon.prop_in_error)
    {
        of << "prop in error: " << k.first << " hr: " << k.second << "\n";
    }

    for (const auto& k : kon.child_in_error)
    {
        of << "child in error: " << k.first << " hr: " << k.second << "\n";
    }
}

static HRESULT query_all_private(std::wofstream& of, IDxDiagProviderPrivate* pddpp)
{
    HRESULT hr = S_OK;

#if 1
    EXEC_METHOD(L"GetSystemInfo");
#endif
#if 1
    EXEC_METHOD(L"GetSystemDevices");
#endif
#if 1
    EXEC_METHOD(L"GetLogicalDisks");
#endif
#if 1
    EXEC_METHOD(L"GetDirectXFilesInfo");
    g_filesInfo = TRUE;
#endif
#if 1
    EXEC_METHOD(L"GetMusicInfo");
    g_musicInfo = TRUE;
#endif
#if 1
    EXEC_METHOD_NOFAIL(L"GetNetworkInfo", NULL); // HR=80040154 ON WINDOWS10
    g_networkInfo = SUCCEEDED(hr) ? TRUE : FALSE;
    if (!g_networkInfo)
        of << "FAIL: GetNetworkInfo: " << hr << "\n";

    hr = S_OK;
#endif
#if 1
    EXEC_METHOD(L"GetInputInfo");
    g_inputInfo = TRUE;
#endif
#if 1
    EXEC_METHOD(L"GetDirectShowInfo");
    g_dshowInfo = TRUE;
#endif
#if 1
    EXEC_METHOD_NOFAIL(L"GetEvrInfo", NULL);
    if (FAILED(hr))
        of << "Failed: GetEvrInfo: " << hr << "\n";

    hr = S_OK;
#endif
#if 1
    EXEC_METHOD_NOFAIL(L"GetVideoCaptureInfo", NULL);
    if (FAILED(hr))
        of << "Failed: GetVideoCaptureInfo: " << hr << "\n";

    hr = S_OK;
#endif
#if 1
    EXEC_METHOD_NOFAIL(L"GetDiagnosticsInfo", NULL);
    if (FAILED(hr))
        of << "Failed: GetDiagnosticsInfo: " << hr << "\n";

    hr = S_OK;
#endif
#if 1
    EXEC_METHOD_NOFAIL(L"GetMediaFoundationInfo", NULL);
    if (FAILED(hr))
        of << "Failed: GetMediaFoundationInfo: " << hr << "\n";

    hr = S_OK;
#endif
#if 1
    EXEC_METHOD_NOFAIL(L"GetUSBDisplayInfo", NULL);
    if (FAILED(hr))
        of << "Failed: GetUSBDisplayInfo: " << hr << "\n";

    hr = S_OK;
#endif
#if 1
    EXEC_METHOD_NOFAIL(L"GetHolographicInfo", NULL);
    if (FAILED(hr))
        of << "Failed: GetHolographicInfo: " << hr << "\n";

    hr = S_OK;
#endif
    return hr;
}

typedef struct _DXDIAG_RESERVED_DATA
{
    WORD wMagic;
    CHAR abReserved[6];
    BOOL bHwCkeckOnly;
} DXDIAG_RESERVED_DATA;

int main(int argc, char** argv)
{
    IDxDiagProvider* pddp = NULL;
    IDxDiagContainer* root = NULL;
    IDxDiagProviderPrivate* pddpp = NULL;
    container root_c;
    std::wofstream ofp;
    HRESULT hr;
    DXDIAG_INIT_RESERVED_DATA res = { DXDIAG_INIT_RESERVED_MAGIC, };
    DXDIAG_INIT_PARAMS params = { sizeof(DXDIAG_INIT_PARAMS), DXDIAG_DX9_SDK_VERSION, TRUE, (PVOID)&res };
    
    if (argc > 1)
    {
        if (argv[1][0] == 'r')
            res.bUsePrivateInterface = TRUE;
    }

    hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (FAILED(hr))
    {
        MessageBox(nullptr, L"Cannot call CoInitialize", L"ERROR", MB_OK | MB_ICONERROR);
        goto error;
    }

    ofp.open("walker.txt");
    if (!ofp.is_open())
    {
        MessageBox(nullptr, L"Cannot create output", L"ERROR", MB_OK | MB_ICONERROR);
        goto error;
    }

    ofp << "DXDIAG TEST\n";

    /* Initialize the DxDiag COM instances. */
    hr = CoCreateInstance(CLSID_DxDiagProvider, NULL, CLSCTX_INPROC_SERVER,
        IID_IDxDiagProvider, (void**)&pddp);
    if (FAILED(hr))
    {
        std::wstring q = L"IDxDiagProvider instance creation failed with ";
        q += std::to_wstring(uint32_t(hr));
        MessageBox(nullptr, q.c_str(), L"ERROR", MB_OK | MB_ICONERROR);
        goto error;
    }

    params.bAllowWHQLChecks = TRUE;
    hr = pddp->Initialize(&params);
    if (FAILED(hr))
        goto error;

    if (res.bUsePrivateInterface)
    {
        hr = pddp->QueryInterface(IID_IDxDiagProviderPrivate, (void**)&pddpp);
        if (FAILED(hr))
        {
            std::wstring q = L"IDxDiagProviderPrivate instance creation failed with ";
            q += std::to_wstring(uint32_t(hr));
            MessageBox(nullptr, q.c_str(), L"ERROR", MB_OK | MB_ICONERROR);
            goto error;
        }

        hr = query_all_private(ofp, pddpp);
        if (FAILED(hr))
        {
            goto error;
        }
    }

    hr = pddp->GetRootContainer(&root);
    if (FAILED(hr))
        goto error;

    walk(root, root_c);
    print(ofp, root_c);

error:
    if (ofp.is_open())
        ofp.close();
    
    if (root) root->Release();
    if (pddp) pddp->Release();
    CoUninitialize();
    return 0;
}
