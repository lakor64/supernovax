/*
 * PROJECT:     ReactOS WDDM Alternative Headers
 * LICENSE:     MIT (https://spdx.org/licenses/MIT)
 * PURPOSE:     d3dkmthk minimal header acqusition
 * COPYRIGHT:   Copyright 2023 Justin Miller <justinmiller100@gmail.com>
 */

#pragma once
/*
 *  These headers are based off of reversing drivers
 *  and minimizing the public WDK headers ***ONLY***
 */

#include "d3dkmdt.h"


typedef struct _OBJECT_ATTRIBUTES OBJECT_ATTRIBUTES;
typedef OBJECT_ATTRIBUTES *POBJECT_ATTRIBUTES;

//
// Available only for Vista (LONGHORN) and later and for
// multiplatform tools such as debugger extensions
//
#if (NTDDI_VERSION >= NTDDI_LONGHORN) || defined(D3DKMDT_SPECIAL_MULTIPLATFORM_TOOL)

typedef struct _D3DKMT_CREATEDEVICEFLAGS
{
    UINT    LegacyMode               :  1;   // 0x00000001
    UINT    RequestVSync             :  1;   // 0x00000002
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
    UINT    DisableGpuTimeout        :  1;   // 0x00000004
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM3_1)
    UINT    TestDevice               :  1;   // 0x00000008 The device is created by a test. Testsigning must be enabled.
    UINT    Reserved                 : 28;   // 0xFFFFFFF0
#else
    UINT    Reserved                 : 29;   // 0xFFFFFFF8
#endif
#else
    UINT    Reserved                 : 30;   // 0xFFFFFFFC
#endif
} D3DKMT_CREATEDEVICEFLAGS;

typedef struct _D3DKMT_CREATEDEVICE
{
    union
    {
        D3DKMT_HANDLE           hAdapter;           // in: identifies the adapter for user-mode creation
        VOID*                   pAdapter;           // in: identifies the adapter for kernel-mode creation
        D3DKMT_PTR_HELPER(pAdapter_Align)
    };

    D3DKMT_CREATEDEVICEFLAGS    Flags;

    D3DKMT_HANDLE               hDevice;                // out: Identifies the device
    D3DKMT_PTR(VOID*,           pCommandBuffer);        // out: D3D10 compatibility.
    UINT                        CommandBufferSize;      // out: D3D10 compatibility.
    D3DKMT_PTR(D3DDDI_ALLOCATIONLIST*, pAllocationList); // out: D3D10 compatibility.
    UINT                        AllocationListSize;     // out: D3D10 compatibility.
    D3DKMT_PTR(D3DDDI_PATCHLOCATIONLIST*, pPatchLocationList); // out: D3D10 compatibility.
    UINT                        PatchLocationListSize;  // out: D3D10 compatibility.
} D3DKMT_CREATEDEVICE;

typedef struct _D3DKMT_DESTROYDEVICE
{
    D3DKMT_HANDLE     hDevice;              // in: Indentifies the device
}D3DKMT_DESTROYDEVICE;

typedef enum _D3DKMT_CLIENTHINT
{
    D3DKMT_CLIENTHINT_UNKNOWN        = 0,
    D3DKMT_CLIENTHINT_OPENGL         = 1,
    D3DKMT_CLIENTHINT_CDD            = 2,       // Internal
    D3DKMT_CLIENTHINT_OPENCL         = 3,
    D3DKMT_CLIENTHINT_VULKAN         = 4,
    D3DKMT_CLIENTHINT_CUDA           = 5,
    D3DKMT_CLIENTHINT_RESERVED       = 6,
    D3DKMT_CLIENTHINT_DX7            = 7,
    D3DKMT_CLIENTHINT_DX8            = 8,
    D3DKMT_CLIENTHINT_DX9            = 9,
    D3DKMT_CLIENTHINT_DX10           = 10,
    D3DKMT_CLIENTHINT_DX11           = 11,
    D3DKMT_CLIENTHINT_DX12           = 12,
    D3DKMT_CLIENTHINT_9ON12          = 13,
    D3DKMT_CLIENTHINT_11ON12         = 14,
    D3DKMT_CLIENTHINT_MFT_ENCODE     = 15,
    D3DKMT_CLIENTHINT_GLON12         = 16,
    D3DKMT_CLIENTHINT_CLON12         = 17,
    D3DKMT_CLIENTHINT_DML_TENSORFLOW = 18,
    D3DKMT_CLIENTHINT_ONEAPI_LEVEL0  = 19,
    D3DKMT_CLIENTHINT_DML_PYTORCH    = 20,
    D3DKMT_CLIENTHINT_MAX
} D3DKMT_CLIENTHINT;

typedef struct _D3DKMT_CREATECONTEXT
{
    D3DKMT_HANDLE               hDevice;                    // in:  Handle to the device owning this context.
    UINT                        NodeOrdinal;                // in:  Identifier for the node targetted by this context.
    UINT                        EngineAffinity;             // in:  Engine affinity within the specified node.
    D3DDDI_CREATECONTEXTFLAGS   Flags;                      // in:  Context creation flags.
    D3DKMT_PTR(VOID*,           pPrivateDriverData);        // in:  Private driver data
    UINT                        PrivateDriverDataSize;      // in:  Size of private driver data
    D3DKMT_CLIENTHINT           ClientHint;                 // in:  Hints which client is creating this
    D3DKMT_HANDLE               hContext;                   // out: Handle of the created context.
    D3DKMT_PTR(VOID*,           pCommandBuffer);            // out: Pointer to the first command buffer.
    UINT                        CommandBufferSize;          // out: Command buffer size (bytes).
    D3DKMT_PTR(D3DDDI_ALLOCATIONLIST*, pAllocationList);    // out: Pointer to the first allocation list.
    UINT                        AllocationListSize;         // out: Allocation list size (elements).
    D3DKMT_PTR(D3DDDI_PATCHLOCATIONLIST*, pPatchLocationList); // out: Pointer to the first patch location list.
    UINT                        PatchLocationListSize;      // out: Patch location list size (elements).
    D3DGPU_VIRTUAL_ADDRESS      CommandBuffer;              // out: GPU virtual address of the command buffer. _ADVSCH_
} D3DKMT_CREATECONTEXT;

typedef struct _D3DKMT_DESTROYCONTEXT
{
    D3DKMT_HANDLE               hContext;                   // in:  Identifies the context being destroyed.
} D3DKMT_DESTROYCONTEXT;

typedef struct _D3DKMT_CREATESYNCHRONIZATIONOBJECT
{
    D3DKMT_HANDLE                           hDevice;        // in:  Handle to the device.
    D3DDDI_SYNCHRONIZATIONOBJECTINFO        Info;           // in:  Attributes of the synchronization object.
    D3DKMT_HANDLE                           hSyncObject;    // out: Handle to the synchronization object created.
} D3DKMT_CREATESYNCHRONIZATIONOBJECT;

typedef struct _D3DKMT_CREATESYNCHRONIZATIONOBJECT2
{
    D3DKMT_HANDLE                           hDevice;        // in:  Handle to the device.
    D3DDDI_SYNCHRONIZATIONOBJECTINFO2       Info;           // in/out: Attributes of the synchronization object.
    D3DKMT_HANDLE                           hSyncObject;    // out: Handle to the synchronization object created.
} D3DKMT_CREATESYNCHRONIZATIONOBJECT2;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM3_1)

typedef struct _D3DKMT_CREATENATIVEFENCE
{
    D3DKMT_HANDLE                   hDevice;        // in:  Handle to the device.
    D3DDDI_CREATENATIVEFENCEINFO    Info;           // in/out: Attributes of the synchronization object.
} D3DKMT_CREATENATIVEFENCE;

#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM3_1)

typedef struct _D3DKMT_DESTROYSYNCHRONIZATIONOBJECT
{
    D3DKMT_HANDLE               hSyncObject;                // in:  Identifies the synchronization objects being destroyed.
} D3DKMT_DESTROYSYNCHRONIZATIONOBJECT;

typedef struct _D3DKMT_OPENSYNCHRONIZATIONOBJECT
{
    D3DKMT_HANDLE               hSharedHandle;              // in: shared handle to synchronization object to be opened.
    D3DKMT_HANDLE               hSyncObject;                // out: Handle to sync object in this process.

    D3DKMT_ALIGN64 UINT64       Reserved[8];
} D3DKMT_OPENSYNCHRONIZATIONOBJECT;

typedef struct _D3DKMT_WAITFORSYNCHRONIZATIONOBJECT
{
    D3DKMT_HANDLE             hContext;                   // in: Identifies the context that needs to wait.
    UINT                      ObjectCount;                // in: Specifies the number of object to wait on.
    D3DKMT_HANDLE             ObjectHandleArray[D3DDDI_MAX_OBJECT_WAITED_ON]; // in: Specifies the object to wait on.
} D3DKMT_WAITFORSYNCHRONIZATIONOBJECT;

typedef struct _D3DKMT_WAITFORSYNCHRONIZATIONOBJECT2
{
    D3DKMT_HANDLE             hContext;                   // in: Identifies the context that needs to wait.
    UINT                      ObjectCount;                // in: Specifies the number of object to wait on.
    D3DKMT_HANDLE             ObjectHandleArray[D3DDDI_MAX_OBJECT_WAITED_ON]; // in: Specifies the object to wait on.
    union
    {
        struct {
            D3DKMT_ALIGN64 UINT64 FenceValue;             // in: fence value to be waited.
        } Fence;
        D3DKMT_ALIGN64 UINT64     Reserved[8];
    };
} D3DKMT_WAITFORSYNCHRONIZATIONOBJECT2;

typedef struct _D3DKMT_SIGNALSYNCHRONIZATIONOBJECT
{
    D3DKMT_HANDLE             hContext;           // in: Identifies the context that needs to signal.
    UINT                      ObjectCount;        // in: Specifies the number of object to signal.
    D3DKMT_HANDLE             ObjectHandleArray[D3DDDI_MAX_OBJECT_SIGNALED]; // in: Specifies the object to be signaled.
    D3DDDICB_SIGNALFLAGS      Flags;                                         // in: Specifies signal behavior.
} D3DKMT_SIGNALSYNCHRONIZATIONOBJECT;

typedef struct _D3DKMT_SIGNALSYNCHRONIZATIONOBJECT2
{
    D3DKMT_HANDLE             hContext;           // in: Identifies the context that needs to signal.
    UINT                      ObjectCount;        // in: Specifies the number of object to signal.
    D3DKMT_HANDLE             ObjectHandleArray[D3DDDI_MAX_OBJECT_SIGNALED]; // in: Specifies the object to be signaled.
    D3DDDICB_SIGNALFLAGS      Flags;                  // in: Specifies signal behavior.
    ULONG                     BroadcastContextCount;  // in: Specifies the number of context
                                                      //     to broadcast this command buffer to.
    D3DKMT_HANDLE             BroadcastContext[D3DDDI_MAX_BROADCAST_CONTEXT]; // in: Specifies the handle of the context to
                                                                              //     broadcast to.
    union
    {
        struct {
            D3DKMT_ALIGN64 UINT64 FenceValue;             // in: fence value to be signaled;
        } Fence;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
        HANDLE                CpuEventHandle;         // in: handle of a CPU event to be signaled
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
        D3DKMT_ALIGN64 UINT64 Reserved[8];
    };
} D3DKMT_SIGNALSYNCHRONIZATIONOBJECT2;

typedef struct _D3DKMT_LOCK
{
    D3DKMT_HANDLE       hDevice;            // in: identifies the device
    D3DKMT_HANDLE       hAllocation;        // in: allocation to lock
                                            // out: New handle representing the allocation after the lock.
    UINT                PrivateDriverData;  // in: Used by UMD for AcquireAperture
    UINT                NumPages;
    D3DKMT_PTR(CONST UINT*, pPages);
    D3DKMT_PTR(VOID*,   pData);             // out: pointer to memory
    D3DDDICB_LOCKFLAGS  Flags;              // in: Bit field defined by D3DDDI_LOCKFLAGS
    D3DGPU_VIRTUAL_ADDRESS GpuVirtualAddress; // out: GPU's Virtual Address of locked allocation. _ADVSCH_
} D3DKMT_LOCK;

typedef struct _D3DKMT_UNLOCK
{
    D3DKMT_HANDLE           hDevice;        // in: Identifies the device
    UINT                    NumAllocations; // in: Number of allocations in the array
    D3DKMT_PTR(CONST D3DKMT_HANDLE*, phAllocations); // in: array of allocations to unlock
} D3DKMT_UNLOCK;

typedef enum _D3DKMDT_MODE_PRUNING_REASON
{
    D3DKMDT_MPR_UNINITIALIZED                               = 0, // mode was pruned or is supported because of:
    D3DKMDT_MPR_ALLCAPS                                     = 1, //   all of the monitor caps (only used to imply lack of support - for support, specific reason is always indicated)
    D3DKMDT_MPR_DESCRIPTOR_MONITOR_SOURCE_MODE              = 2, //   monitor source mode in the monitor descriptor
    D3DKMDT_MPR_DESCRIPTOR_MONITOR_FREQUENCY_RANGE          = 3, //   monitor frequency range in the monitor descriptor
    D3DKMDT_MPR_DESCRIPTOR_OVERRIDE_MONITOR_SOURCE_MODE     = 4, //   monitor source mode in the monitor descriptor override
    D3DKMDT_MPR_DESCRIPTOR_OVERRIDE_MONITOR_FREQUENCY_RANGE = 5, //   monitor frequency range in the monitor descriptor override
    D3DKMDT_MPR_DEFAULT_PROFILE_MONITOR_SOURCE_MODE         = 6, //   monitor source mode in the default monitor profile
    D3DKMDT_MPR_DRIVER_RECOMMENDED_MONITOR_SOURCE_MODE      = 7, //   monitor source mode recommended by the driver
    D3DKMDT_MPR_MONITOR_FREQUENCY_RANGE_OVERRIDE            = 8, //   monitor frequency range override
    D3DKMDT_MPR_CLONE_PATH_PRUNED                           = 9, //   Mode is pruned because other path(s) in clone cluster has(have) no mode supported by monitor
    D3DKMDT_MPR_MAXVALID                                    = 10
}
D3DKMDT_MODE_PRUNING_REASON;

// This structure takes 8 bytes.
// The unnamed UINT of size 0 forces alignment of the structure to
// make it exactly occupy 8 bytes, see MSDN docs on C++ bitfields
// for more details
typedef struct _D3DKMDT_DISPLAYMODE_FLAGS
{
#if (DXGKDDI_INTERFACE_VERSION < DXGKDDI_INTERFACE_VERSION_WIN8)
    BOOLEAN                      ValidatedAgainstMonitorCaps  : 1;
    BOOLEAN                      RoundedFakeMode              : 1;
    D3DKMDT_MODE_PRUNING_REASON  ModePruningReason            : 4;
    UINT                         Reserved                     : 28;
#else
    UINT                         ValidatedAgainstMonitorCaps  : 1;
    UINT                         RoundedFakeMode              : 1;
    UINT                                                      : 0;
    D3DKMDT_MODE_PRUNING_REASON  ModePruningReason            : 4;
    UINT                         Stereo                       : 1;
    UINT                         AdvancedScanCapable          : 1;
#if (DXGKDDI_INTERFACE_VERSION < DXGKDDI_INTERFACE_VERSION_WDDM2_0)
    UINT                         Reserved                     : 26;
#else
    UINT                         PreferredTiming              : 1;
    UINT                         PhysicalModeSupported        : 1;
#if (DXGKDDI_INTERFACE_VERSION < DXGKDDI_INTERFACE_VERSION_WDDM2_9)
    UINT                         Reserved                     : 24;
#else
    UINT                         VirtualRefreshRate           : 1;
    UINT                         Reserved                     : 23;
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_9
#endif
#endif
}
D3DKMDT_DISPLAYMODE_FLAGS;

typedef struct _D3DKMT_DISPLAYMODE
{
    UINT                                   Width;
    UINT                                   Height;
    D3DDDIFORMAT                           Format;
    UINT                                   IntegerRefreshRate;
    D3DDDI_RATIONAL                        RefreshRate;
    D3DDDI_VIDEO_SIGNAL_SCANLINE_ORDERING  ScanLineOrdering;
    D3DDDI_ROTATION                        DisplayOrientation;
    UINT                                   DisplayFixedOutput;
    D3DKMDT_DISPLAYMODE_FLAGS              Flags;
} D3DKMT_DISPLAYMODE;

typedef struct _D3DKMT_GETDISPLAYMODELIST
{
    D3DKMT_HANDLE                   hAdapter;       // in: adapter handle
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;  // in: adapter's VidPN source ID
    D3DKMT_PTR(D3DKMT_DISPLAYMODE*, pModeList);      // out:
    UINT                            ModeCount;      // in/out:
} D3DKMT_GETDISPLAYMODELIST;

typedef struct _D3DKMT_DISPLAYMODELIST
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;
    UINT                            ModeCount;
    D3DKMT_DISPLAYMODE              pModeList[0];
} D3DKMT_DISPLAYMODELIST;

typedef struct _D3DKMT_SETDISPLAYMODE_FLAGS
{
    BOOLEAN  PreserveVidPn   : 1;
    UINT     Reserved       : 31;
}
D3DKMT_SETDISPLAYMODE_FLAGS;

typedef struct _D3DKMT_SETDISPLAYMODE
{
    D3DKMT_HANDLE                          hDevice;                         // in: Identifies the device
    D3DKMT_HANDLE                          hPrimaryAllocation;              // in:
    D3DDDI_VIDEO_SIGNAL_SCANLINE_ORDERING  ScanLineOrdering;                // in:
    D3DDDI_ROTATION                        DisplayOrientation;              // in:
    UINT                                   PrivateDriverFormatAttribute;    // out: Private Format Attribute of the current primary surface if DxgkSetDisplayMode failed with STATUS_GRAPHICS_INCOMPATIBLE_PRIVATE_FORMAT
    D3DKMT_SETDISPLAYMODE_FLAGS            Flags;                           // in:
} D3DKMT_SETDISPLAYMODE;


typedef struct _D3DKMT_MULTISAMPLEMETHOD
{
    UINT    NumSamples;
    UINT    NumQualityLevels;
    UINT    Reserved;   //workaround for NTRAID#Longhorn-1124385-2005/03/14-kanqiu
} D3DKMT_MULTISAMPLEMETHOD;

typedef struct _D3DKMT_GETMULTISAMPLEMETHODLIST
{
    D3DKMT_HANDLE                   hAdapter;       // in: adapter handle
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;  // in: adapter's VidPN source ID
    UINT                            Width;          // in:
    UINT                            Height;         // in:
    D3DDDIFORMAT                    Format;         // in:
    D3DKMT_PTR(D3DKMT_MULTISAMPLEMETHOD*, pMethodList); // out:
    UINT                            MethodCount;    // in/out:
} D3DKMT_GETMULTISAMPLEMETHODLIST;

typedef struct _D3DKMT_PRESENTFLAGS
{
    union
    {
        struct
        {
            UINT    Blt                         : 1;        // 0x00000001
            UINT    ColorFill                   : 1;        // 0x00000002
            UINT    Flip                        : 1;        // 0x00000004
            UINT    FlipDoNotFlip               : 1;        // 0x00000008
            UINT    FlipDoNotWait               : 1;        // 0x00000010
            UINT    FlipRestart                 : 1;        // 0x00000020
            UINT    DstRectValid                : 1;        // 0x00000040
            UINT    SrcRectValid                : 1;        // 0x00000080
            UINT    RestrictVidPnSource         : 1;        // 0x00000100
            UINT    SrcColorKey                 : 1;        // 0x00000200
            UINT    DstColorKey                 : 1;        // 0x00000400
            UINT    LinearToSrgb                : 1;        // 0x00000800
            UINT    PresentCountValid           : 1;        // 0x00001000
            UINT    Rotate                      : 1;        // 0x00002000
            UINT    PresentToBitmap             : 1;        // 0x00004000
            UINT    RedirectedFlip              : 1;        // 0x00008000
            UINT    RedirectedBlt               : 1;        // 0x00010000
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
            UINT    FlipStereo                  : 1;        // 0x00020000   // This is a flip from a stereo alloc. Used in addition to Flip.
            UINT    FlipStereoTemporaryMono     : 1;        // 0x00040000   // This is a flip from a stereo alloc. The left image should used to produce both images. Used in addition to Flip.
            UINT    FlipStereoPreferRight       : 1;        // 0x00080000   // This is a flip from a stereo alloc. Use the right image when cloning to a mono monitor. Used in addition to Flip.
            UINT    BltStereoUseRight           : 1;        // 0x00100000   // This is a Blt from a stereo alloc to a mono alloc. The right image should be used.
            UINT    PresentHistoryTokenOnly     : 1;        // 0x00200000   // Submit Present History Token only.
            UINT    PresentRegionsValid         : 1;        // 0x00400000   // Ptr to present regions is valid
            UINT    PresentDDA                  : 1;        // 0x00800000   // Present from a DDA swapchain
            UINT    ProtectedContentBlankedOut  : 1;        // 0x01000000
            UINT    RemoteSession               : 1;        // 0x02000000
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
            UINT    CrossAdapter                : 1;        // 0x04000000
            UINT    DurationValid               : 1;        // 0x08000000
            UINT    PresentIndirect             : 1;        // 0x10000000   // Present to an indirect-display adapter
            UINT    PresentHMD                  : 1;        // 0x20000000   // Present from an HMD swapchain.
            UINT    Reserved                    : 2;        // 0xC0000000
#else
            UINT    Reserved                    : 6;        // 0xFC000000
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
#else
            UINT    Reserved                    : 15;       // 0xFFFE0000
#endif
        };
        UINT    Value;
    };
} D3DKMT_PRESENTFLAGS;

typedef enum _D3DKMT_PRESENT_MODEL
{
    D3DKMT_PM_UNINITIALIZED       = 0,
    D3DKMT_PM_REDIRECTED_GDI       = 1,
    D3DKMT_PM_REDIRECTED_FLIP      = 2,
    D3DKMT_PM_REDIRECTED_BLT       = 3,
    D3DKMT_PM_REDIRECTED_VISTABLT  = 4,
    D3DKMT_PM_SCREENCAPTUREFENCE   = 5,
    D3DKMT_PM_REDIRECTED_GDI_SYSMEM  = 6,
    D3DKMT_PM_REDIRECTED_COMPOSITION = 7,
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
    D3DKMT_PM_SURFACECOMPLETE        = 8,
#endif
    D3DKMT_PM_FLIPMANAGER            = 9,
} D3DKMT_PRESENT_MODEL;

typedef enum _D3DKMT_FLIPMODEL_INDEPENDENT_FLIP_STAGE
{
    D3DKMT_FLIPMODEL_INDEPENDENT_FLIP_STAGE_FLIP_SUBMITTED = 0,
    D3DKMT_FLIPMODEL_INDEPENDENT_FLIP_STAGE_FLIP_COMPLETE = 1
} D3DKMT_FLIPMODEL_INDEPENDENT_FLIP_STAGE;

typedef struct _D3DKMT_FLIPMODEL_PRESENTHISTORYTOKENFLAGS
{
    union
    {
        struct
        {
            UINT  Video                         :  1;   // 0x00000001
            UINT  RestrictedContent             :  1;   // 0x00000002
            UINT  ClipToView                    :  1;   // 0x00000004
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
            UINT  StereoPreferRight             :  1;   // 0x00000008
            UINT  TemporaryMono                 :  1;   // 0x00000010
            UINT  FlipRestart                   :  1;   // 0x00000020
            UINT  HDRMetaDataChanged            :  1;   // 0x00000040
            UINT  AlphaMode                     :  2;   // 0x00000180
            UINT  SignalLimitOnTokenCompletion  :  1;   // 0x00000200
            UINT  YCbCrFlags                    :  3;   // 0x00001C00
            UINT  IndependentFlip               :  1;   // 0x00002000
            D3DKMT_FLIPMODEL_INDEPENDENT_FLIP_STAGE IndependentFlipStage : 2;   // 0x0000C000
            UINT  IndependentFlipReleaseCount   :  2;   // 0x00030000
            UINT  IndependentFlipForceNotifyDwm :  1;   // 0x00040000
            UINT  UseCustomDuration             :  1;   // 0x00080000
            UINT  IndependentFlipRequestDwmConfirm:1;   // 0x00100000
            UINT  IndependentFlipCandidate      :  1;   // 0x00200000
            UINT  IndependentFlipCheckNeeded    :  1;   // 0x00400000
            UINT  IndependentFlipTrueImmediate  :  1;   // 0x00800000
            UINT  IndependentFlipRequestDwmExit :  1;   // 0x01000000
            UINT  CompSurfaceNotifiedEarly      :  1;   // 0x02000000
            UINT  IndependentFlipDoNotFlip      :  1;   // 0x04000000
            UINT  RequirePairedToken            :  1;   // 0x08000000
            UINT  VariableRefreshOverrideEligible :1;   // 0x10000000
            UINT  Reserved                      :  3;   // 0xE0000000
#else
            UINT  Reserved                      : 29;   // 0xFFFFFFF8
#endif
        };

        UINT  Value;
    };
} D3DKMT_FLIPMODEL_PRESENTHISTORYTOKENFLAGS;

#define D3DKMT_MAX_PRESENT_HISTORY_RECTS 16

typedef struct _D3DKMT_DIRTYREGIONS
{
    UINT  NumRects;
    RECT  Rects[D3DKMT_MAX_PRESENT_HISTORY_RECTS];
} D3DKMT_DIRTYREGIONS;

typedef struct _D3DKMT_COMPOSITION_PRESENTHISTORYTOKEN
{
    D3DKMT_ALIGN64 ULONG64 hPrivateData;
} D3DKMT_COMPOSITION_PRESENTHISTORYTOKEN;

typedef struct _D3DKMT_FLIPMANAGER_PRESENTHISTORYTOKEN
{
    D3DKMT_ALIGN64 ULONG64 hPrivateData;
    D3DKMT_ALIGN64 ULONGLONG PresentAtQpc;
    union
    {
        struct
        {
            UINT Discard   : 1;
            UINT PresentAt : 1;
            UINT hPrivateDataIsPointer : 1;
            UINT Reserved  : 29;
        };
        UINT Value;
    }Flags;
} D3DKMT_FLIPMANAGER_PRESENTHISTORYTOKEN;

typedef enum _D3DKMT_AUXILIARYPRESENTINFO_TYPE
{
    D3DKMT_AUXILIARYPRESENTINFO_TYPE_FLIPMANAGER = 0
} D3DKMT_AUXILIARYPRESENTINFO_TYPE;

typedef struct _D3DKMT_AUXILIARYPRESENTINFO
{
    UINT size;
    D3DKMT_AUXILIARYPRESENTINFO_TYPE type;
} D3DKMT_AUXILIARYPRESENTINFO;

typedef struct _D3DKMT_FLIPMANAGER_AUXILIARYPRESENTINFO
{
    // in: Base information
    D3DKMT_AUXILIARYPRESENTINFO auxiliaryPresentInfo;

    // in: Tracing ID of owner flip manager
    UINT flipManagerTracingId;

    // in: Whether or not the application requested a different custom duration
    // than the previous present
    BOOL customDurationChanged;

    // out: The adapter LUID/VidPn source of the flip output
    LUID FlipAdapterLuid;
    D3DDDI_VIDEO_PRESENT_SOURCE_ID VidPnSourceId;

    // out: Independent flip stage
    D3DKMT_FLIPMODEL_INDEPENDENT_FLIP_STAGE independentFlipStage;

    // out: The DPC frame time of the frame on which the flip was completed
    D3DKMT_ALIGN64 ULONGLONG FlipCompletedQpc;

    // out: The approved frame duration
    UINT HwPresentDurationQpc;

    // out: Whether or not the present was canceled in the scheduler
    BOOL WasCanceled;

    // out: An IFlip submitted token was subsequently cancelled and should be resubmitted as non-IFlip token.
    BOOL ConvertedToNonIFlip;
} D3DKMT_FLIPMANAGER_AUXILIARYPRESENTINFO;

typedef struct _D3DKMT_GDIMODEL_PRESENTHISTORYTOKEN
{
    D3DKMT_ALIGN64 ULONG64 hLogicalSurface;
    D3DKMT_ALIGN64 ULONG64 hPhysicalSurface;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
    RECT                 ScrollRect;
    POINT                ScrollOffset;
#endif
    D3DKMT_DIRTYREGIONS  DirtyRegions;
} D3DKMT_GDIMODEL_PRESENTHISTORYTOKEN;

