#pragma once

#define WIN32_LEAN_AND_MEAN 1
#define STRICT 1
#include <Windows.h>
#include <ddraw.h>
#include <ddrawi.h>
#include <assert.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cwchar>
#include <tchar.h>

#define CHECKHR(x) 	if (FAILED(x)) {\
	printf("Fail: HR=%x File:%s Line:%zu\n", x, __FILE__, __LINE__); \
	return; \
}

#define ASSERT(x) if (!(x)) {\
	printf("Assert!!! File: %s Line: %zu\n", __FILE__, __LINE__); \
	return; \
}

void _print_ddrawi(LPDIRECTDRAW dd);
#define print_ddrawi(x) _print_ddrawi((LPDIRECTDRAW)x)

void ddrawi_oncreate(void);
void ddrawi_coop(void);
void drawi_coop_hwnd_normal(void);
