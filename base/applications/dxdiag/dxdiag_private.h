/*
 * Private definitions for the DirectX Diagnostic Tool
 *
 * Copyright 2011 Andrew Nguyen
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include <windef.h>
#include <winuser.h>

/* Resource definitions. */
#define MAX_STRING_LEN          1024

#define STRING_DXDIAG_TOOL      101
#define STRING_USAGE            102

#define XML_FIELDS_SYSTEMINFO 25


/* Information collection definitions. 
   Refenrece: DxDiag_SystemInfo
*/
struct system_information
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
    WCHAR* szPhysicalMemoryEnglishOS;
    WCHAR* szSystemDPI;
    WCHAR* szDWMScalingDPI;
    WCHAR* szDxDbVersion;
    WCHAR* szUserDPI;
    WCHAR* szMiracastAvailable;
    WCHAR* szMSHybrid;
    INT nDPlayDebugLevel;
    INT nDDrawDebugLevel;
    INT nDIDebugLevel;
    INT nDMusicDebugLevel;
    INT nDShowDebugLevel;
    INT nDSoundDebugLevel;
    BOOL bIsDSoundDebugRuntime;
    BOOL bIsDPlayDebugRuntime;
    BOOL bIsDDrawDebugRuntime;
    BOOL bIsDMusicDebugRuntime;
    BOOL win64;
};

/* Information on current screens
* Reference: DxDiag_DisplayDevices
*/
struct display_device
{
    WCHAR* szDescription;
    WCHAR* szManufacturer;
    WCHAR* szChipType;
    WCHAR* dacType;
    WCHAR* szKeyDeviceID;
    WCHAR* szNotesEnglish;
    WCHAR* szDisplayModeEnglish;
    WCHAR* szDisplayModeLocalized;
    WCHAR* szDriverModelEnglish;
    WCHAR* szVdd;
    WCHAR* szMiniVddDateEnglish;
    WCHAR* szDriverLanguageEnglish;
    WCHAR* szDisplayMemoryEnglish;
    WCHAR* szDisplayMemoryLocalized;
    WCHAR* szAGPStatusEnglish;
    WCHAR* szD3DStatusEnglish;
    WCHAR* szDXVAHDEnglish;
    WCHAR* szDriverDateEnglish;
    WCHAR* szMiniVdd;
    WCHAR* szVendorId;
    WCHAR* szDeviceId;
    WCHAR* szSubSysId;
    WCHAR* szRevisionId;
    WCHAR* szDriverNodeStrongName;
    WCHAR* szRankOfInstalledDriver;
    WCHAR* szDeviceIdentifier;
    WCHAR* szMonitorName;
    WCHAR* szMonitorMaxRes;
    WCHAR* szDriverName;
    WCHAR* szDriverVersion;
    WCHAR* szDriverAssemblyVersion;
    WCHAR* szDXVAModes;
    WCHAR* szGuid;
    WCHAR* szOverlayEnglish;
    WCHAR* szDriverSignDate;
    WCHAR* szDDIVersionEnglish;
    WCHAR* szDDStatusEnglish;
    WCHAR* szTestResultDDEnglish;
    WCHAR* szTestResultD3D7English;
    WCHAR* szTestResultD3D8English;
    WCHAR* szTestResultD3D9English;
    LONG lMiniVddSize;
    LONG lDriverSize;
    BOOL bDriverDebug;
    BOOL bDriverBeta;
};