typedef struct _D3DKMT_GDIMODEL_SYSMEM_PRESENTHISTORYTOKEN
{
    D3DKMT_ALIGN64 ULONG64 hlsurf;
    DWORD dwDirtyFlags;
    D3DKMT_ALIGN64 UINT64 uiCookie;
} D3DKMT_GDIMODEL_SYSMEM_PRESENTHISTORYTOKEN;

typedef ULONGLONG  D3DKMT_VISTABLTMODEL_PRESENTHISTORYTOKEN;

typedef struct _D3DKMT_FENCE_PRESENTHISTORYTOKEN
{
    D3DKMT_ALIGN64 UINT64 Key;
} D3DKMT_FENCE_PRESENTHISTORYTOKEN;

typedef struct _D3DKMT_BLTMODEL_PRESENTHISTORYTOKEN
{
    D3DKMT_ALIGN64 ULONG64 hLogicalSurface;
    D3DKMT_ALIGN64 ULONG64 hPhysicalSurface;
    D3DKMT_ALIGN64 ULONG64 EventId;
    D3DKMT_DIRTYREGIONS                 DirtyRegions;
} D3DKMT_BLTMODEL_PRESENTHISTORYTOKEN;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
#define D3DKMT_MAX_PRESENT_HISTORY_SCATTERBLTS 12

typedef struct _D3DKMT_SCATTERBLT
{
    D3DKMT_ALIGN64 ULONG64 hLogicalSurfaceDestination;
    D3DKMT_ALIGN64 LONG64  hDestinationCompSurfDWM;
    D3DKMT_ALIGN64 UINT64  DestinationCompositionBindingId;
    RECT    SourceRect;
    POINT   DestinationOffset;
} D3DKMT_SCATTERBLT;

typedef struct _D3DKMT_SCATTERBLTS
{
    UINT NumBlts;
    D3DKMT_SCATTERBLT Blts[D3DKMT_MAX_PRESENT_HISTORY_SCATTERBLTS];
} D3DKMT_SCATTERBLTS;
#endif

typedef struct _D3DKMT_FLIPMODEL_PRESENTHISTORYTOKEN
{
    D3DKMT_ALIGN64 UINT64                      FenceValue;
    D3DKMT_ALIGN64 ULONG64                     hLogicalSurface;
    D3DKMT_ALIGN64 D3DKMT_UINT_PTR             dxgContext;
    D3DDDI_VIDEO_PRESENT_SOURCE_ID             VidPnSourceId;
    UINT                                       SwapChainIndex;
    D3DKMT_ALIGN64 UINT64                      PresentLimitSemaphoreId;
    D3DDDI_FLIPINTERVAL_TYPE                   FlipInterval;
    D3DKMT_FLIPMODEL_PRESENTHISTORYTOKENFLAGS  Flags;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
    D3DKMT_ALIGN64 LONG64                      hCompSurf;
    LUID                                       compSurfLuid;
    D3DKMT_ALIGN64 UINT64                      confirmationCookie;
    D3DKMT_ALIGN64 UINT64                      CompositionSyncKey;
    UINT                                       RemainingTokens;
    RECT                                       ScrollRect;
    POINT                                      ScrollOffset;
    UINT                                       PresentCount;
    FLOAT                                      RevealColor[4]; // index 0 == R, ... , 3 == A
    D3DDDI_ROTATION                            Rotation;
    union
    {
        D3DKMT_SCATTERBLTS                     ScatterBlts;     // Unused
        struct
        {
            HANDLE                             hSyncObject;     // NT handle to FlipEx fence.
            D3DDDI_HDR_METADATA_TYPE           HDRMetaDataType;
            union
            {
                D3DDDI_HDR_METADATA_HDR10      HDRMetaDataHDR10;
                D3DDDI_HDR_METADATA_HDR10PLUS  HDRMetaDataHDR10Plus;
            };
        };
    };
    UINT                                       InkCookie;
    RECT                                       SourceRect;
    UINT                                       DestWidth;
    UINT                                       DestHeight;
    RECT                                       TargetRect;
    // DXGI_MATRIX_3X2_F: _11 _12 _21 _22 _31 _32
    FLOAT                                      Transform[6];
    UINT                                       CustomDuration;
    D3DDDI_FLIPINTERVAL_TYPE                   CustomDurationFlipInterval;
    UINT                                       PlaneIndex;
#endif
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
    D3DDDI_COLOR_SPACE_TYPE                    ColorSpace;
#endif
    D3DKMT_DIRTYREGIONS                        DirtyRegions;
} D3DKMT_FLIPMODEL_PRESENTHISTORYTOKEN;

// User mode timeout is in milliseconds, kernel mode timeout is in 100 nanoseconds
#define FLIPEX_TIMEOUT_USER     (2000)
#define FLIPEX_TIMEOUT_KERNEL   (FLIPEX_TIMEOUT_USER*10000)

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
typedef struct _D3DKMT_SURFACECOMPLETE_PRESENTHISTORYTOKEN
{
    D3DKMT_ALIGN64 ULONG64 hLogicalSurface;
} D3DKMT_SURFACECOMPLETE_PRESENTHISTORYTOKEN;
#endif

typedef struct _D3DKMT_PRESENTHISTORYTOKEN
{
    D3DKMT_PRESENT_MODEL  Model;
    // The size of the present history token in bytes including Model.
    // Should be set to zero by when submitting a token.
    // It will be initialized when reading present history and can be used to
    // go to the next token in the present history buffer.
    UINT                  TokenSize;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
    // The binding id as specified by the Composition Surface
    UINT64                CompositionBindingId;
#endif

    union
    {
        D3DKMT_FLIPMODEL_PRESENTHISTORYTOKEN        Flip;
        D3DKMT_BLTMODEL_PRESENTHISTORYTOKEN         Blt;
        D3DKMT_VISTABLTMODEL_PRESENTHISTORYTOKEN    VistaBlt;
        D3DKMT_GDIMODEL_PRESENTHISTORYTOKEN         Gdi;
        D3DKMT_FENCE_PRESENTHISTORYTOKEN            Fence;
        D3DKMT_GDIMODEL_SYSMEM_PRESENTHISTORYTOKEN  GdiSysMem;
        D3DKMT_COMPOSITION_PRESENTHISTORYTOKEN      Composition;
        D3DKMT_FLIPMANAGER_PRESENTHISTORYTOKEN      FlipManager;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
        D3DKMT_SURFACECOMPLETE_PRESENTHISTORYTOKEN  SurfaceComplete;
#endif
    }
    Token;
} D3DKMT_PRESENTHISTORYTOKEN;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
typedef struct _D3DKMT_PRESENT_RGNS
{
    UINT DirtyRectCount;
    D3DKMT_PTR(_Field_size_( DirtyRectCount ) const RECT*, pDirtyRects);
    UINT MoveRectCount;
    D3DKMT_PTR(_Field_size_( MoveRectCount ) const D3DKMT_MOVE_RECT*, pMoveRects);
}D3DKMT_PRESENT_RGNS;
#endif

typedef struct _D3DKMT_PRESENT
{
    union
    {
        D3DKMT_HANDLE               hDevice;            // in: D3D10 compatibility.
        D3DKMT_HANDLE               hContext;           // in: Indentifies the context
    };
    D3DKMT_PTR(HWND,                hWindow);           // in: window to present to
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;      // in: VidPn source ID if RestrictVidPnSource is flagged
    D3DKMT_HANDLE                   hSource;            // in: Source allocation to present from
    D3DKMT_HANDLE                   hDestination;       // in: Destination allocation whenever non-zero
    UINT                            Color;              // in: color value in ARGB 32 bit format
    RECT                            DstRect;            // in: unclipped dest rect
    RECT                            SrcRect;            // in: unclipped src rect
    UINT                            SubRectCnt;         // in: count of sub rects
    D3DKMT_PTR(CONST RECT*,         pSrcSubRects);      // in: sub rects in source space
    UINT                            PresentCount;       // in: present counter
    D3DDDI_FLIPINTERVAL_TYPE        FlipInterval;       // in: flip interval
    D3DKMT_PRESENTFLAGS             Flags;              // in:
    ULONG                           BroadcastContextCount;                          // in: Specifies the number of context
                                                                                    //     to broadcast this command buffer to.
    D3DKMT_HANDLE                   BroadcastContext[D3DDDI_MAX_BROADCAST_CONTEXT]; // in: Specifies the handle of the context to
                                                                                    //     broadcast to.
    HANDLE                          PresentLimitSemaphore;
    D3DKMT_PRESENTHISTORYTOKEN      PresentHistoryToken;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
    D3DKMT_PRESENT_RGNS*            pPresentRegions;
#endif
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
    union
    {
        D3DKMT_HANDLE               hAdapter;           // in: iGpu adapter for PHT redirection. Valid only when the CrossAdapter flag is set.
        D3DKMT_HANDLE               hIndirectContext;   // in: indirect adapter context for redirecting through the DoD present path. Only
                                                        //     valid if PresentIndirect flag is set.
    };
    UINT                            Duration;           // in: Per-present duration. Valid only when the DurationValid flag is set.
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
    D3DKMT_PTR(_Field_size_(BroadcastContextCount)
    D3DKMT_HANDLE*,                 BroadcastSrcAllocation);                    // in: LDA
    D3DKMT_PTR(_Field_size_opt_(BroadcastContextCount)
    D3DKMT_HANDLE*,                 BroadcastDstAllocation);                    // in: LDA
    UINT                            PrivateDriverDataSize;                      // in:
    D3DKMT_PTR(_Field_size_bytes_(PrivateDriverDataSize)
    PVOID,                          pPrivateDriverData);                        // in: Private driver data to pass to DdiPresent and DdiSetVidPnSourceAddress
    BOOLEAN                         bOptimizeForComposition;                    // out: DWM is involved in composition
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
} D3DKMT_PRESENT;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_3)
typedef struct _D3DKMT_PRESENT_REDIRECTEDS_FLAGS
{
    union
    {
        struct
        {
            UINT Reserved : 32; // 0xFFFFFFFF
        };
        UINT Value;
    };
}D3DKMT_PRESENT_REDIRECTED_FLAGS;

typedef struct _D3DKMT_PRESENT_REDIRECTED
{
    D3DKMT_HANDLE                   hSyncObj;              // in: Sync object PHT waits on
    D3DKMT_HANDLE                   hDevice;               // in: Device associated with the present
    D3DKMT_ALIGN64 ULONGLONG        WaitedFenceValue;      // in: Fence value of hSyncObj that PHT waits on
    D3DKMT_PRESENTHISTORYTOKEN      PresentHistoryToken;
    D3DKMT_PRESENT_REDIRECTED_FLAGS Flags;
    D3DKMT_HANDLE                   hSource;               // in: Source allocation to present from
    UINT                            PrivateDriverDataSize; // in:
    D3DKMT_PTR(_Field_size_bytes_(PrivateDriverDataSize)
    PVOID,                          pPrivateDriverData);   // in: Private driver data to pass to DdiPresent and DdiSetVidPnSourceAddress
}D3DKMT_PRESENT_REDIRECTED;
#endif

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM3_0)
typedef struct _D3DKMT_CANCEL_PRESENTS_FLAGS
{
    union
    {
        // D3DKMT_CANCEL_PRESENTS_OPERATION_REPROGRAM_INTERRUPT flags
        struct
        {
            UINT NewVSyncInterruptState :  1;
            UINT Reserved               : 31;
        } ReprogramInterrupt;

        UINT Value;
    };
}D3DKMT_CANCEL_PRESENTS_FLAGS;


typedef enum D3DKMT_CANCEL_PRESENTS_OPERATION
{
    D3DKMT_CANCEL_PRESENTS_OPERATION_CANCEL_FROM            = 0,
    D3DKMT_CANCEL_PRESENTS_OPERATION_REPROGRAM_INTERRUPT    = 1
} D3DKMT_CANCEL_PRESENTS_OPERATION;

typedef struct _D3DKMT_CANCEL_PRESENTS
{
    UINT                                cbSize;
    D3DKMT_HANDLE                       hDevice;
    D3DKMT_CANCEL_PRESENTS_FLAGS        Flags;
    D3DKMT_CANCEL_PRESENTS_OPERATION    Operation;
    D3DKMT_ALIGN64 UINT64               CancelFromPresentId;
    LUID                                CompSurfaceLuid;
    D3DKMT_ALIGN64 UINT64               BindId;
}D3DKMT_CANCEL_PRESENTS;
#endif

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM3_1)


typedef struct _D3DKMT_CREATE_DOORBELL_FLAGS
{
    union
    {
        struct
        {
            UINT RequireSecondaryCpuVA : 1;
            UINT ResizeRingBufferOperation : 1;
            UINT Reserved : 30;
        };
        UINT Value;
    };
}D3DKMT_CREATE_DOORBELL_FLAGS;

typedef struct _D3DKMT_CREATE_DOORBELL
{
    D3DKMT_HANDLE hHwQueue;                                                   // in:      HWQueue for which doorbell is required
    D3DKMT_HANDLE hRingBuffer;                                                // in:      Ring buffer allocation handle
    D3DKMT_HANDLE hRingBufferControl;                                         // in opt:  ring buffer control area allocation handle
    D3DKMT_CREATE_DOORBELL_FLAGS Flags;                                       // in opt:  flags
    _Field_range_(0, D3DDDI_DOORBELL_PRIVATEDATA_MAX_BYTES_WDDM3_1)
    UINT PrivateDriverDataSize;                                               // in:      Size of private driver data
    D3DKMT_PTR(_Field_size_(PrivateDriverDataSize) VOID*, PrivateDriverData); // in/out:  Private driver data
    D3DKMT_PTR(VOID*, DoorbellCPUVirtualAddress);                             // out:     CPU VA of the created doorbell
    D3DKMT_PTR(VOID*, DoorbellSecondaryCPUVirtualAddress);                    // out opt: Secondary CPU VA of the created doorbell
    D3DKMT_PTR(VOID*, DoorbellStatusCPUVirtualAddress);                       // out:     CPU VA of the status page of doorbell
}D3DKMT_CREATE_DOORBELL;

typedef struct _D3DKMT_CONNECT_DOORBELL_FLAGS
{
    union
    {
        struct
        {
            UINT Reserved : 32;
        };
        UINT Value;
    };
}D3DKMT_CONNECT_DOORBELL_FLAGS;

typedef struct _D3DKMT_CONNECT_DOORBELL
{
    D3DKMT_HANDLE hHwQueue;             // in: UM handle to HWQueue whose doorbell is to be connected
    D3DKMT_CONNECT_DOORBELL_FLAGS Flags;
}D3DKMT_CONNECT_DOORBELL;

typedef struct _D3DKMT_DESTROY_DOORBELL
{
    D3DKMT_HANDLE hHwQueue; // in: UM handle to HWQueue whose doorbell is to be destroyed
}D3DKMT_DESTROY_DOORBELL;

typedef struct _D3DKMT_NOTIFY_WORK_SUBMISSION_FLAGS
{
    union
    {
        struct
        {
            UINT Reserved : 32;
        };
        UINT Value;
    };
}D3DKMT_NOTIFY_WORK_SUBMISSION_FLAGS;

typedef struct _D3DKMT_NOTIFY_WORK_SUBMISSION
{
    D3DKMT_HANDLE hHwQueue;                    // in: UM handle to HWQueue
    D3DKMT_NOTIFY_WORK_SUBMISSION_FLAGS Flags;
}D3DKMT_NOTIFY_WORK_SUBMISSION;
#endif

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_4)

typedef struct _D3DKMT_SUBMITPRESENTBLTTOHWQUEUE
{
    D3DKMT_HANDLE         hHwQueue;
    D3DKMT_ALIGN64 UINT64 HwQueueProgressFenceId;
    D3DKMT_PRESENT        PrivatePresentData;
} D3DKMT_SUBMITPRESENTBLTTOHWQUEUE;

#endif

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_5)

typedef struct _D3DKMT_SUBMITPRESENTTOHWQUEUE
{
    D3DKMT_PTR(_Field_size_(PrivatePresentData.BroadcastContextCount + 1)
    D3DKMT_HANDLE*, hHwQueues);
    D3DKMT_PRESENT  PrivatePresentData;
} D3DKMT_SUBMITPRESENTTOHWQUEUE;

#endif

#define D3DKMT_MAX_MULTIPLANE_OVERLAY_PLANES                   8
#define D3DKMT_MAX_MULTIPLANE_OVERLAY_ALLOCATIONS_PER_PLANE   256

typedef enum D3DKMT_MULTIPLANE_OVERLAY_FLAGS
{
    D3DKMT_MULTIPLANE_OVERLAY_FLAG_VERTICAL_FLIP               = 0x1,
    D3DKMT_MULTIPLANE_OVERLAY_FLAG_HORIZONTAL_FLIP             = 0x2,
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM3_0)
    D3DKMT_MULTIPLANE_OVERLAY_FLAG_STATIC_CHECK                = 0x4,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM3_0
} D3DKMT_MULTIPLANE_OVERLAY_FLAGS;

typedef enum D3DKMT_MULTIPLANE_OVERLAY_BLEND
{
    D3DKMT_MULTIPLANE_OVERLAY_BLEND_OPAQUE     = 0x0,
    D3DKMT_MULTIPLANE_OVERLAY_BLEND_ALPHABLEND = 0x1,
} D3DKMT_MULTIPLANE_OVERLAY_BLEND;

typedef enum D3DKMT_MULTIPLANE_OVERLAY_VIDEO_FRAME_FORMAT
{
    D3DKMT_MULIIPLANE_OVERLAY_VIDEO_FRAME_FORMAT_PROGRESSIVE  = 0,
    D3DKMT_MULTIPLANE_OVERLAY_VIDEO_FRAME_FORMAT_INTERLACED_TOP_FIELD_FIRST   = 1,
    D3DKMT_MULTIPLANE_OVERLAY_VIDEO_FRAME_FORMAT_INTERLACED_BOTTOM_FIELD_FIRST    = 2
} D3DKMT_MULTIPLANE_OVERLAY_VIDEO_FRAME_FORMAT;

typedef enum D3DKMT_MULTIPLANE_OVERLAY_YCbCr_FLAGS
{
    D3DKMT_MULTIPLANE_OVERLAY_YCbCr_FLAG_NOMINAL_RANGE = 0x1, // 16 - 235 vs. 0 - 255
    D3DKMT_MULTIPLANE_OVERLAY_YCbCr_FLAG_BT709         = 0x2, // BT.709 vs. BT.601
    D3DKMT_MULTIPLANE_OVERLAY_YCbCr_FLAG_xvYCC         = 0x4, // xvYCC vs. conventional YCbCr
} D3DKMT_MULTIPLANE_OVERLAY_YCbCr_FLAGS;

typedef enum D3DKMT_MULTIPLANE_OVERLAY_STEREO_FORMAT
{
    DXGKMT_MULTIPLANE_OVERLAY_STEREO_FORMAT_MONO               = 0,
    D3DKMT_MULTIPLANE_OVERLAY_STEREO_FORMAT_HORIZONTAL         = 1,
    D3DKMT_MULTIPLANE_OVERLAY_STEREO_FORMAT_VERTICAL           = 2,
    DXGKMT_MULTIPLANE_OVERLAY_STEREO_FORMAT_SEPARATE           = 3,
    DXGKMT_MULTIPLANE_OVERLAY_STEREO_FORMAT_MONO_OFFSET        = 4,
    DXGKMT_MULTIPLANE_OVERLAY_STEREO_FORMAT_ROW_INTERLEAVED    = 5,
    DXGKMT_MULTIPLANE_OVERLAY_STEREO_FORMAT_COLUMN_INTERLEAVED = 6,
    DXGKMT_MULTIPLANE_OVERLAY_STEREO_FORMAT_CHECKERBOARD       = 7
} D3DKMT_MULTIPLANE_OVERLAY_STEREO_FORMAT;

typedef enum _DXGKMT_MULTIPLANE_OVERLAY_STEREO_FLIP_MODE
{
    DXGKMT_MULTIPLANE_OVERLAY_STEREO_FLIP_NONE   = 0,
    DXGKMT_MULTIPLANE_OVERLAY_STEREO_FLIP_FRAME0 = 1,
    DXGKMT_MULTIPLANE_OVERLAY_STEREO_FLIP_FRAME1 = 2,
} DXGKMT_MULTIPLANE_OVERLAY_STEREO_FLIP_MODE;

typedef enum _DXGKMT_MULTIPLANE_OVERLAY_STRETCH_QUALITY
{
    DXGKMT_MULTIPLANE_OVERLAY_STRETCH_QUALITY_BILINEAR        = 0x1,  // Bilinear
    DXGKMT_MULTIPLANE_OVERLAY_STRETCH_QUALITY_HIGH            = 0x2,  // Maximum
} DXGKMT_MULTIPLANE_OVERLAY_STRETCH_QUALITY;

typedef struct D3DKMT_MULTIPLANE_OVERLAY_ATTRIBUTES
{
    UINT                                         Flags;      // D3DKMT_MULTIPLANE_OVERLAY_FLAGS
    RECT                                         SrcRect;
    RECT                                         DstRect;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
    RECT                                         ClipRect;
#endif
    D3DDDI_ROTATION                              Rotation;
    D3DKMT_MULTIPLANE_OVERLAY_BLEND              Blend;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
    UINT                                         DirtyRectCount;
    D3DKMT_PTR(RECT*,                            pDirtyRects);
#else
    UINT                                         NumFilters;
    D3DKMT_PTR(void*,                            pFilters);
#endif
    D3DKMT_MULTIPLANE_OVERLAY_VIDEO_FRAME_FORMAT VideoFrameFormat;
    UINT                                         YCbCrFlags; // D3DKMT_MULTIPLANE_OVERLAY_YCbCr_FLAGS
    D3DKMT_MULTIPLANE_OVERLAY_STEREO_FORMAT      StereoFormat;
    BOOL                                         StereoLeftViewFrame0;
    BOOL                                         StereoBaseViewFrame0;
    DXGKMT_MULTIPLANE_OVERLAY_STEREO_FLIP_MODE   StereoFlipMode;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
    DXGKMT_MULTIPLANE_OVERLAY_STRETCH_QUALITY    StretchQuality;
#endif
} D3DKMT_MULTIPLANE_OVERLAY_ATTRIBUTES;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM_1_3)
typedef struct D3DKMT_CHECK_MULTIPLANE_OVERLAY_PLANE
{
    D3DKMT_HANDLE                        hResource;
    LUID                                 CompSurfaceLuid;
    D3DDDI_VIDEO_PRESENT_SOURCE_ID       VidPnSourceId;
    D3DKMT_MULTIPLANE_OVERLAY_ATTRIBUTES PlaneAttributes;
} D3DKMT_CHECK_MULTIPLANE_OVERLAY_PLANE;

typedef struct D3DKMT_CHECK_MULTIPLANE_OVERLAY_SUPPORT_RETURN_INFO
{
    union
    {
        struct
        {
            UINT    FailingPlane        : 4;   // The 0 based index of the first plane that could not be supported
            UINT    TryAgain            : 1;   // The configuration is not supported due to a transition condition, which should shortly go away
            UINT    Reserved            : 27;
        };
        UINT    Value;
    };
} D3DKMT_CHECK_MULTIPLANE_OVERLAY_SUPPORT_RETURN_INFO;

typedef struct _D3DKMT_CHECKMULTIPLANEOVERLAYSUPPORT
{
    D3DKMT_HANDLE                                       hDevice;            // in : Indentifies the device
    UINT                                                PlaneCount;         // in : Number of resources to pin
    D3DKMT_PTR(D3DKMT_CHECK_MULTIPLANE_OVERLAY_PLANE*,  pOverlayPlanes);    // in : Array of resource handles to pin
    BOOL                                                Supported;
    D3DKMT_CHECK_MULTIPLANE_OVERLAY_SUPPORT_RETURN_INFO ReturnInfo;
} D3DKMT_CHECKMULTIPLANEOVERLAYSUPPORT;
#endif

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM_2_0)
typedef struct _D3DKMT_MULTIPLANE_OVERLAY_ATTRIBUTES2
{
    UINT                                         Flags;     // D3DKMT_MULTIPLANE_OVERLAY_FLAGS
    RECT                                         SrcRect;   // Specifies the source rectangle, of type RECT, relative to the source resource.
    RECT                                         DstRect;   // Specifies the destination rectangle, of type RECT, relative to the monitor resolution.
    RECT                                         ClipRect;  // Specifies any additional clipping, of type RECT, relative to the DstRect rectangle,
                                                            // after the data has been stretched according to the values of SrcRect and DstRect.

                                                            // The driver and hardware can use the ClipRect member to apply a common stretch factor
                                                            // as the clipping changes when an app occludes part of the DstRect destination rectangle.
    D3DDDI_ROTATION                              Rotation;  // Specifies the clockwise rotation of the overlay plane, given as a value from the D3DDDI_ROTATION enumeration.
    D3DKMT_MULTIPLANE_OVERLAY_BLEND              Blend;     // Specifies the blend mode that applies to this overlay plane and the plane beneath it, given as a value from the DXGK_MULTIPLANE_OVERLAY_BLEND enumeration.
    UINT                                         DirtyRectCount;
    D3DKMT_PTR(RECT*,                            pDirtyRects);
    D3DKMT_MULTIPLANE_OVERLAY_VIDEO_FRAME_FORMAT VideoFrameFormat;  // DXGK_MULTIPLANE_OVERLAY_VIDEO_FRAME_FORMAT
    D3DDDI_COLOR_SPACE_TYPE                      ColorSpace;
    D3DKMT_MULTIPLANE_OVERLAY_STEREO_FORMAT      StereoFormat;      // DXGK_MULTIPLANE_OVERLAY_STEREO_FORMAT
    BOOL                                         StereoLeftViewFrame0;  // Reserved for system use. Must always be FALSE.
    BOOL                                         StereoBaseViewFrame0;  // Reserved for system use. Must always be FALSE.
    DXGKMT_MULTIPLANE_OVERLAY_STEREO_FLIP_MODE   StereoFlipMode;        // DXGK_MULTIPLANE_OVERLAY_STEREO_FLIP_MODE
    DXGKMT_MULTIPLANE_OVERLAY_STRETCH_QUALITY    StretchQuality;        // DXGK_MULTIPLANE_OVERLAY_STRETCH_QUALITY
    UINT                                         Reserved1;
} D3DKMT_MULTIPLANE_OVERLAY_ATTRIBUTES2;

typedef struct _D3DKMT_CHECK_MULTIPLANE_OVERLAY_PLANE2
{
    UINT                                  LayerIndex;
    D3DKMT_HANDLE                         hResource;
    LUID                                  CompSurfaceLuid;
    D3DDDI_VIDEO_PRESENT_SOURCE_ID        VidPnSourceId;
    D3DKMT_MULTIPLANE_OVERLAY_ATTRIBUTES2 PlaneAttributes;
} D3DKMT_CHECK_MULTIPLANE_OVERLAY_PLANE2;

typedef struct _D3DKMT_CHECKMULTIPLANEOVERLAYSUPPORT2
{
    D3DKMT_HANDLE                                       hAdapter;           // in: adapter handle
    D3DKMT_HANDLE                                       hDevice;            // in : Indentifies the device
    UINT                                                PlaneCount;         // in : Number of resources to pin
    D3DKMT_PTR(D3DKMT_CHECK_MULTIPLANE_OVERLAY_PLANE2*, pOverlayPlanes);    // in : Array of resource handles to pin
    BOOL                                                Supported;
    D3DKMT_CHECK_MULTIPLANE_OVERLAY_SUPPORT_RETURN_INFO ReturnInfo;
} D3DKMT_CHECKMULTIPLANEOVERLAYSUPPORT2;

typedef struct _D3DKMT_MULTIPLANE_OVERLAY2
{
    UINT                                  LayerIndex;
    BOOL                                  Enabled;
    D3DKMT_HANDLE                         hAllocation;
    D3DKMT_MULTIPLANE_OVERLAY_ATTRIBUTES2 PlaneAttributes;
} D3DKMT_MULTIPLANE_OVERLAY2;

