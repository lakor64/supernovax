/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     GPU Adapter
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#include "pch.h"
#include "dxgiadapter.h"
#include "dxgioutput.h"
#include "utils.h"
#include "dxgithunks.h"
#include "thunkloader.h"

CDXGIAdapter::CDXGIAdapter()
{
	m_desc.Handle = NULL;
	m_desc.IsValid = false;
}

CDXGIAdapter::~CDXGIAdapter()
{
}

STDMETHODIMP CDXGIAdapter::CheckInterfaceSupport(_In_ REFGUID InterfaceName, _Out_ LARGE_INTEGER* pUMDVersion)
{
	// this function checks if the UMD driver supports the specified interface

	if (!pUMDVersion)
		return DXGI_ERROR_INVALID_CALL;

	UINT startVer = KMTUMDVERSION_DX9; // IDXGIDevice (if UMD is supported at all)
	auto isD3d10 = IsEqualIID(IID_ID3D10Device, InterfaceName);

	if (isD3d10)
		startVer = KMTUMDVERSION_DX10; // ID3D10Device (if we support DX10 or greater)

	else if (!IsEqualIID(IID_IDXGIDevice, InterfaceName))
		return DXGI_ERROR_UNSUPPORTED;

	D3DKMT_QUERYADAPTERINFO info;
	D3DKMT_UMDFILENAMEINFO umdFile;
	info.hAdapter = m_desc.Handle;
	info.PrivateDriverDataSize = sizeof(umdFile);
	info.Type = KMTQAITYPE_UMDRIVERNAME;
	info.pPrivateDriverData = &umdFile;

	for (; startVer < NUM_KMTUMDVERSIONS; startVer++)
	{
		// try to find an UMD module that supports the provided version
		// apperently (needs confirmation): some drivers can implement only DXVA2 and fail when it attempts to call DX9 version or similar

		umdFile.Version = (KMTUMDVERSION)startVer;
		auto err = NtErrorToDxgiError(_AtlModule.GetQueryAdapterInfo()(&info));

		if (SUCCEEDED(err))
			break;
		else if (err != E_INVALIDARG)
		{
			if (isD3d10)
				return err; // we do not have a d3d10 compatible driver

			// fallback to gdi32.dll if we don't have a D3D9 compatible driver
			// this is because that we might be running in XDDM mode
			GetModuleFileNameW(_AtlModule.GetGdi32(), umdFile.UmdFileName, MAX_PATH);
		}
	}

	if (isD3d10)
	{
		// we have an UMD driver that claims to DirectX 10
		// let's see if we can actually create a D3D10 device.
		// In case we can NOT create a device with D3D10, we consider that the don't support D3D10

		auto d3d = LoadLibraryW(L"d3d10.dll");
		if (!d3d)
			return DXGI_ERROR_UNSUPPORTED;

		auto d3d10cv = (D3D10CreateDevice_)GetProcAddress(d3d, "D3D10CreateDevice");

		if (!d3d10cv)
			return DXGI_ERROR_UNSUPPORTED;

		ID3D10Device* pDev;
		auto hr = d3d10cv(this, D3D10_DRIVER_TYPE_HARDWARE, nullptr, 0, D3D10_SDK_VERSION, &pDev);

		if (FAILED(hr))
			return DXGI_ERROR_UNSUPPORTED;

		pDev->Release();
	}

	auto sz = GetFileVersionInfoSizeW(umdFile.UmdFileName, nullptr);

	auto pb = new byte[sz];

	if (!pb)
		return E_OUTOFMEMORY;

	if (!GetFileVersionInfoW(umdFile.UmdFileName, 0, sz, pb))
	{
		delete[] pb;
		return DXGI_ERROR_NOT_FOUND;
	}

	VS_FIXEDFILEINFO* ver;
	UINT len = sz;
	if (!VerQueryValueW(pb, L"\\", (LPVOID*)&ver, &len))
	{
		delete[] pb;
		return DXGI_ERROR_NOT_FOUND;
	}

	pUMDVersion->HighPart = ver->dwFileVersionMS;
	pUMDVersion->LowPart = ver->dwFileVersionLS;
	delete[] pb;

	return S_OK;
}

