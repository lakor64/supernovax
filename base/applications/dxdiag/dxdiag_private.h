 /*
  * PROJECT:     SupernovaX Diagnostic Tool
  * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
  * PURPOSE:     Private definitions for the Diagnostic Tool
  * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
  *              Copyright 2011 Andrew Nguyen
  */
#include <windef.h>
#include <winuser.h>

/* Resource definitions. */
//#define MAX_STRING_LEN          1024

//#define STRING_DXDIAG_TOOL      101
//#define STRING_USAGE            102
//
//#define XML_FIELDS_SYSTEMINFO 25

/* Information collection definitions. 
   Refenrece: DxDiag_SystemInfo
*/
typedef struct _DXDIAG_SYSTEM_INFO
{
    WCHAR *szTimeEnglish;
    WCHAR *szTimeLocalized;
    WCHAR *szMachineNameEnglish;
    WCHAR *szMachineNameLocalized;
    WCHAR *szOSExLongEnglish;
    WCHAR *szOSExLocalized;
    WCHAR *szLanguagesEnglish;
    WCHAR *szLanguagesLocalized;
    WCHAR *szSystemManufacturerEnglish;
    WCHAR *szSystemModelEnglish;
    WCHAR *szBIOSEnglish;
    WCHAR *szProcessorEnglish;
    WCHAR *szPhysicalMemoryEnglish;
    WCHAR *szPageFileEnglish;
    WCHAR *szPageFileLocalized;
    WCHAR *szWindowsDir;
    WCHAR *szDirectXVersionLongEnglish;
    WCHAR *szSetupParamEnglish;
    WCHAR *szDxDiagVersion;
    LPWSTR szPhysicalMemoryEnglishOS;
    LPWSTR szSystemDPI;
    LPWSTR szDWMScalingDPI;
    LPWSTR szDxDbVersion;
    LPWSTR szUserDPI;
    LPWSTR szMiracastAvailable;
    LPWSTR szMSHybrid;
    LPWSTR szFirmwareType;
    ULONG nDPlayDebugLevel;
    ULONG nDDrawDebugLevel;
    ULONG nDIDebugLevel;
    ULONG nDMusicDebugLevel;
    ULONG nDShowDebugLevel;
    ULONG nDSoundDebugLevel;
    BOOL bIsDSoundDebugRuntime;
    BOOL bIsDPlayDebugRuntime;
    BOOL bIsDDrawDebugRuntime;
    BOOL bIsDMusicDebugRuntime;
    BOOL win64;
} DXDIAG_SYSTEM_INFO, *PDXDIAG_SYSTEM_INFO;

/*
* Information of the current DXVA caps of a monitor
*/
typedef struct _DXDIAG_DISPLAY_DXVA_INFO
{
    LPWSTR szGuid;
    LPWSTR szCaps;
    LPWSTR szD3DInputFormat;
    LPWSTR szD3DOutputFormat;
    ULONG dwNumPreviousOutputFrames;
    ULONG dwNumForwardRefSamples;
    ULONG dwNumBackwardRefSamples;
} DXDIAG_DISPLAY_DXVA_INFO, *PDXDIAG_DISPLAY_DXVA_INFO;

