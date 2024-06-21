/*
 * PROJECT:     ReactX Graphics Infrastructure
 * LICENSE:     LGPL-2.0-or-later (https://spdx.org/licenses/LGPL-2.0-or-later.html)
 * PURPOSE:     Thunks definitions
 * COPYRIGHT:   Copyright 2023 Christian Rendina <pizzaiolo100@proton.me>
 */
#pragma once

struct DXGI_THUNKS_V1
{
	DWORD version;
	void* D3DKMTRender;
	void* D3DKMTLock;
	void* D3DKMTUnlock;
	void* D3DKMTEscape;
	void* D3DKMTWaitForSynchronizationObject;
	void* D3DKMTSignalSynchronizationObject;
	void* D3DKMTSetDisplayMode;
	void* D3DKMTGetDeviceState;
	void* D3DKMTCreateAllocation;
	void* D3DKMTQueryResourceInfo;
	void* D3DKMTOpenResource;
	void* D3DKMTDestroyAllocation;
	void* D3DKMTSetAllocationPriority;
	void* D3DKMTQueryAllocationResidency;
	void* D3DKMTCreateDevice;
	void* D3DKMTDestroyDevice;
	void* D3DKMTPresent;
	void* D3DKMTSetContextSchedulingPriority;
	void* D3DKMTGetContextSchedulingPriority;
	void* D3DKMTCreateContext;
	void* D3DKMTDestroyContext;
	void* D3DKMTCreateSynchronizationObject;
	void* D3DKMTDestroySynchronizationObject;
	void* D3DKMTSetDisplayPrivateDriverFormat;
	void* D3DKMTQueryAdapterInfo;
	void* D3DKMTGetMultisampleMethodList;
	void* D3DKMTSetQueuedLimit;
};

struct DXGI_THUNKS_V2 : public DXGI_THUNKS_V1
{
	void *D3DKMTCreateAllocation2;
	void *D3DKMTOpenResource2;
	void *D3DKMTCreateKeyedMutex;
	void *D3DKMTOpenKeyedMutex;
	void *D3DKMTDestroyKeyedMutex;
	void *D3DKMTAcquireKeyedMutex;
	void *D3DKMTReleaseKeyedMutex;
	void *D3DKMTCreateSynchronizationObject2;
	void *D3DKMTOpenSynchronizationObject;
	void *D3DKMTWaitForSynchronizationObject2;
	void *D3DKMTSignalSynchronizationObject2;
	void *D3DKMTConfigureSharedResource;
};

struct DXGI_THUNKS_V3 : public DXGI_THUNKS_V2
{
	void* D3DKMTOfferAllocations;
	void* D3DKMTReclaimAllocations;
	void* D3DKMTCreateKeyedMutex2;
	void* D3DKMTOpenKeyedMutex2;
	void* D3DKMTAcquireKeyedMutex2;
	void* D3DKMTReleaseKeyedMutex2;
	void* D3DKMTOutputDuplPresent;
	void* D3DKMTQueryResourceInfoFromNtHandle;
	void* D3DKMTShareObjects;
	void* D3DKMTOpenNtHandleFromName;
	void* D3DKMTOpenResourceFromNtHandle;
	void* D3DKMTPinDirectFlipResources;
	void* D3DKMTUnpinDirectFlipResources;
	void* D3DKMTSetContextInProcessSchedulingPriority;
	void* D3DKMTGetContextInProcessSchedulingPriority;
	void* D3DKMTOpenSyncObjectFromNtHandle;
	void* D3DKMTPresentMultiPlaneOverlay;
	void* D3DKMTCheckMultiPlaneOverlaySupport;
};

