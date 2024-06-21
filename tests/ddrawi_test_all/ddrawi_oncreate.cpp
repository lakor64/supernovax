#include "pch.h"

void ddrawi_oncreate(void)
{
	LPDIRECTDRAW lpDD;
	LPDDRAWI_DIRECTDRAW_INT lpDDINT;
	auto pid = GetCurrentProcessId();

	auto x = DirectDrawCreate(nullptr, &lpDD, (IUnknown*) & lpDDINT);
	ASSERT(x == CLASS_E_NOAGGREGATION);

	x = DirectDrawCreate(nullptr, &lpDD, nullptr);
	CHECKHR(x);

	lpDDINT = (LPDDRAWI_DIRECTDRAW_INT)lpDD;

	ASSERT(lpDDINT->lpLcl->dwProcessId == pid);
	ASSERT(lpDDINT->dwIntRefCnt == 1);
	ASSERT(lpDDINT->lpLcl->dwLocalRefCnt == 1);

	LPDIRECTDRAW7 lpDD7;
	LPDDRAWI_DIRECTDRAW_INT lpDDINT2;
	x = lpDD->QueryInterface(IID_IDirectDraw7, (void**) & lpDD7);
	CHECKHR(x);

	lpDDINT2 = (LPDDRAWI_DIRECTDRAW_INT)lpDD7;

	ASSERT(lpDDINT2->lpLink == lpDDINT);
	ASSERT(lpDDINT2->dwIntRefCnt == 1);
	ASSERT(lpDDINT->lpLcl->dwLocalRefCnt == 2);

	// DirectDraw link test

	LPDIRECTDRAW4 lpDD4;
	LPDDRAWI_DIRECTDRAW_INT lpDD4INT;
	x = lpDD->QueryInterface(IID_IDirectDraw4, (void**)&lpDD4);
	CHECKHR(x);

	lpDD4INT = (LPDDRAWI_DIRECTDRAW_INT)lpDD4;

	ASSERT(lpDD4INT->lpLink == lpDDINT2);
	ASSERT(lpDD4INT->dwIntRefCnt == 1);
	ASSERT(lpDDINT->lpLcl->dwLocalRefCnt == 3);

	printf("INT1:\n");
	print_ddrawi(lpDDINT);
	printf("INT2:\n");
	print_ddrawi(lpDDINT2);
	printf("INT3:\n");
	print_ddrawi(lpDD4INT);

	lpDD4->Release();
	ASSERT(lpDDINT->lpLcl->dwLocalRefCnt == 2);

	lpDD7->Release();
	ASSERT(lpDDINT->lpLcl->dwLocalRefCnt == 1);

	lpDD->Release();
}

void ddrawi_coop(void)
{
	LPDIRECTDRAW7 lpdd7;
	auto hr = DirectDrawCreate(nullptr, (LPDIRECTDRAW*) & lpdd7, nullptr);
	CHECKHR(hr);

	ASSERT(lpdd7->Initialize(nullptr) == DDERR_ALREADYINITIALIZED);

	hr = lpdd7->SetCooperativeLevel(nullptr, DDSCL_NORMAL);
	CHECKHR(hr);

	ASSERT(((LPDDRAWI_DIRECTDRAW_INT)lpdd7)->lpLcl->dwLocalFlags & DDRAWILCL_SETCOOPCALLED);
	print_ddrawi(lpdd7);

	lpdd7->Release();
}
