#include "pch.h"
#include "test.h"

void test_parent(void)
{
	IDXGIFactory* pFactory = NULL;
	IDXGIAdapter* pAdapter = NULL;
	IDXGIOutput* pOutput = NULL;
	IUnknown* pTest = NULL;

	HRESULT hr = CreateDXGIFactory(IID_IDXGIFactory, (void**)pFactory);
	HR_CHECK;

	hr = pAdapter->EnumOutputs(0, &pOutput);
	HR_CHECK; // not a warp dev

	hr = pOutput->GetParent(IID_IDXGIFactory, (void**) & pTest);
	HR_CHECK;

	pTest->Release();

	hr = pOutput->GetParent(IID_IDXGIAdapter, (void**)&pTest);
	HR_CHECK;

	pTest->Release();

	hr = pOutput->GetParent(IID_IDXGIOutput, (void**)&pTest);
	FUN_CHECK(hr == DXGI_ERROR_NOT_FOUND);

	hr = pOutput->GetParent(IID_IUnknown, (void**)&pTest);
	FUN_CHECK(hr == DXGI_ERROR_NOT_FOUND);

	hr = pOutput->GetParent(IID_IDXGIObject, (void**)&pTest);
	FUN_CHECK(hr == DXGI_ERROR_NOT_FOUND);

ss:
	if (pOutput)
		pOutput->Release();

	if (pAdapter)
		pAdapter->Release();

	if (pFactory)
		pFactory->Release();
}

void test_output(void)
{
	IDXGIFactory* pFactory = NULL;
	IDXGIAdapter* pAdapter = NULL;
	IDXGIOutput* pOutput = NULL;

	HRESULT hr = CreateDXGIFactory(IID_IDXGIFactory, (void**)&pFactory);
	HR_CHECK;

	hr = pFactory->EnumAdapters(0, &pAdapter);
	HR_CHECK;

	hr = pAdapter->EnumOutputs(0, &pOutput);
	HR_CHECK; // not a warp dev

ss:
	if (pOutput)
		pOutput->Release();

	if (pAdapter)
		pAdapter->Release();

	if (pFactory)
		pFactory->Release();
}