/* Information on current screens
* Reference: DxDiag_DisplayDevices
*/
typedef struct _DXDIAG_DISPLAY_DEVICE_INFO
{
    LPWSTR szDescription;
    LPWSTR szManufacturer;
    LPWSTR szChipType;
    LPWSTR szDACType;
    LPWSTR szKeyDeviceID;
    LPWSTR szNotesEnglish;
    LPWSTR szDisplayModeEnglish;
    LPWSTR szDisplayModeLocalized;
    LPWSTR szDriverModelEnglish;
    LPWSTR szVdd;
    LPWSTR szMiniVddDateEnglish;
    LPWSTR szDriverLanguageEnglish;
    LPWSTR szDisplayMemoryEnglish;
    LPWSTR szDisplayMemoryLocalized;
    LPWSTR szAGPStatusEnglish;
    LPWSTR szD3DStatusEnglish;
    LPWSTR szDXVAHDEnglish;
    LPWSTR szDriverDateEnglish;
    LPWSTR szMiniVdd;
    LPWSTR szVendorId;
    LPWSTR szDeviceId;
    LPWSTR szSubSysId;
    LPWSTR szRevisionId;
    LPWSTR szDriverNodeStrongName;
    LPWSTR szRankOfInstalledDriver;
    LPWSTR szDeviceIdentifier;
    LPWSTR szMonitorName;
    LPWSTR szMonitorMaxRes;
    LPWSTR szDriverName;
    LPWSTR szDriverVersion;
    LPWSTR szDriverAssemblyVersion;
    LPWSTR szDXVAModes;
    LPWSTR szGuid;
    LPWSTR szOverlayEnglish;
    LPWSTR szDriverSignDate;
    LPWSTR szDDIVersionEnglish;
    LPWSTR szDDStatusEnglish;
    LPWSTR szTestResultDDEnglish;
    LPWSTR szTestResultD3D7English;
    LPWSTR szTestResultD3D8English;
    LPWSTR szTestResultD3D9English;
    LPWSTR szDXVA2Modes;
    LPWSTR szGraphicsPreemptionGranularity;
    LPWSTR szComputePreemptionGranularity;
    LPWSTR szMiracast;
    LPWSTR szHybridGraphicsGPUType;
    LPWSTR szPowerManagementPStates;
    LPWSTR szMPOMaxPlanes;
    LPWSTR szMPOCaps;
    LPWSTR szMPOStretch;
    LPWSTR szMPOHints;
    LPWSTR szMPOFormats;
    LPWSTR szPanelFitterCaps;
    LPWSTR szPanelFitterStretch;
    LPWSTR szHardwareSchedulingAttributes;
    LPWSTR szDisplayableSupport;
    LPWSTR szDriverCatalogAttributes;
    LPWSTR szBlockList;
    LPWSTR szVirtualGPUSupport;
    LPWSTR szDeviceProblemCode;
    LPWSTR szDriverProblemCode;
    LPWSTR szDeviceStatus;
    LPWSTR szHDRSupportEnglish;
    LPWSTR szTopology;
    LPWSTR szColorSpace;
    LPWSTR szColorPrimaries;
    LPWSTR szLuminance;
    LPWSTR szPixelFormat;
    LPWSTR szWmiUserFriendlyName;
    LPWSTR szWmiPerferredMonitorSourceMode;
    LPWSTR szWmiManufacturerName;
    LPWSTR szWmiProductCodeID;
    LPWSTR szWmiVideoOutputTechnology;
    LPWSTR szFeatureLevelEnglish;
    ULONG lMiniVddSize;
    ULONG lDriverSize;
    ULONG dwDedicatedVideoMemory;
    ULONG dwSharedVideoMemory;
    DWORD dwDXVALength;
    BOOL bDriverDebug;
    BOOL bDriverBeta;
    BOOL bDetachable;
    BOOL bEotf2048Supported;
    BOOL bBT2020YCC;
    BOOL bBT2020RGB;
    BOOL bAdvancedColorEnabled;
    BOOL bAdvancedColorSupported;
    BOOL bCheckedMonitorCapabilities;
    BOOL bPostDevice;
    PDXDIAG_DISPLAY_DXVA_INFO aDXVAInfo;
} DXDIAG_DISPLAY_DEVICE_INFO, * PDXDIAG_DISPLAY_DEVICE_INFO;

