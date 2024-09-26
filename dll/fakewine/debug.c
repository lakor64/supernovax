#include <Windows.h>

#define DECLSPEC_EXPORT __declspec(dllexport)
#include "wine/debug.h"

extern unsigned char __cdecl __wine_dbg_get_channel_flags(struct __wine_debug_channel* channel)
{
    return 0;
}

extern const char* __cdecl __wine_dbg_strdup(const char* str)
{
    return _strdup(str);
}

static unsigned char g_wineput = 0;

extern int __cdecl __wine_dbg_output(const char* str)
{
    const char* title = "";
    DWORD style = MB_OK;

    switch (g_wineput)
    {
    case __WINE_DBCL_FIXME:
        title = "FIXME";
        break;
    case __WINE_DBCL_ERR:
        title = "ERR";
        style |= MB_ICONERROR;
        break;
    case __WINE_DBCL_WARN:
        title = "WARN";
        style |= MB_ICONEXCLAMATION;
        break;
    default:
        title = "TRACE";
        style |= MB_ICONINFORMATION;
        break;
    }

    MessageBoxA(NULL, str, title, style);
    return 0;
}

extern int __cdecl __wine_dbg_header(enum __wine_debug_class cls, struct __wine_debug_channel* channel,
    const char* function)
{
    if (channel->flags == __WINE_DBCL_TRACE)
        return -1;

    g_wineput = channel->flags;
    return 0;
}

ULONG DbgPrint(
    _In_ PCSTR Format,
    ...
)
{
    va_list vl;
    char buf[1024];

    va_start(vl, Format);
    vsnprintf_s(buf, _countof(buf), 1024, Format, vl);
    va_end(vl);

    __wine_dbg_output(buf);

    return 0;
}

typedef VOID(WINAPI* RtlRaiseExceptionCb)(_In_ PEXCEPTION_RECORD ExceptionRecord);
static RtlRaiseExceptionCb RTLCB = NULL;
static HMODULE NTDLL = NULL;

VOID WINAPI RtlRaiseException(
    _In_ PEXCEPTION_RECORD ExceptionRecord
)
{
    RTLCB(ExceptionRecord);
}

BOOL WINAPI DllMain(
    HINSTANCE const instance,  // handle to DLL module
    DWORD     const reason,    // reason for calling function
    LPVOID    const reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        NTDLL = LoadLibraryA("ntdll.dll");
        if (!NTDLL)
        {
            MessageBoxA(NULL, "CANNOT LOAD NTDLL.DLL", "ERR", MB_ICONERROR);
            return FALSE;
        }

        RTLCB = (RtlRaiseExceptionCb)GetProcAddress(NTDLL, "RtlRaiseException");
        if (!RTLCB)
        {
            FreeLibrary(NTDLL);
            MessageBoxA(NULL, "CANNOT LOAD RtlRaiseException", "ERR", MB_ICONERROR);
            return FALSE;
        }
    }
    else if (reason == DLL_PROCESS_DETACH)
    {
        if (NTDLL)
            FreeLibrary(NTDLL);

        NTDLL = NULL;
    }

    return TRUE;
}
