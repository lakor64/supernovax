#include "pch.h"

static LRESULT WINAPI WinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void drawi_coop_hwnd_normal(void)
{
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_VREDRAW | CS_HREDRAW;
	wcex.lpfnWndProc = WinProc;
	wcex.hInstance = (HINSTANCE)GetModuleHandle(nullptr);
	wcex.lpszClassName = _T("DRAWI_TEST_CLASSNAME");

	ATOM atm = RegisterClassEx(&wcex);
	ASSERT(atm != 0);

	HWND hwnd = CreateWindow(MAKEINTATOM(atm), _T("TEST"), WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, nullptr, nullptr, wcex.hInstance, nullptr);
	ASSERT(hwnd != nullptr);

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	LPDIRECTDRAW7 lpdd;
	auto hr = DirectDrawCreate(nullptr, (LPDIRECTDRAW*) & lpdd, nullptr);
	CHECKHR(hr);

	hr = lpdd->SetCooperativeLevel(hwnd, DDSCL_NORMAL);
	CHECKHR(hr);

	LPDDRAWI_DIRECTDRAW_INT i = (LPDDRAWI_DIRECTDRAW_INT)lpdd;

	printf("HWND: %x\n", hwnd);
	print_ddrawi(i);

	hr = lpdd->SetCooperativeLevel(hwnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
	CHECKHR(hr);

	printf("HWND: %x\n", hwnd);
	print_ddrawi(i);

	lpdd->Release();
	DestroyWindow(hwnd);
	UnregisterClass(MAKEINTATOM(atm), wcex.hInstance);
}
