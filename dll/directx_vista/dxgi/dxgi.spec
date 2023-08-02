@ stdcall CreateDXGIFactory(ptr ptr)
@ stdcall CreateDXGIFactory1(ptr ptr)
@ stdcall -version=0x601+ CreateDXGIFactory2(long ptr ptr)
@ stub PIXBeginCapture
@ stub PIXEndCapture
@ stub PIXGetCaptureState
@ stub DXGIDumpJournal
@ stub DXGIReportAdapterConfiguration
@ stub SetAppCompatStringPointer
@ stub ApplyCompatResolutionQuirking
@ stub CompatString
@ stub CompatValue
@ stub UpdateHMDEmulationStatus
@ stdcall DXGID3D10CreateDevice(ptr ptr ptr long ptr long ptr)
@ stdcall DXGID3D10CreateLayeredDevice(ptr long ptr ptr ptr)
@ stdcall DXGID3D10GetLayeredDeviceSize(ptr long)
@ stdcall DXGID3D10RegisterLayers(ptr long)
@ stub DXGIDeclareAdapterRemovalSupport
@ stdcall DXGIGetDebugInterface1(long ptr ptr)
@ stdcall OpenAdapter10(ptr)
@ stdcall OpenAdapter10_2(ptr)
@ stdcall D3DKMTCloseAdapter(ptr)
@ stdcall D3DKMTCreateAllocation(ptr)
@ stdcall D3DKMTCreateContext(ptr)
@ stdcall D3DKMTCreateDevice(ptr)
@ stdcall D3DKMTCreateSyncrhonizationObject(ptr)
@ stdcall D3DKMTDestroyAllocation(ptr)
@ stdcall D3DKMTDestroyContext(ptr)
@ stdcall D3DKMTDestroyDevice(ptr)
@ stdcall D3DKMTDestroySynchronizationObject(ptr)
@ stdcall D3DKMTEscape(ptr)
@ stdcall D3DKMTGetContextSchedulingPriority(ptr)
@ stdcall D3DKMTGetDeviceState(ptr)
@ stdcall D3DKMTGetDisplayModeList(ptr)
@ stdcall D3DKMTGetMultisampleMethodList(ptr)
@ stdcall D3DKMTGetRuntimeData(ptr)
@ stdcall D3DKMTGetSharedPrimaryHandle(ptr)
@ stdcall D3DKMTLock(ptr)
@ stdcall D3DKMTOpenAdapterFromHdc(ptr)
@ stdcall D3DKMTOpenResource(ptr)
@ stdcall D3DKMTPresent(ptr)
@ stdcall D3DKMTQueryAdapterInfo(ptr)
@ stdcall D3DKMTQueryAllocationResidency(ptr)
@ stdcall D3DKMTQueryResourceInfo(ptr)
@ stdcall D3DKMTRender(ptr)
@ stdcall D3DKMTSetAllocationPriority(ptr)
@ stdcall D3DKMTSetContextSchedulingPriority(ptr)
@ stdcall D3DKMTSetDisplayMode(ptr)
@ stdcall D3DKMTSetDisplayPrivateDriverFormat(ptr)
@ stdcall D3DKMTSetGammaRamp(ptr)
@ stdcall D3DKMTSetVidPnSourceOwner(ptr)
@ stdcall D3DKMTSignalSynchronizationObject(ptr)
@ stdcall D3DKMTUnlock(ptr)
@ stdcall D3DKMTWaitForSynchronizationObject(ptr)
@ stdcall D3DKMTWaitForVerticalBlankEvent(ptr)
