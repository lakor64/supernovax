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

BOOL WINAPI DllMain(
    HINSTANCE const instance,  // handle to DLL module
    DWORD     const reason,    // reason for calling function
    LPVOID    const reserved)
{
    return TRUE;
}
