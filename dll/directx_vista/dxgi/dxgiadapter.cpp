/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     GPU Adapter
 * COPYRIGHT:   Copyright 2023 Christian Rendina <pizzaiolo100@proton.me>
 */

#include "pch.h"
#include "dxgiadapter.h"
#include "dxgioutput.h"
#include "utils.h"
#include "dxgithunks.h"
#include "thunkloader.h"

CDXGIAdapter::CDXGIAdapter() 
	: m_hDll(nullptr)
	, m_bValid(false)
	, m_hHandle(D3DGPU_NULL)
	, D3DKMTQueryAdapterInfo(nullptr)
	, m_modType(DXGIAdapterModuleType::Invalid)
{
	ZeroMemory(&m_desc, sizeof(m_desc));
}

CDXGIAdapter::~CDXGIAdapter()
{
	if (m_modType == DXGIAdapterModuleType::Warp || m_modType == DXGIAdapterModuleType::Software)
	{
		D3DKMT_CLOSEADAPTER ca;
		D3DKMTCloseAdapter_ close = (D3DKMTCloseAdapter_)GetProcAddress(m_hDll, "D3DKMTCloseAdapter");

		if (!close)
			return;

		// close opened d3dkmt handles here
		for (auto& p : m_vOutputs)
		{
			if (p.AdapterHandle == D3DGPU_NULL)
				continue;

			ca.hAdapter = p.AdapterHandle;
			close(&ca);
		}
	}
}

// this function checks if the UMD driver supports the specified interface
STDMETHODIMP CDXGIAdapter::CheckInterfaceSupport(_In_ REFGUID InterfaceName, _Out_ LARGE_INTEGER* pUMDVersion)
{
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
	info.hAdapter = m_hHandle;
	info.PrivateDriverDataSize = sizeof(umdFile);
	info.Type = KMTQAITYPE_UMDRIVERNAME;
	info.pPrivateDriverData = &umdFile;

	for (; startVer < NUM_KMTUMDVERSIONS; startVer++)
	{
		// try to find an UMD module that supports the provided version
		// apperently (needs confirmation): some drivers can implement only DXVA2 and fail when it attempts to call DX9 version or similar

		umdFile.Version = (KMTUMDVERSION)startVer;
		auto err = NtErrorToDxgiError(D3DKMTQueryAdapterInfo(&info));

		if (SUCCEEDED(err))
			break;
		else if (err != E_INVALIDARG)
		{
			if (isD3d10)
				return err; // we do not have a d3d10 compatible driver

			// fallback to gdi32.dll if we don't have a D3D9 compatible driver
			// this is because that we might be running in XDDM mode
			GetModuleFileNameW(g_GDI32, umdFile.UmdFileName, MAX_PATH);
		}
	}

	if (isD3d10)
	{
		// we have an UMD driver that claims to support DirectX 10
		// let's see if we can actually create a D3D10 device.
		// In case we can NOT create a device with D3D10, we consider that we don't support D3D10

		auto d3d = LoadLibraryW(L"d3d10.dll");
		if (!d3d)
			return DXGI_ERROR_UNSUPPORTED;

		auto d3d10cv = (D3D10CreateDevice_)GetProcAddress(d3d, "D3D10CreateDevice");

		if (!d3d10cv)
			return DXGI_ERROR_UNSUPPORTED;

		ID3D10Device* pDev;
		auto hr = d3d10cv(this, (m_desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) ? D3D10_DRIVER_TYPE_SOFTWARE : D3D10_DRIVER_TYPE_HARDWARE, nullptr, 0, D3D10_SDK_VERSION, &pDev);

		if (FAILED(hr))
			return DXGI_ERROR_UNSUPPORTED;

		pDev->Release();
	}

	// get the resource version of the umd

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

	if ((Output + 1) > m_vOutputs.size())
		return DXGI_ERROR_NOT_FOUND;

	ATL::CComObject<CDXGIOutput>* op;
	HRESULT hr = ATL::CComObject<CDXGIOutput>::CreateInstance(&op);

	if (FAILED(hr))
		return hr;

	hr = op->Initialize(m_hDll, this, m_vOutputs[Output]);
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

	if (!m_bValid)
		GetAdapterDesc();

	pDesc->AdapterLuid = m_desc.AdapterLuid;
	pDesc->DedicatedSystemMemory = m_desc.DedicatedSystemMemory;
	pDesc->DedicatedVideoMemory = m_desc.DedicatedVideoMemory;
	pDesc->SharedSystemMemory = m_desc.SharedSystemMemory;
	StringCchCopyN(pDesc->Description, 128, m_desc.Description, 128);
	pDesc->DeviceId = m_desc.DeviceId;
	pDesc->Revision = m_desc.Revision;
	pDesc->SubSysId = m_desc.SubSysId;
	pDesc->VendorId = m_desc.VendorId;

	return S_OK;
}

