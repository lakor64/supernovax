/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     Monitor handling
 * COPYRIGHT:   Copyright 2023 Christian Rendina <pizzaiolo100@proton.me>
 */

#include "pch.h"
#include "dxgioutput.h"
#include "dxgiadapter.h"
#include "utils.h"

CDXGIOutput::CDXGIOutput()
	: m_hDll(nullptr)
	, m_bValid(false)
	, D3DKMTGetDisplayModeList(nullptr)
	, D3DKMTGetDeviceState(nullptr)
	, D3DKMTWaitForVerticalBlankEvent(nullptr)
	, m_hHandle(D3DGPU_NULL)
	, m_VidPn(D3DDDI_ID_UNINITIALIZED)
{
	ZeroMemory(&m_desc, sizeof(m_desc));
}

STDMETHODIMP CDXGIOutput::FindClosestMatchingMode(_In_ const DXGI_MODE_DESC* pModeToMatch, _Out_ DXGI_MODE_DESC* pClosestMatch, _In_opt_ IUnknown* pConcernedDevice)
{
	if (!pModeToMatch || !pClosestMatch)
		return DXGI_ERROR_INVALID_CALL;

	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGIOutput::FindClosestMatchingMode", "DEBUG", MB_OK);
	return E_NOTIMPL;
}

STDMETHODIMP CDXGIOutput::GetDesc(_Out_ DXGI_OUTPUT_DESC* pDesc)
{
	if (!pDesc)
		return DXGI_ERROR_INVALID_CALL;

	if (!m_bValid)
		GetOutputDesc();

	pDesc->AttachedToDesktop = m_desc.AttachedToDesktop;
	pDesc->DesktopCoordinates = m_desc.DesktopCoordinates;
	pDesc->Monitor = m_desc.Monitor;
	pDesc->Rotation = m_desc.Rotation;
	memcpy(pDesc->DeviceName, m_desc.DeviceName, sizeof(m_desc.DeviceName));

	return S_OK;
}

STDMETHODIMP CDXGIOutput::GetDisplayModeList(_In_ DXGI_FORMAT EnumFormat, _In_ UINT Flags, _In_opt_ UINT* pNumModes, _Out_opt_ DXGI_MODE_DESC* pDesc)
{
	// NOTE: This function DOES NOT match 1:1 Windows DXGI but it's complete enough to mostly work

	if (!pNumModes)
		return DXGI_ERROR_INVALID_CALL;

	D3DKMT_GETDISPLAYMODELIST dml;

	dml.hAdapter = m_hHandle;
	dml.VidPnSourceId = m_VidPn;
	dml.ModeCount = 0;
	dml.pModeList = nullptr;

	auto status = D3DKMTGetDisplayModeList(&dml);
	if (NT_ERROR(status))
		return NtErrorToDxgiError(status);

	dml.pModeList = new D3DKMT_DISPLAYMODE[dml.ModeCount];
	status = D3DKMTGetDisplayModeList(&dml);
	if (NT_ERROR(status))
		return NtErrorToDxgiError(status);

	auto iteSize = 0U;

	for (auto i = 0U; i < dml.ModeCount; i++)
	{
		auto& y = dml.pModeList[i];

		// there is no format without alpha, so convert those into alpha based formats
		if (y.Format == D3DDDIFMT_X8R8G8B8)
			y.Format = D3DDDIFMT_A8R8G8B8;
		else if (y.Format == D3DDDIFMT_X1R5G5B5)
			y.Format = D3DDDIFMT_A1R5G5B5;
		else if (y.Format == D3DDDIFMT_X4R4G4B4)
			y.Format = D3DDDIFMT_A4R4G4B4;
		else if (y.Format == D3DDDIFMT_X8B8G8R8)
			y.Format = D3DDDIFMT_A8B8G8R8;

		if (CheckIfDDIFormatIsOk(y, EnumFormat, Flags))
		{
			iteSize++;
		}
	}

	if (iteSize > *pNumModes && pDesc)
	{
		delete[] dml.pModeList;
		return DXGI_ERROR_MORE_DATA;
	}

	*pNumModes = iteSize;
	
	if (pDesc)
	{
		iteSize = 0;

		for (auto i = 0U; i < dml.ModeCount; i++)
		{
			D3DKMT_DISPLAYMODE* y = (D3DKMT_DISPLAYMODE*)&dml.pModeList[i];

			if (CheckIfDDIFormatIsOk(*y, EnumFormat, Flags))
			{
				pDesc[iteSize].Width = y->Width;
				pDesc[iteSize].Height = y->Height;
				pDesc[iteSize].RefreshRate.Numerator = y->RefreshRate.Numerator;
				pDesc[iteSize].RefreshRate.Denominator = y->RefreshRate.Denominator;
				pDesc[iteSize].ScanlineOrdering = (DXGI_MODE_SCANLINE_ORDER)y->ScanLineOrdering;
				pDesc[iteSize].Scaling = DXGI_MODE_SCALING_UNSPECIFIED; // TODO: figure out how to handle/read scaling
				pDesc[iteSize].Format = EnumFormat;

				iteSize++;
			}
		}
	}

	delete[] dml.pModeList;
	return S_OK;
}

