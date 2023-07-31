/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     Import callback
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#pragma once

typedef NTSTATUS(NTAPI* D3DKMTOpenAdapterFromGdiDisplayName_)(D3DKMT_OPENADAPTERFROMGDIDISPLAYNAME* disp);

#if DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8
typedef NTSTATUS(NTAPI* D3DKMTEnumAdapters2_)(const D3DKMT_ENUMADAPTERS2* adapters);
#endif

typedef NTSTATUS(NTAPI* D3DKMTQueryAdapterInfo_)(const D3DKMT_QUERYADAPTERINFO* info);

typedef ULONG(NTAPI* RtlNtStatusToDosError_)(NTSTATUS Status);

typedef NTSTATUS(NTAPI* D3DKMTCloseAdapter_)(_In_ const D3DKMT_CLOSEADAPTER* close);

typedef NTSTATUS(NTAPI* D3DKMTGetDisplayModeList_)(_In_ D3DKMT_GETDISPLAYMODELIST* dmList);

typedef HRESULT(NTAPI* D3D110CreateDevice_)(_In_opt_ IDXGIAdapter*, _In_ D3D_DRIVER_TYPE, _In_opt_ HMODULE, _In_ UINT, _In_opt_ const D3D_FEATURE_LEVEL*, _In_ UINT FeatureLevels, _In_ UINT SDKVersion, _Out_opt_ ID3D11Device*, _Out_opt_ D3D_FEATURE_LEVEL*, _Out_opt_ ID3D11DeviceContext*);

typedef HRESULT(NTAPI* D3D10CreateDevice_)(_In_opt_ IDXGIAdapter*, _In_ D3D10_DRIVER_TYPE, _In_ HMODULE, _In_ UINT, _In_ UINT, _Out_ ID3D10Device**);