typedef struct _D3DKMT_PRESENT_MULTIPLANE_OVERLAY2
{
    D3DKMT_HANDLE                   hAdapter;           // in: adapter handle
    union
    {
        D3DKMT_HANDLE               hDevice;            // in: D3D10 compatibility.
        D3DKMT_HANDLE               hContext;           // in: Indentifies the context
    };
    ULONG                           BroadcastContextCount;                          // in: Specifies the number of context
                                                                                    //     to broadcast this command buffer to.
    D3DKMT_HANDLE                   BroadcastContext[D3DDDI_MAX_BROADCAST_CONTEXT]; // in: Specifies the handle of the context to
                                                                                    //     broadcast to.

    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;      // in: VidPn source ID if RestrictVidPnSource is flagged
    UINT                            PresentCount;       // in: present counter
    D3DDDI_FLIPINTERVAL_TYPE        FlipInterval;       // in: flip interval
    D3DKMT_PRESENTFLAGS             Flags;              // in:

    UINT                            PresentPlaneCount;
    D3DKMT_PTR(D3DKMT_MULTIPLANE_OVERLAY2*, pPresentPlanes);
    UINT                            Duration;
} D3DKMT_PRESENT_MULTIPLANE_OVERLAY2;
#endif  // DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
typedef struct _D3DKMT_MULTIPLANE_OVERLAY_ATTRIBUTES3
{
    UINT                                         Flags;     // D3DKMT_MULTIPLANE_OVERLAY_FLAGS
    RECT                                         SrcRect;   // Specifies the source rectangle, of type RECT, relative to the source resource.
    RECT                                         DstRect;   // Specifies the destination rectangle, of type RECT, relative to the monitor resolution.
    RECT                                         ClipRect;  // Specifies any additional clipping, of type RECT, relative to the DstRect rectangle,
                                                            // after the data has been stretched according to the values of SrcRect and DstRect.

                                                            // The driver and hardware can use the ClipRect member to apply a common stretch factor
                                                            // as the clipping changes when an app occludes part of the DstRect destination rectangle.
    D3DDDI_ROTATION                              Rotation;  // Specifies the clockwise rotation of the overlay plane, given as a value from the D3DDDI_ROTATION enumeration.
    D3DKMT_MULTIPLANE_OVERLAY_BLEND              Blend;     // Specifies the blend mode that applies to this overlay plane and the plane beneath it, given as a value from the DXGK_MULTIPLANE_OVERLAY_BLEND enumeration.
    UINT                                         DirtyRectCount;
    D3DKMT_PTR(_Field_size_(DirtyRectCount) RECT*, pDirtyRects);
    D3DDDI_COLOR_SPACE_TYPE                      ColorSpace;
    DXGKMT_MULTIPLANE_OVERLAY_STRETCH_QUALITY    StretchQuality;        // DXGK_MULTIPLANE_OVERLAY_STRETCH_QUALITY
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_3)
    UINT                                         SDRWhiteLevel;
#endif
} D3DKMT_MULTIPLANE_OVERLAY_ATTRIBUTES3;

typedef struct _D3DKMT_CHECK_MULTIPLANE_OVERLAY_PLANE3
{
    UINT                                  LayerIndex;
    D3DKMT_HANDLE                         hResource;
    LUID                                  CompSurfaceLuid;
    D3DDDI_VIDEO_PRESENT_SOURCE_ID        VidPnSourceId;
    D3DKMT_PTR(D3DKMT_MULTIPLANE_OVERLAY_ATTRIBUTES3*, pPlaneAttributes);
} D3DKMT_CHECK_MULTIPLANE_OVERLAY_PLANE3;

typedef struct _D3DKMT_MULTIPLANE_OVERLAY_POST_COMPOSITION_FLAGS
{
    union
    {
        struct
        {
            UINT VerticalFlip              : 1;   // 0x00000001
            UINT HorizontalFlip            : 1;   // 0x00000002
            UINT Reserved                  :30;   // 0xFFFFFFFC
        };
        UINT Value;
    };
} D3DKMT_MULTIPLANE_OVERLAY_POST_COMPOSITION_FLAGS;

typedef struct _D3DKMT_MULTIPLANE_OVERLAY_POST_COMPOSITION
{
    D3DKMT_MULTIPLANE_OVERLAY_POST_COMPOSITION_FLAGS    Flags;
    RECT                                                SrcRect;
    RECT                                                DstRect;
    D3DDDI_ROTATION                                     Rotation;
} D3DKMT_MULTIPLANE_OVERLAY_POST_COMPOSITION;

typedef struct _D3DKMT_MULTIPLANE_OVERLAY_POST_COMPOSITION_WITH_SOURCE
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID             VidPnSourceId;
    D3DKMT_MULTIPLANE_OVERLAY_POST_COMPOSITION PostComposition;
} D3DKMT_MULTIPLANE_OVERLAY_POST_COMPOSITION_WITH_SOURCE;

typedef struct _D3DKMT_CHECKMULTIPLANEOVERLAYSUPPORT3
{
    D3DKMT_HANDLE                                            hAdapter;           // in: adapter handle
    D3DKMT_HANDLE                                            hDevice;            // in : Indentifies the device
    UINT                                                     PlaneCount;         // in : Number of resources to pin
    // Note: Array-of-pointers don't work in 32bit WSL
    _Field_size_(PlaneCount)
    D3DKMT_CHECK_MULTIPLANE_OVERLAY_PLANE3**                 ppOverlayPlanes;    // in : Array of pointers to overlay planes
    UINT                                                     PostCompositionCount; // in : Number of resources to pin
    _Field_size_(PostCompositionCount)
    D3DKMT_MULTIPLANE_OVERLAY_POST_COMPOSITION_WITH_SOURCE** ppPostComposition;    // in : Array of pointers to overlay planes
    BOOL                                                     Supported;
    D3DKMT_CHECK_MULTIPLANE_OVERLAY_SUPPORT_RETURN_INFO      ReturnInfo;
} D3DKMT_CHECKMULTIPLANEOVERLAYSUPPORT3;

typedef struct _D3DKMT_PLANE_SPECIFIC_INPUT_FLAGS
{
    union
    {
        struct
        {
            UINT Enabled                   : 1;   // 0x00000001
            UINT Reserved                  :31;   // 0xFFFFFFFE
        };
        UINT Value;
    };
} D3DKMT_PLANE_SPECIFIC_INPUT_FLAGS;

typedef struct _D3DKMT_PLANE_SPECIFIC_OUTPUT_FLAGS
{
    union
    {
        struct
        {
            UINT FlipConvertedToImmediate  : 1;   // 0x00000001
            UINT Reserved                  :31;   // 0xFFFFFFFE
        };
        UINT Value;
    };
} D3DKMT_PLANE_SPECIFIC_OUTPUT_FLAGS;

typedef struct _D3DKMT_MULTIPLANE_OVERLAY3
{
    UINT                                         LayerIndex;
    D3DKMT_PLANE_SPECIFIC_INPUT_FLAGS            InputFlags;
    D3DDDI_FLIPINTERVAL_TYPE                     FlipInterval;
    UINT                                         MaxImmediateFlipLine;
    UINT                                         AllocationCount;
    D3DKMT_PTR(_Field_size_(AllocationCount)
    D3DKMT_HANDLE*,                              pAllocationList);
    UINT                                         DriverPrivateDataSize;
    D3DKMT_PTR(_Field_size_bytes_(DriverPrivateDataSize)
    VOID*,                                       pDriverPrivateData);
    D3DKMT_PTR(const D3DKMT_MULTIPLANE_OVERLAY_ATTRIBUTES3*, pPlaneAttributes);
    D3DKMT_HANDLE                                hFlipToFence;
    D3DKMT_HANDLE                                hFlipAwayFence;
    D3DKMT_ALIGN64 UINT64                        FlipToFenceValue;
    D3DKMT_ALIGN64 UINT64                        FlipAwayFenceValue;
} D3DKMT_MULTIPLANE_OVERLAY3;

typedef struct _D3DKMT_PRESENT_MULTIPLANE_OVERLAY_FLAGS
{
    union
    {
        struct
        {
            UINT FlipStereo                 : 1;    // 0x00000001 This is a flip from a stereo alloc. Used in addition to FlipImmediate or FlipOnNextVSync.
            UINT FlipStereoTemporaryMono    : 1;    // 0x00000002 This is a flip from a stereo alloc. The left image should used. Used in addition to FlipImmediate or FlipOnNextVSync.
            UINT FlipStereoPreferRight      : 1;    // 0x00000004 This is a flip from a stereo alloc. The right image should used when cloning to a mono monitor. Used in addition to FlipImmediate or FlipOnNextVSync.
            UINT FlipDoNotWait              : 1;    // 0x00000008
            UINT FlipDoNotFlip              : 1;    // 0x00000010
            UINT FlipRestart                : 1;    // 0x00000020
            UINT DurationValid              : 1;    // 0x00000040
            UINT HDRMetaDataValid           : 1;    // 0x00000080
            UINT HMD                        : 1;    // 0x00000100
            UINT TrueImmediate              : 1;    // 0x00000200 If a present interval is 0, allow tearing rather than override a previously queued flip
            UINT FromDDisplay               : 1;    // 0x00000400 The flip is from DDisplay
            UINT Reserved                   :21;    // 0xFFFFFC00
        };
        UINT Value;
    };
} D3DKMT_PRESENT_MULTIPLANE_OVERLAY_FLAGS;

typedef struct _D3DKMT_PRESENT_MULTIPLANE_OVERLAY3
{
    D3DKMT_HANDLE                               hAdapter;           // in: adapter handle
    UINT                                        ContextCount;
    D3DKMT_PTR(_Field_size_(ContextCount)
    D3DKMT_HANDLE*,                             pContextList);

    D3DDDI_VIDEO_PRESENT_SOURCE_ID              VidPnSourceId;      // in: VidPn source ID if RestrictVidPnSource is flagged
    UINT                                        PresentCount;       // in: present counter
    D3DKMT_PRESENT_MULTIPLANE_OVERLAY_FLAGS     Flags;              // in:

    UINT                                        PresentPlaneCount;
    // Note: Array-of-pointers don't work in 32bit WSL
    _Field_size_(PresentPlaneCount)
    D3DKMT_MULTIPLANE_OVERLAY3**                ppPresentPlanes;
    D3DKMT_PTR(D3DKMT_MULTIPLANE_OVERLAY_POST_COMPOSITION*, pPostComposition);
    UINT                                        Duration;
    D3DDDI_HDR_METADATA_TYPE                    HDRMetaDataType;
    UINT                                        HDRMetaDataSize;
    D3DKMT_PTR(_Field_size_bytes_(HDRMetaDataSize)
    const VOID*,                                pHDRMetaData);
    UINT                                        BoostRefreshRateMultiplier;
} D3DKMT_PRESENT_MULTIPLANE_OVERLAY3;
#endif  // DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)
typedef struct _D3DKMT_MULTIPLANE_OVERLAY_CAPS
{
    union
    {
        struct
        {
            UINT Rotation                        : 1;    // Full rotation
            UINT RotationWithoutIndependentFlip  : 1;    // Rotation, but without simultaneous IndependentFlip support
            UINT VerticalFlip                    : 1;    // Can flip the data vertically
            UINT HorizontalFlip                  : 1;    // Can flip the data horizontally
            UINT StretchRGB                      : 1;    // Supports stretching RGB formats
            UINT StretchYUV                      : 1;    // Supports stretching YUV formats
            UINT BilinearFilter                  : 1;    // Blinear filtering
            UINT HighFilter                      : 1;    // Better than bilinear filtering
            UINT Shared                          : 1;    // MPO resources are shared across VidPnSources
            UINT Immediate                       : 1;    // Immediate flip support
            UINT Plane0ForVirtualModeOnly        : 1;    // Stretching plane 0 will also stretch the HW cursor and should only be used for virtual mode support
            UINT Version3DDISupport              : 1;    // Driver supports the 2.2 MPO DDIs
            UINT Reserved                        : 20;
        };
        UINT Value;
    };
} D3DKMT_MULTIPLANE_OVERLAY_CAPS;

typedef struct _D3DKMT_GET_MULTIPLANE_OVERLAY_CAPS
{
    D3DKMT_HANDLE                          hAdapter;             // in: adapter handle
    D3DDDI_VIDEO_PRESENT_SOURCE_ID         VidPnSourceId;        // in
    UINT                                   MaxPlanes;            // out: Total number of planes currently supported
    UINT                                   MaxRGBPlanes;         // out: Number of RGB planes currently supported
    UINT                                   MaxYUVPlanes;         // out: Number of YUV planes currently supported
    D3DKMT_MULTIPLANE_OVERLAY_CAPS         OverlayCaps;          // out: Overlay capabilities
    float                                  MaxStretchFactor;     // out
    float                                  MaxShrinkFactor;      // out
} D3DKMT_GET_MULTIPLANE_OVERLAY_CAPS;

typedef struct _D3DKMT_GET_POST_COMPOSITION_CAPS
{
    D3DKMT_HANDLE                          hAdapter;             // in: adapter handle
    D3DDDI_VIDEO_PRESENT_SOURCE_ID         VidPnSourceId;        // in
    float                                  MaxStretchFactor;     // out
    float                                  MaxShrinkFactor;      // out
} D3DKMT_GET_POST_COMPOSITION_CAPS;

typedef struct _D3DKMT_MULTIPLANEOVERLAY_STRETCH_SUPPORT
{
    UINT VidPnSourceId;
    BOOL Update;
    BOOL Supported;
} D3DKMT_MULTIPLANEOVERLAY_STRETCH_SUPPORT;
#endif  // DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2

typedef struct D3DKMT_MULTIPLANE_OVERLAY
{
    UINT                                 LayerIndex;
    BOOL                                 Enabled;
    D3DKMT_HANDLE                        hAllocation;
    D3DKMT_MULTIPLANE_OVERLAY_ATTRIBUTES PlaneAttributes;
} D3DKMT_MULTIPLANE_OVERLAY;

typedef struct D3DKMT_PRESENT_MULTIPLANE_OVERLAY
{
    union
    {
        D3DKMT_HANDLE               hDevice;            // in: D3D10 compatibility.
        D3DKMT_HANDLE               hContext;           // in: Indentifies the context
    };
    ULONG                           BroadcastContextCount;                          // in: Specifies the number of context
                                                                                    //     to broadcast this command buffer to.
    D3DKMT_HANDLE                   BroadcastContext[D3DDDI_MAX_BROADCAST_CONTEXT]; // in: Specifies the handle of the context to
                                                                                    //     broadcast to.

    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;      // in: VidPn source ID if RestrictVidPnSource is flagged
    UINT                            PresentCount;       // in: present counter
    D3DDDI_FLIPINTERVAL_TYPE        FlipInterval;       // in: flip interval
    D3DKMT_PRESENTFLAGS             Flags;              // in:

    UINT                            PresentPlaneCount;
    D3DKMT_MULTIPLANE_OVERLAY*      pPresentPlanes;
    UINT                            Duration;
} D3DKMT_PRESENT_MULTIPLANE_OVERLAY;

typedef struct _D3DKMT_RENDERFLAGS
{
    UINT    ResizeCommandBuffer     :  1;  // 0x00000001
    UINT    ResizeAllocationList    :  1;  // 0x00000002
    UINT    ResizePatchLocationList :  1;  // 0x00000004
    UINT    NullRendering           :  1;  // 0x00000008
    UINT    PresentRedirected       :  1;  // 0x00000010
    UINT    RenderKm                :  1;  // 0x00000020    Cannot be used with DxgkRender
    UINT    RenderKmReadback        :  1;  // 0x00000040    Cannot be used with DxgkRender
    UINT    Reserved                : 25;  // 0xFFFFFF80
} D3DKMT_RENDERFLAGS;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
typedef struct _D3DKMT_OUTPUTDUPLPRESENTFLAGS
{
    union
    {
        struct
        {
            UINT                ProtectedContentBlankedOut  :  1;
            UINT                RemoteSession               :  1;
            UINT                FullScreenPresent           :  1;
            UINT                PresentIndirect             :  1;
            UINT                Reserved                    : 28;
        };
        UINT    Value;
    };
}D3DKMT_OUTPUTDUPLPRESENTFLAGS;

typedef struct _D3DKMT_OUTPUTDUPLPRESENT
{
    D3DKMT_HANDLE                   hContext;           // in: Indentifies the context
    D3DKMT_HANDLE                   hSource;            // in: Source allocation to present from
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;
    ULONG                           BroadcastContextCount;                          // in: Specifies the number of context
    D3DKMT_HANDLE                   BroadcastContext[D3DDDI_MAX_BROADCAST_CONTEXT]; // in: Specifies the handle of the context to
    D3DKMT_PRESENT_RGNS             PresentRegions;     // in: Dirty and move regions
    D3DKMT_OUTPUTDUPLPRESENTFLAGS   Flags;
    D3DKMT_HANDLE                   hIndirectContext;
} D3DKMT_OUTPUTDUPLPRESENT;
#endif

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_6)

typedef struct _D3DKMT_OUTPUTDUPLPRESENTTOHWQUEUE
{
    D3DKMT_HANDLE                   hSource;            // in: Source allocation to present from
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;
    ULONG                           BroadcastHwQueueCount;
    D3DKMT_PTR(_Field_size_(BroadcastHwQueueCount)
    D3DKMT_HANDLE*,                 hHwQueues);
    D3DKMT_PRESENT_RGNS             PresentRegions;     // in: Dirty and move regions
    D3DKMT_OUTPUTDUPLPRESENTFLAGS   Flags;
    D3DKMT_HANDLE                   hIndirectHwQueue;
} D3DKMT_OUTPUTDUPLPRESENTTOHWQUEUE;

#endif

typedef struct _D3DKMT_RENDER
{
    union
    {
        D3DKMT_HANDLE               hDevice;                    // in: D3D10 compatibility.
        D3DKMT_HANDLE               hContext;                   // in: Indentifies the context
    };
    UINT                            CommandOffset;              // in: offset in bytes from start
    UINT                            CommandLength;              // in: number of bytes
    UINT                            AllocationCount;            // in: Number of allocations in allocation list.
    UINT                            PatchLocationCount;         // in: Number of patch locations in patch allocation list.
    D3DKMT_PTR(VOID*,               pNewCommandBuffer);         // out: Pointer to the next command buffer to use.
                                                                // in: When RenderKm flag is set, it points to a command buffer.
    UINT                            NewCommandBufferSize;       // in: Size requested for the next command buffer.
                                                                // out: Size of the next command buffer to use.
    D3DKMT_PTR(D3DDDI_ALLOCATIONLIST*, pNewAllocationList);     // out: Pointer to the next allocation list to use.
                                                                // in: When RenderKm flag is set, it points to an allocation list.
    UINT                            NewAllocationListSize;      // in: Size requested for the next allocation list.
                                                                // out: Size of the new allocation list.
    D3DKMT_PTR(D3DDDI_PATCHLOCATIONLIST*, pNewPatchLocationList); // out: Pointer to the next patch location list.
    UINT                            NewPatchLocationListSize;   // in: Size requested for the next patch location list.
                                                                // out: Size of the new patch location list.
    D3DKMT_RENDERFLAGS              Flags;                      // in:
    D3DKMT_ALIGN64 ULONGLONG        PresentHistoryToken;        // in: Present history token for redirected present calls
    ULONG                           BroadcastContextCount;                          // in: Specifies the number of context
                                                                                    //     to broadcast this command buffer to.
    D3DKMT_HANDLE                   BroadcastContext[D3DDDI_MAX_BROADCAST_CONTEXT]; // in: Specifies the handle of the context to
                                                                                    //     broadcast to.
    ULONG                           QueuedBufferCount;          // out: Number of DMA buffer queued to this context after this submission.
    D3DKMT_ALIGN64 D3DGPU_VIRTUAL_ADDRESS NewCommandBuffer;     // out: GPU virtual address of next command buffer to use. _ADVSCH_
    D3DKMT_PTR(VOID*,               pPrivateDriverData);        // in: pointer to private driver data. _ADVSCH_
    UINT                            PrivateDriverDataSize;      // in: size of private driver data. _ADVSCH_
} D3DKMT_RENDER;


typedef enum _D3DKMT_STANDARDALLOCATIONTYPE
{
    D3DKMT_STANDARDALLOCATIONTYPE_EXISTINGHEAP = 1,
    D3DKMT_STANDARDALLOCATIONTYPE_INTERNALBACKINGSTORE = 2,
    D3DKMT_STANDARDALLOCATIONTYPE_MAX,
} D3DKMT_STANDARDALLOCATIONTYPE;

typedef struct _D3DKMT_STANDARDALLOCATION_EXISTINGHEAP
{
    D3DKMT_ALIGN64 D3DKMT_SIZE_T Size;        // in: Size in bytes of existing heap
} D3DKMT_STANDARDALLOCATION_EXISTINGHEAP;

typedef struct _D3DKMT_CREATESTANDARDALLOCATIONFLAGS
{
    union
    {
        struct
        {
            UINT Reserved : 32; // 0xFFFFFFFF
        };
        UINT Value;
    };
} D3DKMT_CREATESTANDARDALLOCATIONFLAGS;

typedef struct _D3DKMT_CREATESTANDARDALLOCATION
{
    //
    // update onecoreuap/windows/core/ntuser/inc/whwin32.tpl when adding new memeber
    // to this struct
    //
    D3DKMT_STANDARDALLOCATIONTYPE Type;
    union
    {
        D3DKMT_STANDARDALLOCATION_EXISTINGHEAP ExistingHeapData;
    };
    D3DKMT_CREATESTANDARDALLOCATIONFLAGS Flags;
} D3DKMT_CREATESTANDARDALLOCATION;

typedef struct _D3DKMT_CREATEALLOCATIONFLAGS
{
    UINT    CreateResource              :  1;    // 0x00000001
    UINT    CreateShared                :  1;    // 0x00000002
    UINT    NonSecure                   :  1;    // 0x00000004
    UINT    CreateProtected             :  1;    // 0x00000008 Cannot be used when allocation is created from the user mode.
    UINT    RestrictSharedAccess        :  1;    // 0x00000010
    UINT    ExistingSysMem              :  1;    // 0x00000020 Cannot be used when allocation is created from the user mode.
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
    UINT    NtSecuritySharing           :  1;    // 0x00000040
    UINT    ReadOnly                    :  1;    // 0x00000080
    UINT    CreateWriteCombined         :  1;    // 0x00000100 Cannot be used when allocation is created from the user mode.
    UINT    CreateCached                :  1;    // 0x00000200 Cannot be used when allocation is created from the user mode.
    UINT    SwapChainBackBuffer         :  1;    // 0x00000400 Specifies whether an allocation corresponds to a swap chain back buffer.
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
    UINT    CrossAdapter                :  1;    // 0x00000800
    UINT    OpenCrossAdapter            :  1;    // 0x00001000 Cannot be used when allocation is created from the user mode.
    UINT    PartialSharedCreation       :  1;    // 0x00002000
    UINT    Zeroed                      :  1;    // 0x00004000  // out: set when allocation fulfilled by zero pages
    UINT    WriteWatch                  :  1;    // 0x00008000  // in: request Mm to track writes to pages of this allocation
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_3)
    UINT    StandardAllocation          :  1;    // 0x00010000  // in: use pStandardAllocation instead of pPrivateDriverData
    UINT    ExistingSection             :  1;    // 0x00020000  // in: Use Section Handle instead of SysMem in D3DDI_ALLOCATIONINFO2
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_6)
    UINT    AllowNotZeroed              :  1;    // 0x00040000  // in: indicate zeroed pages are not required
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_7)
    UINT    PhysicallyContiguous        :  1;    // 0x00080000  // in: indicate allocation must be physically contguous
    UINT    NoKmdAccess                 :  1;    // 0x00100000  // in: KMD is not notified about the allocation
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM3_0)
    UINT    SharedDisplayable           :  1;    // 0x00200000
    UINT    Reserved                    : 10;    // 0xFFC00000
#else
    UINT    Reserved                    : 11;    // 0xFFE00000
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM3_0)
#else
    UINT    Reserved                    : 13;    // 0xFFF80000
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_7)
#else
    UINT    Reserved                    : 14;    // 0xFFFC0000
#endif //(DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_6)
#else
    UINT    Reserved                    : 16;    // 0xFFFF0000
#endif //(DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_3)
#else
    UINT    Reserved                    : 21;    // 0xFFFFF800
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
#else
    UINT    Reserved                    : 26;    // 0xFFFFFFC0
#endif
} D3DKMT_CREATEALLOCATIONFLAGS;

typedef struct _D3DKMT_CREATEALLOCATION
{
    D3DKMT_HANDLE                   hDevice;
    D3DKMT_HANDLE                   hResource;      //in/out:valid only within device
    D3DKMT_HANDLE                   hGlobalShare;   //out:Shared handle if CreateShared and not NtSecuritySharing
    D3DKMT_PTR(_Field_size_bytes_(PrivateRuntimeDataSize)
    CONST VOID*,                    pPrivateRuntimeData);
    UINT                            PrivateRuntimeDataSize;
    union
    {
        //
        // update onecoreuap/windows/core/ntuser/inc/whwin32.tpl when adding new memeber
        // to this union
        //
        D3DKMT_CREATESTANDARDALLOCATION* pStandardAllocation;
        _Field_size_bytes_(PrivateDriverDataSize)
        CONST VOID*                      pPrivateDriverData;
        D3DKMT_PTR_HELPER(               AlignUnionTo64_1)
    };
    UINT                            PrivateDriverDataSize;
    UINT                            NumAllocations;
    union
    {
        _Field_size_(NumAllocations)       D3DDDI_ALLOCATIONINFO*   pAllocationInfo;
#if ((DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN7) || \
     (D3D_UMD_INTERFACE_VERSION >= D3D_UMD_INTERFACE_VERSION_WIN7))
        _Field_size_(NumAllocations)       D3DDDI_ALLOCATIONINFO2*  pAllocationInfo2; // _ADVSCH_
#endif
        D3DKMT_PTR_HELPER(                                          AlignUnionTo64_2)
    };
    D3DKMT_CREATEALLOCATIONFLAGS    Flags;
    D3DKMT_PTR(HANDLE,              hPrivateRuntimeResourceHandle); // opaque handle used for event tracing
} D3DKMT_CREATEALLOCATION;

typedef struct _D3DKMT_OPENRESOURCE
{
                                                        D3DKMT_HANDLE               hDevice;                            // in : Indentifies the device
                                                        D3DKMT_HANDLE               hGlobalShare;                       // in : Shared resource handle
                                                        UINT                        NumAllocations;                     // in : Number of allocations associated with the resource
   union {
    _Field_size_(NumAllocations)                      D3DDDI_OPENALLOCATIONINFO*  pOpenAllocationInfo;                // in : Array of open allocation structs
#if ((DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN7) || \
     (D3D_UMD_INTERFACE_VERSION >= D3D_UMD_INTERFACE_VERSION_WIN7))
    _Field_size_(NumAllocations)                      D3DDDI_OPENALLOCATIONINFO2* pOpenAllocationInfo2;                // in : Array of open allocation structs // _ADVSCH_
#endif
    D3DKMT_PTR_HELPER(AlignUnionTo64)
   };
    D3DKMT_PTR(_Field_size_bytes_(PrivateRuntimeDataSize) VOID*,                    pPrivateRuntimeData);               // in : Caller supplied buffer where the runtime private data associated with this resource will be copied
                                                        UINT                        PrivateRuntimeDataSize;             // in : Size in bytes of the pPrivateRuntimeData buffer
    D3DKMT_PTR(_Field_size_bytes_(ResourcePrivateDriverDataSize) VOID*,             pResourcePrivateDriverData);        // in : Caller supplied buffer where the driver private data associated with the resource will be copied
                                                        UINT                        ResourcePrivateDriverDataSize;      // in : Size in bytes of the pResourcePrivateDriverData buffer
    D3DKMT_PTR(_Field_size_bytes_(TotalPrivateDriverDataBufferSize) VOID*,          pTotalPrivateDriverDataBuffer);     // in : Caller supplied buffer where the Driver private data will be stored
                                                        UINT                        TotalPrivateDriverDataBufferSize;   // in/out : Size in bytes of pTotalPrivateDriverDataBuffer / Size in bytes of data written to pTotalPrivateDriverDataBuffer
                                                        D3DKMT_HANDLE               hResource;                          // out : Handle for this resource in this process
}D3DKMT_OPENRESOURCE;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
typedef struct _D3DKMT_OPENRESOURCEFROMNTHANDLE
{
                                                        D3DKMT_HANDLE               hDevice;                            // in : Indentifies the device
    D3DKMT_PTR(                                         HANDLE,                     hNtHandle);                         // in : Process's NT handle
                                                        UINT                        NumAllocations;                     // in : Number of allocations associated with the resource
    D3DKMT_PTR(_Field_size_(NumAllocations)             D3DDDI_OPENALLOCATIONINFO2*, pOpenAllocationInfo2);             // in : Array of open allocation structs // _ADVSCH_
                                                        UINT                        PrivateRuntimeDataSize;             // in : Size in bytes of the pPrivateRuntimeData buffer
    D3DKMT_PTR(_Field_size_bytes_(PrivateRuntimeDataSize) VOID*,                    pPrivateRuntimeData);               // in : Caller supplied buffer where the runtime private data associated with this resource will be copied
                                                        UINT                        ResourcePrivateDriverDataSize;      // in : Size in bytes of the pResourcePrivateDriverData buffer
    D3DKMT_PTR(_Field_size_bytes_(ResourcePrivateDriverDataSize) VOID*,             pResourcePrivateDriverData);        // in : Caller supplied buffer where the driver private data associated with the resource will be copied
                                                        UINT                        TotalPrivateDriverDataBufferSize;   // in/out : Size in bytes of pTotalPrivateDriverDataBuffer / Size in bytes of data written to pTotalPrivateDriverDataBuffer
    D3DKMT_PTR(_Field_size_bytes_(TotalPrivateDriverDataBufferSize) VOID*,          pTotalPrivateDriverDataBuffer);     // in : Caller supplied buffer where the Driver private data will be stored
                                                        D3DKMT_HANDLE               hResource;                          // out : Handle for this resource in this process

                                                        D3DKMT_HANDLE               hKeyedMutex;                        // out: Handle to the keyed mutex in this process
    D3DKMT_PTR(_In_reads_bytes_opt_(PrivateRuntimeDataSize) VOID*,                  pKeyedMutexPrivateRuntimeData);     // in:  Buffer containing initial private data.
                                                                                                                        //      If NULL then PrivateRuntimeDataSize must be 0.
                                                                                                                        //      It will only be copied if the keyed mutex does not already have private data.
                                                        UINT                        KeyedMutexPrivateRuntimeDataSize;   // in:  Size in bytes of pPrivateRuntimeData.
                                                        D3DKMT_HANDLE               hSyncObject;                        // out: Handle to sync object in this process.
} D3DKMT_OPENRESOURCEFROMNTHANDLE;