STDMETHODIMP CDXGIAdapter::EnumOutputs(_In_ UINT Output, _COM_Outptr_ IDXGIOutput** ppOutput)
{
	if (!ppOutput)
		return DXGI_ERROR_INVALID_CALL;

	if (IsInSession0())
		return DXGI_ERROR_NOT_CURRENTLY_AVAILABLE;

	*ppOutput = nullptr;

	if ((Output + 1) > m_desc.Outputs.size())
		return DXGI_ERROR_NOT_FOUND;

	ATL::CComObject<CDXGIOutput>* op;
	HRESULT hr = ATL::CComObject<CDXGIOutput>::CreateInstance(&op);

	if (FAILED(hr))
		return hr;

	hr = op->Initialize(this, m_desc.Outputs[Output]);
	if (FAILED(hr))
	{
		delete op;
		return hr;
	}

	hr = op->QueryInterface(IID_IDXGIOutput, (void**)ppOutput);
	if (FAILED(hr))
	{
		delete op;
		return hr;
	}

	return S_OK;
}

STDMETHODIMP CDXGIAdapter::GetDesc(_Out_ DXGI_ADAPTER_DESC* pDesc)
{
	if (!pDesc)
		return DXGI_ERROR_INVALID_CALL;

	if (!m_desc.IsValid)
		GetAdapterDesc();

	pDesc->AdapterLuid = m_desc.AdapterLuid;
	pDesc->DedicatedSystemMemory = m_desc.DedicatedSystemMemory;
	pDesc->DedicatedVideoMemory = m_desc.DedicatedVideoMemory;
	pDesc->SharedSystemMemory = m_desc.SharedSystemMemory;
	wcscpy(pDesc->Description, m_desc.Description);
	pDesc->DeviceId = m_desc.DeviceId;
	pDesc->Revision = m_desc.Revision;
	pDesc->SubSysId = m_desc.SubSysId;
	pDesc->VendorId = m_desc.VendorId;

	return S_OK;
}

STDMETHODIMP CDXGIAdapter::GetUMDDeviceSize(_In_ UINT unk, _In_ UINT unk2, _In_ UINT unk3)
{
	return S_OK;
}

STDMETHODIMP CDXGIAdapter::Initialize(IDXGIFactory* parent, const DXGIAdapterDesc& desc)
{
	SetParent(parent); // keep the reference of self alive...
	m_desc = desc;
	return S_OK;
}

STDMETHODIMP_(void) CDXGIAdapter::GetAdapterDesc()
{
	D3DKMT_QUERYADAPTERINFO qa;
	D3DKMT_SEGMENTSIZEINFO segInfo;

	qa.hAdapter = m_desc.Handle;
	qa.Type = KMTQAITYPE_GETSEGMENTSIZE;
	qa.PrivateDriverDataSize = sizeof(segInfo);
	qa.pPrivateDriverData = &segInfo;

	NTSTATUS s = _AtlModule.GetQueryAdapterInfo()(&qa);

	if (NT_ERROR(s))
		return;

	m_desc.DedicatedSystemMemory = (SIZE_T)segInfo.DedicatedSystemMemorySize;
	m_desc.DedicatedVideoMemory = (SIZE_T)segInfo.DedicatedVideoMemorySize;
	m_desc.SharedSystemMemory = (SIZE_T)segInfo.SharedSystemMemorySize;

	D3DKMT_ADAPTERREGISTRYINFO reg;
	qa.Type = KMTQAITYPE_ADAPTERREGISTRYINFO;
	qa.PrivateDriverDataSize = sizeof(reg);
	qa.pPrivateDriverData = &reg;

	s = _AtlModule.GetQueryAdapterInfo()(&qa);

	if (NT_ERROR(s))
		return;


	WcsMaxCpy(reg.AdapterString, m_desc.Description, 127);

	// TODO!
#if DXGI_VERSION >= 1
	m_desc.Flags = DXGI_ADAPTER_FLAG_NONE;
#endif

#if DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8
	D3DKMT_ADAPTERTYPE at;
	qa.Type = KMTQAITYPE_ADAPTERTYPE;
	qa.PrivateDriverDataSize = sizeof(at);
	qa.pPrivateDriverData = &at;

	s = _AtlModule.GetQueryAdapterInfo()(&qa);

	if (SUCCEEDED(s))
	{
		m_desc.Flags |= at.SoftwareDevice ? DXGI_ADAPTER_FLAG_SOFTWARE : DXGI_ADAPTER_FLAG_NONE;
	}

	// TODO: Use KMTQAITYPE_WDDM_1_2_CAPS to gather GraphicsPreemptionGranularity&&ComputePreemptionGranularity

#elif DXGI_VERSION >= 2
	m_desc.GraphicsPreemptionGranularity = DXGI_GRAPHICS_PREEMPTION_DMA_BUFFER_BOUNDARY;
	m_desc.ComputePreemptionGranularity = DXGI_COMPUTE_PREEMPTION_DMA_BUFFER_BOUNDARY;
#endif

	m_desc.IsValid = true;
}