/* Information on output sound devices
* Reference: DxDiag_SoundDevices
*/
typedef struct _DXDIAG_SOUND_DEVICE_INFO
{
    LPWSTR szDescription;
    LPWSTR szRegKey;
    LPWSTR szManufacturerID;
    LPWSTR szProductID;
    LPWSTR szDriverName;
    LPWSTR szDriverVersion;
    LPWSTR szDriverLanguageEnglish;
    LPWSTR szNotesEnglish;
    LPWSTR szDriverDateEnglish;
    LPWSTR szHardwareID;
    LPWSTR szType;
    LPWSTR szOtherDrivers;
    ULONG lAccelerationLevel;
    ULONG dwFlags;
    ULONG dwMinSecondarySampleRate;
    ULONG dwMaxSecondarySampleRate;
    ULONG dwMaxHwMixingAllBuffers;
    ULONG dwMaxHwMixingStaticBuffers;
    ULONG dwMaxHwMixingStreamingBuffers;
    ULONG dwFreeHwMixingAllBuffers;
    ULONG dwMaxHw3DStaticBuffers;
    ULONG dwFreeHw3DAllBuffers;
    ULONG dwFreeHw3DStaticBuffers;
    ULONG dwFreeHw3DStreamingBuffers;
    ULONG dwMaxHw3DStreamingBuffers;
    ULONG dwFreeHwMixingStreamingBuffers;
    ULONG dwFreeHwMemBytes;
    ULONG dwPrimaryBuffers;
    ULONG dwFreeHwMixingStaticBuffers;
    ULONG dwMaxHw3DAllBuffers;
    ULONG dwMaxContigFreeHwMemBytes;
    ULONG dwTotalHwMemBytes;
    ULONG dwUnlockTransferRateHwBuffers;
    ULONG dwPlayCpuOverheadSwBuffers;
    BOOL bDriverDebug;
    BOOL bDriverBeta;
    BOOL bEAX20Source;
    BOOL bEAX20Listener;
    BOOL bVoiceManager;
    BOOL bDefaultSoundPlayback;
    BOOL bDefaultVoicePlayback;
    BOOL bI3DL2Listener;
    BOOL bI3DL2Source;
    BOOL bZoomFX;
} DXDIAG_SOUND_DEVICE_INFO, *PDXDIAG_SOUND_DEVICE_INFO;

/* Information on sound input devices
* Reference: DxDiag_SoundCaptureDevices
*/
typedef struct _DXDIAG_SOUND_CAPTURE_DEVICE_INFO
{
    LPWSTR szDescription;
    LPWSTR szDriverName;
    LPWSTR szDriverVersion;
    LPWSTR szDriverLanguageEnglish;
    LPWSTR szDriverDateEnglish;
    ULONG dwFormats;
    ULONG dwFlags;
    BOOL bDriverBeta;
    BOOL bDriverDebug;
    BOOL bDefaultVoiceRecording;
    BOOL bDefaultSoundRecording;
} DXDIAG_SOUND_CAPTURE_DEVICE_INFO, *PDXDIAG_SOUND_CAPTURE_DEVICE_INFO;

/* DxDiag_DirectSound */
typedef struct _DXDIAG_DSOUND_INFO
{
    PDXDIAG_SOUND_CAPTURE_DEVICE_INFO inputs;
    PDXDIAG_SOUND_DEVICE_INFO outputs;

    ULONG ulInputs;
    ULONG ulOutputs;
} DXDIAG_DSOUND_INFO, *PDXDIAG_DSOUND_INFO;

/* DxDiag_DirectMusicPorts */
typedef struct _DXDIAG_MUSIC_PORTS_INFO
{
    LPWSTR szDescription;
    BOOL bSoftware;
    BOOL bKernelMode;
    BOOL bUsesDLS;
    BOOL bExternal;
    BOOL bOutputPort;
    BOOL bDefaultPort;
} DXDIAG_MUSIC_PORTS_INFO, *PDXDIAG_MUSIC_PORTS_INFO;

/* DxDiag_DirectMusic */
typedef struct _DXDIAG_DMUSIC_INFO
{
    LPWSTR szGMFilePath;
    LPWSTR szGMFileVersion;
    LPWSTR szNotesEnglish;
    PDXDIAG_MUSIC_PORTS_INFO ports;
    ULONG ulPorts;
} DXDIAG_DMUSIC_INFO, *PDXDIAG_DMUSIC_INFO;

typedef struct _DXDIAG_INPUT_RELATED_DEVICE_INFO
{
    LPWSTR szMatchingDeviceId;
    LPWSTR szDescription;
    LPWSTR szService;
    LPWSTR szLocation;
    LPWSTR szUpperFilters;
    LPWSTR szLowerFilters;
    LPWSTR szOEMData;
    LPWSTR szFlags1;
    LPWSTR szFlags2;
    struct _DXDIAG_INPUT_RELATED_DEVICE_INFO* child;

    ULONG dwVendorID;
    ULONG dwProductID;
} DXDIAG_INPUT_RELATED_DEVICE_INFO, *PDXDIAG_INPUT_RELATED_DEVICE_INFO;