typedef struct _D3DKMT_OPENSYNCOBJECTFROMNTHANDLE
{
    D3DKMT_PTR(HANDLE, hNtHandle);                      // in : NT handle for the sync object.
    D3DKMT_HANDLE   hSyncObject;                        // out: Handle to sync object in this process.
} D3DKMT_OPENSYNCOBJECTFROMNTHANDLE;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)

typedef struct _D3DKMT_OPENSYNCOBJECTFROMNTHANDLE2
{
    D3DKMT_PTR(HANDLE,                  hNtHandle);     // in : NT handle for the sync object.
    D3DKMT_HANDLE                       hDevice;        // in : Device handle to use this sync object on.
    D3DDDI_SYNCHRONIZATIONOBJECT_FLAGS  Flags;          // in : specifies sync object behavior for this device.
    D3DKMT_HANDLE                       hSyncObject;    // out: Handle to sync object in this process.

    union
    {

        struct
        {
            D3DKMT_PTR(VOID*,       FenceValueCPUVirtualAddress);           // out: Read-only mapping of the fence value for the CPU
            D3DKMT_ALIGN64 D3DGPU_VIRTUAL_ADDRESS FenceValueGPUVirtualAddress; // out: Read/write mapping of the fence value for the GPU
            UINT                    EngineAffinity;                         // in: Defines physical adapters where the GPU VA should be mapped
        } MonitoredFence;

        D3DKMT_ALIGN64 UINT64       Reserved[8];
    };

} D3DKMT_OPENSYNCOBJECTFROMNTHANDLE2;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM3_1)

typedef struct _D3DKMT_OPENNATIVEFENCEFROMNTHANDLE
{
    D3DKMT_PTR(HANDLE,                  hNtHandle);         // in : NT handle for the sync object.
    D3DKMT_HANDLE                       hDevice;            // in : Device handle to use this sync object on.

    UINT                                EngineAffinity;     // in: Defines physical adapters where the GPU VA is mapped
    D3DDDI_SYNCHRONIZATIONOBJECT_FLAGS  Flags;              // in: Flags.

    D3DKMT_HANDLE                       hSyncObject;        // out: Handle to sync object in this process.

    D3DDDI_NATIVEFENCEMAPPING           NativeFenceMapping; // out: process mapping information for the native fence
} D3DKMT_OPENNATIVEFENCEFROMNTHANDLE;

#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM3_1)

typedef struct _D3DKMT_OPENSYNCOBJECTNTHANDLEFROMNAME
{
    DWORD                          dwDesiredAccess;
    D3DKMT_PTR(OBJECT_ATTRIBUTES*, pObjAttrib);
    D3DKMT_PTR(HANDLE,             hNtHandle);
} D3DKMT_OPENSYNCOBJECTNTHANDLEFROMNAME;

#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_0

typedef struct _D3DKMT_OPENNTHANDLEFROMNAME
{
    DWORD                          dwDesiredAccess;
    D3DKMT_PTR(OBJECT_ATTRIBUTES*, pObjAttrib);
    D3DKMT_PTR(HANDLE,             hNtHandle);
} D3DKMT_OPENNTHANDLEFROMNAME;

#define SHARED_ALLOCATION_WRITE         0x1
#define SHARED_ALLOCATION_ALL_ACCESS    (STANDARD_RIGHTS_REQUIRED | SHARED_ALLOCATION_WRITE)

typedef struct _D3DKMT_QUERYRESOURCEINFOFROMNTHANDLE
{
    D3DKMT_HANDLE      hDevice;                        // in : Indentifies the device
    D3DKMT_PTR(HANDLE, hNtHandle);                     // in : Global resource handle to open
    D3DKMT_PTR(VOID*,  pPrivateRuntimeData);           // in : Ptr to buffer that will receive runtime private data for the resource
    UINT               PrivateRuntimeDataSize;         // in/out : Size in bytes of buffer passed in for runtime private data / If pPrivateRuntimeData was NULL then size in bytes of buffer required for the runtime private data otherwise size in bytes of runtime private data copied into the buffer
    UINT               TotalPrivateDriverDataSize;     // out : Size in bytes of buffer required to hold all the DriverPrivate data for all of the allocations associated withe the resource
    UINT               ResourcePrivateDriverDataSize;  // out : Size in bytes of the driver's resource private data
    UINT               NumAllocations;                 // out : Number of allocations associated with this resource
}D3DKMT_QUERYRESOURCEINFOFROMNTHANDLE;

#endif

typedef struct _D3DKMT_QUERYRESOURCEINFO
{
    D3DKMT_HANDLE   hDevice;                        // in : Indentifies the device
    D3DKMT_HANDLE   hGlobalShare;                   // in : Global resource handle to open
    D3DKMT_PTR(VOID*, pPrivateRuntimeData);         // in : Ptr to buffer that will receive runtime private data for the resource
    UINT            PrivateRuntimeDataSize;         // in/out : Size in bytes of buffer passed in for runtime private data / If pPrivateRuntimeData was NULL then size in bytes of buffer required for the runtime private data otherwise size in bytes of runtime private data copied into the buffer
    UINT            TotalPrivateDriverDataSize;     // out : Size in bytes of buffer required to hold all the DriverPrivate data for all of the allocations associated withe the resource
    UINT            ResourcePrivateDriverDataSize;  // out : Size in bytes of the driver's resource private data
    UINT            NumAllocations;                 // out : Number of allocations associated with this resource
}D3DKMT_QUERYRESOURCEINFO;

typedef struct _D3DKMT_DESTROYALLOCATION
{
    D3DKMT_HANDLE           hDevice;            // in: Indentifies the device
    D3DKMT_HANDLE           hResource;
    D3DKMT_PTR(CONST D3DKMT_HANDLE*, phAllocationList);   // in: pointer to an array allocation handles to destroy
    UINT                    AllocationCount;    // in: Number of allocations in phAllocationList
} D3DKMT_DESTROYALLOCATION;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)

typedef struct _D3DKMT_DESTROYALLOCATION2
{
    D3DKMT_HANDLE                       hDevice;            // in: Indentifies the device
    D3DKMT_HANDLE                       hResource;
    D3DKMT_PTR(CONST D3DKMT_HANDLE*,    phAllocationList);  // in: pointer to an array allocation handles to destroy
    UINT                                AllocationCount;    // in: Number of allocations in phAllocationList
    D3DDDICB_DESTROYALLOCATION2FLAGS    Flags;              // in: Bit field defined by D3DDDICB_DESTROYALLOCATION2FLAGS
} D3DKMT_DESTROYALLOCATION2;

#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_0

typedef struct _D3DKMT_SETALLOCATIONPRIORITY
{
    D3DKMT_HANDLE           hDevice;            // in: Indentifies the device
    D3DKMT_HANDLE           hResource;          // in: Specify the resource to set priority to.
    D3DKMT_PTR(CONST D3DKMT_HANDLE*, phAllocationList);   // in: pointer to an array allocation handles to destroy
    UINT                    AllocationCount;    // in: Number of allocations in phAllocationList
    D3DKMT_PTR(CONST UINT*, pPriorities);       // in: New priority for each of the allocation in the array.
} D3DKMT_SETALLOCATIONPRIORITY;

typedef enum _D3DKMT_ALLOCATIONRESIDENCYSTATUS
{
    D3DKMT_ALLOCATIONRESIDENCYSTATUS_RESIDENTINGPUMEMORY=1,
    D3DKMT_ALLOCATIONRESIDENCYSTATUS_RESIDENTINSHAREDMEMORY=2,
    D3DKMT_ALLOCATIONRESIDENCYSTATUS_NOTRESIDENT=3,
} D3DKMT_ALLOCATIONRESIDENCYSTATUS;

typedef struct _D3DKMT_QUERYALLOCATIONRESIDENCY
{
    D3DKMT_HANDLE                       hDevice;            // in: Indentifies the device
    D3DKMT_HANDLE                       hResource;          // in: pointer to resource owning the list of allocation.
    D3DKMT_PTR(CONST D3DKMT_HANDLE*,    phAllocationList);  // in: pointer to an array allocation to get residency status.
    UINT                                AllocationCount;    // in: Number of allocations in phAllocationList
    D3DKMT_PTR(D3DKMT_ALLOCATIONRESIDENCYSTATUS*, pResidencyStatus); // out: Residency status of each allocation in the array.
} D3DKMT_QUERYALLOCATIONRESIDENCY;

typedef struct _D3DKMT_GETRUNTIMEDATA
{
    D3DKMT_HANDLE       hAdapter;
    D3DKMT_HANDLE       hGlobalShare;       // in: shared handle
    D3DKMT_PTR(VOID*,   pRuntimeData);      // out: in: for a version?
    UINT                RuntimeDataSize;    // in:
} D3DKMT_GETRUNTIMEDATA;

typedef enum _KMTUMDVERSION
{
    KMTUMDVERSION_DX9 = 0,
    KMTUMDVERSION_DX10,
    KMTUMDVERSION_DX11,
    KMTUMDVERSION_DX12,
    KMTUMDVERSION_DX12_WSA32,
    KMTUMDVERSION_DX12_WSA64,
    NUM_KMTUMDVERSIONS
} KMTUMDVERSION;

typedef struct _D3DKMT_UMDFILENAMEINFO
{
    KMTUMDVERSION       Version;                // In: UMD version
    WCHAR               UmdFileName[MAX_PATH];  // Out: UMD file name
} D3DKMT_UMDFILENAMEINFO;

#define D3DKMT_COMPONENTIZED_INDICATOR  L'#'
#define D3DKMT_SUBKEY_DX9               L"DX9"
#define D3DKMT_SUBKEY_OPENGL            L"OpenGL"

typedef struct _D3DKMT_OPENGLINFO
{
    WCHAR               UmdOpenGlIcdFileName[MAX_PATH];
    ULONG               Version;
    ULONG               Flags;
} D3DKMT_OPENGLINFO;

typedef struct _D3DKMT_SEGMENTSIZEINFO
{
    D3DKMT_ALIGN64 ULONGLONG           DedicatedVideoMemorySize;
    D3DKMT_ALIGN64 ULONGLONG           DedicatedSystemMemorySize;
    D3DKMT_ALIGN64 ULONGLONG           SharedSystemMemorySize;
} D3DKMT_SEGMENTSIZEINFO;

typedef struct _D3DKMT_SEGMENTGROUPSIZEINFO
{
    UINT32 PhysicalAdapterIndex;
    D3DKMT_SEGMENTSIZEINFO LegacyInfo;
    D3DKMT_ALIGN64 ULONGLONG LocalMemory;
    D3DKMT_ALIGN64 ULONGLONG NonLocalMemory;
    D3DKMT_ALIGN64 ULONGLONG NonBudgetMemory;
} D3DKMT_SEGMENTGROUPSIZEINFO;

typedef struct _D3DKMT_WORKINGSETFLAGS
{
    UINT    UseDefault   :  1;   // 0x00000001
    UINT    Reserved     : 31;   // 0xFFFFFFFE
} D3DKMT_WORKINGSETFLAGS;

typedef struct _D3DKMT_WORKINGSETINFO
{
    D3DKMT_WORKINGSETFLAGS Flags;
    ULONG MinimumWorkingSetPercentile;
    ULONG MaximumWorkingSetPercentile;
} D3DKMT_WORKINGSETINFO;

typedef struct _D3DKMT_FLIPINFOFLAGS
{
    UINT                FlipInterval :  1; // 0x00000001 // Set when kmd driver support FlipInterval natively
    UINT                Reserved     : 31; // 0xFFFFFFFE
} D3DKMT_FLIPINFOFLAGS;

typedef struct _D3DKMT_FLIPQUEUEINFO
{
    UINT                 MaxHardwareFlipQueueLength; // Max flip can be queued for hardware flip queue.
    UINT                 MaxSoftwareFlipQueueLength; // Max flip can be queued for software flip queue for non-legacy device.
    D3DKMT_FLIPINFOFLAGS FlipFlags;
} D3DKMT_FLIPQUEUEINFO;

typedef struct _D3DKMT_ADAPTERADDRESS
{
    UINT   BusNumber;              // Bus number on which the physical device is located.
    UINT   DeviceNumber;           // Index of the physical device on the bus.
    UINT   FunctionNumber;         // Function number of the adapter on the physical device.
} D3DKMT_ADAPTERADDRESS;

typedef struct _D3DKMT_ADAPTERREGISTRYINFO
{
    WCHAR   AdapterString[MAX_PATH];
    WCHAR   BiosString[MAX_PATH];
    WCHAR   DacType[MAX_PATH];
    WCHAR   ChipType[MAX_PATH];
} D3DKMT_ADAPTERREGISTRYINFO;

typedef struct _D3DKMT_CURRENTDISPLAYMODE
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID VidPnSourceId;
    D3DKMT_DISPLAYMODE DisplayMode;
} D3DKMT_CURRENTDISPLAYMODE;

typedef struct _D3DKMT_VIRTUALADDRESSFLAGS // _ADVSCH_
{
    UINT   VirtualAddressSupported :  1;
    UINT   Reserved                : 31;
} D3DKMT_VIRTUALADDRESSFLAGS;

typedef struct _D3DKMT_VIRTUALADDRESSINFO // _ADVSCH_
{
    D3DKMT_VIRTUALADDRESSFLAGS VirtualAddressFlags;
} D3DKMT_VIRTUALADDRESSINFO;

typedef enum _QAI_DRIVERVERSION
{
    KMT_DRIVERVERSION_WDDM_1_0               = 1000,
    KMT_DRIVERVERSION_WDDM_1_1_PRERELEASE    = 1102,
    KMT_DRIVERVERSION_WDDM_1_1               = 1105,
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
    KMT_DRIVERVERSION_WDDM_1_2               = 1200,
#endif
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
    KMT_DRIVERVERSION_WDDM_1_3               = 1300,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM1_3
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
    KMT_DRIVERVERSION_WDDM_2_0               = 2000,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_0
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
    KMT_DRIVERVERSION_WDDM_2_1               = 2100,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_1
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)
    KMT_DRIVERVERSION_WDDM_2_2 = 2200,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_2
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_3)
    KMT_DRIVERVERSION_WDDM_2_3 = 2300,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_3
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_4)
    KMT_DRIVERVERSION_WDDM_2_4 = 2400,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_4
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_5)
    KMT_DRIVERVERSION_WDDM_2_5 = 2500,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_5
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_6)
    KMT_DRIVERVERSION_WDDM_2_6 = 2600,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_6
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_7)
    KMT_DRIVERVERSION_WDDM_2_7 = 2700,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_7
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_8)
    KMT_DRIVERVERSION_WDDM_2_8 = 2800,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_8
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_9)
    KMT_DRIVERVERSION_WDDM_2_9 = 2900,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_9
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM3_0)
    KMT_DRIVERVERSION_WDDM_3_0 = 3000,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM3_0
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM3_1)
    KMT_DRIVERVERSION_WDDM_3_1 = 3100
#endif // DXGKDDI_INTERFACE_VERSION_WDDM3_1
} D3DKMT_DRIVERVERSION;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
typedef struct _D3DKMT_ADAPTERTYPE
{
    union
    {
        struct
        {
            UINT   RenderSupported       :  1;
            UINT   DisplaySupported      :  1;
            UINT   SoftwareDevice        :  1;
            UINT   PostDevice            :  1;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
            UINT   HybridDiscrete        :  1;
            UINT   HybridIntegrated      :  1;
            UINT   IndirectDisplayDevice :  1;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_3)
            UINT   Paravirtualized              :  1;
            UINT   ACGSupported                 :  1;
            UINT   SupportSetTimingsFromVidPn   :  1;
            UINT   Detachable                   :  1;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_6)
            UINT   ComputeOnly                  :  1;
            UINT   Prototype                    :  1;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_9)
            UINT   RuntimePowerManagement       :  1;
            UINT   Reserved                     : 18;
#else
            UINT   Reserved                     : 19;
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_9)
#else
            UINT   Reserved              : 21;
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_6)
#else
            UINT   Reserved              : 25;
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_3)
#else
            UINT   Reserved              : 28;
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
        };
        UINT Value;
    };
} D3DKMT_ADAPTERTYPE;

typedef struct _D3DKMT_OUTPUTDUPLCONTEXTSCOUNT
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID VidPnSourceId;
    UINT OutputDuplicationCount;
} D3DKMT_OUTPUTDUPLCONTEXTSCOUNT;

typedef struct _D3DKMT_UMD_DRIVER_VERSION
{
    D3DKMT_ALIGN64 LARGE_INTEGER DriverVersion;
} D3DKMT_UMD_DRIVER_VERSION;

typedef struct _D3DKMT_KMD_DRIVER_VERSION
{
    D3DKMT_ALIGN64 LARGE_INTEGER DriverVersion;
} D3DKMT_KMD_DRIVER_VERSION;

typedef struct _D3DKMT_DIRECTFLIP_SUPPORT
{
    BOOL Supported;
} D3DKMT_DIRECTFLIP_SUPPORT;

typedef struct _D3DKMT_MULTIPLANEOVERLAY_SUPPORT
{
    BOOL Supported;
} D3DKMT_MULTIPLANEOVERLAY_SUPPORT;
#endif

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3_PATH_INDEPENDENT_ROTATION)
typedef struct _D3DKMT_MULTIPLANEOVERLAY_HUD_SUPPORT
{
    UINT VidPnSourceId; // Not yet used.
    BOOL Update;
    BOOL KernelSupported;
    BOOL HudSupported;
} D3DKMT_MULTIPLANEOVERLAY_HUD_SUPPORT;
#endif // DXGKDDI_INTERFACE_VERSION_WDDM1_3_PATH_INDEPENDENT_ROTATION

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)

typedef struct _D3DKMT_DLIST_DRIVER_NAME
{
    WCHAR DListFileName[MAX_PATH];  // Out: DList driver file name
} D3DKMT_DLIST_DRIVER_NAME;

typedef struct _D3DKMT_CPDRIVERNAME
{
    WCHAR  ContentProtectionFileName[MAX_PATH];
} D3DKMT_CPDRIVERNAME;

typedef struct _D3DKMT_MIRACASTCOMPANIONDRIVERNAME
{
    WCHAR  MiracastCompanionDriverName[MAX_PATH];
} D3DKMT_MIRACASTCOMPANIONDRIVERNAME;

#endif // DXGKDDI_INTERFACE_VERSION_WDDM1_3

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)

typedef struct _D3DKMT_XBOX
{
    BOOL IsXBOX;
} D3DKMT_XBOX;

typedef struct _D3DKMT_INDEPENDENTFLIP_SUPPORT
{
    BOOL Supported;
} D3DKMT_INDEPENDENTFLIP_SUPPORT;

typedef struct _D3DKMT_MULTIPLANEOVERLAY_DECODE_SUPPORT
{
    BOOL Supported;
} D3DKMT_MULTIPLANEOVERLAY_DECODE_SUPPORT;

typedef struct _D3DKMT_ISBADDRIVERFORHWPROTECTIONDISABLED
{
    BOOL Disabled;
} D3DKMT_ISBADDRIVERFORHWPROTECTIONDISABLED;

typedef struct _D3DKMT_MULTIPLANEOVERLAY_SECONDARY_SUPPORT
{
    BOOL Supported;
} D3DKMT_MULTIPLANEOVERLAY_SECONDARY_SUPPORT;

typedef struct _D3DKMT_INDEPENDENTFLIP_SECONDARY_SUPPORT
{
    BOOL Supported;
} D3DKMT_INDEPENDENTFLIP_SECONDARY_SUPPORT;

typedef struct _D3DKMT_PANELFITTER_SUPPORT
{
    BOOL Supported;
} D3DKMT_PANELFITTER_SUPPORT;

typedef struct _D3DKMT_PHYSICAL_ADAPTER_COUNT
{
    UINT Count;
} D3DKMT_PHYSICAL_ADAPTER_COUNT;

typedef struct _D3DKMT_DEVICE_IDS
{
    UINT VendorID;
    UINT DeviceID;
    UINT SubVendorID;
    UINT SubSystemID;
    UINT RevisionID;
    UINT BusType;
} D3DKMT_DEVICE_IDS;

typedef struct _D3DKMT_QUERY_DEVICE_IDS
{
    UINT              PhysicalAdapterIndex; // in:
    D3DKMT_DEVICE_IDS DeviceIds;            // out:
} D3DKMT_QUERY_DEVICE_IDS;

typedef enum _D3DKMT_PNP_KEY_TYPE
{
    D3DKMT_PNP_KEY_HARDWARE = 1,
    D3DKMT_PNP_KEY_SOFTWARE = 2
} D3DKMT_PNP_KEY_TYPE;

typedef struct _D3DKMT_QUERY_PHYSICAL_ADAPTER_PNP_KEY
{
    UINT PhysicalAdapterIndex;
    D3DKMT_PNP_KEY_TYPE PnPKeyType;
    D3DKMT_PTR(_Field_size_opt_(*pCchDest) WCHAR*, pDest);
    D3DKMT_PTR(UINT*, pCchDest);
} D3DKMT_QUERY_PHYSICAL_ADAPTER_PNP_KEY;

typedef enum _D3DKMT_MIRACAST_DRIVER_TYPE
{
    D3DKMT_MIRACAST_DRIVER_NOT_SUPPORTED = 0,
    D3DKMT_MIRACAST_DRIVER_IHV = 1,
    D3DKMT_MIRACAST_DRIVER_MS = 2,
} D3DKMT_MIRACAST_DRIVER_TYPE;

typedef struct _D3DKMT_QUERY_MIRACAST_DRIVER_TYPE
{
    D3DKMT_MIRACAST_DRIVER_TYPE MiracastDriverType;
} D3DKMT_QUERY_MIRACAST_DRIVER_TYPE;

typedef struct _D3DKMT_GPUMMU_CAPS
{
    union
    {
        struct
        {
            UINT ReadOnlyMemorySupported                : 1;
            UINT NoExecuteMemorySupported               : 1;
            UINT CacheCoherentMemorySupported           : 1;
            UINT Reserved                               : 29;
        };
        UINT        Value;
    } Flags;
    UINT                        VirtualAddressBitCount;
} D3DKMT_GPUMMU_CAPS;

typedef struct _D3DKMT_QUERY_GPUMMU_CAPS
{
    UINT PhysicalAdapterIndex; // in:
    D3DKMT_GPUMMU_CAPS Caps;   // out:
} D3DKMT_QUERY_GPUMMU_CAPS;

#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_0

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)

typedef struct _D3DKMT_MPO3DDI_SUPPORT
{
    BOOL Supported;
} D3DKMT_MPO3DDI_SUPPORT;

typedef struct _D3DKMT_HWDRM_SUPPORT
{
    BOOLEAN Supported;
} D3DKMT_HWDRM_SUPPORT;

typedef struct _D3DKMT_MPOKERNELCAPS_SUPPORT
{
    BOOL Supported;
} D3DKMT_MPOKERNELCAPS_SUPPORT;

typedef struct _D3DKMT_GET_DEVICE_VIDPN_OWNERSHIP_INFO
{
    D3DKMT_HANDLE hDevice;                           // in : Indentifies the device
    BOOLEAN bFailedDwmAcquireVidPn;                  // out : True if Dwm Acquire VidPn failed due to another Dwm device having ownership
} D3DKMT_GET_DEVICE_VIDPN_OWNERSHIP_INFO;

#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_2

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_4)

typedef struct _D3DKMT_BLOCKLIST_INFO
{
    UINT Size;
    WCHAR BlockList[1];
} D3DKMT_BLOCKLIST_INFO;

typedef struct _D3DKMT_QUERY_ADAPTER_UNIQUE_GUID
{
    WCHAR AdapterUniqueGUID[40];
} D3DKMT_QUERY_ADAPTER_UNIQUE_GUID;

typedef struct _D3DKMT_NODE_PERFDATA
{
    UINT32          NodeOrdinal;            // in: Node ordinal of the requested engine.
    UINT32          PhysicalAdapterIndex;   // in: The physical adapter index, in an LDA chain
    D3DKMT_ALIGN64 ULONGLONG Frequency;     // out: Clock frequency of the engine in hertz
    D3DKMT_ALIGN64 ULONGLONG MaxFrequency;  // out: Max engine clock frequency
    D3DKMT_ALIGN64 ULONGLONG MaxFrequencyOC;// out: Max engine over clock frequency
    ULONG           Voltage;                // out: Voltage of the engine in milli volts mV
    ULONG           VoltageMax;             // out: Max voltage levels in milli volts.
    ULONG           VoltageMaxOC;           // out: Max voltage level while overclocked in milli volts.
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_5)
    D3DKMT_ALIGN64 ULONGLONG MaxTransitionLatency;   // out: Max transition latency to change the frequency in 100 nanoseconds
#else
    D3DKMT_ALIGN64 ULONGLONG Reserved;
#endif
} D3DKMT_NODE_PERFDATA;

typedef struct _D3DKMT_ADAPTER_PERFDATA
{
    UINT32          PhysicalAdapterIndex;   // in: The physical adapter index, in an LDA chain
    D3DKMT_ALIGN64 ULONGLONG MemoryFrequency;        // out: Clock frequency of the memory in hertz
    D3DKMT_ALIGN64 ULONGLONG MaxMemoryFrequency;     // out: Max memory clock frequency
    D3DKMT_ALIGN64 ULONGLONG MaxMemoryFrequencyOC;   // out: Clock frequency of the memory while overclocked in hertz.
    D3DKMT_ALIGN64 ULONGLONG MemoryBandwidth;        // out: Amount of memory transferred in bytes
    D3DKMT_ALIGN64 ULONGLONG PCIEBandwidth;          // out: Amount of memory transferred over PCI-E in bytes
    ULONG           FanRPM;                 // out: Fan rpm
    ULONG           Power;                  // out: Power draw of the adapter in tenths of a percentage
    ULONG           Temperature;            // out: Temperature in deci-Celsius 1 = 0.1C
    UCHAR           PowerStateOverride;     // out: Overrides dxgkrnls power view of linked adapters.
} D3DKMT_ADAPTER_PERFDATA;

typedef struct _D3DKMT_ADAPTER_PERFDATACAPS
{
    UINT32      PhysicalAdapterIndex;   // in: The physical adapter index, in an LDA chain
    D3DKMT_ALIGN64 ULONGLONG MaxMemoryBandwidth;     // out: Max memory bandwidth in bytes for 1 second
    D3DKMT_ALIGN64 ULONGLONG MaxPCIEBandwidth;       // out: Max pcie bandwidth in bytes for 1 second
    ULONG       MaxFanRPM;              // out: Max fan rpm
    ULONG       TemperatureMax;         // out: Max temperature before damage levels
    ULONG       TemperatureWarning;     // out: The temperature level where throttling begins.
} D3DKMT_ADAPTER_PERFDATACAPS;

#define DXGK_MAX_GPUVERSION_NAME_LENGTH 32
typedef struct _D3DKMT_GPUVERSION
{
    UINT32          PhysicalAdapterIndex;                             // in: The physical adapter index, in an LDA chain
    WCHAR           BiosVersion[DXGK_MAX_GPUVERSION_NAME_LENGTH];     //out: The gpu bios version
    WCHAR           GpuArchitecture[DXGK_MAX_GPUVERSION_NAME_LENGTH]; //out: The gpu architectures name.
} D3DKMT_GPUVERSION;