#if DXGI_VERSION >= 1
STDMETHODIMP CDXGIAdapter::GetDesc1(_Out_ DXGI_ADAPTER_DESC1* pDesc)
{
	if (!pDesc)
		return DXGI_ERROR_INVALID_CALL;

	if (!m_desc.IsValid)
		GetAdapterDesc();

	pDesc->AdapterLuid = m_desc.AdapterLuid;
	pDesc->DedicatedSystemMemory = m_desc.DedicatedSystemMemory;
	pDesc->DedicatedVideoMemory = m_desc.DedicatedVideoMemory;
	pDesc->SharedSystemMemory = m_desc.SharedSystemMemory;
	wcscpy(pDesc->Description, m_desc.Description);
	pDesc->DeviceId = m_desc.DeviceId;
	pDesc->Revision = m_desc.Revision;
	pDesc->SubSysId = m_desc.SubSysId;
	pDesc->VendorId = m_desc.VendorId;
	pDesc->Flags = m_desc.Flags;

	return S_OK;
}
#endif

#if DXGI_VERSION >= 2
STDMETHODIMP CDXGIAdapter::GetDesc2(_Out_ DXGI_ADAPTER_DESC2* pDesc)
{
	if (!pDesc)
		return DXGI_ERROR_INVALID_CALL;

	if (!m_desc.IsValid)
		GetAdapterDesc();

	pDesc->AdapterLuid = m_desc.AdapterLuid;
	pDesc->DedicatedSystemMemory = m_desc.DedicatedSystemMemory;
	pDesc->DedicatedVideoMemory = m_desc.DedicatedVideoMemory;
	pDesc->SharedSystemMemory = m_desc.SharedSystemMemory;
	wcscpy(pDesc->Description, m_desc.Description);
	pDesc->DeviceId = m_desc.DeviceId;
	pDesc->Revision = m_desc.Revision;
	pDesc->SubSysId = m_desc.SubSysId;
	pDesc->VendorId = m_desc.VendorId;
	pDesc->Flags = m_desc.Flags;
	pDesc->GraphicsPreemptionGranularity = m_desc.GraphicsPreemptionGranularity;
	pDesc->ComputePreemptionGranularity = m_desc.ComputePreemptionGranularity;

	return S_OK;
}

STDMETHODIMP CDXGIAdapter::LoadUMD(_In_ KMTUMDVERSION Version, _Out_ HINSTANCE* hDLL)
{
	if (!hDLL)
		return DXGI_ERROR_INVALID_CALL;

	*hDLL = nullptr;

	if (Version == NUM_KMTUMDVERSIONS)
		return DXGI_ERROR_INVALID_CALL;

	D3DKMT_QUERYADAPTERINFO qa;
	D3DKMT_UMDFILENAMEINFO um;
	qa.hAdapter = m_desc.Handle;
	qa.PrivateDriverDataSize = sizeof(um);
	qa.pPrivateDriverData = &um;
	qa.Type = KMTQAITYPE_UMDRIVERNAME;
	um.Version = Version;

	auto st = _AtlModule.GetQueryAdapterInfo()(&qa);
	if (NT_ERROR(st))
		return NtErrorToDxgiError(st);

	auto umd = LoadLibraryW(um.UmdFileName);
	if (!umd)
		return GetLastError(); // note: does hit return DXGI errors?

	*hDLL = umd;
	return S_OK;
}