/* DxDiag_DirectInputDevices */
typedef struct _PDXDIAG_DINPUT_DEVICE_INFO
{
    LPWSTR szInstanceName;
    LPWSTR szFFDriverVersion;
    LPWSTR szFFDriverName;
    LPWSTR szFFDriverDateEnglish;
    ULONG dwJoystickID;
    ULONG dwVendorID;
    ULONG dwProductID;
    ULONG dwDevType;
    ULONG lFFDriverSize;
    BOOL bAttached;
} DXDIAG_DINPUT_DEVICE_INFO, *PDXDIAG_DINPUT_DEVICE_INFO;

/* DxDiag_DirectInput */
typedef struct _DXDIAG_DINPUT_INFO
{
    LPWSTR szInputNotesEnglish;
    PDXDIAG_DINPUT_DEVICE_INFO inputs;
    PDXDIAG_INPUT_RELATED_DEVICE_INFO gameports; /* DxDiag_DirectInputGameports */
    PDXDIAG_INPUT_RELATED_DEVICE_INFO usbroots; /* DxDiag_DirectInputUSBRoot */
    PDXDIAG_INPUT_RELATED_DEVICE_INFO ps2devices; /* DxDiag_DirectInputPS2Devices */

    ULONG ulInputs;
    ULONG ulGameports;
    ULONG ulUSBRoots;
    ULONG ulDevices;
    ULONG ulPS2Devices;
    BOOL bPollFlags;
} DXDIAG_DINPUT_INFO, *PDXDIAG_DINPUT_INFO;

/* DxDiag_LogicalDisks */
typedef struct _DXDIAG_LOGICAL_DISK_INFO
{
    LPWSTR szDriveLetter;
    LPWSTR szMaxSpace;
    LPWSTR szFreeSpace;
    LPWSTR szPNPDeviceID;
    LPWSTR szFileSystem;
    LPWSTR szModel;
    ULONG dwHardDriveIndex;
} DXDIAG_LOGICAL_DISK_INFO, *PDXDIAG_LOGICAL_DISK_INFO;

/* DxDiag_SystemDevices */
typedef struct _DXDIAG_SYSTEM_DEVICE_INFO
{
    LPWSTR szDescription;
    LPWSTR szDeviceID;
} DXDIAG_SYSTEM_DEVICE_INFO, *PDXDIAG_SYSTEM_DEVICE_INFO;

/* DxDiag_DirectPlaySPs */
typedef struct _DXDIAG_DPLAY_SP_INFO
{
    LPWSTR szNameEnglish;
    LPWSTR szNameLocalized;
    LPWSTR szVersionEnglish;
    LPWSTR szVersionLocalized;
    LPWSTR szFile;
    //BOOL bRegistryOK;
    //BOOL bFileMissing;
} DXDIAG_DPLAY_SP_INFO, *PDXDIAG_DPLAY_SP_INFO;

/* DxDiag_DirectPlayAdapters */
typedef struct DXDIAG_DPLAY_ADAPTER_INFO
{
    LPWSTR szAdapterName;
    LPWSTR szSPNameEnglish;
    LPWSTR szSPNameLocalized;
    LPWSTR szGuid;
    ULONG dwFlags;
} DXDIAG_DPLAY_ADAPTER_INFO, *PDXDIAG_DPLAY_ADAPTER_INFO;

/* DxDiag_DirectPlayVoiceCodecs */
typedef struct _DXDIAG_NET_VOICE_CODEC_INFO
{
    LPWSTR szName;
    LPWSTR szGuid;
    LPWSTR szDescription;
    ULONG dwFlags;
    ULONG dwMaxBitsPerSecond;
} DXDIAG_NET_VOICE_CODEC_INFO, *PDXDIAG_NET_VOICE_CODEC_INFO;

/* DxDiag_DirectShowFilters */
typedef struct _DXDIAG_DSHOWFILTERS_INFO
{
    LPWSTR szName;
    LPWSTR szCatName;
    LPWSTR szFileName;
    LPWSTR szFileVersion;
    ULONG dwMerit;
    ULONG dwInputs;
    ULONG dwOutputs;
} DXDIAG_DSHOWFILTERS_INFO, *PDXDIAG_DSHOWFILTERS_INFO;