#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_4

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_6)

typedef struct _D3DKMT_DRIVER_DESCRIPTION
{
    WCHAR           DriverDescription[4096];     //out: The driver description
} D3DKMT_DRIVER_DESCRIPTION;

typedef struct _D3DKMT_QUERY_SCANOUT_CAPS
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID VidPnSourceId;
    UINT Caps;
} D3DKMT_QUERY_SCANOUT_CAPS;

typedef enum _KMT_DISPLAY_UMD_VERSION
{
    KMT_DISPLAY_UMDVERSION_1 = 0,
    NUM_KMT_DISPLAY_UMDVERSIONS
} KMT_DISPLAY_UMD_VERSION;

typedef struct _D3DKMT_DISPLAY_UMD_FILENAMEINFO
{
    KMT_DISPLAY_UMD_VERSION Version;                // In: UMD version
    WCHAR                   UmdFileName[MAX_PATH];  // Out: UMD file name
} D3DKMT_DISPLAY_UMD_FILENAMEINFO;

typedef struct _D3DKMT_WSAUMDIMAGENAME
{
    WCHAR                   WsaUmdImageName[MAX_PATH];  // Out: UMD WSA image name
} D3DKMT_WSAUMDIMAGENAME;

typedef struct _D3DKMT_VGPUINTERFACEID
{
    WCHAR                   VirtualGpuIntefaceId[MAX_PATH];  // Out: UMD WSA image name
} D3DKMT_VGPUINTERFACEID;

typedef struct _D3DKMT_PARAVIRTUALIZATION
{
    // This adapter property originates from the VM/ Container, and is currently replicated on adapters.
    // It precludes extended device functions (i.e. Escapes) for paravirtualized devices which not known at all,
    // and therefore assumed not to be secure enough for demanding server scenarios.
    BOOLEAN SecureContainer;
} D3DKMT_PARAVIRTUALIZATION;

#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_6

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_8)

typedef struct _D3DKMT_HYBRID_DLIST_DLL_SUPPORT
{
    BOOL Supported;
} D3DKMT_HYBRID_DLIST_DLL_SUPPORT;

#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_8

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_9)


typedef enum _D3DKMT_CROSSADAPTERRESOURCE_SUPPORT_TIER
{
    D3DKMT_CROSSADAPTERRESOURCE_SUPPORT_TIER_NONE    = 0,
    D3DKMT_CROSSADAPTERRESOURCE_SUPPORT_TIER_COPY    = 1,
    D3DKMT_CROSSADAPTERRESOURCE_SUPPORT_TIER_TEXTURE = 2,
    D3DKMT_CROSSADAPTERRESOURCE_SUPPORT_TIER_SCANOUT = 3,
} D3DKMT_CROSSADAPTERRESOURCE_SUPPORT_TIER;

typedef struct _D3DKMT_CROSSADAPTERRESOURCE_SUPPORT
{
    D3DKMT_CROSSADAPTERRESOURCE_SUPPORT_TIER SupportTier;
} D3DKMT_CROSSADAPTERRESOURCE_SUPPORT;

#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_9

typedef enum _KMTQUERYADAPTERINFOTYPE
{
     KMTQAITYPE_UMDRIVERPRIVATE         =  0,
     KMTQAITYPE_UMDRIVERNAME            =  1,
     KMTQAITYPE_UMOPENGLINFO            =  2,
     KMTQAITYPE_GETSEGMENTSIZE          =  3,
     KMTQAITYPE_ADAPTERGUID             =  4,
     KMTQAITYPE_FLIPQUEUEINFO           =  5,
     KMTQAITYPE_ADAPTERADDRESS          =  6,
     KMTQAITYPE_SETWORKINGSETINFO       =  7,
     KMTQAITYPE_ADAPTERREGISTRYINFO     =  8,
     KMTQAITYPE_CURRENTDISPLAYMODE      =  9,
     KMTQAITYPE_MODELIST                = 10,
     KMTQAITYPE_CHECKDRIVERUPDATESTATUS = 11,
     KMTQAITYPE_VIRTUALADDRESSINFO      = 12, // _ADVSCH_
     KMTQAITYPE_DRIVERVERSION           = 13,
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
     KMTQAITYPE_ADAPTERTYPE             = 15,
     KMTQAITYPE_OUTPUTDUPLCONTEXTSCOUNT = 16,
     KMTQAITYPE_WDDM_1_2_CAPS           = 17,
     KMTQAITYPE_UMD_DRIVER_VERSION      = 18,
     KMTQAITYPE_DIRECTFLIP_SUPPORT      = 19,
#endif
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
     KMTQAITYPE_MULTIPLANEOVERLAY_SUPPORT = 20,
     KMTQAITYPE_DLIST_DRIVER_NAME       = 21,
     KMTQAITYPE_WDDM_1_3_CAPS           = 22,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM1_3
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3_PATH_INDEPENDENT_ROTATION)
     KMTQAITYPE_MULTIPLANEOVERLAY_HUD_SUPPORT = 23,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM1_3_PATH_INDEPENDENT_ROTATION
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
     KMTQAITYPE_WDDM_2_0_CAPS           = 24,
     KMTQAITYPE_NODEMETADATA            = 25,
     KMTQAITYPE_CPDRIVERNAME            = 26,
     KMTQAITYPE_XBOX                    = 27,
     KMTQAITYPE_INDEPENDENTFLIP_SUPPORT = 28,
     KMTQAITYPE_MIRACASTCOMPANIONDRIVERNAME = 29,
     KMTQAITYPE_PHYSICALADAPTERCOUNT    = 30,
     KMTQAITYPE_PHYSICALADAPTERDEVICEIDS = 31,
     KMTQAITYPE_DRIVERCAPS_EXT          = 32,
     KMTQAITYPE_QUERY_MIRACAST_DRIVER_TYPE = 33,
     KMTQAITYPE_QUERY_GPUMMU_CAPS       = 34,
     KMTQAITYPE_QUERY_MULTIPLANEOVERLAY_DECODE_SUPPORT = 35,
     KMTQAITYPE_QUERY_HW_PROTECTION_TEARDOWN_COUNT = 36,
     KMTQAITYPE_QUERY_ISBADDRIVERFORHWPROTECTIONDISABLED = 37,
     KMTQAITYPE_MULTIPLANEOVERLAY_SECONDARY_SUPPORT = 38,
     KMTQAITYPE_INDEPENDENTFLIP_SECONDARY_SUPPORT = 39,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_0
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
     KMTQAITYPE_PANELFITTER_SUPPORT     = 40,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_1
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)
     KMTQAITYPE_PHYSICALADAPTERPNPKEY   = 41,
     KMTQAITYPE_GETSEGMENTGROUPSIZE     = 42,
     KMTQAITYPE_MPO3DDI_SUPPORT         = 43,
     KMTQAITYPE_HWDRM_SUPPORT           = 44,
     KMTQAITYPE_MPOKERNELCAPS_SUPPORT   = 45,
     KMTQAITYPE_MULTIPLANEOVERLAY_STRETCH_SUPPORT = 46,
     KMTQAITYPE_GET_DEVICE_VIDPN_OWNERSHIP_INFO = 47,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_2
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_4)
     KMTQAITYPE_QUERYREGISTRY           = 48,
     KMTQAITYPE_KMD_DRIVER_VERSION      = 49,
     KMTQAITYPE_BLOCKLIST_KERNEL        = 50,
     KMTQAITYPE_BLOCKLIST_RUNTIME       = 51,
     KMTQAITYPE_ADAPTERGUID_RENDER              = 52,
     KMTQAITYPE_ADAPTERADDRESS_RENDER           = 53,
     KMTQAITYPE_ADAPTERREGISTRYINFO_RENDER      = 54,
     KMTQAITYPE_CHECKDRIVERUPDATESTATUS_RENDER  = 55,
     KMTQAITYPE_DRIVERVERSION_RENDER            = 56,
     KMTQAITYPE_ADAPTERTYPE_RENDER              = 57,
     KMTQAITYPE_WDDM_1_2_CAPS_RENDER            = 58,
     KMTQAITYPE_WDDM_1_3_CAPS_RENDER            = 59,
     KMTQAITYPE_QUERY_ADAPTER_UNIQUE_GUID = 60,
     KMTQAITYPE_NODEPERFDATA            = 61,
     KMTQAITYPE_ADAPTERPERFDATA         = 62,
     KMTQAITYPE_ADAPTERPERFDATA_CAPS    = 63,
     KMTQUITYPE_GPUVERSION              = 64,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_4
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_6)
     KMTQAITYPE_DRIVER_DESCRIPTION        = 65,
     KMTQAITYPE_DRIVER_DESCRIPTION_RENDER = 66,
     KMTQAITYPE_SCANOUT_CAPS              = 67,
     KMTQAITYPE_DISPLAY_UMDRIVERNAME      = 71, // Added in 19H2
     KMTQAITYPE_PARAVIRTUALIZATION_RENDER = 68,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_6
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_7)
     KMTQAITYPE_SERVICENAME = 69,
     KMTQAITYPE_WDDM_2_7_CAPS = 70,
     KMTQAITYPE_TRACKEDWORKLOAD_SUPPORT = 72,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_7
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_8)
     KMTQAITYPE_HYBRID_DLIST_DLL_SUPPORT = 73,
     KMTQAITYPE_DISPLAY_CAPS             = 74,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_8
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_9)
     KMTQAITYPE_WDDM_2_9_CAPS                = 75,
     KMTQAITYPE_CROSSADAPTERRESOURCE_SUPPORT = 76,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_9
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM3_0)
     KMTQAITYPE_WDDM_3_0_CAPS                = 77,
     KMTQAITYPE_WSAUMDIMAGENAME             = 78,
     KMTQAITYPE_VGPUINTERFACEID             = 79,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM3_0
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM3_1)
     KMTQAITYPE_WDDM_3_1_CAPS               = 80,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM3_1
// If a new enum will be used by DXGI or D3D11 software driver code, update the test content in the area.
// Search for KMTQAITYPE_PARAVIRTUALIZATION_RENDER in directx\dxg\dxgi\unittests for references.
} KMTQUERYADAPTERINFOTYPE;

typedef struct _D3DKMT_QUERYADAPTERINFO
{
    D3DKMT_HANDLE           hAdapter;
    KMTQUERYADAPTERINFOTYPE Type;
    D3DKMT_PTR(VOID*,       pPrivateDriverData);
    UINT                    PrivateDriverDataSize;
} D3DKMT_QUERYADAPTERINFO;

typedef struct _D3DKMT_OPENADAPTERFROMHDC
{
    D3DKMT_PTR(HDC,                 hDc);           // in:  DC that maps to a single display
    D3DKMT_HANDLE                   hAdapter;       // out: adapter handle
    LUID                            AdapterLuid;    // out: adapter LUID
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;  // out: VidPN source ID for that particular display
} D3DKMT_OPENADAPTERFROMHDC;

typedef struct _D3DKMT_OPENADAPTERFROMGDIDISPLAYNAME
{
    WCHAR                           DeviceName[32]; // in:  Name of GDI device from which to open an adapter instance
    D3DKMT_HANDLE                   hAdapter;       // out: adapter handle
    LUID                            AdapterLuid;    // out: adapter LUID
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;  // out: VidPN source ID for that particular display
} D3DKMT_OPENADAPTERFROMGDIDISPLAYNAME;

typedef struct _D3DKMT_OPENADAPTERFROMDEVICENAME
{
    D3DKMT_PTR(PCWSTR,              pDeviceName);   // in:  NULL terminated string containing the device name to open
    D3DKMT_HANDLE                   hAdapter;       // out: adapter handle
    LUID                            AdapterLuid;    // out: adapter LUID
} D3DKMT_OPENADAPTERFROMDEVICENAME;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)

#define MAX_ENUM_ADAPTERS   16

typedef struct _D3DKMT_ADAPTERINFO
{
    D3DKMT_HANDLE       hAdapter;
    LUID                AdapterLuid;
    ULONG               NumOfSources;
    BOOL                bPrecisePresentRegionsPreferred;
} D3DKMT_ADAPTERINFO;

typedef struct _D3DKMT_ENUMADAPTERS
{
    _In_range_(0, MAX_ENUM_ADAPTERS) ULONG  NumAdapters;
    D3DKMT_ADAPTERINFO                      Adapters[MAX_ENUM_ADAPTERS];
} D3DKMT_ENUMADAPTERS;

typedef struct _D3DKMT_ENUMADAPTERS2
{
    ULONG                 NumAdapters;           // in/out: On input, the count of the pAdapters array buffer.  On output, the number of adapters enumerated.
    D3DKMT_PTR(D3DKMT_ADAPTERINFO*, pAdapters);  // out: Array of enumerated adapters containing NumAdapters elements
} D3DKMT_ENUMADAPTERS2;

typedef struct _D3DKMT_OPENADAPTERFROMLUID
{
    LUID            AdapterLuid;
    D3DKMT_HANDLE   hAdapter;
} D3DKMT_OPENADAPTERFROMLUID;

typedef struct _D3DKMT_QUERYREMOTEVIDPNSOURCEFROMGDIDISPLAYNAME
{
    WCHAR                           DeviceName[32]; // in:  Name of GDI device from which to open an adapter instance
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;  // out: VidPN source ID for that particular display
} D3DKMT_QUERYREMOTEVIDPNSOURCEFROMGDIDISPLAYNAME;
#endif

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_7)
typedef union _D3DKMT_ENUMADAPTERS_FILTER
{
    // Setting none of these flags will still enumerate adapters,
    // but there are fewer adapters than EnumAdapters2 enumerates.
    // ComputeOnly adapters are left out of the default enumeration, to avoid breaking applications.
    // DisplayOnly adapters are also left out of the default enumeration.
    struct
    {
        ULONGLONG IncludeComputeOnly            : 1;
        ULONGLONG IncludeDisplayOnly            : 1;
        ULONGLONG Reserved                      : 62;
    };
    D3DKMT_ALIGN64 ULONGLONG Value;
} D3DKMT_ENUMADAPTERS_FILTER;

typedef struct _D3DKMT_ENUMADAPTERS3
{
    D3DKMT_ENUMADAPTERS_FILTER      Filter;      // in: Defines the filter
    ULONG                           NumAdapters; // in/out: On input, the count of the pAdapters array buffer.  On output, the number of adapters enumerated.
    D3DKMT_PTR(D3DKMT_ADAPTERINFO*, pAdapters);  // out: Array of enumerated adapters containing NumAdapters elements
} D3DKMT_ENUMADAPTERS3;
#endif

typedef struct _D3DKMT_CLOSEADAPTER
{
    D3DKMT_HANDLE   hAdapter;   // in: adapter handle
} D3DKMT_CLOSEADAPTER;

typedef struct _D3DKMT_GETSHAREDPRIMARYHANDLE
{
    D3DKMT_HANDLE                   hAdapter;       // in: adapter handle
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;  // in: adapter's VidPN source ID
    D3DKMT_HANDLE                   hSharedPrimary; // out: global shared primary handle (if one exists currently)
} D3DKMT_GETSHAREDPRIMARYHANDLE;

typedef struct _D3DKMT_SHAREDPRIMARYLOCKNOTIFICATION
{
    LUID                            AdapterLuid;
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;
    RECTL                           LockRect;               // in: If zero rect then we are locking the whole primary else the lock sub-rect
} D3DKMT_SHAREDPRIMARYLOCKNOTIFICATION;

typedef struct _D3DKMT_SHAREDPRIMARYUNLOCKNOTIFICATION
{
    LUID                            AdapterLuid;
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;
} D3DKMT_SHAREDPRIMARYUNLOCKNOTIFICATION;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
typedef struct _D3DKMT_PINDIRECTFLIPRESOURCES
{
    D3DKMT_HANDLE               hDevice;                           // in : Indentifies the device
    UINT                        ResourceCount;                     // in : Number of resources to pin
    D3DKMT_PTR(_Field_size_(ResourceCount)  D3DKMT_HANDLE*, pResourceList);     // in : Array of resource handles to pin
} D3DKMT_PINDIRECTFLIPRESOURCES;

typedef struct _D3DKMT_UNPINDIRECTFLIPRESOURCES
{
    D3DKMT_HANDLE               hDevice;                           // in : Indentifies the device
    UINT                        ResourceCount;                     // in : Number of resources to unpin
    D3DKMT_PTR(_Field_size_(ResourceCount) D3DKMT_HANDLE*, pResourceList);     // in : Array of resource handles to unpin
} D3DKMT_UNPINDIRECTFLIPRESOURCES;
#endif


typedef enum _D3DKMT_ESCAPETYPE
{
    D3DKMT_ESCAPE_DRIVERPRIVATE                 =  0,
    D3DKMT_ESCAPE_VIDMM                         =  1,
    D3DKMT_ESCAPE_TDRDBGCTRL                    =  2,
    D3DKMT_ESCAPE_VIDSCH                        =  3,
    D3DKMT_ESCAPE_DEVICE                        =  4,
    D3DKMT_ESCAPE_DMM                           =  5,
    D3DKMT_ESCAPE_DEBUG_SNAPSHOT                =  6,
    // unused (7 was previously used to set driver update in-progress status, D3DKMT_ESCAPE_SETDRIVERUPDATESTATUS)
    D3DKMT_ESCAPE_DRT_TEST                      =  8,
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
    D3DKMT_ESCAPE_DIAGNOSTICS                   =  9,
    D3DKMT_ESCAPE_OUTPUTDUPL_SNAPSHOT           = 10,
    D3DKMT_ESCAPE_OUTPUTDUPL_DIAGNOSTICS        = 11,
    D3DKMT_ESCAPE_BDD_PNP                       = 12,
    D3DKMT_ESCAPE_BDD_FALLBACK                  = 13,
    D3DKMT_ESCAPE_ACTIVATE_SPECIFIC_DIAG        = 14,
    D3DKMT_ESCAPE_MODES_PRUNED_OUT              = 15,
    D3DKMT_ESCAPE_WHQL_INFO                     = 16,
    D3DKMT_ESCAPE_BRIGHTNESS                    = 17,
    D3DKMT_ESCAPE_EDID_CACHE                    = 18,
    // unused (19 was previously D3DKMT_ESCAPE_GENERIC_ADAPTER_DIAG_INFO)
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
    D3DKMT_ESCAPE_MIRACAST_DISPLAY_REQUEST      = 20,
    D3DKMT_ESCAPE_HISTORY_BUFFER_STATUS         = 21,
    // 22 can be reused for future needs as it was never exposed for external purposes
    D3DKMT_ESCAPE_MIRACAST_ADAPTER_DIAG_INFO    = 23,
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
    D3DKMT_ESCAPE_FORCE_BDDFALLBACK_HEADLESS    = 24,
    D3DKMT_ESCAPE_REQUEST_MACHINE_CRASH         = 25,
    // unused (26 was previously D3DKMT_ESCAPE_HMD_GET_EDID_BASE_BLOCK)
    D3DKMT_ESCAPE_SOFTGPU_ENABLE_DISABLE_HMD    = 27,
    D3DKMT_ESCAPE_PROCESS_VERIFIER_OPTION       = 28,
    D3DKMT_ESCAPE_ADAPTER_VERIFIER_OPTION       = 29,
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
    D3DKMT_ESCAPE_IDD_REQUEST                   = 30,
    D3DKMT_ESCAPE_DOD_SET_DIRTYRECT_MODE        = 31,
    D3DKMT_ESCAPE_LOG_CODEPOINT_PACKET          = 32,
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)
    D3DKMT_ESCAPE_LOG_USERMODE_DAIG_PACKET      = 33,
    D3DKMT_ESCAPE_GET_EXTERNAL_DIAGNOSTICS      = 34,
    // unused (35 previously was D3DKMT_ESCAPE_GET_PREFERRED_MODE)
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_3)
    D3DKMT_ESCAPE_GET_DISPLAY_CONFIGURATIONS    = 36,
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_4)
    D3DKMT_ESCAPE_QUERY_IOMMU_STATUS            = 37,
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_6)
    D3DKMT_ESCAPE_CCD_DATABASE                  = 38,
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM3_0)
    D3DKMT_ESCAPE_QUERY_DMA_REMAPPING_STATUS    = 39,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM3_0
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_6
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_4
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_3
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_2
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_1
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_0
#endif // DXGKDDI_INTERFACE_VERSION_WDDM1_3

    D3DKMT_ESCAPE_WIN32K_START                  = 1024,
    D3DKMT_ESCAPE_WIN32K_HIP_DEVICE_INFO        = 1024,
    D3DKMT_ESCAPE_WIN32K_QUERY_CD_ROTATION_BLOCK = 1025,
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
    D3DKMT_ESCAPE_WIN32K_DPI_INFO               = 1026, // Use hContext for the desired hdev
    D3DKMT_ESCAPE_WIN32K_PRESENTER_VIEW_INFO    = 1027,
    D3DKMT_ESCAPE_WIN32K_SYSTEM_DPI             = 1028,
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
    D3DKMT_ESCAPE_WIN32K_BDD_FALLBACK           = 1029,
    D3DKMT_ESCAPE_WIN32K_DDA_TEST_CTL           = 1030,
    D3DKMT_ESCAPE_WIN32K_USER_DETECTED_BLACK_SCREEN = 1031,
    // unused (1032 was previously D3DKMT_ESCAPE_WIN32K_HMD_ENUM)
    // unused (1033 was previously D3DKMT_ESCAPE_WIN32K_HMD_CONTROL)
    // unused (1034 was previously D3DKMT_ESCAPE_WIN32K_LPMDISPLAY_CONTROL)
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_5)
    D3DKMT_ESCAPE_WIN32K_DISPBROKER_TEST        = 1035,
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_6)
    D3DKMT_ESCAPE_WIN32K_COLOR_PROFILE_INFO     = 1036,
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_7)
    D3DKMT_ESCAPE_WIN32K_SET_DIMMED_STATE       = 1037,
    D3DKMT_ESCAPE_WIN32K_SPECIALIZED_DISPLAY_TEST = 1038,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_7
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_6
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_5
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_0
#endif // DXGKDDI_INTERFACE_VERSION_WDDM1_3
#endif // DXGKDDI_INTERFACE_VERSION_WIN8
} D3DKMT_ESCAPETYPE;

typedef struct _D3DKMT_DOD_SET_DIRTYRECT_MODE
{
    BOOL bForceFullScreenDirty;      // in: indicates if this adapter should always give full screen dirty for every Dod present
}D3DKMT_DOD_SET_DIRTYRECT_MODE;

typedef enum _D3DKMT_TDRDBGCTRLTYPE
{
    D3DKMT_TDRDBGCTRLTYPE_FORCETDR          = 0, //Simulate a TDR
    D3DKMT_TDRDBGCTRLTYPE_DISABLEBREAK      = 1, //Disable DebugBreak on timeout
    D3DKMT_TDRDBGCTRLTYPE_ENABLEBREAK       = 2, //Enable DebugBreak on timeout
    D3DKMT_TDRDBGCTRLTYPE_UNCONDITIONAL     = 3, //Disables all safety conditions (e.g. check for consecutive recoveries)
    D3DKMT_TDRDBGCTRLTYPE_VSYNCTDR          = 4, //Simulate a Vsync TDR
    D3DKMT_TDRDBGCTRLTYPE_GPUTDR            = 5, //Simulate a GPU TDR
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
    D3DKMT_TDRDBGCTRLTYPE_FORCEDODTDR       = 6, //Simulate a Display Only Present TDR
    D3DKMT_TDRDBGCTRLTYPE_FORCEDODVSYNCTDR  = 7, //Simulate a Display Only Vsync TDR
    D3DKMT_TDRDBGCTRLTYPE_ENGINETDR         = 8, //Simulate an engine TDR
#endif
} D3DKMT_TDRDBGCTRLTYPE;

typedef enum _D3DKMT_VIDMMESCAPETYPE
{
    D3DKMT_VIDMMESCAPETYPE_SETFAULT                     = 0,
    D3DKMT_VIDMMESCAPETYPE_RUN_COHERENCY_TEST           = 1,
    D3DKMT_VIDMMESCAPETYPE_RUN_UNMAP_TO_DUMMY_PAGE_TEST = 2,
    D3DKMT_VIDMMESCAPETYPE_APERTURE_CORRUPTION_CHECK    = 3,
    D3DKMT_VIDMMESCAPETYPE_SUSPEND_CPU_ACCESS_TEST      = 4,
    D3DKMT_VIDMMESCAPETYPE_EVICT                        = 5,
    D3DKMT_VIDMMESCAPETYPE_EVICT_BY_NT_HANDLE           = 6,
    D3DKMT_VIDMMESCAPETYPE_GET_VAD_INFO                 = 7,
    D3DKMT_VIDMMESCAPETYPE_SET_BUDGET                   = 8,
    D3DKMT_VIDMMESCAPETYPE_SUSPEND_PROCESS              = 9,
    D3DKMT_VIDMMESCAPETYPE_RESUME_PROCESS               = 10,
    D3DKMT_VIDMMESCAPETYPE_GET_BUDGET                   = 11,
    D3DKMT_VIDMMESCAPETYPE_SET_TRIM_INTERVALS           = 12,
    D3DKMT_VIDMMESCAPETYPE_EVICT_BY_CRITERIA            = 13,
    D3DKMT_VIDMMESCAPETYPE_WAKE                         = 14,
    D3DKMT_VIDMMESCAPETYPE_DEFRAG                       = 15,
    D3DKMT_VIDMMESCAPETYPE_DELAYEXECUTION               = 16,
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_7)
    D3DKMT_VIDMMESCAPETYPE_VALIDATE_INTEGRITY           = 17,
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_9)
    D3DKMT_VIDMMESCAPETYPE_SET_EVICTION_CONFIG          = 18,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_9
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_7
} D3DKMT_VIDMMESCAPETYPE;

typedef enum _D3DKMT_VIDSCHESCAPETYPE
{
    D3DKMT_VIDSCHESCAPETYPE_PREEMPTIONCONTROL    = 0, //Enable/Disable preemption
    D3DKMT_VIDSCHESCAPETYPE_SUSPENDSCHEDULER     = 1, //Suspend/Resume scheduler (obsolate)
    D3DKMT_VIDSCHESCAPETYPE_TDRCONTROL           = 2, //Tdr control
    D3DKMT_VIDSCHESCAPETYPE_SUSPENDRESUME        = 3, //Suspend/Resume scheduler
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
    D3DKMT_VIDSCHESCAPETYPE_ENABLECONTEXTDELAY   = 4, //Enable/Disable context delay
#endif
    D3DKMT_VIDSCHESCAPETYPE_CONFIGURE_TDR_LIMIT  = 5, // Configure TdrLimitCount and TdrLimitTime
    D3DKMT_VIDSCHESCAPETYPE_VGPU_RESET           = 6, // Trigger VGPU reset
    D3DKMT_VIDSCHESCAPETYPE_PFN_CONTROL          = 7, // Periodic frame notification control
    D3DKMT_VIDSCHESCAPETYPE_VIRTUAL_REFRESH_RATE = 8,
} D3DKMT_VIDSCHESCAPETYPE;

typedef enum _D3DKMT_DMMESCAPETYPE
{
    D3DKMT_DMMESCAPETYPE_UNINITIALIZED                       =  0,
    D3DKMT_DMMESCAPETYPE_GET_SUMMARY_INFO                    =  1,
    D3DKMT_DMMESCAPETYPE_GET_VIDEO_PRESENT_SOURCES_INFO      =  2,
    D3DKMT_DMMESCAPETYPE_GET_VIDEO_PRESENT_TARGETS_INFO      =  3,
    D3DKMT_DMMESCAPETYPE_GET_ACTIVEVIDPN_INFO                =  4,
    D3DKMT_DMMESCAPETYPE_GET_MONITORS_INFO                   =  5,
    D3DKMT_DMMESCAPETYPE_RECENTLY_COMMITTED_VIDPNS_INFO      =  6,
    D3DKMT_DMMESCAPETYPE_RECENT_MODECHANGE_REQUESTS_INFO     =  7,
    D3DKMT_DMMESCAPETYPE_RECENTLY_RECOMMENDED_VIDPNS_INFO    =  8,
    D3DKMT_DMMESCAPETYPE_RECENT_MONITOR_PRESENCE_EVENTS_INFO =  9,
    D3DKMT_DMMESCAPETYPE_ACTIVEVIDPN_SOURCEMODESET_INFO      = 10,
    D3DKMT_DMMESCAPETYPE_ACTIVEVIDPN_COFUNCPATHMODALITY_INFO = 11,
    D3DKMT_DMMESCAPETYPE_GET_LASTCLIENTCOMMITTEDVIDPN_INFO   = 12,
    D3DKMT_DMMESCAPETYPE_GET_VERSION_INFO                    = 13,
    D3DKMT_DMMESCAPETYPE_VIDPN_MGR_DIAGNOSTICS               = 14
} D3DKMT_DMMESCAPETYPE;