STDMETHODIMP CDXGIAdapter::GetUMDDeviceSize(_In_ UINT unk, _In_ UINT unk2, _In_ UINT unk3)
{
	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGIAdapter::GetUMDDeviceSize", "DEBUG", MB_OK);
	return S_OK;
}

STDMETHODIMP CDXGIAdapter::Initialize(_In_ IDXGIFactory* parent)
{
	SetParent(parent); // keep the reference of self alive...
	m_hDll = g_GDI32;
	
	auto hr = LoadD3DKMTApi();
	if (FAILED(hr))
		return hr;

	m_modType = DXGIAdapterModuleType::Hardware;

	if (FAILED(QueryUMDVersion(KMTUMDVERSION_DX10)))
		ChangeDataToSoftAdapter();

	return S_OK;
}

STDMETHODIMP CDXGIAdapter::Initialize(_In_ IDXGIFactory* parent, _In_ HMODULE hSoft)
{
	SetParent(parent);

	m_hDll = hSoft;
	
	auto hr = LoadD3DKMTApi();
	if (FAILED(hr))
		return hr;

	// clear information that was copied from real outputs
	m_desc.AdapterLuid.HighPart = 0;
	m_desc.AdapterLuid.LowPart = 0;
	m_desc.VendorId = 0;
	m_desc.DeviceId = 0;
	m_desc.Revision = 0;
	m_desc.SubSysId = 0;
	m_hHandle = D3DGPU_NULL;

	// set module type

	// Ordinal 199 is an undocumented exports that is used for internal IDXGIAdapterWarp data
	if ((GetProcAddress(m_hDll, "OpenAdapter10") || GetProcAddress(m_hDll, "OpenAdapter10_2")) && GetProcAddress(m_hDll, (LPCSTR)199))
		m_modType = DXGIAdapterModuleType::Warp;
	// dxgi.dll of Windows hardcodes this, but we can use this two exports to check if we are using ref devices
	else if (GetProcAddress(m_hDll, "D3D11RefGetLastCreation") || GetProcAddress(m_hDll, "D3D10RefGetLastCreation"))
		m_modType = DXGIAdapterModuleType::Software;

	auto gdiDisp = (D3DKMTOpenAdapterFromGdiDisplayName_)GetProcAddress(hSoft, "D3DKMTOpenAdapterFromGdiDisplayName");

	if (gdiDisp && m_modType != DXGIAdapterModuleType::Invalid)
	{
		NTSTATUS err;
		bool failed = false;

		ChangeDataToSoftAdapter();

		// we might have outputs to enumerate
		for (auto& x : m_vOutputs)
		{
			D3DKMT_OPENADAPTERFROMGDIDISPLAYNAME gdi = { 0 };
			StringCchCopyN(gdi.DeviceName, 32, x.DeviceName, 32);
			err = gdiDisp(&gdi);

			if (FAILED(err))
			{
				failed = true;
				break;
			}

			if (m_hHandle == D3DGPU_NULL)
				m_hHandle = gdi.hAdapter;

			x.AdapterHandle = gdi.hAdapter;
			x.VidPn = gdi.VidPnSourceId;
			m_desc.AdapterLuid = gdi.AdapterLuid;
		}
	}
	else
	{
		// we cannot enumerate the adapters, which means we don't have any!
		m_vOutputs.clear();
	}

	return S_OK;
}

STDMETHODIMP_(void) CDXGIAdapter::AddOutput(const DXGIEnumInfo& e)
{
	m_desc.VendorId = e.VendorId;
	m_desc.DeviceId = e.DeviceId;
	m_desc.Revision = e.Revision;
	m_desc.SubSysId = e.SubSystemId;
	m_desc.AdapterLuid = e.AdapterLuid;
	
	if (m_hHandle == D3DGPU_NULL)
		m_hHandle = e.AdapterHandle;

	DXGIOutputInfo o;
	o.AdapterHandle = e.AdapterHandle;
	o.VidPn = e.VidPn;
	StringCchCopyN(o.DeviceName, 32, e.DeviceName, 32);
	m_vOutputs.push_back(o);
}