/* DxDiag_DirectXFiles */
typedef struct _DXDIAG_COMPONENT_INFO
{
    LPWSTR szName;
    LPWSTR szVersion;
    LPWSTR szLanguageEnglish;
    LPWSTR szDatestampEnglish;
    LONG lNumBytes;
    BOOL bExists;
    BOOL bProblem;
    BOOL bDebug;
    BOOL bBeta;
} DXDIAG_COMPONENT_INFO, *PDXDIAG_COMPONENT_INFO;

typedef struct _DXDIAG_FILES_INFO
{
    LPWSTR szDXFileNotesEnglish;
    PDXDIAG_COMPONENT_INFO components;
    ULONG ulComponents;
} DXDIAG_FILES_INFO, *PDXDIAG_FILES_INFO;

/* DxDiag_DirectPlay */
typedef struct _DXDIAG_NET_INFO
{
    PDXDIAG_DPLAY_SP_INFO service_provider;
    PDXDIAG_DPLAY_ADAPTER_INFO adapters;
    PDXDIAG_NET_VOICE_CODEC_INFO voice_codecs;
    LPWSTR szVoiceWizardFullDuplexTestEnglish;
    LPWSTR szVoiceWizardHalfDuplexTestEnglish;
    LPWSTR szVoiceWizardMicTestEnglish;
    LPWSTR szNetworkNotesEnglish;
    LPWSTR szNetworkNotesLocalized;
    LPWSTR szTestResultEnglish;
    ULONG ulServiceProviders;
    ULONG ulLobbyableApps;
    ULONG ulAdapters;
    ULONG ulVoiceCodecs;
} DXDIAG_NET_INFO, *PDXDIAG_NET_INFO;

typedef struct _DXDIAG_INFO
{
    PDXDIAG_LOGICAL_DISK_INFO logical_disks;
    PDXDIAG_SYSTEM_DEVICE_INFO system_devices;
    PDXDIAG_DSHOWFILTERS_INFO video_filters;
    PDXDIAG_DISPLAY_DEVICE_INFO display_devices;
    
    ULONG ulDisplays;
    ULONG ulLogicalDisks;
    ULONG ulSystemDevices;
    ULONG ulVideoFilters;

    DXDIAG_NET_INFO network_info;
    DXDIAG_FILES_INFO files;
    DXDIAG_SYSTEM_INFO system_info;
    DXDIAG_DSOUND_INFO sound_devices;
    DXDIAG_DINPUT_INFO input_info;
    DXDIAG_DMUSIC_INFO music_info;
} DXDIAG_INFO, *PDXDIAG_INFO;

typedef struct _DXDIAG_INFO_CONTEXT
{
    IDxDiagProvider* ddp;
    IDxDiagProviderPrivate* ddpp;
    IDxDiagContainer* root;
} DXDIAG_INFO_CONTEXT, *PDXDIAG_INFO_CONTEXT;

typedef struct _DXDIAG_CONTEXT
{
    HWND* hDisplayWnd;
    HWND* hSoundWnd;
    HWND hMainDialog;
    HWND hTabCtrl;
    HWND hDialogs[5];
} DXDIAG_GUI_CONTEXT, * PDXDIAG_GUI_CONTEXT;

typedef struct dxdiag_context
{
    DXDIAG_INFO_CONTEXT info;
    DXDIAG_GUI_CONTEXT gui;
    DXDIAG_INFO data;
} DXDIAG_CONTEXT, * PDXDIAG_CONTEXT;

/* Output backend definitions. */
enum output_type
{
    OUTPUT_NONE,
    OUTPUT_TEXT,
    OUTPUT_XML,
};

static inline LPCSTR debugstr_output_type(enum output_type type)
{
    switch (type)
    {
    case OUTPUT_NONE:
        return "(none)";
    case OUTPUT_TEXT:
        return "Plain-text output";
    case OUTPUT_XML:
        return "XML output";
    default:
        return "(unknown)";
    }
}

LPCWSTR get_output_extension(enum output_type type);
BOOL output_dxdiag_information(PDXDIAG_CONTEXT ctx, LPCWSTR filename, enum output_type type);
void output_dxdiag_gui(PDXDIAG_CONTEXT ctx);
