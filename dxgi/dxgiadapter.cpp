/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     GPU Adapter
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#include "pch.h"
#include "dxgiadapter.h"

STDMETHODIMP CDXGIAdapter::CheckInterfaceSupport(_In_ REFGUID InterfaceName, _Out_ LARGE_INTEGER* pUMDVersion)
{
	pUMDVersion->QuadPart = 0;
	return S_OK; // TODO!
}

STDMETHODIMP CDXGIAdapter::EnumOutputs(_In_ UINT Output, _COM_Outptr_ IDXGIOutput** ppOutput)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDXGIAdapter::GetDesc(_Out_ DXGI_ADAPTER_DESC* pDesc)
{
	if (!pDesc)
		return DXGI_ERROR_INVALID_CALL;

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

STDMETHODIMP CDXGIAdapter::GetDesc1(_Out_ DXGI_ADAPTER_DESC1* pDesc)
{
	if (!pDesc)
		return DXGI_ERROR_INVALID_CALL;

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

STDMETHODIMP CDXGIAdapter::Initialize(IDXGIFactory1* parent, const DXGIAdapterDesc& desc)
{
	m_pParent = parent;
	m_desc = desc;
	return S_OK;
}