STDMETHODIMP CDXGIOutput::GetDisplaySurfaceData(_In_ IDXGISurface* pDestination)
{
	if (!pDestination)
		return DXGI_ERROR_INVALID_CALL;

	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGIOutput::GetDisplaySurfaceData", "DEBUG", MB_OK);
	return E_NOTIMPL;
}

STDMETHODIMP CDXGIOutput::GetFrameStatistics(_Out_ DXGI_FRAME_STATISTICS* pStats)
{
	if (!pStats)
		return DXGI_ERROR_INVALID_CALL;

	D3DKMT_GETDEVICESTATE ds;
	ds.StateType = D3DKMT_DEVICESTATE_PRESENT;
	ds.hDevice = m_hHandle;
	ds.PresentState.VidPnSourceId = m_VidPn;

	auto status = D3DKMTGetDeviceState(&ds);
	if (NT_ERROR(status))
		return NtErrorToDxgiError(status);

	auto es = ds.PresentState.PresentStats;

	pStats->PresentCount = es.PresentCount;
	pStats->PresentRefreshCount = es.PresentRefreshCount;
	pStats->SyncRefreshCount = es.SyncRefreshCount;
	pStats->SyncGPUTime = es.SyncGPUTime;
	pStats->SyncQPCTime = es.SyncQPCTime;

	return S_OK;
}

STDMETHODIMP CDXGIOutput::GetGammaControl(_Out_ DXGI_GAMMA_CONTROL* pArray)
{
	if (!pArray)
		return DXGI_ERROR_INVALID_CALL;

	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGIOutput::GetGammaControl", "DEBUG", MB_OK);
	return E_NOTIMPL;
}

STDMETHODIMP CDXGIOutput::GetGammaControlCapabilities(_Out_ DXGI_GAMMA_CONTROL_CAPABILITIES* pGammaCaps)
{
	if (!pGammaCaps)
		return DXGI_ERROR_INVALID_CALL;

	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGIOutput::GetGammaControlCapabilities", "DEBUG", MB_OK);
	return E_NOTIMPL;
}

STDMETHODIMP_(void) CDXGIOutput::ReleaseOwnership(void)
{
	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGIOutput::ReleaseOwnership", "DEBUG", MB_OK);
}

STDMETHODIMP CDXGIOutput::SetDisplaySurface(_In_ IDXGISurface* pScanoutSurface)
{
	if (!pScanoutSurface)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGIOutput::SetGammaControl(_In_ const DXGI_GAMMA_CONTROL* pArray)
{
	if (!pArray)
		return DXGI_ERROR_INVALID_CALL;

	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGIOutput::SetGammaControl", "DEBUG", MB_OK);
	return E_NOTIMPL;
}

STDMETHODIMP CDXGIOutput::TakeOwnership(_In_ IUnknown* pDevice, _In_ BOOL Exclusive)
{
	if (!pDevice)
		return DXGI_ERROR_INVALID_CALL;

	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGIOutput::TakeOwnership", "DEBUG", MB_OK);
	return E_NOTIMPL;
}

STDMETHODIMP CDXGIOutput::WaitForVBlank(void)
{
	D3DKMT_WAITFORVERTICALBLANKEVENT v;
	v.hAdapter = m_hHandle;
	v.VidPnSourceId = m_VidPn;
	v.hDevice = NULL;

	return NtErrorToDxgiError(D3DKMTWaitForVerticalBlankEvent(&v));
}

STDMETHODIMP CDXGIOutput::Initialize(_In_ HMODULE hSoft, _In_ CDXGIAdapter* adapter, const DXGIOutputInfo& dsc)
{
	SetParent((IDXGIAdapter*)adapter);
	m_hDll = hSoft;
	m_hHandle = dsc.AdapterHandle;
	m_VidPn = dsc.VidPn;
	StringCchCopyN(m_desc.DeviceName, 32, dsc.DeviceName, 32);
	return LoadD3DKMTApi();
}

STDMETHODIMP_(bool) CDXGIOutput::CheckIfDDIFormatIsOk(const D3DKMT_DISPLAYMODE& ddi, DXGI_FORMAT fmt, UINT flags)
{
	if (ddi.Format != DXGI_MFMapDXGIFormatToDX9Format(fmt))
		return false;

	if (!ddi.Flags.ValidatedAgainstMonitorCaps)
		return false;

	if (ddi.DisplayOrientation != D3DDDI_ROTATION_IDENTITY)
		return false;

	// for some reason I don't see 59hz refresh in DXGI
	if (ddi.RefreshRate.Denominator != 1)
		return false;

	// TODO: I don't know if this is ok!
	if (ddi.DisplayFixedOutput != 0)
		return false;

	// TODO: DXGI_ENUM_MODES_INTERLACED
	// TODO: DXGI_ENUM_MODES_SCALING

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8) && !_WINSDK_7
	if (ddi.Flags.Stereo && !(flags & DXGI_ENUM_MODES_STEREO))
		return false;

	// TODO: DXGI_ENUM_MODES_DISABLED_STEREO
#endif

	return true;
}

