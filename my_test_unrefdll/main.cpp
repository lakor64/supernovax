#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>
#include <dxgi.h>
#include <stdio.h>
#include <assert.h>

#define DEFINE_GUID2(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) EXTERN_C const GUID DECLSPEC_SELECTANY name = { l, w1, w2, { b1, b2, b3, b4, b5, b6, b7, b8 } }
DEFINE_GUID2(IID_IDXGIFactory, 0x7b7166ec, 0x21c7, 0x44ae, 0xb2, 0x1a, 0xc9, 0xae, 0x32, 0x1a, 0xe3, 0x69);

#define FUN_ASSERT \
		printf("function check fail! (hr: %x file: %S line: %llu)\n", hr, __FILEW__, (ULONGLONG)__LINE__); \
		assert(false); \
		goto ss;

#define HR_CHECK if (!SUCCEEDED(hr)) { FUN_ASSERT; }
#define FUN_CHECK(x) if (!(x)) { FUN_ASSERT; }

typedef HRESULT(WINAPI* CreateDXGIFactory_)(REFIID, void**);

int main()
{
	IDXGIFactory* pFactory = nullptr;
	IDXGIAdapter* adp = nullptr;
	IDXGIOutput* opt = nullptr;
	HRESULT hr = S_OK;
	CreateDXGIFactory_ f;
	auto xd = LoadLibraryW(L"dxgi.dll");
	FUN_CHECK(xd != nullptr);

	f = (CreateDXGIFactory_)GetProcAddress(xd, "CreateDXGIFactory");
	FUN_CHECK(f != nullptr);

	hr = f(IID_IDXGIFactory, (void**)&pFactory);
	HR_CHECK;


	hr = pFactory->EnumAdapters(0, &adp);
	HR_CHECK;

	FreeLibrary(xd);
	// It is expected to crash after FreeLibrary!
	
	hr = adp->EnumOutputs(0, &opt);
	HR_CHECK;

	adp->Release();
	hr = pFactory->EnumAdapters(0, &adp);
	HR_CHECK;

ss:
	if (opt)
		opt->Release();

	if (adp)
		adp->Release();

	if (pFactory)
		pFactory->Release();

	return 0;
}
