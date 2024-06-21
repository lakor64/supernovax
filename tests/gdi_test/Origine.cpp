#include <Windows.h>
#include <stdio.h>
#include <d3dkmthk.h>
#include <d3dukmdt.h>

typedef NTSTATUS(NTAPI* D3DKMTOpenAdapterFromGdiDisplayName_)(_Inout_ D3DKMT_OPENADAPTERFROMGDIDISPLAYNAME* disp);
typedef NTSTATUS(NTAPI* D3DKMTCloseAdapter_)(_In_ CONST D3DKMT_CLOSEADAPTER* close);
typedef NTSTATUS(NTAPI* D3DKMTGetDisplayModeList_)(_In_ D3DKMT_GETDISPLAYMODELIST* dmList);


int main()
{
	DISPLAY_DEVICEW ddw = { 0 };
	ddw.cb = sizeof(ddw);

	if (!EnumDisplayDevicesW(nullptr, 0, &ddw, 0))
	{
		printf("kys\n");
		return 0;
	}

	DEVMODEW devMode = { 0 };
	if (!EnumDisplaySettingsW(ddw.DeviceName, ENUM_CURRENT_SETTINGS, &devMode))
	{
		printf("kys 2\n");
		return 0;
	}

	auto hm = LoadLibraryW(L"GDI32.DLL");
	if (!hm)
	{
		printf("kys 3\n");
		return 0;
	}

	auto x = (D3DKMTOpenAdapterFromGdiDisplayName_)GetProcAddress(hm, "D3DKMTOpenAdapterFromGdiDisplayName");
	if (!x)
	{
		printf("kys 4\n");
		return 0;
	}

	auto y = (D3DKMTCloseAdapter_)GetProcAddress(hm, "D3DKMTCloseAdapter");
	if (!y)
	{
		printf("kys 5\n");
		return 0;
	}

	auto z = (D3DKMTGetDisplayModeList_)GetProcAddress(hm, "D3DKMTGetDisplayModeList");
	if (!z)
	{
		printf("kys 6\n");
		return 0;
	}

	D3DKMT_OPENADAPTERFROMGDIDISPLAYNAME xg = { 0 };
	wcscpy_s(xg.DeviceName, _countof(xg.DeviceName), ddw.DeviceName);

	auto s = x(&xg);
	if (FAILED(s))
	{
		printf("kys 7\n");
		return 0;
	}

	D3DKMT_CLOSEADAPTER yg = { 0 };
	yg.hAdapter = xg.hAdapter;

	D3DKMT_GETDISPLAYMODELIST zg = { 0 };
	zg.hAdapter = xg.hAdapter;
	zg.VidPnSourceId = xg.VidPnSourceId;

	s = z(&zg);
	if (FAILED(s))
	{
		y(&yg);
		printf("kys 8\n");
		return 0;
	}

	auto dd = new D3DKMT_DISPLAYMODE[zg.ModeCount];

	if (!dd)
	{
		y(&yg);
		printf("kys 9\n");
		return 0;
	}

	zg.pModeList = dd;
	
	s = z(&zg);
	if (FAILED(s))
	{
		y(&yg);
		printf("kys 10\n");
		return 0;
	}

	y(&yg);

	for (auto i = 0u; i < zg.ModeCount; i++)
	{
		auto mm = &zg.pModeList[i];
		printf("MODE %u\n", i);
		printf("\tWidth: %u\n\tHeight: %u\n\tScanline ordering: %u"
			"\n\tRefresh rate: %u %u\n\tInt refresh rate: %u\n\t"
			"Format: %u\n\tRotation: %u\n\tFixedOutput: %u\n\tFlags:"
			"\n\t\tAdvancedScanCapable: %u   ModePruningReason: %u\n   PhysicalModeSupported: %u\n"
			"\t\tPreferredTiming: %u   RoundedFakeMode: %u   Stereo: %u   ValidatedAgainstMonitorCaps: %u\n"
			"\t\tReserved %u\n"
			, mm->Width, mm->Height, mm->ScanLineOrdering, 
			mm->RefreshRate.Denominator, mm->RefreshRate.Denominator, mm->IntegerRefreshRate
			, mm->Format, mm->DisplayOrientation, mm->DisplayFixedOutput,

		mm->Flags.AdvancedScanCapable, mm->Flags.ModePruningReason, mm->Flags.PhysicalModeSupported
			, mm->Flags.PreferredTiming, mm->Flags.RoundedFakeMode, mm->Flags.Stereo, mm->Flags.ValidatedAgainstMonitorCaps
			, mm->Flags.Reserved
		);
	}

	// ... ok ...
	return 0;
}
