/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     D3DKMT API exports stubs
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */
#include "pch.h"

extern "C"
{
	D3DKMTCloseAdapter
		D3DKMTCreateAllocation
		D3DKMTCreateContext
		D3DKMTCreateDevice
		D3DKMTCreateSyncrhonizationObject
		D3DKMTDestroyAllocation
		D3DKMTDestroyContext
		D3DKMTDestroyDevice
		D3DKMTDestroySynchronizationObject
		D3DKMTEscape
		D3DKMTGetContextSchedulingPriority
		D3DKMTGetDeviceState
		D3DKMTGetDisplayModeList
		D3DKMTGetMultisampleMethodList
		D3DKMTGetRuntimeData
		D3DKMTGetSharedPrimaryHandle
		D3DKMTLock
		D3DKMTOpenAdapterFromHdc
		D3DKMTOpenResource
		D3DKMTPresent
		D3DKMTQueryAdapterInfo
		D3DKMTQueryAllocationResidency
		D3DKMTQueryResourceInfo
		D3DKMTRender
		D3DKMTSetAllocationPriority
		D3DKMTSetContextSchedulingPriority
		D3DKMTSetDisplayMode
		D3DKMTSetDisplayPrivateDriverFormat
		D3DKMTSetGammaRamp
		D3DKMTSetVidPnSourceOwner
		D3DKMTSignalSynchronizationObject
		D3DKMTUnlock
		D3DKMTWaitForSynchronizationObject
		D3DKMTWaitForVerticalBlankEvent
}