/* Information on output sound devices
* Reference: DxDiag_SoundDevices
*/
struct sound_output_device
{
    WCHAR* szDescription;
    WCHAR* szRegKey;
    WCHAR* szManufacturerID;
    WCHAR* szProductID;
    WCHAR* szDriverName;
    WCHAR* szDriverVersion;
    WCHAR* szDriverLanguageEnglish;
    WCHAR* szNotesEnglish;
    WCHAR* szDriverDateEnglish;
    WCHAR* szHardwareID;
    WCHAR* szType;
    WCHAR* szOtherDrivers;
    LONG lAccelerationLevel;
    DWORD dwFlags;
    DWORD dwMinSecondarySampleRate;
    DWORD dwMaxSecondarySampleRate;
    DWORD dwMaxHwMixingAllBuffers;
    DWORD dwMaxHwMixingStaticBuffers;
    DWORD dwMaxHwMixingStreamingBuffers;
    DWORD dwFreeHwMixingAllBuffers;
    DWORD dwMaxHw3DStaticBuffers;
    DWORD dwFreeHw3DAllBuffers;
    DWORD dwFreeHw3DStaticBuffers;
    DWORD dwFreeHw3DStreamingBuffers;
    DWORD dwMaxHw3DStreamingBuffers;
    DWORD dwFreeHwMixingStreamingBuffers;
    DWORD dwFreeHwMemBytes;
    DWORD dwPrimaryBuffers;
    DWORD dwFreeHwMixingStaticBuffers;
    DWORD dwMaxHw3DAllBuffers;
    DWORD dwMaxContigFreeHwMemBytes;
    DWORD dwTotalHwMemBytes;
    DWORD dwUnlockTransferRateHwBuffers;
    DWORD dwPlayCpuOverheadSwBuffers;
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
};

/* Information on sound input devices
* Reference: DxDiag_SoundCaptureDevices
*/
struct sound_input_device
{
    WCHAR* szDescription;
    WCHAR* szDriverName;
    WCHAR* szDriverVersion;
    WCHAR* szDriverLanguageEnglish;
    WCHAR* szDriverDateEnglish;
    DWORD dwFormats;
    DWORD dwFlags;
    BOOL bDriverBeta;
    BOOL bDriverDebug;
    BOOL bDefaultVoiceRecording;
    BOOL bDefaultSoundRecording;
};

/* DxDiag_DirectSound */
struct sound_devices
{
    ULONG ulInputs;
    ULONG ulOutputs;
    struct sound_input_device* inputs;
    struct sound_output_device* outputs;
};

/* DxDiag_DirectMusicPorts */
struct music_port
{
    WCHAR* szDescription;
    BOOL bSoftware;
    BOOL bKernelMode;
    BOOL bUsesDLS;
    BOOL bExternal;
    BOOL bOutputPort;
    BOOL bDefaultPort;
};

/* DxDiag_DirectMusic */
struct music_information
{
    WCHAR* szGMFilePath;
    WCHAR* szGMFileVersion;
    WCHAR* szNotesEnglish;
    ULONG ulPorts;
    struct music_port* ports;
};

struct input_related_device
{
    WCHAR* szMatchingDeviceId;
    WCHAR* szDescription;
    WCHAR* szService;
    WCHAR* szLocation;
    WCHAR* szUpperFilters;
    WCHAR* szLowerFilters;
    WCHAR* szOEMData;
    WCHAR* szFlags1;
    WCHAR* szFlags2;
    struct input_related_device* child;

    DWORD dwVendorID;
    DWORD dwProductID;
};

/* DxDiag_DirectInputDevices */
struct input_device
{
    WCHAR* szInstanceName;
    WCHAR* szFFDriverVersion;
    WCHAR* szFFDriverName;
    WCHAR* szFFDriverDateEnglish;
    DWORD dwJoystickID;
    DWORD dwVendorID;
    DWORD dwProductID;
    DWORD dwDevType;
    LONG lFFDriverSize;
    BOOL bAttached;
};

/* DxDiag_DirectInput */
struct input_information
{
    WCHAR* szInputNotesEnglish;
    struct input_device* inputs;
    struct input_related_device* gameports; /* DxDiag_DirectInputGameports */
    struct input_related_device* usbroots; /* DxDiag_DirectInputUSBRoot */
    struct input_related_device* ps2devices; /* DxDiag_DirectInputPS2Devices */

    ULONG ulInputs;
    ULONG ulGameports;
    ULONG ulUSBRoots;
    ULONG ulDevices;
    ULONG ulPS2Devices;
    BOOL bPollFlags;
};

