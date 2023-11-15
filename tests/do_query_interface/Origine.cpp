#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>
#include <dxgi.h>
#include <d3d11.h>
#include <cstdio>
#include <crtdbg.h>
#include <tchar.h>

#include <dxgidwm.h>
#include <dxgipartner.h>
#include <dxgixaml.h>
#include <dxgiternl.h>

#undef  DEFINE_GUID
#define DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) EXTERN_C const GUID name = { l, w1, w2, { b1, b2, b3, b4, b5, b6, b7, b8 } }

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d11.lib")

/*
	*** GUIDS TO TEST ***
	* 
	Windows Vista RTM
		IDXGISwapChain
			9b7e4a01_342c_4106_a19f_4f2704f689f0

		ID3D10Device
			0fee0f52_6b6f_4715_bde8_d43eade9c8e6
			5a92ae4f_81fa_4cac_a1d8_ae479ac581cd
			00000040_342d_4106_a19f_4f2704f689f0

		ID3D10Resource
			00000040_342d_4106_a19f_4f2704f689f0

		ID3D10SurfaceView
			00000040_342d_4106_a19f_4f2704f689f0

		CDeviceChild??
			9b7e4a03_342c_4106_a19f_4f2704f689f0
			9b7e4a01_342c_4106_a19f_4f2704f689f0

	Windows 7 SP1
		IDXGISwapChain
			8f0f30db_446a_4282_9fa2_28f75c1f39ad (to fix)
			b02d7a1a_05e0_4a71_8ef4_5c5bbf475086 (to fix)

		IDXGIAdapter
			712bd56d_86ff_4b71_91e1_c13b274ff2a2 (to fix, we don't know the name...)
*/

typedef struct ITestVtbl
{
public:
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

	ULONG (STDMETHODCALLTYPE* XdMethod1)(void);
	ULONG(STDMETHODCALLTYPE* XdMethod2)(void);
	ULONG(STDMETHODCALLTYPE* XdMethod3)(void);
	ULONG(STDMETHODCALLTYPE* XdMethod4)(void);
	ULONG(STDMETHODCALLTYPE* XdMethod5)(void);
	ULONG(STDMETHODCALLTYPE* XdMethod6)(void);
	ULONG(STDMETHODCALLTYPE* XdMethod7)(void);
	END_INTERFACE
} ITestVtbl;

interface ITest
{
	CONST_VTBL struct ITestVtbl* lpVtbl;
};

static LRESULT CALLBACK Bruuuh(_In_ HWND hWnd, _In_ UINT Msg, _In_opt_ WPARAM wParam, _In_opt_ LPARAM lParam)
{
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

DEFINE_GUID(IID_TESTGUID, 0x712bd56d, 0x86ff, 0x4b71, 0x91, 0xe1, 0xc1, 0x3b, 0x27, 0x4f, 0xf2, 0xa2);

int main()
{
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

	IDXGIOutput* out;
	hr = adpt->EnumOutputs(0, &out);
	if (FAILED(hr))
	{
		printf("kys 7\n");
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

	ITest* x2;
	hr = adpt->QueryInterface(IID_TESTGUID, (void**)&x2);
	//hr = p->QueryInterface(__uuidof(IDXGIFactoryPartner), (void**)&x2);
	if (FAILED(hr))
	{
		printf("bah\n");
		//return -3;
	}

	// 1. CloseKernelHandle (?)

	auto vtbl = x2->lpVtbl;

	printf("continue\n");

	auto _1 = vtbl->XdMethod1;
	auto _2 = vtbl->XdMethod2;
	auto _3 = vtbl->XdMethod3;
	auto _4 = vtbl->XdMethod4;
	auto _5 = vtbl->XdMethod5;
	auto _6 = vtbl->XdMethod6;
	auto _7 = vtbl->XdMethod7;

	_CrtDbgBreak();


	_3();

	return 0;
}