typedef struct _D3DKMT_HISTORY_BUFFER_STATUS
{
    BOOLEAN Enabled;
    UINT Reserved;
} D3DKMT_HISTORY_BUFFER_STATUS;

typedef enum _D3DKMT_VAD_ESCAPE_COMMAND
{
    D3DKMT_VAD_ESCAPE_GETNUMVADS,
    D3DKMT_VAD_ESCAPE_GETVAD,
    D3DKMT_VAD_ESCAPE_GETVADRANGE,
    D3DKMT_VAD_ESCAPE_GET_PTE,
    D3DKMT_VAD_ESCAPE_GET_GPUMMU_CAPS,
    D3DKMT_VAD_ESCAPE_GET_SEGMENT_CAPS,
} D3DKMT_VAD_ESCAPE_COMMAND;

typedef struct _D3DKMT_VAD_DESC
{
    UINT                  VadIndex;           // in: 0xFFFFFFFF to use the VAD address
    D3DKMT_ALIGN64 UINT64 VadAddress;         // in
    UINT                  NumMappedRanges;    // out
    UINT                  VadType;            // out: 0 - reserved, 1 - Mapped
    D3DKMT_ALIGN64 UINT64 StartAddress;       // out
    D3DKMT_ALIGN64 UINT64 EndAddress;         // out
} D3DKMT_VAD_DESC;

typedef struct _D3DKMT_VA_RANGE_DESC
{
    D3DKMT_ALIGN64 UINT64 VadAddress;             // in
    UINT                  VaRangeIndex;           // in
    UINT                  PhysicalAdapterIndex;   // in
    D3DKMT_ALIGN64 UINT64 StartAddress;           // out
    D3DKMT_ALIGN64 UINT64 EndAddress;             // out
    D3DKMT_ALIGN64 UINT64 DriverProtection;       // out
    UINT                  OwnerType;              // out: VIDMM_VAD_OWNER_TYPE
    D3DKMT_ALIGN64 UINT64 pOwner;                 // out
    D3DKMT_ALIGN64 UINT64 OwnerOffset;            // out
    UINT                  Protection;             // out: D3DDDIGPUVIRTUALADDRESS_PROTECTION_TYPE
} D3DKMT_VA_RANGE_DESC;

typedef struct _D3DKMT_EVICTION_CRITERIA
{
    D3DKMT_ALIGN64 UINT64 MinimumSize;
    D3DKMT_ALIGN64 UINT64 MaximumSize;
    struct
    {
        union
        {
            struct
            {
                UINT Primary  :  1; // 0x00000001
                UINT Reserved : 31; // 0xFFFFFFFE
            } Flags;
            UINT Value;
        };
    };
} D3DKMT_EVICTION_CRITERIA;

typedef enum _D3DKMT_DEFRAG_ESCAPE_OPERATION
{
    D3DKMT_DEFRAG_ESCAPE_GET_FRAGMENTATION_STATS       =  0,
    D3DKMT_DEFRAG_ESCAPE_DEFRAG_UPWARD                 =  1,
    D3DKMT_DEFRAG_ESCAPE_DEFRAG_DOWNWARD               =  2,
    D3DKMT_DEFRAG_ESCAPE_DEFRAG_PASS                   =  3,
    D3DKMT_DEFRAG_ESCAPE_VERIFY_TRANSFER               =  4,
} D3DKMT_DEFRAG_ESCAPE_OPERATION;

typedef struct _D3DKMT_PAGE_TABLE_LEVEL_DESC
{
    UINT                  IndexBitCount;
    D3DKMT_ALIGN64 UINT64 IndexMask;
    D3DKMT_ALIGN64 UINT64 IndexShift;
    D3DKMT_ALIGN64 UINT64 LowerLevelsMask;
    D3DKMT_ALIGN64 UINT64 EntryCoverageInPages;
} D3DKMT_PAGE_TABLE_LEVEL_DESC;

typedef struct _DXGK_ESCAPE_GPUMMUCAPS
{
    BOOLEAN ReadOnlyMemorySupported;
    BOOLEAN NoExecuteMemorySupported;
    BOOLEAN ZeroInPteSupported;
    BOOLEAN CacheCoherentMemorySupported;
    BOOLEAN LargePageSupported;
    BOOLEAN DualPteSupported;
    BOOLEAN AllowNonAlignedLargePageAddress;
    UINT    VirtualAddressBitCount;
    UINT    PageTableLevelCount;
    D3DKMT_PAGE_TABLE_LEVEL_DESC PageTableLevelDesk[DXGK_MAX_PAGE_TABLE_LEVEL_COUNT];
} DXGK_ESCAPE_GPUMMUCAPS;

typedef struct _D3DKMT_GET_GPUMMU_CAPS
{
    UINT                    PhysicalAdapterIndex;   // In
    DXGK_ESCAPE_GPUMMUCAPS  GpuMmuCaps;             // Out
} D3DKMT_GET_GPUMMU_CAPS;

#define D3DKMT_GET_PTE_MAX 64

typedef struct _D3DKMT_GET_PTE
{
    UINT        PhysicalAdapterIndex;                               // In
    UINT        PageTableLevel;                                     // In
    UINT        PageTableIndex[DXGK_MAX_PAGE_TABLE_LEVEL_COUNT];    // In
    BOOLEAN     b64KBPte;                                           // In - Valid only when dual PTEs are supported. Out - PT is 64KB.
    UINT        NumPtes;                                            // In - Number of PTEs to fill. Out - number of filled PTEs
    DXGK_PTE    Pte[D3DKMT_GET_PTE_MAX];                            // Out
    UINT        NumValidEntries;                                    // Out
} D3DKMT_GET_PTE;

#define D3DKMT_MAX_SEGMENT_COUNT 32

typedef enum _D3DKMT_MEMORY_SEGMENT_GROUP
{
    D3DKMT_MEMORY_SEGMENT_GROUP_LOCAL = 0,
    D3DKMT_MEMORY_SEGMENT_GROUP_NON_LOCAL = 1
} D3DKMT_MEMORY_SEGMENT_GROUP;

typedef struct _D3DKMT_SEGMENT_CAPS
{
    D3DKMT_ALIGN64 UINT64 Size;
    UINT    PageSize;
    ULONG   SegmentId;
    BOOLEAN bAperture;
    BOOLEAN bReservedSysMem;
    D3DKMT_MEMORY_SEGMENT_GROUP BudgetGroup;
} D3DKMT_SEGMENT_CAPS;

typedef struct _D3DKMT_GET_SEGMENT_CAPS
{
    UINT        PhysicalAdapterIndex;                               // In
    UINT        NumSegments;                                        // Out
    D3DKMT_SEGMENT_CAPS SegmentCaps[D3DKMT_MAX_SEGMENT_COUNT];      // Out
} D3DKMT_GET_SEGMENT_CAPS;

typedef enum _D3DKMT_ESCAPE_PFN_CONTROL_COMMAND
{
    D3DKMT_ESCAPE_PFN_CONTROL_DEFAULT,
    D3DKMT_ESCAPE_PFN_CONTROL_FORCE_CPU,
    D3DKMT_ESCAPE_PFN_CONTROL_FORCE_GPU
} D3DKMT_ESCAPE_PFN_CONTROL_COMMAND;

// params for D3DKMT_VIDSCHESCAPETYPE_VIRTUAL_REFRESH_RATE
typedef enum _D3DKMT_ESCAPE_VIRTUAL_REFRESH_RATE_TYPE
{
    D3DKMT_ESCAPE_VIRTUAL_REFRESH_RATE_TYPE_SET_BASE_DESKTOP_DURATION = 0,
    D3DKMT_ESCAPE_VIRTUAL_REFRESH_RATE_TYPE_SET_VSYNC_MULTIPLIER = 1,
    D3DKMT_ESCAPE_VIRTUAL_REFRESH_RATE_TYPE_SET_PROCESS_BOOST_ELIGIBLE = 2,
} D3DKMT_ESCAPE_VIRTUAL_REFRESH_RATE_TYPE;

typedef struct _D3DKMT_ESCAPE_VIRTUAL_REFRESH_RATE
{
    D3DKMT_ESCAPE_VIRTUAL_REFRESH_RATE_TYPE Type;
    UINT     VidPnSourceId;
    BOOLEAN  ProcessBoostEligible;
    UINT     VSyncMultiplier;
    UINT     BaseDesktopDuration;
    UCHAR    Reserved[16];
} D3DKMT_ESCAPE_VIRTUAL_REFRESH_RATE;

typedef struct _D3DKMT_VIDMM_ESCAPE
{
    D3DKMT_VIDMMESCAPETYPE Type;
    union
    {
        struct
        {
            union
            {
                struct
                {
                    ULONG ProbeAndLock : 1;
                    ULONG SplitPoint : 1;
                    ULONG NoDemotion : 1;
                    ULONG SwizzlingAperture : 1;
                    ULONG PagingPathLockSubRange : 1;
                    ULONG PagingPathLockMinRange : 1;
                    ULONG ComplexLock : 1;
                    ULONG FailVARotation : 1;
                    ULONG NoWriteCombined : 1;
                    ULONG NoPrePatching : 1;
                    ULONG AlwaysRepatch : 1;
                    ULONG ExpectPreparationFailure : 1;
                    ULONG FailUserModeVAMapping : 1;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
                    ULONG NeverDiscardOfferedAllocation : 1;
                    ULONG AlwaysDiscardOfferedAllocation : 1;
                    ULONG Reserved : 17;
#else
                    ULONG Reserved : 19;
#endif
                };
                ULONG Value;
            };
        } SetFault;
        struct
        {
            D3DKMT_HANDLE ResourceHandle;
            D3DKMT_HANDLE AllocationHandle;
            D3DKMT_PTR(HANDLE, hProcess);        // 0 to evict memory for the current process, otherwise it is a process handle from OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessId).
        } Evict;
        struct
        {
            D3DKMT_ALIGN64 UINT64 NtHandle;           // Used by D3DKMT_VIDMMESCAPETYPE_EVICT_BY_NT_HANDLE
        } EvictByNtHandle;
        struct
        {
            union
            {
                struct
                {
                    UINT NumVads;
                } GetNumVads;
                D3DKMT_VAD_DESC GetVad;
                D3DKMT_VA_RANGE_DESC GetVadRange;
                D3DKMT_GET_GPUMMU_CAPS GetGpuMmuCaps;
                D3DKMT_GET_PTE  GetPte;
                D3DKMT_GET_SEGMENT_CAPS GetSegmentCaps;
            };
            D3DKMT_VAD_ESCAPE_COMMAND Command;      // in
            NTSTATUS    Status;                     // out
        } GetVads;
        struct
        {
            D3DKMT_ALIGN64 ULONGLONG LocalMemoryBudget;
            D3DKMT_ALIGN64 ULONGLONG SystemMemoryBudget;
        } SetBudget;
        struct
        {
            D3DKMT_PTR(HANDLE, hProcess);
            BOOL bAllowWakeOnSubmission;
        } SuspendProcess;
        struct
        {
            D3DKMT_PTR(HANDLE, hProcess);
        } ResumeProcess;
        struct
        {
            D3DKMT_ALIGN64 UINT64 NumBytesToTrim;
        } GetBudget;
        struct
        {
            ULONG MinTrimInterval; // In 100ns units
            ULONG MaxTrimInterval; // In 100ns units
            ULONG IdleTrimInterval; // In 100ns units
        } SetTrimIntervals;
        D3DKMT_EVICTION_CRITERIA EvictByCriteria;
        struct
        {
            BOOL bFlush;
        } Wake;
        struct
        {
            D3DKMT_DEFRAG_ESCAPE_OPERATION  Operation;

            UINT                            SegmentId;

            D3DKMT_ALIGN64 ULONGLONG                       TotalCommitted;
            D3DKMT_ALIGN64 ULONGLONG                       TotalFree;
            D3DKMT_ALIGN64 ULONGLONG                       LargestGapBefore;
            D3DKMT_ALIGN64 ULONGLONG                       LargestGapAfter;
        } Defrag;
        struct
        {
            D3DKMT_HANDLE hPagingQueue;
            UINT PhysicalAdapterIndex;
            ULONG Milliseconds;
            D3DKMT_ALIGN64 ULONGLONG PagingFenceValue;
        } DelayExecution;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_7)
        struct
        {
            UINT SegmentId;
        } VerifyIntegrity;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_9)
        struct
        {
            D3DKMT_ALIGN64 LONGLONG TimerValue;
        } DelayedEvictionConfig;
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_9
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_7
    };
} D3DKMT_VIDMM_ESCAPE;

typedef struct _D3DKMT_VIDSCH_ESCAPE
{
    D3DKMT_VIDSCHESCAPETYPE Type;
    union
    {
        BOOL PreemptionControl; // enable/disable preemption
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
        BOOL EnableContextDelay; // enable/disable context delay
        struct
        {
            ULONG TdrControl;   // control tdr
            union
            {
                ULONG NodeOrdinal;  // valid if TdrControl is set to D3DKMT_TDRDBGCTRLTYPE_ENGINETDR
            };
        } TdrControl2;
#endif
        BOOL SuspendScheduler;  // suspend/resume scheduler (obsolate)
        ULONG TdrControl;       // control tdr
        ULONG SuspendTime;      // time period to suspend.
        struct
        {
            UINT Count;
            UINT Time; // In seconds
        } TdrLimit;

        D3DKMT_ESCAPE_PFN_CONTROL_COMMAND  PfnControl;   // periodic frame notification control
    };
    D3DKMT_ESCAPE_VIRTUAL_REFRESH_RATE VirtualRefreshRateControl;
} D3DKMT_VIDSCH_ESCAPE;

typedef struct _D3DKMT_TDRDBGCTRL_ESCAPE
{
    D3DKMT_TDRDBGCTRLTYPE TdrControl;   // control tdr
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
    union
    {
        ULONG NodeOrdinal;  // valid if TdrControl is set to D3DKMT_TDRDBGCTRLTYPE_ENGINETDR
    };
#endif
} D3DKMT_TDRDBGCTRL_ESCAPE;

// Upper boundary on the DMM escape data size (in bytes).
enum
{
    D3DKMT_MAX_DMM_ESCAPE_DATASIZE = 100*1024
};

// NOTE: If (ProvidedBufferSize >= MinRequiredBufferSize), then MinRequiredBufferSize = size of the actual complete data set in the Data[] array.
typedef struct _D3DKMT_DMM_ESCAPE
{
    _In_  D3DKMT_DMMESCAPETYPE  Type;
    _In_  D3DKMT_ALIGN64 D3DKMT_SIZE_T ProvidedBufferSize;     // actual size of Data[] array, in bytes.
    _Out_ D3DKMT_ALIGN64 D3DKMT_SIZE_T MinRequiredBufferSize;  // minimum required size of Data[] array to contain requested data.
    _Out_writes_bytes_(ProvidedBufferSize) UCHAR  Data[1];
} D3DKMT_DMM_ESCAPE;

typedef enum _D3DKMT_BRIGHTNESS_INFO_TYPE
{
    D3DKMT_BRIGHTNESS_INFO_GET_POSSIBLE_LEVELS  = 1,
    D3DKMT_BRIGHTNESS_INFO_GET                  = 2,
    D3DKMT_BRIGHTNESS_INFO_SET                  = 3,
    D3DKMT_BRIGHTNESS_INFO_GET_CAPS             = 4,
    D3DKMT_BRIGHTNESS_INFO_SET_STATE            = 5,
    D3DKMT_BRIGHTNESS_INFO_SET_OPTIMIZATION     = 6,
    D3DKMT_BRIGHTNESS_INFO_GET_REDUCTION        = 7,
    D3DKMT_BRIGHTNESS_INFO_BEGIN_MANUAL_MODE    = 8,
    D3DKMT_BRIGHTNESS_INFO_END_MANUAL_MODE      = 9,
    D3DKMT_BRIGHTNESS_INFO_TOGGLE_LOGGING       = 10,
    D3DKMT_BRIGHTNESS_INFO_GET_NIT_RANGES       = 11,
} D3DKMT_BRIGHTNESS_INFO_TYPE;

typedef struct _D3DKMT_BRIGHTNESS_POSSIBLE_LEVELS
{
    UCHAR LevelCount;
    UCHAR BrightnessLevels[256];
} D3DKMT_BRIGHTNESS_POSSIBLE_LEVELS;

typedef struct _D3DKMT_BRIGHTNESS_INFO
{
    D3DKMT_BRIGHTNESS_INFO_TYPE    Type;
    ULONG                          ChildUid;
    union
    {
        D3DKMT_BRIGHTNESS_POSSIBLE_LEVELS   PossibleLevels;
        UCHAR                               Brightness;
        DXGK_BRIGHTNESS_CAPS                BrightnessCaps;
        DXGK_BRIGHTNESS_STATE               BrightnessState;
        DXGK_BACKLIGHT_OPTIMIZATION_LEVEL   OptimizationLevel;
        DXGK_BACKLIGHT_INFO                 ReductionInfo;
        BOOLEAN                             VerboseLogging;
        DXGK_BRIGHTNESS_GET_NIT_RANGES_OUT  NitRanges;
        DXGK_BRIGHTNESS_GET_OUT             GetBrightnessMillinits;
        DXGK_BRIGHTNESS_SET_IN              SetBrightnessMillinits;
    };
} D3DKMT_BRIGHTNESS_INFO;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
typedef struct _D3DKMT_BDDFALLBACK_CTL
{
    BOOLEAN ForceBddHeadlessNextFallback;
} D3DKMT_BDDFALLBACK_CTL;

typedef struct _D3DKMT_REQUEST_MACHINE_CRASH_ESCAPE
{
    D3DKMT_ALIGN64 D3DKMT_ULONG_PTR Param1;
    D3DKMT_ALIGN64 D3DKMT_ULONG_PTR Param2;
    D3DKMT_ALIGN64 D3DKMT_ULONG_PTR Param3;
} D3DKMT_REQUEST_MACHINE_CRASH_ESCAPE;

//
// VERIFIER OPTIONS
//
typedef enum _D3DKMT_VERIFIER_OPTION_MODE
{
    D3DKMT_VERIFIER_OPTION_QUERY,
    D3DKMT_VERIFIER_OPTION_SET
} D3DKMT_VERIFIER_OPTION_MODE;

typedef enum _D3DKMT_PROCESS_VERIFIER_OPTION_TYPE
{
    //
    // Dxgkrnl (0xxx)
    //

    //
    // VidMm (1xxx)
    //
    D3DKMT_PROCESS_VERIFIER_OPTION_VIDMM_FLAGS              = 1000,
    D3DKMT_PROCESS_VERIFIER_OPTION_VIDMM_RESTRICT_BUDGET    = 1001,

    //
    // VidSch (2xxx)
    //

} D3DKMT_PROCESS_VERIFIER_OPTION_TYPE;

typedef union _D3DKMT_PROCESS_VERIFIER_VIDMM_FLAGS
{
    struct
    {
        UINT ForceSynchronousEvict        : 1;
        UINT NeverDeferEvictions          : 1;
        UINT AlwaysFailCommitOnReclaim    : 1;
        UINT AlwaysPlaceInDemotedLocation : 1;
        UINT Reserved : 28;
    };
    UINT32 Value;
} D3DKMT_PROCESS_VERIFIER_VIDMM_FLAGS;

typedef struct _D3DKMT_PROCESS_VERIFIER_VIDMM_RESTRICT_BUDGET
{
    D3DKMT_ALIGN64 UINT64 LocalBudget;
    D3DKMT_ALIGN64 UINT64 NonLocalBudget;
} D3DKMT_PROCESS_VERIFIER_VIDMM_RESTRICT_BUDGET;

typedef union _D3DKMT_PROCESS_VERIFIER_OPTION_DATA
{
    D3DKMT_PROCESS_VERIFIER_VIDMM_FLAGS VidMmFlags;
    D3DKMT_PROCESS_VERIFIER_VIDMM_RESTRICT_BUDGET VidMmRestrictBudget;
} D3DKMT_PROCESS_VERIFIER_OPTION_DATA;

typedef struct _D3DKMT_PROCESS_VERIFIER_OPTION
{
    D3DKMT_PTR(HANDLE, hProcess);
    D3DKMT_PROCESS_VERIFIER_OPTION_TYPE Type;
    D3DKMT_VERIFIER_OPTION_MODE Mode;
    D3DKMT_PROCESS_VERIFIER_OPTION_DATA Data;
} D3DKMT_PROCESS_VERIFIER_OPTION;

typedef enum _D3DKMT_ADAPTER_VERIFIER_OPTION_TYPE
{
    //
    // Dxgkrnl (0xxx)
    //

    //
    // VidMm (1xxx)
    //
    D3DKMT_ADAPTER_VERIFIER_OPTION_VIDMM_FLAGS          = 1000,
    D3DKMT_ADAPTER_VERIFIER_OPTION_VIDMM_TRIM_INTERVAL  = 1001,

    //
    // VidSch (2xxx)
    //
} D3DKMT_ADAPTER_VERIFIER_OPTION_TYPE;

typedef union _D3DKMT_ADAPTER_VERIFIER_VIDMM_FLAGS
{
    struct
    {
        UINT AlwaysRepatch                      : 1;
        UINT FailSharedPrimary                  : 1;
        UINT FailProbeAndLock                   : 1;
        UINT AlwaysDiscardOffer                 : 1;
        UINT NeverDiscardOffer                  : 1;
        UINT ForceComplexLock                   : 1;
        UINT NeverPrepatch                      : 1;
        UINT ExpectPreparationFailure           : 1;
        UINT TakeSplitPoint                     : 1;
        UINT FailAcquireSwizzlingRange          : 1;
        UINT PagingPathLockSubrange             : 1;
        UINT PagingPathLockMinrange             : 1;
        UINT FailVaRotation                     : 1;
        UINT NoDemotion                         : 1;
        UINT FailDefragPass                     : 1;
        UINT AlwaysProcessOfferList             : 1;
        UINT AlwaysDecommitOffer                : 1;
        UINT NeverMoveDefrag                    : 1;
        UINT AlwaysRelocateDisplayableResources : 1;
        UINT AlwaysFailGrowVPRMoves             : 1;
        UINT Reserved                           : 12;
    };
    UINT32 Value;
} D3DKMT_ADAPTER_VERIFIER_VIDMM_FLAGS;

typedef struct _D3DKMT_ADAPTER_VERIFIER_VIDMM_TRIM_INTERVAL
{
    D3DKMT_ALIGN64 UINT64 MinimumTrimInterval;
    D3DKMT_ALIGN64 UINT64 MaximumTrimInterval;
    D3DKMT_ALIGN64 UINT64 IdleTrimInterval;
} D3DKMT_ADAPTER_VERIFIER_VIDMM_TRIM_INTERVAL;

typedef union _D3DKMT_ADAPTER_VERIFIER_OPTION_DATA
{
    D3DKMT_ADAPTER_VERIFIER_VIDMM_FLAGS VidMmFlags;
    D3DKMT_ADAPTER_VERIFIER_VIDMM_TRIM_INTERVAL VidMmTrimInterval;
} D3DKMT_ADAPTER_VERIFIER_OPTION_DATA;

typedef struct _D3DKMT_ADAPTER_VERIFIER_OPTION
{
    D3DKMT_ADAPTER_VERIFIER_OPTION_TYPE Type;
    D3DKMT_VERIFIER_OPTION_MODE Mode;
    D3DKMT_ADAPTER_VERIFIER_OPTION_DATA Data;
} D3DKMT_ADAPTER_VERIFIER_OPTION;

#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_0

typedef enum _D3DKMT_DEVICEESCAPE_TYPE
{
    D3DKMT_DEVICEESCAPE_VIDPNFROMALLOCATION = 0,
    D3DKMT_DEVICEESCAPE_RESTOREGAMMA        = 1,
} D3DKMT_DEVICEESCAPE_TYPE;

typedef struct _D3DKMT_DEVICE_ESCAPE
{
    D3DKMT_DEVICEESCAPE_TYPE Type;
    union
    {
        struct
        {
            D3DKMT_HANDLE                   hPrimaryAllocation; // in: Primary allocation handle
            D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;      // out: VidPnSoureId of primary allocation
        } VidPnFromAllocation;
    };
} D3DKMT_DEVICE_ESCAPE;

typedef struct _D3DKMT_DEBUG_SNAPSHOT_ESCAPE
{
    ULONG Length;   // out: Actual length of the snapshot written in Buffer
    BYTE Buffer[1]; // out: Buffer to place snapshot
} D3DKMT_DEBUG_SNAPSHOT_ESCAPE;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
#ifndef DXGK_DIAG_PROCESS_NAME_LENGTH
#define DXGK_DIAG_PROCESS_NAME_LENGTH 16
#endif

typedef enum _OUTPUTDUPL_CONTEXT_DEBUG_STATUS
{
    OUTPUTDUPL_CONTEXT_DEBUG_STATUS_INACTIVE = 0,
    OUTPUTDUPL_CONTEXT_DEBUG_STATUS_ACTIVE = 1,
    OUTPUTDUPL_CONTEXT_DEBUG_STATUS_PENDING_DESTROY = 2,
    OUTPUTDUPL_CONTEXT_DEBUG_STATUS_FORCE_UINT32 = 0xffffffff
}OUTPUTDUPL_CONTEXT_DEBUG_STATUS;

typedef struct _OUTPUTDUPL_CONTEXT_DEBUG_INFO
{
    OUTPUTDUPL_CONTEXT_DEBUG_STATUS Status;
    D3DKMT_PTR(HANDLE,              ProcessID);
    UINT32                          AccumulatedPresents;
    D3DKMT_ALIGN64 LARGE_INTEGER    LastPresentTime;
    D3DKMT_ALIGN64 LARGE_INTEGER    LastMouseTime;
    CHAR                            ProcessName[DXGK_DIAG_PROCESS_NAME_LENGTH];
} OUTPUTDUPL_CONTEXT_DEBUG_INFO;

#define GET_OUTPUT_DUPL_DEBUG_INFO_FROM_SNAPSHOT(pSnapshot, VidPnSource, OutputDuplContextIndex) \
    (pSnapshot->OutputDuplDebugInfos[(VidPnSource * pSnapshot->NumOutputDuplContexts) + OutputDuplContextIndex])

typedef struct _D3DKMT_OUTPUTDUPL_SNAPSHOT
{
    UINT Size;                          // _In_/out: Size of entire structure

    UINT SessionProcessCount;           // _Out_: Number of processes currently duplicating output in this session (max possible will be equal to NumOutputDuplContexts)
    UINT SessionActiveConnectionsCount; // _Out_: Total number of active contexts in this session, may be more than number active in 2D array because that is per adapter

    UINT NumVidPnSources;               // _Out_: Max of first array index
    UINT NumOutputDuplContexts;         // _Out_: Max of second array index

    UINT Padding;

    // This field is in reality a two dimensional array, use GET_OUTPUT_DUPL_DEBUG_INFO_FROM_SNAPSHOT macro to get a specific one
    _Field_size_bytes_(Size - sizeof(_D3DKMT_OUTPUTDUPL_SNAPSHOT)) OUTPUTDUPL_CONTEXT_DEBUG_INFO OutputDuplDebugInfos[0];
} D3DKMT_OUTPUTDUPL_SNAPSHOT;
#endif

typedef enum _D3DKMT_ACTIVATE_SPECIFIC_DIAG_TYPE
{
    D3DKMT_ACTIVATE_SPECIFIC_DIAG_TYPE_EXTRA_CCD_DATABASE_INFO = 0,
    D3DKMT_ACTIVATE_SPECIFIC_DIAG_TYPE_MODES_PRUNED            = 15,
}D3DKMT_ACTIVATE_SPECIFIC_DIAG_TYPE;

typedef struct _D3DKMT_ACTIVATE_SPECIFIC_DIAG_ESCAPE
{
    D3DKMT_ACTIVATE_SPECIFIC_DIAG_TYPE  Type;     // The escape type that needs to be (de)activated
    BOOL                                Activate; // FALSE means deactivate
} D3DKMT_ACTIVATE_SPECIFIC_DIAG_ESCAPE;

typedef struct _D3DKMT_ESCAPE
{
    D3DKMT_HANDLE       hAdapter;               // in: adapter handle
    D3DKMT_HANDLE       hDevice;                // in: device handle [Optional]
    D3DKMT_ESCAPETYPE   Type;                   // in: escape type.
    D3DDDI_ESCAPEFLAGS  Flags;                  // in: flags
    D3DKMT_PTR(VOID*,   pPrivateDriverData);    // in/out: escape data
    UINT                PrivateDriverDataSize;  // in: size of escape data
    D3DKMT_HANDLE       hContext;               // in: context handle [Optional]
} D3DKMT_ESCAPE;