STDMETHODIMP CDXGIAdapter::InstanceThunks(_In_ DXGI_THUNKS_VERSION Version, _In_ D3DKMT_HANDLE* Adapter, _In_ UINT ThunkSize, _Out_opt_ void* Thunks)
{
	HRESULT hr = S_OK;

	switch (Version)
	{
	default:
		return E_NOINTERFACE;

	case DXGI_THUNKS_VERSION_NONE:
		break;

	case DXGI_THUNKS_VERSION_3:
	{
		if (!Thunks)
			break;

		if (ThunkSize != sizeof(DXGI_THUNKS_V3))
			return E_POINTER;

		*((DWORD*)Thunks) = 3; // NOTE: not that great... v4 is hardcoded in w10

		hr = DXGILoadThunk(_AtlModule.GetGdi32(), (DXGI_THUNKS_V3*)Thunks);
		break;
	}

	case DXGI_THUNKS_VERSION_2:
	{
		if (!Thunks)
			break;

		if (ThunkSize != sizeof(DXGI_THUNKS_V2))
			return E_POINTER;

		*((DWORD*)Thunks) = 2; // NOTE: not that great... v4 is hardcoded in w10

		hr = DXGILoadThunk(_AtlModule.GetGdi32(), (DXGI_THUNKS_V2*)Thunks);

		break;
	}

	case DXGI_THUNKS_VERSION_1:
	{
		if (!Thunks)
			break;

		if (ThunkSize != sizeof(DXGI_THUNKS_V1))
			return E_POINTER;

		*((DWORD*)Thunks) = 1; // NOTE: not that great... v4 is hardcoded in w10

		hr = DXGILoadThunk(_AtlModule.GetGdi32(), (DXGI_THUNKS_V1*)Thunks);
		break;
	}

	case DXGI_THUNKS_VERSION_4:
	{
		if (!Thunks)
			break;

		if (ThunkSize != sizeof(DXGI_THUNKS_V4))
			return E_POINTER;

		*((DWORD*)Thunks) = 4; // NOTE: not that great... v4 is hardcoded in w10

		hr = DXGILoadThunk(_AtlModule.GetGdi32(), (DXGI_THUNKS_V4*)Thunks);
		break;
	}


	}

	if (FAILED(hr))
		return hr;

	if (Adapter)
		*Adapter = m_desc.Handle;

	return S_OK;
}

STDMETHODIMP CDXGIAdapter::RetireUsage(_In_ D3DKMT_HANDLE Adapter)
{
	return S_OK;
}

STDMETHODIMP CDXGIAdapter::SetAdapterCapabilities(_In_ DXGI_ADAPTER_CAPABILITIES* cap)
{
	return S_OK;
}

STDMETHODIMP CDXGIAdapter::GetAdapterCapabilities(_Inout_ DXGI_ADAPTER_CAPABILITIES* cap)
{
	return S_OK;
}

STDMETHODIMP_(BOOL) CDXGIAdapter::IsWARP(void)
{
	return FALSE;
}

STDMETHODIMP_(D3DDDI_VIDEO_PRESENT_SOURCE_ID) CDXGIAdapter::GetPrimaryVidPnSourceId(void)
{
	return 0;
}

STDMETHODIMP_(UINT) CDXGIAdapter::WddmVersion(void)
{
	return 0;
}

STDMETHODIMP_(BOOL) CDXGIAdapter::MismatchedVendorLda(void)
{
	return FALSE;
}

STDMETHODIMP_(BOOL) CDXGIAdapter::IsLda(void)
{
	return FALSE;
}

#endif
