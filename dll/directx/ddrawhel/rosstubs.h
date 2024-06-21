/*
https://github.com/reactos/reactos/blob/40955b447cc225a9df1f03980f6ccaa5cfbd0573/dll/directx/ddraw/rosdraw.h
*/
#pragma once

#include <cstdlib>
#include <cstdio>
#include <cstring>

/*********** Macros ***********/

/*
   use this macro to close
   down the debugger text complete
   no debuging at all, it will
   crash ms debugger in VS
*/

//#define DX_WINDBG_trace()
//#define DX_STUB
//#define DX_STUB_DD_OK return DD_OK;
//#define DX_STUB_str(x)
//#define DX_WINDBG_trace_res


/*
   Use this macro if you want debug in visual studio or
   if you have a program to look at the _INT struct from
   ReactOS ddraw.dll or ms ddraw.dll, so you can see what
   value ms are being setup.

   This macro will create allot warnings and can not be help when you compile
*/


//#define DX_WINDBG_trace()
//#define DX_STUB
//#define DX_STUB_DD_OK return DD_OK;
//#define DX_STUB_str(x) printf("%s",x);
//#define DX_WINDBG_trace_res

/*
   use this if want doing a trace from a program
   like a game and ReactOS ddraw.dll in windows
   so you can figout what going wrong and what
   api are being call or if it hel or is it hal

   This marco does not create warnings when you compile
*/

#define DX_STUB \
{ \
	static BOOL firstcall = TRUE; \
	if (firstcall) \
	{ \
		char buffer[1024]; \
		sprintf_s ( buffer, _countof(buffer), "Function %s is not implemented yet (%s:%d)\n", __FUNCTION__,__FILE__,__LINE__ ); \
		OutputDebugStringA(buffer); \
		firstcall = FALSE; \
	} \
} \
	return DDERR_UNSUPPORTED;



#define DX_STUB_DD_OK \
{ \
	static BOOL firstcall = TRUE; \
	if (firstcall) \
	{ \
		char buffer[1024]; \
		sprintf_s ( buffer, _countof(buffer), "Function %s is not implemented yet (%s:%d)\n", __FUNCTION__,__FILE__,__LINE__ ); \
		OutputDebugStringA(buffer); \
		firstcall = FALSE; \
	} \
} \
	return DD_OK;


#if 1
#define DX_STUB_str(x) \
    { \
        char buffer[1024]; \
        sprintf_s ( buffer, _countof(buffer),  "Function %s %s (%s:%d)\n", __FUNCTION__,x,__FILE__,__LINE__ ); \
        OutputDebugStringA(buffer); \
    }


#define DX_WINDBG_trace() \
        static BOOL firstcallx = TRUE; \
        if (firstcallx) \
        { \
            char buffer[1024]; \
            sprintf_s ( buffer, _countof(buffer),  "Enter Function %s (%s:%d)\n", __FUNCTION__,__FILE__,__LINE__ ); \
            OutputDebugStringA(buffer); \
            firstcallx = TRUE; \
        }


#define DX_WINDBG_trace_res(width,height,bpp, freq) \
    static BOOL firstcallxx = TRUE; \
    if (firstcallxx) \
    { \
        char buffer[1024]; \
        sprintf_s ( buffer, _countof(buffer),  "Setmode have been req width=%ld, height=%ld bpp=%ld freq = %ld\n",width,height,bpp, freq); \
        OutputDebugStringA(buffer); \
        firstcallxx = TRUE; \
    }
#else
#define DX_WINDBG_trace() //
#define DX_WINDBG_trace_res(width,height,bpp, freq) \\

#define DX_STUB_str(x) //

#endif