struct DXGI_THUNKS_V4 : public DXGI_THUNKS_V3
{
	void* D3DKMTMakeResident;
	void* D3DKMTEvict;
	void* D3DKMTWaitForSynchronizationObjectFromCpu;
	void* D3DKMTSignalSynchronizationObjectFromCpu;
	void* D3DKMTWaitForSynchronizationObjectFromGpu;
	void* D3DKMTSignalSynchronizationObjectFromGpu;
	void* D3DKMTCreatePagingQueue;
	void* D3DKMTDestroyPagingQueue;
	void* D3DKMTLock2;
	void* D3DKMTUnlock2;
	void* D3DKMTInvalidateCache;
	void* D3DKMTMapGpuVirtualAddress;
	void* D3DKMTReserveGpuVirtualAddress;
	void* D3DKMTFreeGpuVirtualAddress;
	void* D3DKMTUpdateGpuVirtualAddress;
	void* D3DKMTCreateContextVirtual;
	void* D3DKMTSubmitCommand;
	void* D3DKMTOpenSyncObjectFromNtHandle2;
	void* D3DKMTOpenSyncObjectNtHandleFromName;
	void* D3DKMTDestroyAllocation2;
	void* D3DKMTSignalSynchronizationObjectFromGpu2;
	void* D3DKMTRegisterTrimNotification;
	void* D3DKMTUnregisterTrimNotification;
	void* D3DKMTQueryVideoMemoryInfo;
	void* D3DKMTChangeVideoMemoryReservation;
	void* d3dkmt2900;
	void* d3dkmt3900;
	void* D3DKMTReclaimAllocations2;
	void* D3DKMTPresentMultiPlaneOverlay2;
	void* D3DKMTCheckMultiPlaneOverlaySupport2;
	void* D3DKMTGetResourcePresentPrivateDriverData;
	void* D3DKMTSetStablePowerState;
	void* D3DKMTQueryClockCalibration;
	void* D3DKMTMarkDeviceAsError;
	void* D3DKMTFlushHeapTransitions;
	void* D3DKMTUpdateAllocationProperty;
	void* D3DKMTGetAllocationPriority;
};

constexpr const char* DXGI_THUNKS_NAMES_V1[] = {
	"D3DKMTRender",
	"D3DKMTLock",
	"D3DKMTUnlock",
	"D3DKMTEscape",
	"D3DKMTWaitForSynchronizationObject",
	"D3DKMTSignalSynchronizationObject",
	"D3DKMTSetDisplayMode",
	"D3DKMTGetDeviceState",
	"D3DKMTCreateAllocation",
	"D3DKMTQueryResourceInfo",
	"D3DKMTOpenResource",
	"D3DKMTDestroyAllocation",
	"D3DKMTSetAllocationPriority",
	"D3DKMTQueryAllocationResidency",
	"D3DKMTCreateDevice",
	"D3DKMTDestroyDevice",
	"D3DKMTPresent",
	"D3DKMTSetContextSchedulingPriority",
	"D3DKMTGetContextSchedulingPriority",
	"D3DKMTCreateContext",
	"D3DKMTDestroyContext",
	"D3DKMTCreateSynchronizationObject",
	"D3DKMTDestroySynchronizationObject",
	"D3DKMTSetDisplayPrivateDriverFormat",
	"D3DKMTQueryAdapterInfo",
	"D3DKMTGetMultisampleMethodList",
	"D3DKMTSetQueuedLimit",
};

constexpr const char* DXGI_THUNKS_NAMES_V2[] = {
	// V1
	"D3DKMTRender",
	"D3DKMTLock",
	"D3DKMTUnlock",
	"D3DKMTEscape",
	"D3DKMTWaitForSynchronizationObject",
	"D3DKMTSignalSynchronizationObject",
	"D3DKMTSetDisplayMode",
	"D3DKMTGetDeviceState",
	"D3DKMTCreateAllocation",
	"D3DKMTQueryResourceInfo",
	"D3DKMTOpenResource",
	"D3DKMTDestroyAllocation",
	"D3DKMTSetAllocationPriority",
	"D3DKMTQueryAllocationResidency",
	"D3DKMTCreateDevice",
	"D3DKMTDestroyDevice",
	"D3DKMTPresent",
	"D3DKMTSetContextSchedulingPriority",
	"D3DKMTGetContextSchedulingPriority",
	"D3DKMTCreateContext",
	"D3DKMTDestroyContext",
	"D3DKMTCreateSynchronizationObject",
	"D3DKMTDestroySynchronizationObject",
	"D3DKMTSetDisplayPrivateDriverFormat",
	"D3DKMTQueryAdapterInfo",
	"D3DKMTGetMultisampleMethodList",
	"D3DKMTSetQueuedLimit",
	// V2
	"D3DKMTCreateAllocation2",
	"D3DKMTOpenResource2",
	"D3DKMTCreateKeyedMutex",
	"D3DKMTOpenKeyedMutex",
	"D3DKMTDestroyKeyedMutex",
	"D3DKMTAcquireKeyedMutex",
	"D3DKMTReleaseKeyedMutex",
	"D3DKMTCreateSynchronizationObject2",
	"D3DKMTOpenSynchronizationObject",
	"D3DKMTWaitForSynchronizationObject2",
	"D3DKMTSignalSynchronizationObject2",
	"D3DKMTConfigureSharedResource",
};

