#include "pch.h"
#include "test.h"

void test_adapter(void)
{
	IDXGIFactory* pFactory = NULL;
	IDXGIAdapter* pAdapter = NULL;
	IDXGIOutput* pOutput = NULL;
	DXGI_ADAPTER_DESC desc;
	LARGE_INTEGER v;

	HRESULT hr = CreateDXGIFactory(IID_IDXGIFactory, (void**)&pFactory);
	HR_CHECK;

	hr = pFactory->EnumAdapters(0, &pAdapter);
	HR_CHECK;

	pAdapter->CheckInterfaceSupport(__uuidof(IDXGIDevice), &v);
	HR_CHECK;
	printf("Interface IDXGIDevice: %u %u\n", v.HighPart, v.LowPart);

	hr = pAdapter->CheckInterfaceSupport(__uuidof(ID3D10Device), &v);
	HR_CHECK;
	printf("Interface ID3D10Device: %u %u\n", v.HighPart, v.LowPart);

	hr = pAdapter->CheckInterfaceSupport(__uuidof(ID3D11Device), &v);
	FUN_CHECK(hr == DXGI_ERROR_UNSUPPORTED);

	hr = pAdapter->GetDesc(&desc);
	HR_CHECK;

	printf("ADAPTER DESC:\n"
			"\tDescription: %S\n"
			"\tVendorID: %u\n"
			"\tDeviceID: %u\n"
			"\tSubSysID: %u\n"
			"\tRevision: %u\n"
			"\tDedicated vmem: %zu\n"
			"\tDedicated sysmem: %zu\n"
			"\tShared sysmem: %zu\n"
			"\tAdapterLUID HI:%x LO:%x\n"
		, desc.Description, desc.VendorId, desc.DeviceId,
		desc.SubSysId, desc.Revision, desc.DedicatedVideoMemory, desc.DedicatedSystemMemory,
		desc.SharedSystemMemory, desc.AdapterLuid.HighPart, desc.AdapterLuid.LowPart);

	hr = pAdapter->EnumOutputs(0, &pOutput);
	HR_CHECK; // not a warp dev
	pOutput->Release();

	hr = pAdapter->EnumOutputs(999, &pOutput);
	FUN_CHECK(hr == DXGI_ERROR_NOT_FOUND);
	pOutput = NULL;

ss:
	if (pOutput)
		pOutput->Release();

	if (pAdapter)
		pAdapter->Release();

	if (pFactory)
		pFactory->Release();
}
