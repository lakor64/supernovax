#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>
#include <dxdiag.h>
#include <tchar.h>
#include <ShellAPI.h>
#include <dxdiag_private.h>
#include <iostream>
#include <string>

#define EXEC_METHOD(m, vt) \
    hr = pddpp->ExecMethod(m, vt); \
    if (FAILED(hr)) { \
        std::wstring q = L"ExecMethod " m L" failed with "; \
        q += std::to_wstring(uint32_t(hr)); \
        MessageBoxW(nullptr, q.c_str(), L"ERROR", MB_OK | MB_ICONERROR); \
        goto error; \
    }

#define RUN_DXDIAG ShellExecuteW(nullptr, L"open", L"dxdiag.exe", nullptr, nullptr, SW_SHOW)

#define YOO_BOX MessageBox(nullptr, _T("Press OK to continue"), _T("yoo"), MB_OK)

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

static void print_val(const VARIANT& v)
{
    std::cout << "type: " << val_type(v) << " val: ";

    switch (v.vt)
    {
    case VT_I1:
    case VT_UI1:
        std::cout << int(v.bVal);
        break;
    case VT_I2:
    case VT_UI2:
        std::cout << v.iVal;
        break;
    case VT_I4:
    case VT_UINT:
    case VT_INT:
    case VT_UI4:
    case VT_VARIANT:
    case VT_HRESULT:
    case VT_FILETIME:
        std::cout << v.lVal;
        break;
    case VT_BOOL:
        std::cout << v.boolVal;
        break;
    case VT_I8:
    case VT_UI8:
    case VT_DECIMAL:
        std::cout << v.llVal;
        break;
    case VT_CY:
        std::cout << v.cyVal.int64;
        break;
    case VT_DATE:
        std::cout << v.date;
        break;
    case VT_PTR:
        std::cout << uint64_t(v.punkVal);
        break;
    case VT_SAFEARRAY:
        std::cout << "elements: " << v.parray->cbElements << " dims: " << v.parray->cDims << " locks: " << v.parray->cLocks << " features: " << v.parray->fFeatures;
        break;
    case VT_LPSTR:
        std::cout << v.pcVal;
        break;
    case VT_BSTR:
        std::cout << "len: " << SysStringLen(v.bstrVal) << " val: " << v.bstrVal;
        break;
    case VT_LPWSTR:
        std::cout << (LPWSTR)v.pcVal;
        break;
    case VT_INT_PTR:
    case VT_UINT_PTR:
        std::cout << *v.puintVal;
        break;
    default:
        break;
    }

    std::cout << "\n";
}

static ATOM g_atm = 0;
static HWND g_hwnd = nullptr;
static HINSTANCE g_hi = nullptr;

static LRESULT WINAPI MYWNDPROC(_In_ HWND hw, _In_ UINT Msg, _In_ WPARAM wp, _In_ LPARAM lp)
{
    switch (Msg)
    {
    case WM_CREATE:
        break;
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hw, Msg, wp, lp);
    }

    return FALSE;
}

static bool mk_thing(void)
{
    WNDCLASSEX wcex = { 0 };
    wcex.cbSize = sizeof(wcex);
    wcex.hInstance = GetModuleHandle(nullptr);
    wcex.lpszClassName = L"CIAOOO";
    wcex.lpfnWndProc = MYWNDPROC;
    g_atm = RegisterClassEx(&wcex);
    if (!g_atm)
    {
        MessageBoxA(nullptr, "REGISTERCLASSEX FAIL :(", "ERROR", MB_OK | MB_ICONERROR);
        return false;
    }

    g_hi = wcex.hInstance;

    g_hwnd = CreateWindow(MAKEINTATOM(g_atm), L"XDDDDD", WS_SYSMENU | WS_CAPTION, 0, 0, 800, 600, nullptr, nullptr, wcex.hInstance, nullptr);
    if (!g_hwnd)
    {
        MessageBoxA(nullptr, "CreateWindow FAIL :(", "ERROR", MB_OK | MB_ICONERROR);
        UnregisterClass(MAKEINTATOM(g_atm), wcex.hInstance);
        return false;
    }

    ShowWindow(g_hwnd, SW_HIDE);
    UpdateWindow(g_hwnd);

    return true;
}

static void del_thing(void)
{
    if (g_hwnd)
    {
        DestroyWindow(g_hwnd);
        g_hwnd = nullptr;
    }

    if (g_atm)
    {
        UnregisterClass(MAKEINTATOM(g_atm), g_hi);
        g_atm = 0;
    }

    g_hi = nullptr;
}

