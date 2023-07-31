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
	DXGI_OUTPUT_DESC desc;

	HRESULT hr = CreateDXGIFactory(IID_IDXGIFactory, (void**)&pFactory);
	HR_CHECK;

	hr = pFactory->EnumAdapters(0, &pAdapter);
	HR_CHECK;

	hr = pAdapter->EnumOutputs(0, &pOutput);
	HR_CHECK; // not a warp dev


	hr = pOutput->GetDesc(&desc);
	HR_CHECK;

	printf("OUTPUT DESC:\n"
		"\tDevice name: %S\n"
		"\tDesktop coord: %ld %ld %ld %ld\n"
		"\tAttached to desktop: %d\n"
		"\tRotation: %d\n"
		"\tMonitor handle: %llx\n",
		desc.DeviceName,
		desc.DesktopCoordinates.top, desc.DesktopCoordinates.left,
		desc.DesktopCoordinates.bottom, desc.DesktopCoordinates.right,
		desc.AttachedToDesktop, desc.Rotation, desc.Monitor
	);

#if 0
	DXGI_GAMMA_CONTROL gg;
	hr = pOutput->GetGammaControl(&gg);
	HR_CHECK;

	printf("GAMME CONTROL:\n"
		"\tScale: %f %f %f\n"
		"\tOffset: %f %f %f\n",
		gg.Scale.Red, gg.Scale.Green, gg.Scale.Blue,
		gg.Offset.Red, gg.Offset.Green, gg.Offset.Blue
	);

	for (auto i = 0; i < 1025; i++)
	{
		printf("\tGamme curve %d: %f %f %f\n",
			gg.GammaCurve[i].Red, gg.GammaCurve[i].Green, gg.GammaCurve[i].Blue);
	}

	DXGI_GAMMA_CONTROL_CAPABILITIES cc;
	hr = pOutput->GetGammaControlCapabilities(&cc);
	HR_CHECK;

	printf("GAMMA CONTROL CAPABILITIES:\n"
		"\tScale offset supported: %d\n"
		"\tMax converted value: %f\n"
		"\tMin converted value: %f\n"
		"\tNum gamma control pointers: %u\n",
		cc.ScaleAndOffsetSupported, cc.MaxConvertedValue,
		cc.MinConvertedValue, cc.NumGammaControlPoints
	);

	for (auto i = 0; i < 1025; i++)
	{
		printf("Control point pos %d: %f\n", cc.ControlPointPositions[i]);
	}
#endif

	UINT nn;
	hr = pOutput->GetDisplayModeList(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_ENUM_MODES_INTERLACED | DXGI_ENUM_MODES_SCALING,
		&nn, NULL);
	HR_CHECK;

	DXGI_MODE_DESC* dx = new DXGI_MODE_DESC[nn];
	FUN_CHECK(dx != nullptr);

	hr = pOutput->GetDisplayModeList(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_ENUM_MODES_INTERLACED | DXGI_ENUM_MODES_SCALING,
		&nn, dx);
	HR_CHECK;

	for (auto i = 0U; i < nn; i++)
	{
		printf("DXGI MODE %d\n", i);
		printf("\tWidth: %u\n"
			"\tHeight: %u\n"
			"\tRefresh rate: %u %u\n"
			"\tFormat: %x\n"
			"\tScanline order: %u\n"
			"\tScaling: %u\n",
			dx[i].Width, dx[i].Height,
			dx[i].RefreshRate.Denominator, dx[i].RefreshRate.Numerator,
			dx[i].Format, dx[i].ScanlineOrdering, dx[i].Scaling
		);
	}

	delete[] dx;

	hr = pOutput->WaitForVBlank();
	HR_CHECK;

ss:
	if (pOutput)
		pOutput->Release();

	if (pAdapter)
		pAdapter->Release();

	if (pFactory)
		pFactory->Release();
}
