#define D3D_DEBUG_INFO 1

#include <dxgi.h>
#include <d3d11.h>
#include <stdio.h>
#include <crtdbg.h>
#include <d3dkmthk.h>

typedef NTSTATUS(NTAPI* D3DKMTOpenAdapterFromGdiDisplayName_)(_Inout_ D3DKMT_OPENADAPTERFROMGDIDISPLAYNAME* disp);
typedef NTSTATUS(NTAPI* D3DKMTQueryAdapterInfo_)(_Inout_ CONST D3DKMT_QUERYADAPTERINFO* info);


#if 0
#define oh_dbg() _CrtDbgBreak()
#else
#define oh_dbg()
#endif

#if 0
#define main_0 main
#else
#define main_1 main
#endif


#define oh_no(cond) { \
	if (!(cond)) { \
		printf("Failure of %S:%u (WIN32 ERROR %x, LAST HRESULT %x)\n", __FILEW__, __LINE__, GetLastError(), hr); \
		oh_dbg(); \
	} \
}

#define oh_no_hr() oh_no(SUCCEEDED(hr))

int main_0()
{
	HRESULT hr = S_OK;
	DISPLAY_DEVICEW dd = { 0 };
	dd.cb = sizeof(dd);
	
	auto x = EnumDisplayDevicesW(nullptr, 0, &dd, 0);
	oh_no(x != FALSE);

	D3DKMT_OPENADAPTERFROMGDIDISPLAYNAME gdi = { 0 };

	memcpy(gdi.DeviceName, dd.DeviceName, sizeof(dd.DeviceName));

	// 1. Get DXGI.DLL procedure
	auto hDxgi = LoadLibraryW(L"D3D11REF.DLL");
	oh_no(hDxgi != nullptr);

	auto p = (D3DKMTOpenAdapterFromGdiDisplayName_)GetProcAddress(hDxgi, "D3DKMTOpenAdapterFromGdiDisplayName");
	oh_no(p != nullptr);

	hr = p(&gdi);
	oh_no_hr();

	D3DKMT_QUERYADAPTERINFO qa;
	D3DKMT_SEGMENTSIZEINFO segInfo;

	qa.hAdapter = gdi.hAdapter;
	qa.Type = KMTQAITYPE_GETSEGMENTSIZE;
	qa.PrivateDriverDataSize = sizeof(segInfo);
	qa.pPrivateDriverData = &segInfo;

	auto p2 = (D3DKMTQueryAdapterInfo_)GetProcAddress(hDxgi, "D3DKMTQueryAdapterInfo");
	oh_no(p2 != nullptr);

	NTSTATUS s = p2(&qa);
	oh_no(s == 0);

	D3DKMT_UMDFILENAMEINFO umdFile;
	qa.PrivateDriverDataSize = sizeof(umdFile);
	qa.Type = KMTQAITYPE_UMDRIVERNAME;
	qa.pPrivateDriverData = &umdFile;
	umdFile.Version = (KMTUMDVERSION)KMTUMDVERSION_DX10;

	s = p2(&qa);
	oh_no(s == 0);

	D3DKMT_ADAPTERREGISTRYINFO reg = { 0 };
	qa.Type = KMTQAITYPE_ADAPTERREGISTRYINFO;
	qa.PrivateDriverDataSize = sizeof(reg);
	qa.pPrivateDriverData = &reg;

	s = p2(&qa);
	oh_no(s == 0);

	GUID g = { 0 };
	qa.PrivateDriverDataSize = sizeof(g);
	qa.pPrivateDriverData = &g;
	qa.Type = KMTQAITYPE_ADAPTERGUID;
	s = p2(&qa);
	oh_no(s == 0);

	oh_dbg();


	return 0;
}