STDMETHODIMP CDXGIAdapter::LoadD3DKMTApi()
{
	D3DKMTQueryAdapterInfo = (D3DKMTQueryAdapterInfo_)GetProcAddress(m_hDll, "D3DKMTQueryAdapterInfo");
	if (!D3DKMTQueryAdapterInfo)
		return DXGI_ERROR_UNSUPPORTED;

	return S_OK;
}

STDMETHODIMP_(void) CDXGIAdapter::GetAdapterDesc()
{
	D3DKMT_QUERYADAPTERINFO qa;
	D3DKMT_SEGMENTSIZEINFO segInfo;

	/// skip query information if the adapter is invalid
	if (m_modType == DXGIAdapterModuleType::Invalid)
	{
		m_bValid = true;
		return;
	}

	qa.hAdapter = m_hHandle;
	qa.Type = KMTQAITYPE_GETSEGMENTSIZE;
	qa.PrivateDriverDataSize = sizeof(segInfo);
	qa.pPrivateDriverData = &segInfo;

	NTSTATUS s = D3DKMTQueryAdapterInfo(&qa);

	if (NT_ERROR(s))
		return;

	m_desc.DedicatedSystemMemory = (SIZE_T)segInfo.DedicatedSystemMemorySize;
	m_desc.DedicatedVideoMemory = (SIZE_T)segInfo.DedicatedVideoMemorySize;
	m_desc.SharedSystemMemory = (SIZE_T)segInfo.SharedSystemMemorySize;

	D3DKMT_ADAPTERREGISTRYINFO reg = { 0 };
	qa.Type = KMTQAITYPE_ADAPTERREGISTRYINFO;
	qa.PrivateDriverDataSize = sizeof(reg);
	qa.pPrivateDriverData = &reg;

	s = D3DKMTQueryAdapterInfo(&qa);

	if (NT_SUCCESS(s))
	{
		StringCchCopyN(m_desc.Description, 128, reg.AdapterString, 260);
	}

#if DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8
	D3DKMT_ADAPTERTYPE at;
	qa.Type = KMTQAITYPE_ADAPTERTYPE;
	qa.PrivateDriverDataSize = sizeof(at);
	qa.pPrivateDriverData = &at;

	s = ApiCallback.D3DKMTGetQueryAdapterInfo(&qa);

	if (NT_SUCCESS(s))
	{
		m_desc.Flags |= at.SoftwareDevice ? DXGI_ADAPTER_FLAG_SOFTWARE : DXGI_ADAPTER_FLAG_NONE;
	}

	// TODO: Use KMTQAITYPE_WDDM_1_2_CAPS to gather GraphicsPreemptionGranularity&&ComputePreemptionGranularity

#elif DXGI_VERSION >= 2
	// hardcoded because we are not in Windows 8
	m_desc.GraphicsPreemptionGranularity = DXGI_GRAPHICS_PREEMPTION_DMA_BUFFER_BOUNDARY;
	m_desc.ComputePreemptionGranularity = DXGI_COMPUTE_PREEMPTION_DMA_BUFFER_BOUNDARY;
#endif

	m_bValid = true;
}