static BOOL CALLBACK EnumOutput(HMONITOR hm, HDC hdc, LPRECT rect, LPARAM user)
{
	const auto pOutput = (CDXGIOutput*)user;
	MONITORINFOEXW mi;
	mi.cbSize = sizeof(mi);

	if (GetMonitorInfoW(hm, (LPMONITORINFO) & mi))
	{
		if (wcscmp(mi.szDevice, pOutput->GetDeviceName()) == 0)
		{
			// note: this is true because dxgifactory only enum active devices at the moment
			pOutput->SetMonitorInfo(mi.rcMonitor, hm, TRUE);
			return FALSE;
		}
	}

	return TRUE;
}

STDMETHODIMP_(void) CDXGIOutput::GetOutputDesc()
{
	EnumDisplayMonitors(nullptr, nullptr, EnumOutput, (LPARAM)this);
	DEVMODEW dm = { 0 };
	dm.dmSize = sizeof(dm);

	if (EnumDisplaySettingsExW(m_desc.DeviceName, ENUM_CURRENT_SETTINGS, &dm, EDS_ROTATEDMODE))
	{
		if (dm.dmFields & DM_DISPLAYORIENTATION)
		{
			switch (dm.dmDisplayOrientation)
			{
			case DMDO_90:
				m_desc.Rotation = DXGI_MODE_ROTATION_ROTATE90;
				break;
			case DMDO_180:
				m_desc.Rotation = DXGI_MODE_ROTATION_ROTATE180;
				break;
			case DMDO_270:
				m_desc.Rotation = DXGI_MODE_ROTATION_ROTATE270;
				break;

			default:
				m_desc.Rotation = DXGI_MODE_ROTATION_IDENTITY;
				break;
			}
		}
	}

	m_bValid = true;
}

STDMETHODIMP CDXGIOutput::LoadD3DKMTApi()
{
	D3DKMTGetDisplayModeList = (D3DKMTGetDisplayModeList_)GetProcAddress(m_hDll, "D3DKMTGetDisplayModeList");
	D3DKMTGetDeviceState = (D3DKMTGetDeviceState_)GetProcAddress(m_hDll, "D3DKMTGetDeviceState");
	D3DKMTWaitForVerticalBlankEvent = (D3DKMTWaitForVerticalBlankEvent_)GetProcAddress(m_hDll, "D3DKMTWaitForVerticalBlankEvent");

	if (!D3DKMTWaitForVerticalBlankEvent || !D3DKMTGetDeviceState || !D3DKMTGetDisplayModeList)
		return DXGI_ERROR_UNSUPPORTED;

	return S_OK;
}

#if DXGI_VERSION >= 2
STDMETHODIMP CDXGIOutput::GetDisplayModeList1(_In_ DXGI_FORMAT EnumFormat, _In_ UINT Flags, _Inout_  UINT* pNumModes, _Out_writes_to_opt_(*pNumModes, *pNumModes)  DXGI_MODE_DESC1* pDesc)
{
	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGIOutput::GetDisplayModeList1", "DEBUG", MB_OK);
	return DXGI_ERROR_UNSUPPORTED;
}

STDMETHODIMP CDXGIOutput::FindClosestMatchingMode1(_In_  const DXGI_MODE_DESC1* pModeToMatch, _Out_  DXGI_MODE_DESC1* pClosestMatch, _In_opt_  IUnknown* pConcernedDevice)
{
	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGIOutput::FindClosestMatchingMode1", "DEBUG", MB_OK);
	return DXGI_ERROR_UNSUPPORTED;
}

STDMETHODIMP CDXGIOutput::GetDisplaySurfaceData1(_In_  IDXGIResource* pDestination)
{
	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGIOutput::GetDisplaySurfaceData1", "DEBUG", MB_OK);
	return DXGI_ERROR_UNSUPPORTED;
}

STDMETHODIMP CDXGIOutput::DuplicateOutput(_In_ IUnknown* pDevice, _COM_Outptr_  IDXGIOutputDuplication** ppOutputDuplication)
{
	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGIOutput::DuplicateOutput", "DEBUG", MB_OK);
	return DXGI_ERROR_UNSUPPORTED;
}
#endif