//
// begin D3DKMT_QUERYSTATISTICS
//

typedef enum _D3DKMT_QUERYRESULT_PREEMPTION_ATTEMPT_RESULT
{
    D3DKMT_PreemptionAttempt                               = 0,
    D3DKMT_PreemptionAttemptSuccess                        = 1,
    D3DKMT_PreemptionAttemptMissNoCommand                  = 2,
    D3DKMT_PreemptionAttemptMissNotEnabled                 = 3,
    D3DKMT_PreemptionAttemptMissNextFence                  = 4,
    D3DKMT_PreemptionAttemptMissPagingCommand              = 5,
    D3DKMT_PreemptionAttemptMissSplittedCommand            = 6,
    D3DKMT_PreemptionAttemptMissFenceCommand               = 7,
    D3DKMT_PreemptionAttemptMissRenderPendingFlip          = 8,
    D3DKMT_PreemptionAttemptMissNotMakingProgress          = 9,
    D3DKMT_PreemptionAttemptMissLessPriority               = 10,
    D3DKMT_PreemptionAttemptMissRemainingQuantum           = 11,
    D3DKMT_PreemptionAttemptMissRemainingPreemptionQuantum = 12,
    D3DKMT_PreemptionAttemptMissAlreadyPreempting          = 13,
    D3DKMT_PreemptionAttemptMissGlobalBlock                = 14,
    D3DKMT_PreemptionAttemptMissAlreadyRunning             = 15,
    D3DKMT_PreemptionAttemptStatisticsMax                  = 16,
} D3DKMT_QUERYRESULT_PREEMPTION_ATTEMPT_RESULT;

//
// WOW will not allow enum member as array length, so define it as a constant
//
#define D3DKMT_QUERYRESULT_PREEMPTION_ATTEMPT_RESULT_MAX 16
C_ASSERT(D3DKMT_QUERYRESULT_PREEMPTION_ATTEMPT_RESULT_MAX == D3DKMT_PreemptionAttemptStatisticsMax);

//
// Command packet type
//
typedef enum _D3DKMT_QUERYSTATISTICS_DMA_PACKET_TYPE {
    D3DKMT_ClientRenderBuffer       = 0, // (Dma packet) should be 0 base.
    D3DKMT_ClientPagingBuffer       = 1, // (Dma packet)
    D3DKMT_SystemPagingBuffer       = 2, // (Dma packet)
    D3DKMT_SystemPreemptionBuffer   = 3, // (Dma packet)
    D3DKMT_DmaPacketTypeMax         = 4
} D3DKMT_QUERYSTATISTICS_DMA_PACKET_TYPE;

//
// WOW will not allow enum member as array length, so define it as a constant
//
#define D3DKMT_QUERYSTATISTICS_DMA_PACKET_TYPE_MAX 4
C_ASSERT(D3DKMT_QUERYSTATISTICS_DMA_PACKET_TYPE_MAX == D3DKMT_DmaPacketTypeMax);

typedef enum _D3DKMT_QUERYSTATISTICS_QUEUE_PACKET_TYPE {
    D3DKMT_RenderCommandBuffer      = 0, // (Queue Packet) should be 0 base.
    D3DKMT_DeferredCommandBuffer    = 1, // (Queue Packet)
    D3DKMT_SystemCommandBuffer      = 2, // (Queue Packet)
    D3DKMT_MmIoFlipCommandBuffer    = 3, // (Queue Packet)
    D3DKMT_WaitCommandBuffer        = 4, // (Queue Packet)
    D3DKMT_SignalCommandBuffer      = 5, // (Queue Packet)
    D3DKMT_DeviceCommandBuffer      = 6, // (Queue Packet)
    D3DKMT_SoftwareCommandBuffer    = 7, // (Queue Packet)
    D3DKMT_QueuePacketTypeMax       = 8
} D3DKMT_QUERYSTATISTICS_QUEUE_PACKET_TYPE;

//
// WOW will not allow enum member as array length, so define it as a constant
//
#define D3DKMT_QUERYSTATISTICS_QUEUE_PACKET_TYPE_MAX 8
C_ASSERT(D3DKMT_QUERYSTATISTICS_QUEUE_PACKET_TYPE_MAX == D3DKMT_QueuePacketTypeMax);

typedef enum _D3DKMT_QUERYSTATISTICS_ALLOCATION_PRIORITY_CLASS
{
    D3DKMT_AllocationPriorityClassMinimum = 0,
    D3DKMT_AllocationPriorityClassLow = 1,
    D3DKMT_AllocationPriorityClassNormal = 2,
    D3DKMT_AllocationPriorityClassHigh = 3,
    D3DKMT_AllocationPriorityClassMaximum = 4,
    D3DKMT_MaxAllocationPriorityClass = 5
} D3DKMT_QUERYSTATISTICS_ALLOCATION_PRIORITY_CLASS;

//
// WOW will not allow enum member as array length, so define it as a constant
//

#define D3DKMT_QUERYSTATISTICS_ALLOCATION_PRIORITY_CLASS_MAX 5
C_ASSERT(D3DKMT_QUERYSTATISTICS_ALLOCATION_PRIORITY_CLASS_MAX == D3DKMT_MaxAllocationPriorityClass);

//
// Allocation segment preference set can contain 5 preferences
//
#define D3DKMT_QUERYSTATISTICS_SEGMENT_PREFERENCE_MAX 5

typedef struct _D3DKMT_QUERYSTATISTICS_COUNTER
{
    ULONG Count;
    ULONGLONG Bytes;
} D3DKMT_QUERYSTATISTICS_COUNTER;

typedef struct _D3DKMT_QUERYSTATISTICS_DMA_PACKET_TYPE_INFORMATION {
    ULONG PacketSubmited;
    ULONG PacketCompleted;
    ULONG PacketPreempted;
    ULONG PacketFaulted;
} D3DKMT_QUERYSTATISTICS_DMA_PACKET_TYPE_INFORMATION;

typedef struct _D3DKMT_QUERYSTATISTICS_QUEUE_PACKET_TYPE_INFORMATION {
    ULONG  PacketSubmited;
    ULONG  PacketCompleted;
} D3DKMT_QUERYSTATISTICS_QUEUE_PACKET_TYPE_INFORMATION;

typedef struct _D3DKMT_QUERYSTATISTICS_PACKET_INFORMATION {
  D3DKMT_QUERYSTATISTICS_QUEUE_PACKET_TYPE_INFORMATION QueuePacket[D3DKMT_QUERYSTATISTICS_QUEUE_PACKET_TYPE_MAX];  //Size = D3DKMT_QueuePacketTypeMax
  D3DKMT_QUERYSTATISTICS_DMA_PACKET_TYPE_INFORMATION   DmaPacket[D3DKMT_QUERYSTATISTICS_DMA_PACKET_TYPE_MAX];    //Size = D3DKMT_DmaPacketTypeMax
} D3DKMT_QUERYSTATISTICS_PACKET_INFORMATION;

typedef struct _D3DKMT_QUERYSTATISTICS_PREEMPTION_INFORMATION {
    ULONG PreemptionCounter[D3DKMT_QUERYRESULT_PREEMPTION_ATTEMPT_RESULT_MAX];
} D3DKMT_QUERYSTATISTICS_PREEMPTION_INFORMATION;

typedef struct _D3DKMT_QUERYSTATISTICS_PROCESS_NODE_INFORMATION {
    D3DKMT_ALIGN64 LARGE_INTEGER                  RunningTime;          // Running time in micro-second.
    ULONG                                         ContextSwitch;
    D3DKMT_QUERYSTATISTICS_PREEMPTION_INFORMATION PreemptionStatistics;
    D3DKMT_QUERYSTATISTICS_PACKET_INFORMATION     PacketStatistics;
    D3DKMT_ALIGN64 UINT64                         Reserved[8];
} D3DKMT_QUERYSTATISTICS_PROCESS_NODE_INFORMATION;

typedef struct _D3DKMT_QUERYSTATISTICS_NODE_INFORMATION {
    D3DKMT_QUERYSTATISTICS_PROCESS_NODE_INFORMATION GlobalInformation; //Global statistics
    D3DKMT_QUERYSTATISTICS_PROCESS_NODE_INFORMATION SystemInformation; //Statistics for system thread
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_4)
    D3DKMT_NODE_PERFDATA                            NodePerfData;
    UINT32                                          Reserved[3];
#else
    D3DKMT_ALIGN64 UINT64                           Reserved[8];
#endif
} D3DKMT_QUERYSTATISTICS_NODE_INFORMATION;

typedef struct _D3DKMT_QUERYSTATISTICS_PROCESS_VIDPNSOURCE_INFORMATION {
    ULONG  Frame;          // both by Blt and Flip.
    ULONG  CancelledFrame; // by restart (flip only).
    ULONG  QueuedPresent;  // queued present.
    UINT   Padding;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_7)
    D3DKMT_ALIGN64 UINT64 IsVSyncEnabled;
    D3DKMT_ALIGN64 UINT64 VSyncOnTotalTimeMs;
    D3DKMT_ALIGN64 UINT64 VSyncOffKeepPhaseTotalTimeMs;
    D3DKMT_ALIGN64 UINT64 VSyncOffNoPhaseTotalTimeMs;
    D3DKMT_ALIGN64 UINT64 Reserved[4];
#else
    D3DKMT_ALIGN64 UINT64 Reserved[8];
#endif

} D3DKMT_QUERYSTATISTICS_PROCESS_VIDPNSOURCE_INFORMATION;

typedef struct _D3DKMT_QUERYSTATISTICS_VIDPNSOURCE_INFORMATION {
    D3DKMT_QUERYSTATISTICS_PROCESS_VIDPNSOURCE_INFORMATION GlobalInformation;   //Global statistics
    D3DKMT_QUERYSTATISTICS_PROCESS_VIDPNSOURCE_INFORMATION SystemInformation;   //Statistics for system thread
    D3DKMT_ALIGN64 UINT64 Reserved[8];
} D3DKMT_QUERYSTATISTICS_VIDPNSOURCE_INFORMATION;

typedef struct _D3DKMT_QUERYSTATSTICS_REFERENCE_DMA_BUFFER
{
    ULONG NbCall;
    ULONG NbAllocationsReferenced;
    ULONG MaxNbAllocationsReferenced;
    ULONG NbNULLReference;
    ULONG NbWriteReference;
    ULONG NbRenamedAllocationsReferenced;
    ULONG NbIterationSearchingRenamedAllocation;
    ULONG NbLockedAllocationReferenced;
    ULONG NbAllocationWithValidPrepatchingInfoReferenced;
    ULONG NbAllocationWithInvalidPrepatchingInfoReferenced;
    ULONG NbDMABufferSuccessfullyPrePatched;
    ULONG NbPrimariesReferencesOverflow;
    ULONG NbAllocationWithNonPreferredResources;
    ULONG NbAllocationInsertedInMigrationTable;
} D3DKMT_QUERYSTATSTICS_REFERENCE_DMA_BUFFER;

typedef struct _D3DKMT_QUERYSTATSTICS_RENAMING
{
    ULONG NbAllocationsRenamed;
    ULONG NbAllocationsShrinked;
    ULONG NbRenamedBuffer;
    ULONG MaxRenamingListLength;
    ULONG NbFailuresDueToRenamingLimit;
    ULONG NbFailuresDueToCreateAllocation;
    ULONG NbFailuresDueToOpenAllocation;
    ULONG NbFailuresDueToLowResource;
    ULONG NbFailuresDueToNonRetiredLimit;
} D3DKMT_QUERYSTATSTICS_RENAMING;

typedef struct _D3DKMT_QUERYSTATSTICS_PREPRATION
{
    ULONG BroadcastStall;
    ULONG NbDMAPrepared;
    ULONG NbDMAPreparedLongPath;
    ULONG ImmediateHighestPreparationPass;
    D3DKMT_QUERYSTATISTICS_COUNTER AllocationsTrimmed;
} D3DKMT_QUERYSTATSTICS_PREPRATION;

typedef struct _D3DKMT_QUERYSTATSTICS_PAGING_FAULT
{
    D3DKMT_QUERYSTATISTICS_COUNTER Faults;
    D3DKMT_QUERYSTATISTICS_COUNTER FaultsFirstTimeAccess;
    D3DKMT_QUERYSTATISTICS_COUNTER FaultsReclaimed;
    D3DKMT_QUERYSTATISTICS_COUNTER FaultsMigration;
    D3DKMT_QUERYSTATISTICS_COUNTER FaultsIncorrectResource;
    D3DKMT_QUERYSTATISTICS_COUNTER FaultsLostContent;
    D3DKMT_QUERYSTATISTICS_COUNTER FaultsEvicted;
    D3DKMT_QUERYSTATISTICS_COUNTER AllocationsMEM_RESET;
    D3DKMT_QUERYSTATISTICS_COUNTER AllocationsUnresetSuccess;
    D3DKMT_QUERYSTATISTICS_COUNTER AllocationsUnresetFail;
    ULONG AllocationsUnresetSuccessRead;
    ULONG AllocationsUnresetFailRead;

    D3DKMT_QUERYSTATISTICS_COUNTER Evictions;
    D3DKMT_QUERYSTATISTICS_COUNTER EvictionsDueToPreparation;
    D3DKMT_QUERYSTATISTICS_COUNTER EvictionsDueToLock;
    D3DKMT_QUERYSTATISTICS_COUNTER EvictionsDueToClose;
    D3DKMT_QUERYSTATISTICS_COUNTER EvictionsDueToPurge;
    D3DKMT_QUERYSTATISTICS_COUNTER EvictionsDueToSuspendCPUAccess;
} D3DKMT_QUERYSTATSTICS_PAGING_FAULT;

typedef struct _D3DKMT_QUERYSTATSTICS_PAGING_TRANSFER
{
    D3DKMT_ALIGN64 ULONGLONG BytesFilled;
    D3DKMT_ALIGN64 ULONGLONG BytesDiscarded;
    D3DKMT_ALIGN64 ULONGLONG BytesMappedIntoAperture;
    D3DKMT_ALIGN64 ULONGLONG BytesUnmappedFromAperture;
    D3DKMT_ALIGN64 ULONGLONG BytesTransferredFromMdlToMemory;
    D3DKMT_ALIGN64 ULONGLONG BytesTransferredFromMemoryToMdl;
    D3DKMT_ALIGN64 ULONGLONG BytesTransferredFromApertureToMemory;
    D3DKMT_ALIGN64 ULONGLONG BytesTransferredFromMemoryToAperture;
} D3DKMT_QUERYSTATSTICS_PAGING_TRANSFER;

typedef struct _D3DKMT_QUERYSTATSTICS_SWIZZLING_RANGE
{
    ULONG NbRangesAcquired;
    ULONG NbRangesReleased;
} D3DKMT_QUERYSTATSTICS_SWIZZLING_RANGE;

typedef struct _D3DKMT_QUERYSTATSTICS_LOCKS
{
    ULONG NbLocks;
    ULONG NbLocksWaitFlag;
    ULONG NbLocksDiscardFlag;
    ULONG NbLocksNoOverwrite;
    ULONG NbLocksNoReadSync;
    ULONG NbLocksLinearization;
    ULONG NbComplexLocks;
} D3DKMT_QUERYSTATSTICS_LOCKS;

typedef struct _D3DKMT_QUERYSTATSTICS_ALLOCATIONS
{
    D3DKMT_QUERYSTATISTICS_COUNTER Created;
    D3DKMT_QUERYSTATISTICS_COUNTER Destroyed;
    D3DKMT_QUERYSTATISTICS_COUNTER Opened;
    D3DKMT_QUERYSTATISTICS_COUNTER Closed;
    D3DKMT_QUERYSTATISTICS_COUNTER MigratedSuccess;
    D3DKMT_QUERYSTATISTICS_COUNTER MigratedFail;
    D3DKMT_QUERYSTATISTICS_COUNTER MigratedAbandoned;
} D3DKMT_QUERYSTATSTICS_ALLOCATIONS;

typedef struct _D3DKMT_QUERYSTATSTICS_TERMINATIONS
{
    //
    // We separate shared / nonshared because for nonshared we know that every alloc
    // terminated will lead cause a global alloc destroyed, but not for nonshared.
    //
    D3DKMT_QUERYSTATISTICS_COUNTER TerminatedShared;
    D3DKMT_QUERYSTATISTICS_COUNTER TerminatedNonShared;
    D3DKMT_QUERYSTATISTICS_COUNTER DestroyedShared;
    D3DKMT_QUERYSTATISTICS_COUNTER DestroyedNonShared;
} D3DKMT_QUERYSTATSTICS_TERMINATIONS;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
typedef struct _D3DKMT_QUERYSTATISTICS_ADAPTER_INFORMATION_FLAGS
{
    union
    {
        struct
        {
            UINT64 NumberOfMemoryGroups : 2;
            UINT64 SupportsDemotion     : 1;
            UINT64 Reserved             :61;
        };
        D3DKMT_ALIGN64 UINT64 Value;
    };
} D3DKMT_QUERYSTATISTICS_ADAPTER_INFORMATION_FLAGS;
#endif

typedef struct _D3DKMT_QUERYSTATISTICS_ADAPTER_INFORMATION
{
    ULONG NbSegments;
    ULONG NodeCount;
    ULONG VidPnSourceCount;

    ULONG VSyncEnabled;
    ULONG TdrDetectedCount;

    D3DKMT_ALIGN64 LONGLONG ZeroLengthDmaBuffers;
    D3DKMT_ALIGN64 ULONGLONG RestartedPeriod;

    D3DKMT_QUERYSTATSTICS_REFERENCE_DMA_BUFFER ReferenceDmaBuffer;
    D3DKMT_QUERYSTATSTICS_RENAMING Renaming;
    D3DKMT_QUERYSTATSTICS_PREPRATION Preparation;
    D3DKMT_QUERYSTATSTICS_PAGING_FAULT PagingFault;
    D3DKMT_QUERYSTATSTICS_PAGING_TRANSFER PagingTransfer;
    D3DKMT_QUERYSTATSTICS_SWIZZLING_RANGE SwizzlingRange;
    D3DKMT_QUERYSTATSTICS_LOCKS Locks;
    D3DKMT_QUERYSTATSTICS_ALLOCATIONS Allocations;
    D3DKMT_QUERYSTATSTICS_TERMINATIONS Terminations;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)
    D3DKMT_QUERYSTATISTICS_ADAPTER_INFORMATION_FLAGS Flags;
    D3DKMT_ALIGN64 UINT64 Reserved[7];
#else
    D3DKMT_ALIGN64 UINT64 Reserved[8];
#endif
} D3DKMT_QUERYSTATISTICS_ADAPTER_INFORMATION;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_4)
typedef struct _D3DKMT_QUERYSTATISTICS_PHYSICAL_ADAPTER_INFORMATION
{
    D3DKMT_ADAPTER_PERFDATA      AdapterPerfData;
    D3DKMT_ADAPTER_PERFDATACAPS  AdapterPerfDataCaps;
    D3DKMT_GPUVERSION            GpuVersion;
} D3DKMT_QUERYSTATISTICS_PHYSICAL_ADAPTER_INFORMATION;
#endif

typedef struct _D3DKMT_QUERYSTATISTICS_SYSTEM_MEMORY
{
    D3DKMT_ALIGN64 ULONGLONG BytesAllocated;
    D3DKMT_ALIGN64 ULONGLONG BytesReserved;
    ULONG SmallAllocationBlocks;
    ULONG LargeAllocationBlocks;
    D3DKMT_ALIGN64 ULONGLONG WriteCombinedBytesAllocated;
    D3DKMT_ALIGN64 ULONGLONG WriteCombinedBytesReserved;
    D3DKMT_ALIGN64 ULONGLONG CachedBytesAllocated;
    D3DKMT_ALIGN64 ULONGLONG CachedBytesReserved;
    D3DKMT_ALIGN64 ULONGLONG SectionBytesAllocated;
    D3DKMT_ALIGN64 ULONGLONG SectionBytesReserved;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_4)
    D3DKMT_ALIGN64 ULONGLONG BytesZeroed;
#else
    D3DKMT_ALIGN64 ULONGLONG Reserved;
#endif
} D3DKMT_QUERYSTATISTICS_SYSTEM_MEMORY;

typedef struct _D3DKMT_QUERYSTATISTICS_PROCESS_INFORMATION
{
    ULONG NodeCount;
    ULONG VidPnSourceCount;

    D3DKMT_QUERYSTATISTICS_SYSTEM_MEMORY SystemMemory;

    D3DKMT_ALIGN64 UINT64 Reserved[7];
} D3DKMT_QUERYSTATISTICS_PROCESS_INFORMATION;

typedef struct _D3DKMT_QUERYSTATISTICS_DMA_BUFFER
{
    D3DKMT_QUERYSTATISTICS_COUNTER Size;
    ULONG AllocationListBytes;
    ULONG PatchLocationListBytes;
} D3DKMT_QUERYSTATISTICS_DMA_BUFFER;

typedef struct _D3DKMT_QUERYSTATISTICS_COMMITMENT_DATA
{
    D3DKMT_ALIGN64 UINT64          TotalBytesEvictedFromProcess;
    D3DKMT_ALIGN64 UINT64          BytesBySegmentPreference[D3DKMT_QUERYSTATISTICS_SEGMENT_PREFERENCE_MAX];
} D3DKMT_QUERYSTATISTICS_COMMITMENT_DATA;

typedef struct _D3DKMT_QUERYSTATISTICS_POLICY
{
    D3DKMT_ALIGN64 ULONGLONG PreferApertureForRead[D3DKMT_QUERYSTATISTICS_ALLOCATION_PRIORITY_CLASS_MAX];
    D3DKMT_ALIGN64 ULONGLONG PreferAperture[D3DKMT_QUERYSTATISTICS_ALLOCATION_PRIORITY_CLASS_MAX];
    D3DKMT_ALIGN64 ULONGLONG MemResetOnPaging;
    D3DKMT_ALIGN64 ULONGLONG RemovePagesFromWorkingSetOnPaging;
    D3DKMT_ALIGN64 ULONGLONG MigrationEnabled;
} D3DKMT_QUERYSTATISTICS_POLICY;

// Process interference counters indicate how much this process GPU workload interferes with packets
// attempting to preempt it. 9 buckets will be exposed based on how long preemption took:
// [0] 100 microseconds <= preemption time < 250 microseconds
// [1] 250 microseconds <= preemption time < 500 microseconds
// [2] 500 microseconds <= preemption time < 1 milliseconds
// [3] 1 milliseconds   <= preemption time < 2.5 milliseconds
// [4] 2.5 milliseconds <= preemption time < 5 milliseconds
// [5] 5 milliseconds   <= preemption time < 10 milliseconds
// [6] 10 milliseconds  <= preemption time < 25 milliseconds
// [7] 25 milliseconds  <= preemption time < 50 milliseconds
// [8] 50 milliseconds  <= preemption time
//
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
#define D3DKMT_QUERYSTATISTICS_PROCESS_INTERFERENCE_BUCKET_COUNT 9

typedef struct _D3DKMT_QUERYSTATISTICS_PROCESS_INTERFERENCE_COUNTERS
{
    D3DKMT_ALIGN64 UINT64 InterferenceCount[D3DKMT_QUERYSTATISTICS_PROCESS_INTERFERENCE_BUCKET_COUNT];
} D3DKMT_QUERYSTATISTICS_PROCESS_INTERFERENCE_COUNTERS;
#endif

typedef struct _D3DKMT_QUERYSTATISTICS_PROCESS_ADAPTER_INFORMATION
{
    ULONG NbSegments;
    ULONG NodeCount;
    ULONG VidPnSourceCount;

    //
    // Virtual address space used by vidmm for this process
    //
    ULONG VirtualMemoryUsage;

    D3DKMT_QUERYSTATISTICS_DMA_BUFFER DmaBuffer;
    D3DKMT_QUERYSTATISTICS_COMMITMENT_DATA CommitmentData;
    D3DKMT_QUERYSTATISTICS_POLICY _Policy;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
    D3DKMT_QUERYSTATISTICS_PROCESS_INTERFERENCE_COUNTERS ProcessInterferenceCounters;
#else
    D3DKMT_ALIGN64 UINT64 Reserved[9];
#endif

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_9)
    D3DKMT_CLIENTHINT       ClientHint;
#else
    UINT Reserve;
#endif
} D3DKMT_QUERYSTATISTICS_PROCESS_ADAPTER_INFORMATION;

typedef struct _D3DKMT_QUERYSTATISTICS_MEMORY
{
    D3DKMT_ALIGN64 ULONGLONG TotalBytesEvicted;
    ULONG AllocsCommitted;
    ULONG AllocsResident;
} D3DKMT_QUERYSTATISTICS_MEMORY;

typedef enum _D3DKMT_QUERYSTATISTICS_SEGMENT_TYPE
{
    D3DKMT_QUERYSTATISTICS_SEGMENT_TYPE_APERTURE = 0,
    D3DKMT_QUERYSTATISTICS_SEGMENT_TYPE_MEMORY   = 1,
    D3DKMT_QUERYSTATISTICS_SEGMENT_TYPE_SYSMEM   = 2
} D3DKMT_QUERYSTATISTICS_SEGMENT_TYPE;

typedef struct _D3DKMT_QUERYSTATISTICS_SEGMENT_INFORMATION
{
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
    D3DKMT_ALIGN64 ULONGLONG CommitLimit;
    D3DKMT_ALIGN64 ULONGLONG BytesCommitted;
    D3DKMT_ALIGN64 ULONGLONG BytesResident;
#else
    ULONG CommitLimit;
    ULONG BytesCommitted;
    ULONG BytesResident;
#endif

    D3DKMT_QUERYSTATISTICS_MEMORY Memory;

    //
    // Boolean, whether this is an aperture segment
    //
    ULONG Aperture;

    //
    // Breakdown of bytes evicted by priority class
    //
    D3DKMT_ALIGN64 ULONGLONG TotalBytesEvictedByPriority[D3DKMT_QUERYSTATISTICS_ALLOCATION_PRIORITY_CLASS_MAX];   //Size = D3DKMT_MaxAllocationPriorityClass

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
    D3DKMT_ALIGN64 UINT64 SystemMemoryEndAddress;
    struct D3DKMT_ALIGN64
    {
        UINT64 PreservedDuringStandby : 1;
        UINT64 PreservedDuringHibernate : 1;
        UINT64 PartiallyPreservedDuringHibernate : 1;
        UINT64 Reserved : 61;
    } PowerFlags;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_9)
    struct D3DKMT_ALIGN64
    {
        UINT64 SystemMemory : 1;
        UINT64 PopulatedByReservedDDRByFirmware : 1;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM3_1)
        UINT64 SegmentType : 4; // D3DKMT_QUERYSTATISTICS_SEGMENT_TYPE
        UINT64 Reserved : 58;
#else
        UINT64 Reserved : 62;
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM3_1)
    } SegmentProperties;
    D3DKMT_ALIGN64 UINT64 Reserved[5];
#else
    D3DKMT_ALIGN64 UINT64 Reserved[6];
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_9)
#else
    D3DKMT_ALIGN64 UINT64 Reserved[8];
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
} D3DKMT_QUERYSTATISTICS_SEGMENT_INFORMATION;

//
// Video memory statistics.
//
typedef struct _D3DKMT_QUERYSTATISTICS_VIDEO_MEMORY
{
    ULONG AllocsCommitted;
    D3DKMT_QUERYSTATISTICS_COUNTER AllocsResidentInP[D3DKMT_QUERYSTATISTICS_SEGMENT_PREFERENCE_MAX];
    D3DKMT_QUERYSTATISTICS_COUNTER AllocsResidentInNonPreferred;
    D3DKMT_ALIGN64 ULONGLONG TotalBytesEvictedDueToPreparation;
} D3DKMT_QUERYSTATISTICS_VIDEO_MEMORY;

//
// VidMM Policies
//
typedef struct _D3DKMT_QUERYSTATISTICS_PROCESS_SEGMENT_POLICY
{
    D3DKMT_ALIGN64 ULONGLONG UseMRU;
} D3DKMT_QUERYSTATISTICS_PROCESS_SEGMENT_POLICY;