int main_1()
{
	HRESULT hr = S_OK;
	IDXGIFactory1* pFactory = nullptr;
	IDXGIAdapter* pAdapter = nullptr;
	IDXGIAdapter1* pAdapter1 = nullptr;
	IDXGIOutput* pOutput = nullptr;
	DXGI_ADAPTER_DESC pDesc;
	DXGI_ADAPTER_DESC1 pDesc1;
	LARGE_INTEGER dwUmdV;
	char _log_[1024];
	FILE* fpx;
	fopen_s(&fpx, "report_sasa.txt", "w");

	// 1. Get DXGI.DLL procedure
	auto hDxgi = LoadLibraryW(L"D3D11REF.DLL");
	oh_no(hDxgi != nullptr);

	// is DXGI.DLL a software adapter??
	auto check = GetProcAddress(hDxgi, "OpenAdapter10");
	oh_no(check != nullptr); // Windows 8+

	hr = CreateDXGIFactory1(__uuidof(pFactory), (void**) & pFactory);
	oh_no_hr();

	hr = pFactory->CreateSoftwareAdapter(hDxgi, &pAdapter);
	oh_no_hr();

	hr = pAdapter->GetDesc(&pDesc);
	oh_no_hr();
	oh_dbg();

	sprintf_s(_log_, _countof(_log_), "ADAPTER DESC:\n\tDescription: %S\n\tVendorID: %u\n\tDeviceID: %u\n\tSubSysId: %u\n\tRevision: %u\n\tDedicatedVideoMemory: %zu\n\tDedicatedSystemMemory: %zu\n\tSharedSystemMemory: %zu\n\tAdapterLuid: %x %x\n"
		, pDesc.Description, pDesc.VendorId, pDesc.DeviceId, pDesc.SubSysId, pDesc.Revision, pDesc.DedicatedVideoMemory, pDesc.DedicatedSystemMemory, pDesc.SharedSystemMemory, pDesc.AdapterLuid.HighPart, pDesc.AdapterLuid.LowPart);
	fwrite(_log_, strlen(_log_), 1, fpx);

	hr = pAdapter->CheckInterfaceSupport(__uuidof(IDXGIDevice), &dwUmdV);
	oh_no_hr();
	oh_dbg();

#if 0 // not supported
	hr = pAdapter->CheckInterfaceSupport(__uuidof(ID3D10Device), &dwUmdV);
	oh_no_hr();
	oh_dbg();
#endif

	hr = pAdapter->QueryInterface(&pAdapter1);
	oh_no_hr();

	hr = pAdapter1->GetDesc1(&pDesc1);
	oh_no_hr();
	oh_dbg();

	sprintf_s(_log_, _countof(_log_), "ADAPTER DESC1:\n\tDescription: %S\n\tVendorID: %u\n\tDeviceID: %u\n\tSubSysId: %u\n\tRevision: %u\n\tDedicatedVideoMemory: %zu\n\tDedicatedSystemMemory: %zu\n\tSharedSystemMemory: %zu\n\tAdapterLuid: %x %x\n\tFlags: %u\n"
		, pDesc1.Description, pDesc1.VendorId, pDesc1.DeviceId, pDesc1.SubSysId, pDesc1.Revision, pDesc1.DedicatedVideoMemory, pDesc1.DedicatedSystemMemory, pDesc1.SharedSystemMemory, pDesc1.AdapterLuid.HighPart, pDesc1.AdapterLuid.LowPart, pDesc1.Flags);
	fwrite(_log_, strlen(_log_), 1, fpx);


	for (auto i = 0U; i < 16; i++)
	{
		DXGI_OUTPUT_DESC poDesc;

#if 0
		DXGI_FRAME_STATISTICS fs;
#endif

		hr = pAdapter->EnumOutputs(i, &pOutput);
		oh_no_hr();

		if (!pOutput)
			continue;

		hr = pOutput->GetDesc(&poDesc);
		oh_no_hr();
		oh_dbg();

		sprintf_s(_log_, _countof(_log_), "OUTPUT %d\n\tDeviceName: %S\n\tDesktopCoords: l:%u t:%u r:%u b:%u\n\tAttachedToDesktop: %u\n\tRotation: %u\n\tHMONITOR: %p\n"
			,i, poDesc.DeviceName, poDesc.DesktopCoordinates.left, poDesc.DesktopCoordinates.top, poDesc.DesktopCoordinates.right, poDesc.DesktopCoordinates.bottom, poDesc.AttachedToDesktop, poDesc.Rotation, poDesc.Monitor);
		fwrite(_log_, strlen(_log_), 1, fpx);

#if 0
		hr = pOutput->GetFrameStatistics(&fs);
		oh_no_hr();
		oh_dbg();
#endif

		UINT nm;
		hr = pOutput->GetDisplayModeList(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_ENUM_MODES_INTERLACED | DXGI_ENUM_MODES_SCALING, &nm, nullptr);
		oh_no_hr();

		auto md = new DXGI_MODE_DESC[nm];
		oh_no(md != nullptr);
		
		hr = pOutput->GetDisplayModeList(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_ENUM_MODES_INTERLACED | DXGI_ENUM_MODES_SCALING, &nm, md);
		oh_no_hr();



		for (auto i = 0U; i < nm; i++)
		{
			printf("DXGI MODE %d\n", i);
			printf("\tWidth: %u\n"
				"\tHeight: %u\n"
				"\tRefresh rate: %u %u\n"
				"\tFormat: %x\n"
				"\tScanline order: %u\n"
				"\tScaling: %u\n",
				md[i].Width, md[i].Height,
				md[i].RefreshRate.Denominator, md[i].RefreshRate.Numerator,
				md[i].Format, md[i].ScanlineOrdering, md[i].Scaling
			);

			sprintf_s(_log_, _countof(_log_), "\tDXGI MODE %d\n\t\tWidth: %u\n"
				"\t\tHeight: %u\n"
				"\t\tRefresh rate: %u %u\n"
				"\t\tFormat: %x\n"
				"\t\tScanline order: %u\n"
				"\t\tScaling: %u\n",
				i,
				md[i].Width, md[i].Height,
				md[i].RefreshRate.Denominator, md[i].RefreshRate.Numerator,
				md[i].Format, md[i].ScanlineOrdering, md[i].Scaling
			);
			fwrite(_log_, strlen(_log_), 1, fpx);
		}
		oh_dbg();

		delete[] md;
		pOutput->Release();
	}

	fclose(fpx);
	pAdapter1->Release();
	pAdapter->Release();
	pFactory->Release();
	FreeLibrary(hDxgi);

	return 0;
}
