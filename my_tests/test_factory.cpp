#include "pch.h"
#include "test.h"

void test_factory(void)
{
	IDXGIFactory* pFactory = NULL;
	IDXGIFactory* pFactory2 = NULL;
	IDXGIFactory1* pFactory3 = NULL;
	IDXGIFactory* pFactory4 = NULL;
	IDXGIAdapter* pAdapter = NULL;

	HRESULT hr = CreateDXGIFactory(IID_MyFakeData, (void**) & pFactory);
	FUN_CHECK(hr == E_NOINTERFACE);

	hr = CreateDXGIFactory(IID_IDXGIFactory, (void**)&pFactory);
	HR_CHECK;

	pFactory2 = pFactory;

	hr = CreateDXGIFactory(IID_IDXGIFactory, (void**)&pFactory);
	HR_CHECK;

	hr = CreateDXGIFactory(IID_IDXGIFactory1, (void**)&pFactory3);
	FUN_CHECK(hr == E_NOINTERFACE);

	hr = CreateDXGIFactory1(IID_IDXGIFactory, (void**)&pFactory4);
	HR_CHECK;
	pFactory4->Release();

	hr = CreateDXGIFactory1(IID_IDXGIFactory1, (void**)&pFactory3);
	pFactory3->Release();

	FUN_CHECK(pFactory2->Release() == 0);


	hr = pFactory->EnumAdapters(0, NULL);
	FUN_CHECK(hr == DXGI_ERROR_INVALID_CALL);

	hr = pFactory->EnumAdapters(0, &pAdapter);
	HR_CHECK;
	FUN_CHECK(pAdapter != NULL);

	pAdapter->Release();
	hr = pFactory->EnumAdapters(10, &pAdapter);
	FUN_CHECK(hr == DXGI_ERROR_NOT_FOUND);

ss:
	if (pAdapter)
		pAdapter->Release();

	if (pFactory)
		pFactory->Release();
}
