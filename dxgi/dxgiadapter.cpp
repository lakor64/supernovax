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

CDXGIAdapter::CDXGIAdapter()
{
	memset(&m_desc, 0, sizeof(m_desc));
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

#if 0 // TODO: UNCOMMENT THIS WHEN WE CAN ACTUALLY CREATE A DX10 DEVICE
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
#endif

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

	if ((Output + 1) >= m_desc.Outputs.size())
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

	m_desc.DedicatedSystemMemory = segInfo.DedicatedSystemMemorySize;
	m_desc.DedicatedVideoMemory = segInfo.DedicatedVideoMemorySize;
	m_desc.SharedSystemMemory = segInfo.SharedSystemMemorySize;

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

STDMETHODIMP CDXGIAdapter::LoadUMD(_In_ UINT ver, _Out_ HINSTANCE* inst)
{
	return S_OK;
}

STDMETHODIMP CDXGIAdapter::InstanceTrunks(_In_ UINT ver, _In_ UINT* unk, _In_ UINT unk2, _Out_ void* unk3)
{
	return S_OK;
}

STDMETHODIMP CDXGIAdapter::RetireUsage(_In_ UINT v)
{
	return S_OK;
}

STDMETHODIMP CDXGIAdapter::SetAdapterCapabilities(_In_ void* cap)
{
	return S_OK;
}

STDMETHODIMP CDXGIAdapter::GetAdapterCapabilities(_Inout_ void* cap)
{
	return S_OK;
}

STDMETHODIMP_(BOOL) CDXGIAdapter::IsWARP(void)
{
	return FALSE;
}
#endif