constexpr const char* DXGI_THUNKS_NAMES_V3[] = {
	// V1
	"D3DKMTRender",
	"D3DKMTLock",
	"D3DKMTUnlock",
	"D3DKMTEscape",
	"D3DKMTWaitForSynchronizationObject",
	"D3DKMTSignalSynchronizationObject",
	"D3DKMTSetDisplayMode",
	"D3DKMTGetDeviceState",
	"D3DKMTCreateAllocation",
	"D3DKMTQueryResourceInfo",
	"D3DKMTOpenResource",
	"D3DKMTDestroyAllocation",
	"D3DKMTSetAllocationPriority",
	"D3DKMTQueryAllocationResidency",
	"D3DKMTCreateDevice",
	"D3DKMTDestroyDevice",
	"D3DKMTPresent",
	"D3DKMTSetContextSchedulingPriority",
	"D3DKMTGetContextSchedulingPriority",
	"D3DKMTCreateContext",
	"D3DKMTDestroyContext",
	"D3DKMTCreateSynchronizationObject",
	"D3DKMTDestroySynchronizationObject",
	"D3DKMTSetDisplayPrivateDriverFormat",
	"D3DKMTQueryAdapterInfo",
	"D3DKMTGetMultisampleMethodList",
	"D3DKMTSetQueuedLimit",
	// V2
	"D3DKMTCreateAllocation2",
	"D3DKMTOpenResource2",
	"D3DKMTCreateKeyedMutex",
	"D3DKMTOpenKeyedMutex",
	"D3DKMTDestroyKeyedMutex",
	"D3DKMTAcquireKeyedMutex",
	"D3DKMTReleaseKeyedMutex",
	"D3DKMTCreateSynchronizationObject2",
	"D3DKMTOpenSynchronizationObject",
	"D3DKMTWaitForSynchronizationObject2",
	"D3DKMTSignalSynchronizationObject2",
	"D3DKMTConfigureSharedResource",
	// V3
	"D3DKMTOfferAllocations",
	"D3DKMTReclaimAllocations",
	"D3DKMTCreateKeyedMutex2",
	"D3DKMTOpenKeyedMutex2",
	"D3DKMTAcquireKeyedMutex2",
	"D3DKMTReleaseKeyedMutex2",
	"D3DKMTOutputDuplPresent",
	"D3DKMTQueryResourceInfoFromNtHandle",
	"D3DKMTShareObjects",
	"D3DKMTOpenNtHandleFromName",
	"D3DKMTOpenResourceFromNtHandle",
	"D3DKMTPinDirectFlipResources",
	"D3DKMTUnpinDirectFlipResources",
	"D3DKMTSetContextInProcessSchedulingPriority",
	"D3DKMTGetContextInProcessSchedulingPriority",
	"D3DKMTOpenSyncObjectFromNtHandle",
	"D3DKMTPresentMultiPlaneOverlay",
	"D3DKMTCheckMultiPlaneOverlaySupport",
};