#if DXGI_VERSION >= 1
STDMETHODIMP CDXGIAdapter::GetDesc1(_Out_ DXGI_ADAPTER_DESC1* pDesc)
{
	if (!pDesc)
		return DXGI_ERROR_INVALID_CALL;

	if (!m_bValid)
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

	if (!m_bValid)
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
	qa.hAdapter = m_hHandle;
	qa.PrivateDriverDataSize = sizeof(um);
	qa.pPrivateDriverData = &um;
	qa.Type = KMTQAITYPE_UMDRIVERNAME;
	um.Version = Version;

	auto st = D3DKMTQueryAdapterInfo(&qa);
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
	bool hr = true;

	switch (Version)
	{
	default:
		return E_NOINTERFACE;

	case DXGI_THUNKS_VERSION_NONE:
		break;


	case DXGI_THUNKS_VERSION_1:
	{
		if (!Thunks)
			break;

		if (ThunkSize != sizeof(DXGI_THUNKS_V1))
			return E_POINTER;

		*((DWORD*)Thunks) = 1;
		hr = DXGILoadThunkProcs(m_hDll, DXGI_THUNKS_NAMES_V1, (FARPROC*)Thunks);
		break;
	}

	case DXGI_THUNKS_VERSION_2:
	{
		if (!Thunks)
			break;

		if (ThunkSize != sizeof(DXGI_THUNKS_V2))
			return E_POINTER;

		*((DWORD*)Thunks) = 2;
		hr = DXGILoadThunkProcs(m_hDll, DXGI_THUNKS_NAMES_V2, (FARPROC*)Thunks);

		break;
	}

	case DXGI_THUNKS_VERSION_3:
	{
		if (!Thunks)
			break;

		if (ThunkSize != sizeof(DXGI_THUNKS_V3))
			return E_POINTER;

		*((DWORD*)Thunks) = 3;
		hr = DXGILoadThunkProcs(m_hDll, DXGI_THUNKS_NAMES_V3, (FARPROC*)Thunks);
		break;
	}

	case DXGI_THUNKS_VERSION_4:
	{
		if (!Thunks)
			break;

		if (ThunkSize != sizeof(DXGI_THUNKS_V4))
			return E_POINTER;

		*((DWORD*)Thunks) = 4;
		hr = DXGILoadThunkProcs(m_hDll, DXGI_THUNKS_NAMES_V4, (FARPROC*)Thunks);
		break;
	}


	}

	if (!hr)
		return E_NOINTERFACE;

	if (Adapter)
		*Adapter = m_hHandle;

	return S_OK;
}

STDMETHODIMP CDXGIAdapter::QueryUMDVersion(KMTUMDVERSION uv)
{
	D3DKMT_QUERYADAPTERINFO info;
	D3DKMT_UMDFILENAMEINFO umdFile;
	info.hAdapter = m_hHandle;
	info.PrivateDriverDataSize = sizeof(umdFile);
	info.Type = KMTQAITYPE_UMDRIVERNAME;
	info.pPrivateDriverData = &umdFile;
	umdFile.Version = uv;
	return NtErrorToDxgiError(D3DKMTQueryAdapterInfo(&info));
}

STDMETHODIMP_(void) CDXGIAdapter::ChangeDataToSoftAdapter()
{
	StringCchCopy(m_desc.Description, 128, L"Software Adapter");
	m_desc.VendorId = 0;
	m_desc.DeviceId = 0;
	m_desc.SubSysId = 0;
	m_desc.Revision = 0;
}

STDMETHODIMP CDXGIAdapter::CloseKernelHandle(_In_ D3DKMT_HANDLE* pHandle)
{
	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGIAdapter::CloseKernelHandle", "DEBUG", MB_OK);
	return S_OK;
}

STDMETHODIMP CDXGIAdapter::RetireUsage(_In_ D3DKMT_HANDLE Adapter)
{
	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGIAdapter::RetireUsage", "DEBUG", MB_OK);
	return S_OK;
}

STDMETHODIMP CDXGIAdapter::SetAdapterCapabilities(_In_ DXGI_ADAPTER_CAPABILITIES* cap)
{
	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGIAdapter::SetAdapterCapabilities", "DEBUG", MB_OK);
	return S_OK;
}

STDMETHODIMP CDXGIAdapter::GetAdapterCapabilities(_Inout_ DXGI_ADAPTER_CAPABILITIES* cap)
{
	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGIAdapter::GetAdapterCapabilities", "DEBUG", MB_OK);
	return S_OK;
}

STDMETHODIMP_(BOOL) CDXGIAdapter::IsWARP(void)
{
	return m_modType == DXGIAdapterModuleType::Warp ? TRUE : FALSE;
}

STDMETHODIMP_(D3DDDI_VIDEO_PRESENT_SOURCE_ID) CDXGIAdapter::GetPrimaryVidPnSourceId(void)
{
	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGIAdapter::GetPrimaryVidPnSourceId", "DEBUG", MB_OK);
	return 0;
}

STDMETHODIMP_(UINT) CDXGIAdapter::WddmVersion(void)
{
	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGIAdapter::WddmVersion", "DEBUG", MB_OK);
	return 0;
}

STDMETHODIMP_(BOOL) CDXGIAdapter::MismatchedVendorLda(void)
{
	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGIAdapter::MismatchedVendorLda", "DEBUG", MB_OK);
	return FALSE;
}

STDMETHODIMP_(BOOL) CDXGIAdapter::IsLda(void)
{
	MessageBoxA(nullptr, "NOT IMPLEMENTED: CDXGIAdapter::IsLda", "DEBUG", MB_OK);
	return FALSE;
}

#endif