/* DxDiag_LogicalDisks */
struct logical_disk
{
    WCHAR* szDriveLetter;
    WCHAR* szMaxSpace;
    WCHAR* szFreeSpace;
    WCHAR* szPNPDeviceID;
    WCHAR* szFileSystem;
    WCHAR* szModel;
    DWORD dwHardDriveIndex;
};

/* DxDiag_SystemDevices */
struct system_device
{
    WCHAR* szDescription;
    WCHAR* szDeviceID;
};

/* DxDiag_DirectPlaySPs */
struct net_sp
{
    WCHAR* szNameEnglish;
    WCHAR* szNameLocalized;
    WCHAR* szVersionEnglish;
    WCHAR* szVersionLocalized;
    WCHAR* szFile;
    //BOOL bRegistryOK;
    //BOOL bFileMissing;
};

/* DxDiag_DirectPlayAdapters */
struct net_adapters
{
    WCHAR* szAdapterName;
    WCHAR* szSPNameEnglish;
    WCHAR* szSPNameLocalized;
    WCHAR* szGuid;
    DWORD dwFlags;
};

/* DxDiag_DirectPlayVoiceCodecs */
struct net_voicecodecs
{
    WCHAR* szName;
    WCHAR* szGuid;
    WCHAR* szDescription;
    DWORD dwFlags;
    DWORD dwMaxBitsPerSecond;
};

/* DxDiag_DirectShowFilters */
struct video_showfilters
{
    WCHAR* szName;
    WCHAR* szCatName;
    WCHAR* szFileName;
    WCHAR* szFileVersion;
    DWORD dwMerit;
    DWORD dwInputs;
    DWORD dwOutputs;
};

/* DxDiag_DirectXFiles */
struct dx_components
{
    WCHAR* szName;
    WCHAR* szVersion;
    WCHAR* szLanguageEnglish;
    WCHAR* szDatestampEnglish;
    LONG lNumBytes;
    BOOL bExists;
    BOOL bProblem;
    BOOL bDebug;
    BOOL bBeta;
};

struct dx_files
{
    WCHAR* szDXFileNotesEnglish;
    struct dx_components* components;
    ULONG ulComponents;
};

/* DxDiag_DirectPlay */
struct net_information
{
    struct net_sp* service_provider;
    struct net_adapters* adapters;
    struct net_voicecodecs* voice_codecs;
    WCHAR* szVoiceWizardFullDuplexTestEnglish;
    WCHAR* szVoiceWizardHalfDuplexTestEnglish;
    WCHAR* szVoiceWizardMicTestEnglish;
    WCHAR* szNetworkNotesEnglish;
    WCHAR* szNetworkNotesLocalized;
    WCHAR* szTestResultEnglish;
    ULONG ulServiceProviders;
    ULONG ulLobbyableApps;
    ULONG ulAdapters;
    ULONG ulVoiceCodecs;
};

struct dxdiag_information
{
    struct system_information system_info;
    struct sound_devices sound_devices; 
    struct input_information input_info;
    struct music_information music_info;
    struct logical_disk* logical_disks;
    struct system_device* system_devices;
    struct video_showfilters* video_filters;
    struct net_information network_info;
    struct display_device* display_devices;
    struct dx_files files;
    ULONG ulDisplays;
    ULONG ulLogicalDisks;
    ULONG ulSystemDevices;
    ULONG ulVideoFilters;
};

struct dxdiag_information *collect_dxdiag_information(BOOL whql_check);
void free_dxdiag_information(struct dxdiag_information *dxdiag_info);

/* Output backend definitions. */
enum output_type
{
    OUTPUT_NONE,
    OUTPUT_TEXT,
    OUTPUT_XML,
};

static inline const char *debugstr_output_type(enum output_type type)
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

const WCHAR *get_output_extension(enum output_type type);
BOOL output_dxdiag_information(struct dxdiag_information *dxdiag_info, const WCHAR *filename, enum output_type type);
BOOL output_xml_information(struct dxdiag_information* dxdiag_info, const WCHAR* filename);
BOOL output_text_information(struct dxdiag_information* dxdiag_info, const WCHAR* filename);
