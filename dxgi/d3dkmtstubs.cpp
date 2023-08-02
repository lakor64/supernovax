/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     D3DKMT API exports stubs
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */
#include "pch.h"

extern "C"
{
	NTSTATUS D3DKMTGetDeviceState(_Inout_ D3DKMT_GETDEVICESTATE* ds)
	{
		if (ds->StateType == D3DKMT_DEVICESTATE_EXECUTION)
		{
			ds->ExecutionState = D3DKMT_DEVICEEXECUTION_ACTIVE;
		}
		else if (ds->StateType == D3DKMT_DEVICESTATE_PRESENT)
		{
			memset(&ds->PresentState, 0, sizeof(ds->PresentState));
		}
		else
			return STATUS_NOT_SUPPORTED;

		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTOpenAdapterFromHdc(_Inout_ D3DKMT_OPENADAPTERFROMHDC* hdc)
	{
		memset(hdc, 0, sizeof(*hdc));
		hdc->hAdapter = 0xF0F;
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTQueryAdapterInfo(_Inout_ D3DKMT_QUERYADAPTERINFO* ai)
	{
		if (ai->Type == KMTQAITYPE_UMDRIVERNAME)
		{
			if (ai->PrivateDriverDataSize != sizeof(D3DKMT_UMDFILENAMEINFO))
				return STATUS_ACCESS_VIOLATION; // meme, non va bene lol

			wcscpy(((D3DKMT_UMDFILENAMEINFO*)ai->pPrivateDriverData)->UmdFileName, L"dxgi.dll");
			((D3DKMT_UMDFILENAMEINFO*)ai->pPrivateDriverData)->Version = KMTUMDVERSION_DX10;
		}
		else if (ai->Type == KMTQAITYPE_UMDRIVERPRIVATE)
		{
			*((DWORD*)ai->pPrivateDriverData) = 0;
		}

		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTOpenResource(_Inout_ D3DKMT_OPENRESOURCE*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTPresent(_Inout_ D3DKMT_PRESENT*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTQueryAllocationResidency(_Inout_ D3DKMT_QUERYALLOCATIONRESIDENCY*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTQueryResourceInfo(_Inout_ D3DKMT_QUERYRESOURCEINFO*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTCloseAdapter(_Inout_ D3DKMT_CLOSEADAPTER*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTRender(_Inout_ D3DKMT_RENDER*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTLock(_Inout_ D3DKMT_LOCK*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTSetAllocationPriority(_Inout_ D3DKMT_SETALLOCATIONPRIORITY*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTSetContextSchedulingPriority(_Inout_ /*D3DKMT_SETCONTEXTSCHEDULINGPRIORITY*/ void*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTSetDisplayMode(_Inout_ D3DKMT_SETDISPLAYMODE*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTSetDisplayPrivateDriverFormat(_Inout_ /*D3DKMT_SETDISPLAYPRIVATEDRIVERFORMAT*/ void*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTSetGammaRamp(_Inout_ D3DKMT_SETGAMMARAMP*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTSetVidPnSourceOwner(_Inout_ D3DKMT_SETVIDPNSOURCEOWNER*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTSignalSynchronizationObject(_Inout_ D3DKMT_SIGNALSYNCHRONIZATIONOBJECT*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTUnlock(_Inout_ D3DKMT_UNLOCK*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTWaitForSynchronizationObject(_Inout_ D3DKMT_WAITFORSYNCHRONIZATIONOBJECT*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTWaitForVerticalBlankEvent(_Inout_ D3DKMT_WAITFORVERTICALBLANKEVENT*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTCreateAllocation(_Inout_ D3DKMT_CREATEALLOCATION*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTCreateDevice(_Inout_ D3DKMT_CREATEDEVICE*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTCreateContext(_Inout_ D3DKMT_CREATECONTEXT*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTCreateSyncrhonizationObject(_Inout_ D3DKMT_CREATESYNCHRONIZATIONOBJECT*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTDestroyAllocation(_Inout_ D3DKMT_DESTROYALLOCATION*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTDestroyContext(_Inout_ D3DKMT_DESTROYCONTEXT*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTDestroyDevice(_Inout_ D3DKMT_DESTROYDEVICE*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTDestroySynchronizationObject(_Inout_ D3DKMT_DESTROYSYNCHRONIZATIONOBJECT*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTGetContextSchedulingPriority(_Inout_ void*) // NOTE
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTEscape(_Inout_ D3DKMT_ESCAPE*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTGetDisplayModeList(_Inout_ D3DKMT_GETDISPLAYMODELIST*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTGetMultisampleMethodList(_Inout_ D3DKMT_GETMULTISAMPLEMETHODLIST*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTGetRuntimeData(_Inout_ D3DKMT_GETRUNTIMEDATA*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS D3DKMTGetSharedPrimaryHandle(_Inout_ D3DKMT_GETSHAREDPRIMARYHANDLE*)
	{
		return STATUS_SUCCESS;
	}
}
