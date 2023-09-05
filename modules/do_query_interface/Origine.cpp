#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>
#include <dxgi.h>
#include <d3d11.h>
#include <cstdio>
#include <crtdbg.h>
#include <tchar.h>

#undef  DEFINE_GUID
#define DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) EXTERN_C const GUID name = { l, w1, w2, { b1, b2, b3, b4, b5, b6, b7, b8 } }

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d11.lib")

/*
		-- GUIDS TO TEST --
	IDXGIDevice: [WINDOWS 10]
	- b898d4fd_b5b3_4ffc_8694_0259864ffcf8
	- d75fab3e_73b6_4fdf_a47e_f35ca18a7dbf
	- fef19e0a_40c0_472b_ae40_59ef97af3529
	- f898b024_b5c8_42cd_a14f_ac5adbf4be22
	- 3d6f7d5e_09a0_40df_9c87_586ac542c76a
	- 00000040_1bbe_4d12_afbf_8fdf7e0a87c7 [ IIRC PARENT IDXGIResource*]

	IDXGIResource: [WINDOWS10]
	- 7778752f_5de8_4589_9b5f_cabad2b25b95
	- 9b7e4a01_342c_4106_a19f_4f2704f689f0

	[ WINDOWS 7 ]
	- a8bf320a_6e96_4096_9ac7_d7630fb5d81e

	ID3D11DeviceContext:
	- GUID_ffffffff_1bbe_4d12_afbf_8fdf7e0a87c7
*/

typedef struct ITestVft
{
    BEGIN_INTERFACE

        HRESULT(STDMETHODCALLTYPE* QueryInterface)(
            IUnknown* This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */
            _COM_Outptr_  void** ppvObject);

    ULONG(STDMETHODCALLTYPE* AddRef)(
        IUnknown* This);

    ULONG(STDMETHODCALLTYPE* Release)(
        IUnknown* This);

	ULONG(STDMETHODCALLTYPE* XdMethod)();
	ULONG(STDMETHODCALLTYPE* XdMethod2)();
	ULONG(STDMETHODCALLTYPE* XdMethod3)();
	ULONG(STDMETHODCALLTYPE* XdMethod4)();
	ULONG(STDMETHODCALLTYPE* XdMethod5)();
	ULONG(STDMETHODCALLTYPE* XdMethod6)();
	ULONG(STDMETHODCALLTYPE* XdMethod7)();

    END_INTERFACE
} IUnknownVtbl;


interface ITest
{
    CONST_VTBL struct ITestVft* lpVtbl;
};

static LRESULT CALLBACK Bruuuh(_In_ HWND hWnd, _In_ UINT Msg, _In_opt_ WPARAM wParam, _In_opt_ LPARAM lParam)
{
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}
  
//DEFINE_GUID(IID_TESTGUID, 0xbbfeb1e3, 0x6f00, 0x4ad0, 0xa0, 0x03, 0xdc, 0x3c, 0x98, 0xc4, 0x15, 0xe8); // adapter 0?
//DEFINE_GUID(IID_TESTGUID, 0x7abb6563, 0x02bc, 0x47c4, 0x8e, 0xf9, 0xac, 0xc4, 0x79, 0x5e, 0xdb, 0xcf); // adapter 0?
//DEFINE_GUID(IID_TESTGUID, 0x1ae9fb77, 0x7181, 0x4326, 0x8c, 0x90, 0x8e, 0xbc, 0x69, 0xf0, 0xae, 0xf8); // adapter 0?
DEFINE_GUID(IID_TESTGUID, 0x712bd56d, 0x86ff, 0x4b71,0x91, 0xe1, 0xc1, 0x3b, 0x27, 0x4f, 0xf2, 0xa3); // adapter 0?

int main()
{
	ITest* x2;

	IDXGIFactory* p;
	auto hr = CreateDXGIFactory(IID_IDXGIFactory, (void**)&p);
	if (FAILED(hr))
	{
		printf("kys\n");
		//return -5;
	}

	IDXGIAdapter* adpt;
	hr = p->EnumAdapters(0, &adpt);
	if (FAILED(hr))
	{
		printf("kys 4\n");
		return 0;
	}

	ID3D11Device* dv;
	IDXGISwapChain* sp;
	D3D_FEATURE_LEVEL fl = D3D_FEATURE_LEVEL_10_0;

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	//set buffer dimensions and format
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Width = 1024;
	swapChainDesc.BufferDesc.Height = 768;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;;

	//set refresh rate
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

	//sampling settings
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SampleDesc.Count = 1;

	//output window handle
	swapChainDesc.OutputWindow = nullptr;
	swapChainDesc.Windowed = true;

	auto hInst = (HINSTANCE)GetModuleHandle(nullptr);

	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(wcex);
	wcex.lpszClassName = _T("xdclass");
	wcex.hInstance = hInst;
	wcex.lpfnWndProc = Bruuuh;
	if (!RegisterClassEx(&wcex))
	{
		printf("kys 5 %x\n", GetLastError());
	}

	HWND hw = CreateWindow(_T("xdclass"), _T("xd"), WS_POPUP, 0, 0, 640, 480, nullptr, nullptr, hInst, nullptr);
	if (!hw)
	{
		printf("kys 6 %x\n", GetLastError());
	}

	swapChainDesc.OutputWindow = hw;

	hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, &fl, 1, D3D11_SDK_VERSION, &swapChainDesc, &sp, &dv, nullptr, nullptr);
	if (FAILED(hr))
	{
		printf("kys 2 %x\n", hr);
		//return -4;
	}

	ID3D11Texture2D* xd;
	hr = sp->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&xd);
	if (FAILED(hr))
	{
		printf("kys 3\n");
	}

	hr = adpt->QueryInterface(IID_TESTGUID, (void**)&x2);
	if (FAILED(hr))
	{
		printf("bah\n");
		//return -3;
	}

	_CrtDbgBreak();

	x2->lpVtbl->XdMethod2();

	return 0;
}