static void while_thing(void)
{
    MSG msg = { 0 };

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (msg.message == WM_QUIT)
            break;

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

int main(int argc, char** argv)
{
    IDxDiagProvider* pddp = NULL;
    IDxDiagContainer* root = NULL;
    IDxDiagProviderPrivate* pddpp = NULL;
    HRESULT hr;
    DXDIAG_INIT_RESERVED_DATA res = { DXDIAG_INIT_RESERVED_MAGIC, };
    DXDIAG_INIT_PARAMS params = { sizeof(DXDIAG_INIT_PARAMS), DXDIAG_DX9_SDK_VERSION, TRUE, &res };
    VARIANT v = { 0 };

    res.bUsePrivateInterface = TRUE;

    hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (FAILED(hr))
    {
        MessageBox(nullptr, L"Cannot call CoInitialize", L"ERROR", MB_OK | MB_ICONERROR);
        goto error;
    }

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

    hr = pddp->QueryInterface(IID_IDxDiagProviderPrivate, (void**)&pddpp);

    if (FAILED(hr))
    {
        std::wstring q = L"IDxDiagProviderPrivate instance creation failed with ";
        q += std::to_wstring(uint32_t(hr));
        MessageBox(nullptr, q.c_str(), L"ERROR", MB_OK | MB_ICONERROR);
        goto error;
    }


    if (!mk_thing())
        goto error;

    printf("pls verify with dxdiag.exe plz plz plz plz\n");
    
    /*
        Can't pass NULL to:
        SetDDrawHWAccel (E_INVALIDARG)
        SetD3DHWAccel (E_INVALIDARG)
        SetAGPHWAccel (E_INVALIDARG)
        SetSoundHWAccel (E_INVALIDARG)
        RunNetVoiceWizard (Doesn't fail but doesn't do anything, so it always expects a VARIANT PTR even if the variant value is NULL)
        TestDD (E_INVALIDARG)
    */

#if 0 // all verified, everything works according to plan
    printf("We disable DDRAW ACCEL\n");
    v.vt = VT_BOOL;
    v.boolVal = FALSE;
    EXEC_METHOD(L"SetDDrawHWAccel", &v); // can't pass NULL
    EXEC_METHOD(L"IsDDHWAccelEnabled", &v); // should be S_FALSE
    printf("IsDDHWAccelEnabled HR=%lu\n", hr);
    RUN_DXDIAG;
    YOO_BOX;
    printf("We enable DDRAW ACCEL\n");
    v.boolVal = TRUE;
    EXEC_METHOD(L"SetDDrawHWAccel", &v);
    EXEC_METHOD(L"IsDDHWAccelEnabled", &v); // should be S_OK
    printf("IsDDHWAccelEnabled HR=%lu\n", hr);
    RUN_DXDIAG;
    YOO_BOX;

    printf("We disable D3D ACCEL\n");
    v.vt = VT_BOOL;
    v.boolVal = FALSE;
    EXEC_METHOD(L"SetD3DHWAccel", &v);
    EXEC_METHOD(L"IsD3DHWAccelEnabled", &v); // should be S_FALSE
    printf("IsD3DHWAccelEnabled HR=%lu\n", hr);
    RUN_DXDIAG;
    YOO_BOX;
    printf("We enable DDRAW ACCEL\n");
    v.boolVal = TRUE;
    EXEC_METHOD(L"SetD3DHWAccel", &v);
    EXEC_METHOD(L"IsD3DHWAccelEnabled", &v); // should be S_OK
    printf("IsD3DHWAccelEnabled HR=%lu\n", hr);
    RUN_DXDIAG;
    YOO_BOX;

    printf("We disable AGP ACCEL\n");
    v.vt = VT_BOOL;
    v.boolVal = FALSE;
    EXEC_METHOD(L"SetAGPHWAccel", &v);
    EXEC_METHOD(L"IsAGPHWAccelEnabled", &v); // should be S_FALSE
    printf("IsAGPHWAccelEnabled HR=%lu\n", hr);
    RUN_DXDIAG;
    YOO_BOX;
    printf("We enable AGP ACCEL\n");
    v.boolVal = TRUE;
    EXEC_METHOD(L"SetAGPHWAccel", &v);
    EXEC_METHOD(L"IsAGPHWAccelEnabled", &v); // should be S_OK
    printf("IsAGPHWAccelEnabled HR=%lu\n", hr);
    RUN_DXDIAG;
    YOO_BOX;
#endif

#if 0 // verified, it's all ok
    printf("We now execute RunNetVoiceWizard\n");
    v.vt = VT_BYREF;

    // works both way!!
    //v.puintVal = (UINT*)g_hwnd;
    v.puintVal = NULL;
    // ---

    EXEC_METHOD(L"RunNetVoiceWizard", &v);
    printf("RunNetVoiceWizard returned\n");
#endif

    printf("We now change sound hw accel\n");
    ULONG x = 0;
    v.vt = VT_UINT_PTR;
    v.pulVal = &x;
    EXEC_METHOD(L"SetSoundHWAccel", &v);
    RUN_DXDIAG;
    YOO_BOX;


    printf("We now execute TestDD\n");
    v.vt = VT_UI8;
    v.ullVal = 0;
    EXEC_METHOD(L"TestDD", NULL);
    printf("TestDD returned\n");
    while_thing();

error:
    del_thing();

    if (root) root->Release();
    if (pddp) pddp->Release();
    CoUninitialize();
    return 0;
}
