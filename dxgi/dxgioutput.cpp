/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     Monitor output
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#include "pch.h"
#include "dxgioutput.h"
#include "dxgiadapter.h"
#include "utils.h"

CDXGIOutput::CDXGIOutput()
{
	memset(&m_desc, 0, sizeof(m_desc));
}

STDMETHODIMP CDXGIOutput::FindClosestMatchingMode(_In_ const DXGI_MODE_DESC* pModeToMatch, _Out_ DXGI_MODE_DESC* pClosestMatch, _In_opt_ IUnknown* pConcernedDevice)
{
	if (!pModeToMatch || !pClosestMatch)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGIOutput::GetDesc(_Out_ DXGI_OUTPUT_DESC* pDesc)
{
	if (!pDesc)
		return DXGI_ERROR_INVALID_CALL;

	if (!m_desc.IsValid)
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
	if (!pNumModes)
		return DXGI_ERROR_INVALID_CALL;

	D3DKMT_GETDISPLAYMODELIST dml;

	dml.hAdapter = m_desc.Handle;
	dml.VidPnSourceId = m_desc.VidPn;
	dml.ModeCount = 0;
	dml.pModeList = nullptr;

	auto status = _AtlModule.GetDisplayModeList()(&dml);
	if (NT_ERROR(status))
		return _AtlModule.GetNtStatusToDosError()(status);

	dml.pModeList = (D3DKMT_DISPLAYMODE*)new byte[dml.ModeCount * 0x2C]; // wait for header fix...
	status = _AtlModule.GetDisplayModeList()(&dml);
	if (NT_ERROR(status))
		return _AtlModule.GetNtStatusToDosError()(status);

	auto iteSize = 0U;

	for (auto i = 0U; i < dml.ModeCount; i++)
	{
		D3DKMT_DISPLAYMODE* y = (D3DKMT_DISPLAYMODE*)(((byte*)dml.pModeList) + (i * 0x2C)); // wait for header fix...

		// there is no format without alpha, so convert those into alpha based formats
		if (y->Format == D3DDDIFMT_X8R8G8B8)
			y->Format = D3DDDIFMT_A8R8G8B8;
		else if (y->Format == D3DDDIFMT_X1R5G5B5)
			y->Format = D3DDDIFMT_A1R5G5B5;
		else if (y->Format == D3DDDIFMT_X4R4G4B4)
			y->Format = D3DDDIFMT_A4R4G4B4;
		else if (y->Format == D3DDDIFMT_X8B8G8R8)
			y->Format = D3DDDIFMT_A8B8G8R8;

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
			D3DKMT_DISPLAYMODE* y = (D3DKMT_DISPLAYMODE*)(((byte*)dml.pModeList) + (i * 0x2C)); // wait for header fix...

			if (CheckIfDDIFormatIsOk(y, EnumFormat, Flags))
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

	return E_NOTIMPL;
}

STDMETHODIMP CDXGIOutput::GetFrameStatistics(_Out_ DXGI_FRAME_STATISTICS* pStats)
{
	if (!pStats)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGIOutput::GetGammaControl(_Out_ DXGI_GAMMA_CONTROL* pArray)
{
	if (!pArray)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGIOutput::GetGammaControlCapabilities(_Out_ DXGI_GAMMA_CONTROL_CAPABILITIES* pGammaCaps)
{
	if (!pGammaCaps)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}

STDMETHODIMP_(void) CDXGIOutput::ReleaseOwnership(void)
{

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

	return E_NOTIMPL;
}

STDMETHODIMP CDXGIOutput::TakeOwnership(_In_ IUnknown* pDevice, _In_ BOOL Exclusive)
{
	if (!pDevice)
		return DXGI_ERROR_INVALID_CALL;

	return E_NOTIMPL;
}

STDMETHODIMP CDXGIOutput::WaitForVBlank(void)
{
	D3DKMT_WAITFORVERTICALBLANKEVENT v;
	v.hAdapter = m_desc.Handle;
	v.VidPnSourceId = m_desc.VidPn;
	v.hDevice = NULL;

	return _AtlModule.GetNtStatusToDosError()(_AtlModule.GetWaitForVBlank()(&v));
}

STDMETHODIMP CDXGIOutput::Initialize(CDXGIAdapter* adapter, DXGIOutputDescBasic& dsc)
{
	m_pParent = adapter;
	m_desc.Handle = dsc.Handle;
	m_desc.VidPn = dsc.VidPn;
	memcpy(m_desc.DeviceName, dsc.DeviceName, sizeof(dsc.DeviceName));
	return S_OK;
}

STDMETHODIMP_(bool) CDXGIOutput::CheckIfDDIFormatIsOk(D3DKMT_DISPLAYMODE* ddi, DXGI_FORMAT fmt, UINT flags)
{
	if (ddi->Format != DXGI_MFMapDXGIFormatToDX9Format(fmt))
		return false;

	if (!ddi->Flags.ValidatedAgainstMonitorCaps)
		return false;

	if (ddi->DisplayOrientation != D3DDDI_ROTATION_IDENTITY)
		return false;

	// for some reason I don't see 59hz refresh in DXGI
	if (ddi->RefreshRate.Denominator != 1)
		return false;

	// note: I don't know if this is ok!
	if (ddi->DisplayFixedOutput != 0)
		return false;

	// TODO: DXGI_ENUM_MODES_INTERLACED
	// TODO: DXGI_ENUM_MODES_SCALING

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8) && (_WIN32_WINNT >= 0x601)
	if (ddi->Flags.Stereo && !(flags & DXGI_ENUM_MODES_STEREO))
		return false;

	// TODO: DXGI_ENUM_MODES_DISABLED_STEREO
#endif

	return true;
}

static BOOL CALLBACK EnumOutput(HMONITOR hm, HDC hdc, LPRECT rect, LPARAM user)
{
	DXGIOutputDesc* pDesc = (DXGIOutputDesc*)user;
	MONITORINFOEXW mi;
	mi.cbSize = sizeof(mi);

	if (GetMonitorInfoW(hm, &mi))
	{
		if (wcscmp(mi.szDevice, pDesc->DeviceName) == 0)
		{
			pDesc->DesktopCoordinates = mi.rcMonitor;
			pDesc->Monitor = hm;
			pDesc->AttachedToDesktop = FALSE;
			return FALSE;
		}
	}

	return TRUE;
}

STDMETHODIMP_(void) CDXGIOutput::GetOutputDesc()
{
	EnumDisplayMonitors(nullptr, nullptr, EnumOutput, (LPARAM)&m_desc);
	DEVMODEW dm;

	if (EnumDisplaySettingsW(m_desc.DeviceName, ENUM_CURRENT_SETTINGS, &dm))
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

	m_desc.IsValid = true;
}
