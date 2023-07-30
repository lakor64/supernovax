/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     Import callback
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#pragma once

using D3DKMTOpenAdapterFromGdiDisplayName = NTSTATUS(NTAPI*)(_Inout_ D3DKMT_OPENADAPTERFROMGDIDISPLAYNAME* disp);

#if DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8
using D3DKMTEnumAdapters2 = NTSTATUS(NTAPI*)(_Inout_ const D3DKMT_ENUMADAPTERS2* adapters);
#endif

using D3DKMTQueryAdapterInfo = NTSTATUS(NTAPI*)(_In_ const D3DKMT_QUERYADAPTERINFO* info);

using RtlNtStatusToDosError_ = ULONG(NTAPI*)(_In_ NTSTATUS Status);