typedef struct _D3DKMT_QUERYSTATISTICS_PROCESS_SEGMENT_INFORMATION
{
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
    D3DKMT_ALIGN64 ULONGLONG BytesCommitted;
    D3DKMT_ALIGN64 ULONGLONG MaximumWorkingSet;
    D3DKMT_ALIGN64 ULONGLONG MinimumWorkingSet;

    ULONG NbReferencedAllocationEvictedInPeriod;
    UINT Padding;
#else
    ULONG BytesCommitted;
    ULONG NbReferencedAllocationEvictedInPeriod;
    ULONG MaximumWorkingSet;
    ULONG MinimumWorkingSet;
#endif

    D3DKMT_QUERYSTATISTICS_VIDEO_MEMORY VideoMemory;
    D3DKMT_QUERYSTATISTICS_PROCESS_SEGMENT_POLICY _Policy;

    D3DKMT_ALIGN64 UINT64 Reserved[8];
} D3DKMT_QUERYSTATISTICS_PROCESS_SEGMENT_INFORMATION;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
typedef struct _D3DKMT_QUERYSTATISTICS_PROCESS_SEGMENT_GROUP_INFORMATION
{
    D3DKMT_ALIGN64 UINT64 Budget;
    D3DKMT_ALIGN64 UINT64 Requested;
    D3DKMT_ALIGN64 UINT64 Usage;
    D3DKMT_ALIGN64 UINT64 Demoted[D3DKMT_QUERYSTATISTICS_ALLOCATION_PRIORITY_CLASS_MAX];
} D3DKMT_QUERYSTATISTICS_PROCESS_SEGMENT_GROUP_INFORMATION;
#endif

typedef enum _D3DKMT_QUERYSTATISTICS_TYPE
{
    D3DKMT_QUERYSTATISTICS_ADAPTER                = 0,
    D3DKMT_QUERYSTATISTICS_PROCESS                = 1,
    D3DKMT_QUERYSTATISTICS_PROCESS_ADAPTER        = 2,
    D3DKMT_QUERYSTATISTICS_SEGMENT                = 3,
    D3DKMT_QUERYSTATISTICS_PROCESS_SEGMENT        = 4,
    D3DKMT_QUERYSTATISTICS_NODE                   = 5,
    D3DKMT_QUERYSTATISTICS_PROCESS_NODE           = 6,
    D3DKMT_QUERYSTATISTICS_VIDPNSOURCE            = 7,
    D3DKMT_QUERYSTATISTICS_PROCESS_VIDPNSOURCE    = 8,
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
    D3DKMT_QUERYSTATISTICS_PROCESS_SEGMENT_GROUP  = 9,
#endif
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_4)
    D3DKMT_QUERYSTATISTICS_PHYSICAL_ADAPTER       = 10,
#endif
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM3_1)
    D3DKMT_QUERYSTATISTICS_ADAPTER2               = 11,
    D3DKMT_QUERYSTATISTICS_SEGMENT2               = 12,
    D3DKMT_QUERYSTATISTICS_PROCESS_ADAPTER2       = 13,
    D3DKMT_QUERYSTATISTICS_PROCESS_SEGMENT2       = 14,
    D3DKMT_QUERYSTATISTICS_PROCESS_SEGMENT_GROUP2 = 15,
    D3DKMT_QUERYSTATISTICS_SEGMENT_USAGE          = 16,
    D3DKMT_QUERYSTATISTICS_SEGMENT_GROUP_USAGE    = 17,
    D3DKMT_QUERYSTATISTICS_NODE2                  = 18,
    D3DKMT_QUERYSTATISTICS_PROCESS_NODE2          = 19
#endif
} D3DKMT_QUERYSTATISTICS_TYPE;

typedef struct _D3DKMT_QUERYSTATISTICS_QUERY_SEGMENT
{
    ULONG SegmentId; // in: id of node to get statistics for
} D3DKMT_QUERYSTATISTICS_QUERY_SEGMENT;

typedef struct _D3DKMT_QUERYSTATISTICS_QUERY_NODE
{
    ULONG NodeId;
} D3DKMT_QUERYSTATISTICS_QUERY_NODE;

typedef struct _D3DKMT_QUERYSTATISTICS_QUERY_VIDPNSOURCE
{
    ULONG VidPnSourceId; // in: id of segment to get statistics for
} D3DKMT_QUERYSTATISTICS_QUERY_VIDPNSOURCE;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_4)
typedef struct _D3DKMT_QUERYSTATISTICS_QUERY_PHYSICAL_ADAPTER
{
    ULONG PhysicalAdapterIndex;
} D3DKMT_QUERYSTATISTICS_QUERY_PHYSICAL_ADAPTER;
#endif

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM3_1)

typedef struct _D3DKMT_QUERYSTATISTICS_MEMORY_USAGE
{
    D3DKMT_ALIGN64 UINT64 AllocatedBytes;
    D3DKMT_ALIGN64 UINT64 FreeBytes;
    D3DKMT_ALIGN64 UINT64 ZeroBytes;
    D3DKMT_ALIGN64 UINT64 ModifiedBytes;
    D3DKMT_ALIGN64 UINT64 StandbyBytes;
} D3DKMT_QUERYSTATISTICS_MEMORY_USAGE;

typedef struct _D3DKMT_QUERYSTATISTICS_QUERY_SEGMENT2
{
    UINT16 PhysicalAdapterIndex;
    UINT16 SegmentId;
} D3DKMT_QUERYSTATISTICS_QUERY_SEGMENT2;

typedef struct _D3DKMT_QUERYSTATISTICS_QUERY_SEGMENT_USAGE
{
    UINT16 PhysicalAdapterIndex;
    UINT16 SegmentId;
} D3DKMT_QUERYSTATISTICS_QUERY_SEGMENT_USAGE;

typedef struct _D3DKMT_QUERYSTATISTICS_QUERY_SEGMENT_GROUP_USAGE
{
    UINT16 PhysicalAdapterIndex;
    UINT16 SegmentGroup; // D3DKMT_MEMORY_SEGMENT_GROUP
} D3DKMT_QUERYSTATISTICS_QUERY_SEGMENT_GROUP_USAGE;

typedef struct _D3DKMT_QUERYSTATISTICS_QUERY_ADAPTER2
{
    UINT16 PhysicalAdapterIndex;
} D3DKMT_QUERYSTATISTICS_QUERY_ADAPTER2;

typedef struct _D3DKMT_QUERYSTATISTICS_QUERY_ADAPTER_INFORMATION2
{
    UINT16 PhysicalAdapterIndex;
} D3DKMT_QUERYSTATISTICS_QUERY_ADAPTER_INFORMATION2;

typedef struct _D3DKMT_QUERYSTATISTICS_QUERY_PROCESS_SEGMENT_GROUP2
{
    UINT16 PhysicalAdapterIndex;
    UINT16 SegmentGroup; // D3DKMT_MEMORY_SEGMENT_GROUP
} D3DKMT_QUERYSTATISTICS_QUERY_PROCESS_SEGMENT_GROUP2;

typedef struct _D3DKMT_QUERYSTATISTICS_QUERY_NODE2
{
    UINT16 PhysicalAdapterIndex;
    UINT16 NodeOrdinal;
} D3DKMT_QUERYSTATISTICS_QUERY_NODE2;

#endif

typedef union _D3DKMT_QUERYSTATISTICS_RESULT
{
    D3DKMT_QUERYSTATISTICS_ADAPTER_INFORMATION AdapterInformation;                          // out: result of D3DKMT_QUERYSTATISTICS_ADAPTER(2) query
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_4)
    D3DKMT_QUERYSTATISTICS_PHYSICAL_ADAPTER_INFORMATION PhysAdapterInformation;             // out: result of D3DKMT_QUERYSTATISTICS_PHYSICAL_ADAPTER query
#endif
    D3DKMT_QUERYSTATISTICS_SEGMENT_INFORMATION SegmentInformation;                          // out: result of D3DKMT_QUERYSTATISTICS_SEGMENT(2) query
    D3DKMT_QUERYSTATISTICS_NODE_INFORMATION NodeInformation;                                // out: result of D3DKMT_QUERYSTATISTICS_NODE query
    D3DKMT_QUERYSTATISTICS_VIDPNSOURCE_INFORMATION VidPnSourceInformation;                  // out: result of D3DKMT_QUERYSTATISTICS_VIDPNSOURCE query
    D3DKMT_QUERYSTATISTICS_PROCESS_INFORMATION ProcessInformation;                          // out: result of D3DKMT_QUERYSTATISTICS_PROCESS query
    D3DKMT_QUERYSTATISTICS_PROCESS_ADAPTER_INFORMATION ProcessAdapterInformation;           // out: result of D3DKMT_QUERYSTATISTICS_PROCESS_ADAPTER(2) query
    D3DKMT_QUERYSTATISTICS_PROCESS_SEGMENT_INFORMATION ProcessSegmentInformation;           // out: result of D3DKMT_QUERYSTATISTICS_PROCESS_SEGMENT(2) query
    D3DKMT_QUERYSTATISTICS_PROCESS_NODE_INFORMATION ProcessNodeInformation;                 // out: result of D3DKMT_QUERYSTATISTICS_PROCESS_NODE query
    D3DKMT_QUERYSTATISTICS_PROCESS_VIDPNSOURCE_INFORMATION ProcessVidPnSourceInformation;   // out: result of D3DKMT_QUERYSTATISTICS_PROCESS_VIDPNSOURCE query
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
    D3DKMT_QUERYSTATISTICS_PROCESS_SEGMENT_GROUP_INFORMATION ProcessSegmentGroupInformation;// out: result of D3DKMT_QUERYSTATISTICS_PROCESS_SEGMENT_GROUP(2) query
#endif
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM3_1)
    D3DKMT_QUERYSTATISTICS_MEMORY_USAGE SegmentUsageInformation;                            // out: result of D3DKMT_QUERYSTATISTICS_SEGMENT_USAGE query
    D3DKMT_QUERYSTATISTICS_MEMORY_USAGE SegmentGroupUsageInformation;                       // out: result of D3DKMT_QUERYSTATISTICS_SEGMENT_GROUP_USAGE query
#endif
} D3DKMT_QUERYSTATISTICS_RESULT;

typedef struct _D3DKMT_QUERYSTATISTICS
{
    D3DKMT_QUERYSTATISTICS_TYPE   Type;        // in: type of data requested
    LUID                          AdapterLuid; // in: adapter to get export / statistics from
    D3DKMT_PTR(HANDLE,            hProcess);   // in: process to get statistics for, if required for this query type
    D3DKMT_QUERYSTATISTICS_RESULT QueryResult; // out: requested data

    union
    {
        D3DKMT_QUERYSTATISTICS_QUERY_SEGMENT QuerySegment;                // in: id of segment to get statistics for
        D3DKMT_QUERYSTATISTICS_QUERY_SEGMENT QueryProcessSegment;         // in: id of segment to get statistics for
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
        D3DKMT_MEMORY_SEGMENT_GROUP QueryProcessSegmentGroup;             // in: id of segment group to get statistics for
#endif
        D3DKMT_QUERYSTATISTICS_QUERY_NODE QueryNode;                      // in: id of node to get statistics for
        D3DKMT_QUERYSTATISTICS_QUERY_NODE QueryProcessNode;               // in: id of node to get statistics for
        D3DKMT_QUERYSTATISTICS_QUERY_VIDPNSOURCE QueryVidPnSource;        // in: id of vidpnsource to get statistics for
        D3DKMT_QUERYSTATISTICS_QUERY_VIDPNSOURCE QueryProcessVidPnSource; // in: id of vidpnsource to get statistics for
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_4)
        D3DKMT_QUERYSTATISTICS_QUERY_PHYSICAL_ADAPTER QueryPhysAdapter;   // in: id of physical adapter to get statistics for
#endif
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM3_1)
    D3DKMT_QUERYSTATISTICS_QUERY_ADAPTER2 QueryAdapter2;
    D3DKMT_QUERYSTATISTICS_QUERY_SEGMENT2 QuerySegment2;
    D3DKMT_QUERYSTATISTICS_QUERY_ADAPTER2 QueryProcessAdapter2;
    D3DKMT_QUERYSTATISTICS_QUERY_SEGMENT2 QueryProcessSegment2;
    D3DKMT_QUERYSTATISTICS_QUERY_PROCESS_SEGMENT_GROUP2 QueryProcessSegmentGroup2;
    D3DKMT_QUERYSTATISTICS_QUERY_SEGMENT_USAGE QuerySegmentUsage;
    D3DKMT_QUERYSTATISTICS_QUERY_SEGMENT_GROUP_USAGE QuerySegmentGroupUsage;
    D3DKMT_QUERYSTATISTICS_QUERY_NODE2 QueryNode2;                      // in: id of node to get statistics for
    D3DKMT_QUERYSTATISTICS_QUERY_NODE2 QueryProcessNode2;               // in: id of node to get statistics for
#endif
    };
} D3DKMT_QUERYSTATISTICS;


//
// end D3DKMT_QUERYSTATISTICS
//


typedef struct _D3DKMT_PRESENT_STATS_DWM2
{
    ULONG                        cbSize; // in: size of struct for versioning
    UINT                         PresentCount;
    UINT                         PresentRefreshCount;
    D3DKMT_ALIGN64 LARGE_INTEGER PresentQPCTime;
    UINT                         SyncRefreshCount;
    D3DKMT_ALIGN64 LARGE_INTEGER SyncQPCTime;
    UINT                         CustomPresentDuration;
    UINT                         VirtualSyncRefreshCount;
    D3DKMT_ALIGN64 LARGE_INTEGER VirtualSyncQPCTime;
} D3DKMT_PRESENT_STATS_DWM2;


typedef enum _D3DKMT_VIDPNSOURCEOWNER_TYPE
{
     D3DKMT_VIDPNSOURCEOWNER_UNOWNED        = 0,    //Has no owner or GDI is the owner
     D3DKMT_VIDPNSOURCEOWNER_SHARED         = 1,    //Has shared owner, that is owner can yield to any exclusive owner, not available to legacy devices
     D3DKMT_VIDPNSOURCEOWNER_EXCLUSIVE      = 2,    //Has exclusive owner without shared gdi primary,
     D3DKMT_VIDPNSOURCEOWNER_EXCLUSIVEGDI   = 3,    //Has exclusive owner with shared gdi primary and must be exclusive owner of all VidPn sources, only available to legacy devices
     D3DKMT_VIDPNSOURCEOWNER_EMULATED       = 4,    //Does not have real primary ownership, but allows the device to set gamma on its owned sources
} D3DKMT_VIDPNSOURCEOWNER_TYPE;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
typedef struct _D3DKMT_VIDPNSOURCEOWNER_FLAGS
{
    union
    {
        struct
        {
            UINT AllowOutputDuplication : 1;
            UINT DisableDWMVirtualMode  : 1;
            UINT UseNtHandles           : 1;
            UINT Reserved               : 29;
        };
        UINT Value;
    };
} D3DKMT_VIDPNSOURCEOWNER_FLAGS;
#endif

typedef struct _D3DKMT_SETVIDPNSOURCEOWNER
{
    D3DKMT_HANDLE                           hDevice;            // in: Device handle
    D3DKMT_PTR(CONST D3DKMT_VIDPNSOURCEOWNER_TYPE*, pType);     // in: OwnerType array
    D3DKMT_PTR(CONST D3DDDI_VIDEO_PRESENT_SOURCE_ID*, pVidPnSourceId); // in: VidPn source ID array
    UINT                                    VidPnSourceCount;   // in: Number of valid entries in above array
} D3DKMT_SETVIDPNSOURCEOWNER;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
typedef struct _D3DKMT_SETVIDPNSOURCEOWNER1
{
    D3DKMT_SETVIDPNSOURCEOWNER              Version0;
    D3DKMT_VIDPNSOURCEOWNER_FLAGS           Flags;
} D3DKMT_SETVIDPNSOURCEOWNER1;
#endif

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_3)
typedef struct _D3DKMT_SETVIDPNSOURCEOWNER2
{
    D3DKMT_SETVIDPNSOURCEOWNER1             Version1;
    D3DKMT_PTR(CONST D3DKMT_PTR_TYPE*,      pVidPnSourceNtHandles); // in: VidPn source owner DispMgr NT handles
} D3DKMT_SETVIDPNSOURCEOWNER2;
#endif

typedef struct _D3DKMT_CHECKVIDPNEXCLUSIVEOWNERSHIP
{
    D3DKMT_HANDLE                           hAdapter;           // in: Adapter handle
    D3DDDI_VIDEO_PRESENT_SOURCE_ID          VidPnSourceId;      // in: VidPn source ID array
} D3DKMT_CHECKVIDPNEXCLUSIVEOWNERSHIP;

#define D3DKMT_GETPRESENTHISTORY_MAXTOKENS  2048

typedef struct _D3DKMT_GETPRESENTHISTORY
{
    D3DKMT_HANDLE                                             hAdapter;     // in: Handle to adapter
    UINT                                                      ProvidedSize; // in: Size of provided buffer
    UINT                                                      WrittenSize;  // out: Copied token size or required size for first token
    D3DKMT_PTR(_Field_size_bytes_(ProvidedSize) D3DKMT_PRESENTHISTORYTOKEN*, pTokens); // in: Pointer to buffer.
    UINT                                                      NumTokens;    // out: Number of copied token
} D3DKMT_GETPRESENTHISTORY;

typedef struct _D3DKMT_CREATEOVERLAY
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;      // in
    D3DKMT_HANDLE                   hDevice;            // in: Indentifies the device
    D3DDDI_KERNELOVERLAYINFO        OverlayInfo;        // in
    D3DKMT_HANDLE                   hOverlay;           // out: Kernel overlay handle
} D3DKMT_CREATEOVERLAY;

typedef struct _D3DKMT_UPDATEOVERLAY
{
    D3DKMT_HANDLE            hDevice;           // in: Indentifies the device
    D3DKMT_HANDLE            hOverlay;          // in: Kernel overlay handle
    D3DDDI_KERNELOVERLAYINFO OverlayInfo;       // in
} D3DKMT_UPDATEOVERLAY;

typedef struct _D3DKMT_FLIPOVERLAY
{
    D3DKMT_HANDLE        hDevice;               // in: Indentifies the device
    D3DKMT_HANDLE        hOverlay;              // in: Kernel overlay handle
    D3DKMT_HANDLE        hSource;               // in: Allocation currently displayed
    D3DKMT_PTR(VOID*,    pPrivateDriverData);   // in: Private driver data
    UINT                 PrivateDriverDataSize; // in: Size of private driver data
} D3DKMT_FLIPOVERLAY;

typedef struct _D3DKMT_GETOVERLAYSTATE
{
    D3DKMT_HANDLE        hDevice;               // in: Indentifies the device
    D3DKMT_HANDLE        hOverlay;              // in: Kernel overlay handle
    BOOLEAN              OverlayEnabled;
} D3DKMT_GETOVERLAYSTATE;

typedef struct _D3DKMT_DESTROYOVERLAY
{
    D3DKMT_HANDLE        hDevice;               // in: Indentifies the device
    D3DKMT_HANDLE        hOverlay;              // in: Kernel overlay handle
} D3DKMT_DESTROYOVERLAY;

typedef struct _D3DKMT_WAITFORVERTICALBLANKEVENT
{
    D3DKMT_HANDLE                   hAdapter;      // in: adapter handle
    D3DKMT_HANDLE                   hDevice;       // in: device handle [Optional]
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId; // in: adapter's VidPN Source ID
} D3DKMT_WAITFORVERTICALBLANKEVENT;

#define D3DKMT_MAX_WAITFORVERTICALBLANK_OBJECTS 8

typedef struct _D3DKMT_WAITFORVERTICALBLANKEVENT2
{
    D3DKMT_HANDLE                   hAdapter;      // in: adapter handle
    D3DKMT_HANDLE                   hDevice;       // in: device handle [Optional]
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId; // in: adapter's VidPN Source ID
    UINT                            NumObjects;
    D3DKMT_PTR_TYPE                 ObjectHandleArray[D3DKMT_MAX_WAITFORVERTICALBLANK_OBJECTS]; // in: Specifies the objects to wait on.
} D3DKMT_WAITFORVERTICALBLANKEVENT2;

typedef struct _D3DKMT_GETVERTICALBLANKEVENT
{
    D3DKMT_HANDLE                   hAdapter;      // in: adapter handle
    D3DKMT_HANDLE                   hDevice;       // in: device handle [Optional]
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId; // in: adapter's VidPN Source ID
    D3DKMT_PTR(D3DKMT_PTR_TYPE*,    phEvent);
} D3DKMT_GETVERTICALBLANKEVENT;

typedef struct _D3DKMT_SETSYNCREFRESHCOUNTWAITTARGET
{
    D3DKMT_HANDLE                   hAdapter;      // in: adapter handle
    D3DKMT_HANDLE                   hDevice;       // in: device handle [Optional]
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId; // in: adapter's VidPN Source ID
    UINT                            TargetSyncRefreshCount;
} D3DKMT_SETSYNCREFRESHCOUNTWAITTARGET;

typedef struct _D3DKMT_SETGAMMARAMP
{
    D3DKMT_HANDLE                   hDevice;       // in: device handle
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId; // in: adapter's VidPN Source ID
    D3DDDI_GAMMARAMP_TYPE           Type;          // in: Gamma ramp type

    union
    {
        D3DDDI_GAMMA_RAMP_RGB256x3x16* pGammaRampRgb256x3x16;
        D3DDDI_GAMMA_RAMP_DXGI_1*      pGammaRampDXGI1;
        D3DKMT_PTR_HELPER(             AlignUnionTo64)
    };
    UINT                            Size;
} D3DKMT_SETGAMMARAMP;

typedef struct _D3DKMT_ADJUSTFULLSCREENGAMMA
{
    D3DKMT_HANDLE                   hAdapter;      // in: adapter handle
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId; // in: adapter's VidPN Source ID
    D3DDDI_DXGI_RGB                 Scale;
    D3DDDI_DXGI_RGB                 Offset;
} D3DKMT_ADJUSTFULLSCREENGAMMA;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_3)

typedef struct _D3DKMT_SET_COLORSPACE_TRANSFORM
{
    _In_ LUID  AdapterLuid;
    _In_ D3DDDI_VIDEO_PRESENT_TARGET_ID  VidPnTargetId;
    _In_ D3DDDI_GAMMARAMP_TYPE  Type;
    _In_ UINT  Size;
    union
    {
        _In_reads_bytes_opt_(Size) D3DKMDT_3x4_COLORSPACE_TRANSFORM*  pColorSpaceTransform;
        D3DKMT_PTR_HELPER(                                            AlignUnionTo64)
    };
} D3DKMT_SET_COLORSPACE_TRANSFORM;

#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_3

typedef struct _D3DKMT_SETVIDPNSOURCEHWPROTECTION
{
    D3DKMT_HANDLE                   hAdapter;      // in: adapter handle
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId; // in: adapter's VidPN Source ID
    BOOL                            HwProtected;   // in: HW protection status
} D3DKMT_SETVIDPNSOURCEHWPROTECTION;

typedef struct _D3DKMT_SETHWPROTECTIONTEARDOWNRECOVERY
{
    D3DKMT_HANDLE                   hAdapter;      // in: adapter handle
    BOOL                            Recovered;     // in: HW protection teardown recovery
} D3DKMT_SETHWPROTECTIONTEARDOWNRECOVERY;

typedef enum _D3DKMT_DEVICEEXECUTION_STATE
{
    D3DKMT_DEVICEEXECUTION_ACTIVE               = 1,
    D3DKMT_DEVICEEXECUTION_RESET                = 2,
    D3DKMT_DEVICEEXECUTION_HUNG                 = 3,
    D3DKMT_DEVICEEXECUTION_STOPPED              = 4,
    D3DKMT_DEVICEEXECUTION_ERROR_OUTOFMEMORY    = 5,
    D3DKMT_DEVICEEXECUTION_ERROR_DMAFAULT       = 6,
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
    D3DKMT_DEVICEEXECUTION_ERROR_DMAPAGEFAULT   = 7,
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
} D3DKMT_DEVICEEXECUTION_STATE;

typedef struct _D3DKMT_DEVICERESET_STATE
{
    union
    {
        struct
        {
            UINT    DesktopSwitched : 1;        // 0x00000001
            UINT    Reserved        :31;        // 0xFFFFFFFE
        };
        UINT    Value;
    };
} D3DKMT_DEVICERESET_STATE;

typedef struct _D3DKMT_PRESENT_STATS
{
    UINT PresentCount;
    UINT PresentRefreshCount;
    UINT SyncRefreshCount;
    D3DKMT_ALIGN64 LARGE_INTEGER SyncQPCTime;
    D3DKMT_ALIGN64 LARGE_INTEGER SyncGPUTime;
} D3DKMT_PRESENT_STATS;

typedef struct _D3DKMT_DEVICEPRESENT_STATE
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID VidPnSourceId; // in: present source id
    D3DKMT_PRESENT_STATS           PresentStats;  // out: present stats
} D3DKMT_DEVICEPRESENT_STATE;

typedef struct _D3DKMT_PRESENT_STATS_DWM
{
    UINT PresentCount;
    UINT PresentRefreshCount;
    D3DKMT_ALIGN64 LARGE_INTEGER PresentQPCTime;
    UINT SyncRefreshCount;
    D3DKMT_ALIGN64 LARGE_INTEGER SyncQPCTime;
    UINT CustomPresentDuration;
} D3DKMT_PRESENT_STATS_DWM;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)

typedef struct _D3DKMT_DEVICEPAGEFAULT_STATE
{
    D3DKMT_ALIGN64 UINT64       FaultedPrimitiveAPISequenceNumber; // when per draw fence write is enabled, identifies the draw that caused the page fault, or DXGK_PRIMITIVE_API_SEQUENCE_NUMBER_UNKNOWN if such information is not available.
    DXGK_RENDER_PIPELINE_STAGE  FaultedPipelineStage;   // render pipeline stage during which the fault was generated, or DXGK_RENDER_PIPELINE_STAGE_UNKNOWN if such information is not available.
    UINT                        FaultedBindTableEntry;  // a bind table index of a resource being accessed at the time of the fault, or DXGK_BIND_TABLE_ENTRY_UNKNOWN if such information is not available.
    DXGK_PAGE_FAULT_FLAGS       PageFaultFlags;         // flags specifying the nature of the fault
    DXGK_FAULT_ERROR_CODE       FaultErrorCode;         // Structure that contains error code describing the fault.
    D3DKMT_ALIGN64 D3DGPU_VIRTUAL_ADDRESS FaultedVirtualAddress;  // virtual address of faulting resource, or D3DGPU_NULL if such information is not available.
} D3DKMT_DEVICEPAGEFAULT_STATE;

#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)

typedef struct _D3DKMT_DEVICEPRESENT_STATE_DWM
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID VidPnSourceId; // in: present source id
    D3DKMT_PRESENT_STATS_DWM       PresentStatsDWM; // out: present stats rev 2
} D3DKMT_DEVICEPRESENT_STATE_DWM;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)

typedef struct _D3DKMT_DEVICEPRESENT_QUEUE_STATE
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID VidPnSourceId; // in: present source id
    BOOLEAN bQueuedPresentLimitReached;           // out: whether the queued present limit has been reached
} D3DKMT_DEVICEPRESENT_QUEUE_STATE;

#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)

typedef enum _D3DKMT_DEVICESTATE_TYPE
{
    D3DKMT_DEVICESTATE_EXECUTION = 1,
    D3DKMT_DEVICESTATE_PRESENT   = 2,
    D3DKMT_DEVICESTATE_RESET     = 3,
    D3DKMT_DEVICESTATE_PRESENT_DWM = 4,

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)

    D3DKMT_DEVICESTATE_PAGE_FAULT = 5,

#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)

    D3DKMT_DEVICESTATE_PRESENT_QUEUE = 6,

#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_1
} D3DKMT_DEVICESTATE_TYPE;

typedef struct _D3DKMT_GETDEVICESTATE
{
    D3DKMT_HANDLE                   hDevice;       // in: device handle
    D3DKMT_DEVICESTATE_TYPE         StateType;     // in: device state type
    union
    {
        D3DKMT_DEVICEEXECUTION_STATE ExecutionState; // out: device state
        D3DKMT_DEVICEPRESENT_STATE   PresentState;   // in/out: present state
        D3DKMT_DEVICERESET_STATE     ResetState;     // out: reset state
        D3DKMT_DEVICEPRESENT_STATE_DWM  PresentStateDWM;  // in/out: present state

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)

        D3DKMT_DEVICEPAGEFAULT_STATE PageFaultState; // out: page fault state

#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)

        D3DKMT_DEVICEPRESENT_QUEUE_STATE PresentQueueState; // in/out: present queue state

#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_1
    };
} D3DKMT_GETDEVICESTATE;


// ADDD MORE HEADERS HERE FROM HERE VVVVVVV
//typedef struct _D3DKMT_CREATEDCFROMMEMORY

#endif // (NTDDI_VERSION >= NTDDI_LONGHORN) || defined(D3DKMDT_SPECIAL_MULTIPLATFORM_TOOL)

