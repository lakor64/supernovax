#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>
#include <dxgi.h>
#include <d3d11.h>
#include <cstdio>
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

//DEFINE_GUID(IID_IDXGIObject,			0xaec22fb8, 0x76f3, 0x4639, 0x9b, 0xe0, 0x28, 0xeb, 0x43, 0xa6, 0x7a, 0x2e);
//DEFINE_GUID(IID_IDXGIDebugProducer,	0x9b7e4a00, 0x342c, 0x4106, 0xa1, 0x9f, 0x4f, 0x27, 0x04, 0xf6, 0x89, 0xf0);
  DEFINE_GUID(IID_IUnknownX,			0xcbe8c719, 0x71a3, 0x40ed, 0xa3, 0xad, 0xa0, 0x51, 0x61, 0xdc, 0xb8, 0x33);
//DEFINE_GUID(IID_IDXGIDeviceInternal3, 0xf74ee86f, 0x7270, 0x48e8, 0x9d, 0x63, 0x38, 0xaf, 0x75, 0xf2, 0x2d, 0x57);
//DEFINE_GUID(IID_IDXGIResourceInternal2,			0x79d2046c, 0x22ef, 0x451b, 0x9e, 0x74, 0x22, 0x45, 0xd9, 0xc7, 0x60, 0xea);
  DEFINE_GUID(IID_IUnknownZ,			0x00000040, 0x1bbe, 0x4d12, 0xaf, 0xbf, 0x8f, 0xdf, 0x7e, 0x0a, 0x87, 0xc7); // IDXGIResource*
  
  DEFINE_GUID(IID_IDXGIResourceInternal2, 0xa8bf320a, 0x6e96, 0x4096, 0x9a, 0xc7, 0xd7, 0x63, 0x0f, 0xb5, 0xd8, 0x1e);
  DEFINE_GUID(IID_IK, 0x7778752f, 0x5de8, 0x4589, 0x9b, 0x5f, 0xca, 0xba, 0xd2, 0xb2, 0x5b, 0x95);

  DEFINE_GUID(IID_IUnknownY, 0xcbe8c719, 0x71a3, 0x40ed, 0xa3, 0xad, 0xa0, 0x51, 0x61, 0xdc, 0xb8, 0x33);

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

#if 0
	hr = p->QueryInterface(IID_IDXGIUnknownX, (void**)&x2); // IDXGIDEBUGPRODUCER
	if (FAILED(hr))
	{
		printf("bah\n");
		p->Release();
		//return -2;
	}
#endif
	p->Release();

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

	hr = xd->QueryInterface(IID_IK, (void**)&x2);
	if (FAILED(hr))
	{
		printf("bah\n");
		//return -3;
	}

	printf("pls debug me senpai\n");
	((void(__stdcall*)(int))(x2->lpVtbl))(400);

	return 0;
}