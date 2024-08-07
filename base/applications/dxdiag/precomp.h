#ifndef PRECOMP_H__
#define PRECOMP_H__

#define WIN32_LEAN_AND_MEAN
#define COBJMACROS

#ifdef __PFF__
#define DECLSPEC_EXPORT __declspec(dllimport)
#endif

#include <stdarg.h>
#include <windows.h>
#include <assert.h>
#include <stdio.h>
#include <dxdiag.h>

#include "resource.h"
#include "wine/debug.h"
#include "dxdiag_private.h"

#ifdef _DEBUG
#include <crtdbg.h>
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(A) (sizeof(A)/sizeof(*(A)))
#endif

#ifdef __REACTOS__
typedef struct _DXDIAG_CONTEXT
{
    HWND* hDisplayWnd;
    HWND* hSoundWnd;
    HWND hMainDialog;
    HWND hTabCtrl;
    HWND hDialogs[5];
    DWORD NumDisplayAdapter;
    DWORD NumSoundAdapter;
}DXDIAG_CONTEXT, * PDXDIAG_CONTEXT;

extern void output_dxdiag_gui(struct dxdiag_information* dxdiag_info);
#endif

/* globals */
extern HINSTANCE hInstance;

#endif /* PRECOMP_H__ */
