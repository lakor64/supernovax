#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>
#include <dxgi.h>
#include <d3d10.h>
#include <cstdio>
#include <crtdbg.h>
#include <tchar.h>

#undef  DEFINE_GUID
#define DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) EXTERN_C const GUID name = { l, w1, w2, { b1, b2, b3, b4, b5, b6, b7, b8 } }

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d10.lib")

/*
	*** GUIDS TO TEST ***
	* 
	Windows Vista RTM
		IDXGISwapChain
			9b7e4a01_342c_4106_a19f_4f2704f689f0

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
			void** ppvObject);

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

DEFINE_GUID(IID_TESTGUID, 0x00000040,0x342d,0x4106,0xa1,0x9f,0x4f,0x27,0x04,0xf6,0x89,0xf0);

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

	ID3D10Device* dv;
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

	hr = D3D10CreateDeviceAndSwapChain(nullptr, D3D10_DRIVER_TYPE_WARP, nullptr, 0, D3D10_SDK_VERSION, &swapChainDesc, &sp, &dv);
	if (FAILED(hr))
	{
		printf("kys 2 %x\n", hr);
		//return -4;
	}

	ID3D10Texture2D* xd;
	hr = sp->GetBuffer(0, __uuidof(ID3D10Texture2D), (void**)&xd);
	if (FAILED(hr))
	{
		printf("kys 3\n");
	}

	ITest* x2;
	hr = dv->QueryInterface(IID_TESTGUID, (void**)&x2);
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