constexpr const char* DXGI_THUNKS_NAMES_V4[] = {
	// V1
	"D3DKMTRender",
	"D3DKMTLock",
	"D3DKMTUnlock",
	"D3DKMTEscape",
	"D3DKMTWaitForSynchronizationObject",
	"D3DKMTSignalSynchronizationObject",
	"D3DKMTSetDisplayMode",
	"D3DKMTGetDeviceState",
	"D3DKMTCreateAllocation",
	"D3DKMTQueryResourceInfo",
	"D3DKMTOpenResource",
	"D3DKMTDestroyAllocation",
	"D3DKMTSetAllocationPriority",
	"D3DKMTQueryAllocationResidency",
	"D3DKMTCreateDevice",
	"D3DKMTDestroyDevice",
	"D3DKMTPresent",
	"D3DKMTSetContextSchedulingPriority",
	"D3DKMTGetContextSchedulingPriority",
	"D3DKMTCreateContext",
	"D3DKMTDestroyContext",
	"D3DKMTCreateSynchronizationObject",
	"D3DKMTDestroySynchronizationObject",
	"D3DKMTSetDisplayPrivateDriverFormat",
	"D3DKMTQueryAdapterInfo",
	"D3DKMTGetMultisampleMethodList",
	"D3DKMTSetQueuedLimit",
	// V2
	"D3DKMTCreateAllocation2",
	"D3DKMTOpenResource2",
	"D3DKMTCreateKeyedMutex",
	"D3DKMTOpenKeyedMutex",
	"D3DKMTDestroyKeyedMutex",
	"D3DKMTAcquireKeyedMutex",
	"D3DKMTReleaseKeyedMutex",
	"D3DKMTCreateSynchronizationObject2",
	"D3DKMTOpenSynchronizationObject",
	"D3DKMTWaitForSynchronizationObject2",
	"D3DKMTSignalSynchronizationObject2",
	"D3DKMTConfigureSharedResource",
	// V3
	"D3DKMTOfferAllocations",
	"D3DKMTReclaimAllocations",
	"D3DKMTCreateKeyedMutex2",
	"D3DKMTOpenKeyedMutex2",
	"D3DKMTAcquireKeyedMutex2",
	"D3DKMTReleaseKeyedMutex2",
	"D3DKMTOutputDuplPresent",
	"D3DKMTQueryResourceInfoFromNtHandle",
	"D3DKMTShareObjects",
	"D3DKMTOpenNtHandleFromName",
	"D3DKMTOpenResourceFromNtHandle",
	"D3DKMTPinDirectFlipResources",
	"D3DKMTUnpinDirectFlipResources",
	"D3DKMTSetContextInProcessSchedulingPriority",
	"D3DKMTGetContextInProcessSchedulingPriority",
	"D3DKMTOpenSyncObjectFromNtHandle",
	"D3DKMTPresentMultiPlaneOverlay",
	"D3DKMTCheckMultiPlaneOverlaySupport",
	// V4
	"D3DKMTMakeResident",
	"D3DKMTEvict",
	"D3DKMTWaitForSynchronizationObjectFromCpu",
	"D3DKMTSignalSynchronizationObjectFromCpu",
	"D3DKMTWaitForSynchronizationObjectFromGpu",
	"D3DKMTSignalSynchronizationObjectFromGpu",
	"D3DKMTCreatePagingQueue",
	"D3DKMTDestroyPagingQueue",
	"D3DKMTLock2",
	"D3DKMTUnlock2",
	"D3DKMTInvalidateCache",
	"D3DKMTMapGpuVirtualAddress",
	"D3DKMTReserveGpuVirtualAddress",
	"D3DKMTFreeGpuVirtualAddress",
	"D3DKMTUpdateGpuVirtualAddress",
	"D3DKMTCreateContextVirtual",
	"D3DKMTSubmitCommand",
	"D3DKMTOpenSyncObjectFromNtHandle2",
	"D3DKMTOpenSyncObjectNtHandleFromName",
	"D3DKMTDestroyAllocation2",
	"D3DKMTSignalSynchronizationObjectFromGpu2",
	"D3DKMTRegisterTrimNotification",
	"D3DKMTUnregisterTrimNotification",
	"D3DKMTQueryVideoMemoryInfo",
	"D3DKMTChangeVideoMemoryReservation",
	nullptr,
	nullptr,
	"D3DKMTReclaimAllocations2",
	"D3DKMTPresentMultiPlaneOverlay2",
	"D3DKMTCheckMultiPlaneOverlaySupport2",
	"D3DKMTGetResourcePresentPrivateDriverData",
	"D3DKMTSetStablePowerState",
	"D3DKMTQueryClockCalibration",
	"D3DKMTMarkDeviceAsError",
	"D3DKMTFlushHeapTransitions",
	"D3DKMTUpdateAllocationProperty",
	"D3DKMTGetAllocationPriority",
};
