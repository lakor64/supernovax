/*
 * DxDiag xml file information output
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
#include "precomp.h"
#include <initguid.h>
#include <msxml2.h>

WINE_DEFAULT_DEBUG_CHANNEL(dxdiag);

#define FIELD(name, val) \
    fields[id].type = XML_TYPE_FIELD; \
    fields[id].field.tag_name = name; \
    wcscpy_s(fields[id++].field.value, sizeof(fields[id].field.value), val == NULL ? L"" : val);

#define FIELD_BOOL(name, val) FIELD(name, val ? L"1" : L"0")
#define FIELD_DWORD(name, val) \
    fields[id].type = XML_TYPE_FIELD; \
    fields[id].field.tag_name = name; \
    swprintf_s(fields[id++].field.value, sizeof(fields[id].field.value), L"%lu", val);

#define FIELD_TODO(name) FIELD(name, L"TODO: Fix")

enum xml_info
{
    XML_TYPE_NONE,
    XML_TYPE_FIELD,
    XML_TYPE_CHILD,
};

struct xml_information_field
{
    const WCHAR* tag_name;
    WCHAR value[256];
};

struct xml_information_data
{
    int type;
    union
    {
        struct xml_information_block* child;
        struct xml_information_field field;
    };
};

struct xml_information_block
{
    const WCHAR* tag_name;
    struct xml_information_data data[90];
};

static IXMLDOMElement* xml_create_element(IXMLDOMDocument* xmldoc, const WCHAR* name)
{
    BSTR bstr = SysAllocString(name);
    IXMLDOMElement* ret;
    HRESULT hr;

    if (!bstr)
        return NULL;

    hr = IXMLDOMDocument_createElement(xmldoc, bstr, &ret);
    SysFreeString(bstr);

#ifdef _DEBUG
    if (FAILED(hr))
        _CrtDbgBreak();
#endif

    return SUCCEEDED(hr) ? ret : NULL;
}

static HRESULT xml_put_element_text(IXMLDOMElement* element, const WCHAR* text)
{
    BSTR bstr = SysAllocString(text);
    HRESULT hr;

    if (!bstr)
        return E_OUTOFMEMORY;

    hr = IXMLDOMElement_put_text(element, bstr);
    SysFreeString(bstr);

    return hr;
}

static HRESULT save_xml_document(IXMLDOMDocument* xmldoc, const WCHAR* filename)
{
    BSTR bstr = SysAllocString(filename);
    VARIANT destVar;
    HRESULT hr;

    if (!bstr)
        return E_OUTOFMEMORY;

    V_VT(&destVar) = VT_BSTR;
    V_BSTR(&destVar) = bstr;

    hr = IXMLDOMDocument_save(xmldoc, destVar);
    VariantClear(&destVar);

    return hr;
}

static inline void fill_system_xml_output_table(struct dxdiag_information* dxdiag_info, struct xml_information_data* fields)
{
    DWORD id = 0;
    FIELD(L"Time", dxdiag_info->system_info.szTimeEnglish);
    FIELD(L"MachineName", dxdiag_info->system_info.szMachineNameEnglish);
    FIELD_TODO(L"MachineId");
    FIELD(L"OperatingSystem", dxdiag_info->system_info.szOSExLongEnglish);
    FIELD(L"Language", dxdiag_info->system_info.szLanguagesEnglish);
    FIELD(L"SystemManufacturer", dxdiag_info->system_info.szSystemManufacturerEnglish);
    FIELD(L"SystemModel", dxdiag_info->system_info.szSystemModelEnglish);
    FIELD(L"BIOS", dxdiag_info->system_info.szBIOSEnglish);
    FIELD_TODO(L"FirmwareType");
    FIELD(L"Processor", dxdiag_info->system_info.szProcessorEnglish);
    FIELD(L"Memory", dxdiag_info->system_info.szPhysicalMemoryEnglish);
    FIELD(L"AvaliableOSMem", dxdiag_info->system_info.szPhysicalMemoryEnglishOS);
    FIELD(L"PageFile", dxdiag_info->system_info.szPageFileEnglish);
    FIELD(L"WindowsDir", dxdiag_info->system_info.szWindowsDir);
    FIELD(L"DirectXVersion", dxdiag_info->system_info.szDirectXVersionLongEnglish);
    FIELD(L"DXSetupParameters", dxdiag_info->system_info.szSetupParamEnglish);

    if (!dxdiag_info->system_info.szUserDPI || wcscmp(dxdiag_info->system_info.szUserDPI, L"Using System DPI") == 0)
    {
        FIELD(L"UserDPISettings", dxdiag_info->system_info.szSystemDPI);
    }
    else
    {
        FIELD(L"UserDPISettings", dxdiag_info->system_info.szUserDPI);
    }

    FIELD(L"SystemDPISettings", dxdiag_info->system_info.szSystemDPI);
    FIELD(L"DWMDPIScaling", dxdiag_info->system_info.szDWMScalingDPI);
    FIELD(L"DxDiagVersion", dxdiag_info->system_info.szDxDiagVersion);
#ifdef _UNICODE
    FIELD(L"DxDiagUnicode", L"1");
#else
    FIELD(L"DxDiagUnicode", L"0");
#endif
    FIELD_BOOL(L"DxDiag64Bit", dxdiag_info->system_info.win64);
    FIELD(L"Miracast", dxdiag_info->system_info.szMiracastAvailable);

    if (!dxdiag_info->system_info.szMSHybrid || dxdiag_info->system_info.szMSHybrid[0] == '\0')
    {
        FIELD(L"MSHybrid", L"Not Supported");
    }
    else
    {
        FIELD(L"MSHybrid", dxdiag_info->system_info.szMSHybrid);
    }

    FIELD(L"DirectXDatabaseVersion", dxdiag_info->system_info.szDxDbVersion);
}

static inline void fill_dxdiag_notes(struct dxdiag_information* dxdiag_info, struct xml_information_data* fields)
{
    DWORD id = 0;
    ULONG i = 0;

    FIELD(L"DirectXFilesTab", dxdiag_info->files.szDXFileNotesEnglish);

    for (; i < dxdiag_info->ulDisplays; i++)
    {
        FIELD(L"DisplayTab", dxdiag_info->display_devices[i].szNotesEnglish);
    }

    for (i = 0; i < dxdiag_info->sound_devices.ulOutputs; i++)
    {
        FIELD(L"SoundTab", dxdiag_info->sound_devices.outputs[i].szNotesEnglish);
    }

    // not present in nt6
    FIELD(L"MusicTab", dxdiag_info->music_info.szNotesEnglish);
    FIELD(L"InputTab", dxdiag_info->input_info.szInputNotesEnglish);
    FIELD(L"NetworkTab", dxdiag_info->network_info.szNetworkNotesEnglish);
}

static inline void fill_dxdebug_level(WCHAR* tag, ULONG curr, ULONG max, WCHAR* runtime, struct xml_information_block* blk)
{
    DWORD id = 0;
    struct xml_information_data* fields = blk->data;
    blk->tag_name = tag;
    FIELD_DWORD(L"Current", curr);
    FIELD_DWORD(L"Max", max);
    FIELD(L"Runtime", runtime);
}

#define DXDEBUG_LEVEL(tag, curr, max, runtime) \
    fields[id].type = XML_TYPE_CHILD; \
    fields[id].child = malloc(sizeof(struct xml_information_block)); \
    if (!fields[id].child) \
        return; \
    fill_dxdebug_level(tag, curr, max, runtime, fields[id++].child);

static inline void fill_dxdebug_levels(struct dxdiag_information* dxdiag_info, struct xml_information_data* fields)
{
    DWORD id = 0;

    DXDEBUG_LEVEL(L"Direct3D", 0, 0, L"n/a");
    DXDEBUG_LEVEL(L"DirectDraw", dxdiag_info->system_info.nDDrawDebugLevel, 0, L"n/a");
    DXDEBUG_LEVEL(L"DirectInput", dxdiag_info->system_info.nDIDebugLevel, 0, L"n/a");
    DXDEBUG_LEVEL(L"DirectMusic", dxdiag_info->system_info.nDMusicDebugLevel, 0, L"n/a");
    DXDEBUG_LEVEL(L"DirectPlay", dxdiag_info->system_info.nDPlayDebugLevel, 0, L"n/a");
    DXDEBUG_LEVEL(L"DirectSound", dxdiag_info->system_info.nDSoundDebugLevel, 0, L"n/a");
    DXDEBUG_LEVEL(L"DirectShow", dxdiag_info->system_info.nDShowDebugLevel, 0, L"n/a");
}

static inline void fill_display_device(struct dxdiag_information* dxdiag_info, struct xml_information_data* fields, ULONG current)
{
    struct display_device* display = &dxdiag_info->display_devices[current];
    DWORD id = 0;

    FIELD(L"Cardname", display->szDescription);
    FIELD(L"Manufacturer", display->szManufacturer);
    FIELD(L"ChipType", display->szChipType);
    FIELD(L"DACType", display->dacType);
    FIELD_TODO(L"DeviceType");
    FIELD(L"DeviceKey", display->szKeyDeviceID);
    FIELD_TODO(L"DeviceStatus"); // nt6+
    FIELD_TODO(L"DeviceProblemCode"); // nt6+
    FIELD_TODO(L"DriverProblemCode"); // nt6+
    FIELD(L"DisplayMemory", display->szDisplayMemoryEnglish);
    FIELD_TODO(L"DedicatedMemory"); // nt6+
    FIELD_TODO(L"SharedMemory"); // nt6+
    FIELD(L"CurrentMode", display->szDisplayModeEnglish);
    FIELD_TODO(L"HDRSupport"); // nt6+
    FIELD_TODO(L"Topology"); // nt6+
    FIELD_TODO(L"ColorSpace"); // nt6+
    FIELD_TODO(L"ColorPrimaries"); // nt6+
    FIELD_TODO(L"Luminance"); // nt6+
    FIELD(L"MonitorName", display->szMonitorName); // nt6+
    FIELD_TODO(L"MonitorModel"); // nt6+
    FIELD_TODO(L"MonitorId"); // nt6+
    FIELD_TODO(L"NativeMode"); // nt6+
    FIELD_TODO(L"Monitor"); // nt5 only
    FIELD_TODO(L"OutputType"); // nt6+
    FIELD_TODO(L"Eotf2084Supported"); // nt6+
    FIELD_TODO(L"BT2020YCC"); // nt6+
    FIELD_TODO(L"BT2020RGB"); // nt6+
    FIELD_TODO(L"AdvancedColorEnabled"); // nt6+
    FIELD_TODO(L"AdvancedColorSupported"); // nt6+
    FIELD_TODO(L"bCheckedMonitorCapabilities"); // nt6+
    FIELD_TODO(L"PixelFormat"); // nt6+
    FIELD(L"MonitorMaxRes", display->szMonitorMaxRes);
    FIELD(L"DriverName", display->szDriverName);
    FIELD(L"DriverFileVersion", display->szDriverVersion); // nt6+
    FIELD(L"DriverVersion", display->szDriverAssemblyVersion);
    FIELD(L"DriverLanguage", display->szDriverLanguageEnglish);
    FIELD(L"DDIVersion", display->szDDIVersionEnglish);
    FIELD_TODO(L"FeatureLevels"); // nt6+
    FIELD(L"DriverModel", display->szDriverModelEnglish); // nt6+
    FIELD_BOOL(L"DriverBeta", display->bDriverBeta);
    FIELD_BOOL(L"DriverDebug", display->bDriverDebug);
    FIELD(L"DriverDate", display->szDriverDateEnglish);
    FIELD_DWORD(L"DriverSize", display->lDriverSize);
    FIELD_TODO(L"DriverWHQLLogo");
    FIELD(L"WHQLDateStamp", display->szDriverSignDate);
    FIELD(L"VDD", display->szVdd);
    FIELD(L"MiniVDD", display->szMiniVdd);
    FIELD(L"MiniVDDDate", display->szMiniVddDateEnglish);
    FIELD_DWORD(L"MiniVDDSize", display->lMiniVddSize);
    FIELD(L"DeviceIdentifier", display->szDeviceIdentifier);
    FIELD(L"VendorID", display->szVendorId);
    FIELD(L"DeviceID", display->szDeviceId);
    FIELD(L"SubSysID", display->szSubSysId);
    FIELD(L"RevisionID", display->szRevisionId);
    FIELD(L"DriverNodeStrongName", display->szDriverNodeStrongName); // nt6+
    FIELD(L"RankOfInstalledDriver", display->szRankOfInstalledDriver); // nt6+
    FIELD(L"DXVAModes", display->szDXVAModes);
    FIELD_TODO(L"DXVA2Modes"); // nt6+
    FIELD_TODO(L"GraphicsPreemption"); // nt6+
    FIELD_TODO(L"ComputePreemption"); // nt6+
    FIELD_TODO(L"Miracast"); // nt6+
    FIELD_TODO(L"DetachableGPU"); // nt6+
    FIELD_TODO(L"HybridGraphicsGPUType"); // nt6+
    FIELD_TODO(L"PowerManagementPStates"); // nt6+
    FIELD_TODO(L"VirtualGPUSupport"); // nt6+
    FIELD_TODO(L"BlockList"); // nt6+
    FIELD_TODO(L"DriverCatalogAttributes"); // nt6+
    FIELD_TODO(L"MPOMaxPlanes"); // nt6+
    FIELD_TODO(L"MPOCaps"); // nt6+
    FIELD_TODO(L"MPOStretch"); // nt6+
    FIELD_TODO(L"MPOMediaHints"); // nt6+
    FIELD_TODO(L"MPOFormats"); // nt6+
    FIELD_TODO(L"PanelFitterCaps"); // nt6+
    FIELD_TODO(L"PanelFitterStretch"); // nt6+
    FIELD_TODO(L"HardwareSchedulingAttributes"); // nt6+
    FIELD_TODO(L"DisplayableSupport"); // nt6+
    FIELD_TODO(L"DXVADeinterlaceCaps");
    FIELD(L"D3D9Overlay", display->szOverlayEnglish); // nt6+
    FIELD(L"DXVAHD", display->szDXVAHDEnglish); // nt6+
    FIELD(L"DDrawStatus", display->szDDStatusEnglish);
    FIELD(L"D3DStatus", display->szD3DStatusEnglish);
    FIELD(L"AGPStatus", display->szAGPStatusEnglish);
    FIELD(L"DDrawTestResult", display->szTestResultDDEnglish); // nt5 only
    FIELD(L"D3D7TestResult", display->szTestResultD3D7English); // nt5 only
    FIELD(L"D3D8TestResult", display->szTestResultD3D8English); // nt5 only
    FIELD(L"D3D9TestResult", display->szTestResultD3D9English); // nt5 only
}

static inline void fill_display_devices(struct dxdiag_information* dxdiag_info, struct xml_information_data* fields)
{
    for (ULONG i = 0; i < dxdiag_info->ulDisplays; i++)
    {
        fields[i].type = XML_TYPE_CHILD;
        fields[i].child = malloc(sizeof(struct xml_information_block));
        if (!fields[i].child)
            return;
        memset(fields[i].child, 0, sizeof(struct xml_information_block));
        fields[i].child->tag_name = L"DisplayDevice";
        fill_display_device(dxdiag_info, fields[i].child->data, i);
    }
}

static inline void fill_sound_device(struct dxdiag_information* dxdiag_info, struct xml_information_data* fields, ULONG current)
{
    struct sound_output_device* display = &dxdiag_info->sound_devices.outputs[current];
    DWORD id = 0;

    FIELD(L"Description", display->szDescription);
    FIELD(L"HardwareID", display->szHardwareID);
    FIELD(L"ManufacturerID", display->szManufacturerID);
    FIELD(L"ProductID", display->szProductID);
    FIELD(L"Type", display->szType);
    FIELD(L"DriverName", display->szDriverName);
    FIELD(L"DriverVersion", display->szDriverVersion);
    FIELD(L"DriverLanguage", display->szDriverLanguageEnglish);
    FIELD_BOOL(L"DriverBeta", display->bDriverBeta);
    FIELD_BOOL(L"DriverDebug", display->bDriverDebug);
    FIELD_TODO(L"DriverWHQLLogo");
    FIELD(L"DriverDate", display->szDriverDateEnglish);
    FIELD_TODO(L"DriverSize");
    FIELD_TODO(L"DriverProvider"); // NT5 only
    FIELD(L"OtherFiles", display->szOtherDrivers);
    FIELD_TODO(L"HwAccelLevel");
    FIELD_BOOL(L"DefaultSoundPlayback", display->bDefaultSoundPlayback);
    FIELD_BOOL(L"DefaultVoicePlayback", display->bDefaultVoicePlayback);
    FIELD_BOOL(L"VoiceManager", display->bVoiceManager);
    FIELD_BOOL(L"EAX20Listener", display->bEAX20Listener);
    FIELD_BOOL(L"EAX20Source", display->bEAX20Source);
    FIELD_BOOL(L"I3DL2Listener", display->bI3DL2Listener);
    FIELD_BOOL(L"I3DL2Source", display->bI3DL2Source);
    FIELD_BOOL(L"ZoomFX", display->bZoomFX);
    FIELD_DWORD(L"Flags", display->dwFlags);
    FIELD_DWORD(L"MinSecondarySampleRate", display->dwMinSecondarySampleRate);
    FIELD_DWORD(L"MaxSecondarySampleRate", display->dwMaxSecondarySampleRate);
    FIELD_DWORD(L"PrimaryBuffers", display->dwPrimaryBuffers);
    FIELD_DWORD(L"MaxHwMixingAllBuffers", display->dwMaxHwMixingAllBuffers);
    FIELD_DWORD(L"MaxHwMixingStaticBuffers", display->dwMaxHwMixingStaticBuffers);
    FIELD_DWORD(L"MaxHwMixingStreamingBuffers", display->dwMaxHwMixingStreamingBuffers);
    FIELD_DWORD(L"FreeHwMixingAllBuffers", display->dwFreeHwMixingAllBuffers);
    FIELD_DWORD(L"FreeHwMixingStaticBuffers", display->dwFreeHwMixingStaticBuffers);
    FIELD_DWORD(L"FreeHwMixingStreamingBuffers", display->dwFreeHwMixingStreamingBuffers);
    FIELD_DWORD(L"MaxHw3DAllBuffers", display->dwMaxHw3DAllBuffers);
    FIELD_DWORD(L"MaxHw3DStaticBuffers", display->dwMaxHw3DStaticBuffers);
    FIELD_DWORD(L"MaxHw3DStreamingBuffers", display->dwMaxHw3DStreamingBuffers);
    FIELD_DWORD(L"FreeHw3DAllBuffers", display->dwFreeHw3DAllBuffers);
    FIELD_DWORD(L"FreeHw3DStaticBuffers", display->dwFreeHw3DStaticBuffers);
    FIELD_DWORD(L"FreeHw3DStreamingBuffers", display->dwFreeHw3DStreamingBuffers);
    FIELD_DWORD(L"TotalHwMemBytes", display->dwTotalHwMemBytes);
    FIELD_DWORD(L"FreeHwMemBytes", display->dwFreeHwMemBytes);
    FIELD_DWORD(L"MaxContigFreeHwMemBytes", display->dwMaxContigFreeHwMemBytes);
    FIELD_DWORD(L"UnlockTransferRateHwBuffers", display->dwUnlockTransferRateHwBuffers);
    FIELD_DWORD(L"PlayCPUOverheadSwBuffers", display->dwPlayCpuOverheadSwBuffers);
    FIELD_TODO(L"Registry"); // NT5 only
}

static inline void fill_sound_devices(struct dxdiag_information* dxdiag_info, struct xml_information_data* fields)
{
    for (ULONG i = 0; i < dxdiag_info->sound_devices.ulOutputs; i++)
    {
        fields[i].type = XML_TYPE_CHILD;
        fields[i].child = malloc(sizeof(struct xml_information_block));
        if (!fields[i].child)
            return;
        memset(fields[i].child, 0, sizeof(struct xml_information_block));
        fields[i].child->tag_name = L"SoundDevice";
        fill_sound_device(dxdiag_info, fields[i].child->data, i);
    }
}

static inline void fill_sound_capture_device(struct dxdiag_information* dxdiag_info, struct xml_information_data* fields, ULONG current)
{
    struct sound_input_device* display = &dxdiag_info->sound_devices.inputs[current];
    DWORD id = 0;

    FIELD(L"Description", display->szDescription);
    FIELD(L"DriverName", display->szDriverName);
    FIELD(L"DriverVersion", display->szDriverVersion);
    FIELD(L"DriverLanguage", display->szDriverLanguageEnglish);
    FIELD_BOOL(L"DriverBeta", display->bDriverBeta);
    FIELD_BOOL(L"DriverDebug", display->bDriverDebug);
    FIELD(L"DriverDate", display->szDriverDateEnglish);
    FIELD_TODO(L"DriverSize");
    FIELD_BOOL(L"DefaultSoundRecording", display->bDefaultSoundRecording);
    FIELD_BOOL(L"DefaultVoiceRecording", display->bDefaultVoiceRecording);
    FIELD_DWORD(L"Flags", display->dwFlags);
    FIELD_DWORD(L"Formats", display->dwFormats);
}

static inline void fill_sound_capture_devices(struct dxdiag_information* dxdiag_info, struct xml_information_data* fields)
{
    for (ULONG i = 0; i < dxdiag_info->sound_devices.ulInputs; i++)
    {
        fields[i].type = XML_TYPE_CHILD;
        fields[i].child = malloc(sizeof(struct xml_information_block));
        if (!fields[i].child)
            return;
        memset(fields[i].child, 0, sizeof(struct xml_information_block));
        fields[i].child->tag_name = L"SoundCaptureDevice";
        fill_sound_capture_device(dxdiag_info, fields[i].child->data, i);
    }
}

static inline void fill_sound(struct dxdiag_information* dxdiag_info, struct xml_information_data* fields)
{
    fields[0].type = XML_TYPE_CHILD;
    fields[0].child = malloc(sizeof(struct xml_information_block));

    if (!fields[0].child)
        return;

    memset(fields[0].child, 0, sizeof(struct xml_information_block));

    fields[0].child->tag_name = L"SoundDevices";
    fill_sound_devices(dxdiag_info, fields[0].child->data);

    fields[1].type = XML_TYPE_CHILD;
    fields[1].child = malloc(sizeof(struct xml_information_block));
    if (!fields[1].child)
        return;

    memset(fields[1].child, 0, sizeof(struct xml_information_block));

    fields[1].child->tag_name = L"SoundCaptureDevices";
    fill_sound_capture_devices(dxdiag_info, fields[1].child->data);
}

static inline void fill_music_port(struct dxdiag_information* dxdiag_info, struct xml_information_data* fields, ULONG current)
{
    DWORD id = 0;
    struct music_port* port = &dxdiag_info->music_info.ports[current];

    FIELD(L"Description", port->szDescription);
    FIELD_BOOL(L"Software", port->bSoftware);
    FIELD_BOOL(L"KernelMode", port->bKernelMode);
    FIELD_BOOL(L"OutputPort", port->bOutputPort)
    FIELD_BOOL(L"UsesDLS", port->bUsesDLS);
    FIELD_BOOL(L"External", port->bExternal);
    FIELD_BOOL(L"DefaultPort", port->bDefaultPort);
}

static inline void fill_music_ports(struct dxdiag_information* dxdiag_info, struct xml_information_data* fields)
{
    ULONG i = 0;

    for (; i < dxdiag_info->music_info.ulPorts; i++)
    {
        fields[i].type = XML_TYPE_CHILD;
        fields[i].child = malloc(sizeof(struct xml_information_block));
        if (!fields[i].child)
            return;
        memset(fields[i].child, 0, sizeof(struct xml_information_block));
        fields[i].child->tag_name = L"Port";
        fill_music_port(dxdiag_info, fields[i].child->data, i);
    }
}

static inline void fill_music(struct dxdiag_information* dxdiag_info, struct xml_information_data* fields)
{
    DWORD id = 0;
    struct music_information* music = &dxdiag_info->music_info;

    FIELD(L"DLSPath", music->szGMFilePath);
    FIELD(L"DLSVersion", music->szGMFileVersion);
    FIELD_TODO(L"Acceleration");

    fields[id].type = XML_TYPE_CHILD;
    fields[id].child = malloc(sizeof(struct xml_information_block));
    if (!fields[id].child)
        return;
    memset(fields[id].child, 0, sizeof(struct xml_information_block));
    fields[id].child->tag_name = L"Ports";
    fill_music_ports(dxdiag_info, fields[id++].child->data);

    FIELD_TODO(L"Registry");
}

static inline void fill_input_related_device(struct input_related_device* device, struct xml_information_data* fields)
{
    DWORD id = 0;

    FIELD(L"Description", device->szDescription);
    FIELD_DWORD(L"VendorID", device->dwVendorID);
    FIELD_DWORD(L"ProductID", device->dwProductID);
    FIELD(L"Location", device->szLocation);
    FIELD(L"MatchingDeviceID", device->szMatchingDeviceId);
    FIELD(L"UpperFilters", device->szUpperFilters);
    FIELD(L"LowerFilters", device->szLowerFilters);
    FIELD(L"Service", device->szService);
    FIELD(L"OEMData", device->szOEMData);
    FIELD(L"Flags1", device->szFlags1);
    FIELD(L"Flags2", device->szFlags2);
    FIELD_TODO(L"Drivers");

    if (device->child)
    {
        fields[id].type = XML_TYPE_CHILD;
        fields[id].child = malloc(sizeof(struct xml_information_block));
        if (!fields[id].child)
            return;
        memset(fields[id].child, 0, sizeof(struct xml_information_block));
        fields[id].child->tag_name = L"InputRelatedDevice";
        fill_input_related_device(device->child, fields[id].child->data);
    }
}

static inline void fill_input_related_devices(struct input_related_device* devices, struct xml_information_data* fields, ULONG len)
{
    ULONG i = 0;

    for (; i < len; i++)
    {
        fields[i].type = XML_TYPE_CHILD;
        fields[i].child = malloc(sizeof(struct xml_information_block));
        if (!fields[i].child)
            return;
        memset(fields[i].child, 0, sizeof(struct xml_information_block));
        fields[i].child->tag_name = L"InputRelatedDevice";
        fill_input_related_device(&devices[i], fields[i].child->data);
    }
}

static inline void fill_input_device(struct dxdiag_information* info, struct xml_information_data* fields, ULONG current)
{
    struct input_device* input = &info->input_info.inputs[current];
    DWORD id = 0;

    FIELD(L"DeviceName", input->szInstanceName);
    FIELD_BOOL(L"Attached", input->bAttached);
    FIELD_DWORD(L"JoystickID", input->dwJoystickID);
    FIELD_DWORD(L"VendorID", input->dwVendorID);
    FIELD_DWORD(L"ProductID", input->dwProductID);
    FIELD_DWORD(L"DevType", input->dwDevType);
    FIELD(L"FFDriverName", input->szFFDriverName);
    FIELD(L"FFDriverDateEnglish", input->szFFDriverDateEnglish);
    FIELD(L"FFDriverVersion", input->szFFDriverVersion);
    FIELD_DWORD(L"FFDriverSize", input->lFFDriverSize);
}

static inline void fill_input_devices(struct dxdiag_information* dxdiag, struct xml_information_data* fields)
{
    ULONG i = 0;

    for (; i < dxdiag->input_info.ulInputs; i++)
    {
        fields[i].type = XML_TYPE_CHILD;
        fields[i].child = malloc(sizeof(struct xml_information_block));
        if (!fields[i].child)
            return;
        memset(fields[i].child, 0, sizeof(struct xml_information_block));
        fields[i].child->tag_name = L"DirectInputDevice";
        fill_input_device(dxdiag, fields[i].child->data, i);
    }
}

static inline void fill_input(struct dxdiag_information* dxdiag_info, struct xml_information_data* fields)
{
    fields[0].type = XML_TYPE_CHILD;
    fields[0].child = malloc(sizeof(struct xml_information_block));
    if (!fields[0].child)
        return;
    memset(fields[0].child, 0, sizeof(struct xml_information_block));
    fields[0].child->tag_name = L"DirectInputDevices";
    fill_input_devices(dxdiag_info, fields[0].child->data);

    fields[1].type = XML_TYPE_CHILD;
    fields[1].child = malloc(sizeof(struct xml_information_block));
    if (!fields[1].child)
        return;
    memset(fields[1].child, 0, sizeof(struct xml_information_block));
    fields[1].child->tag_name = L"USBRoot";
    fill_input_related_devices(dxdiag_info->input_info.usbroots, fields[1].child->data, dxdiag_info->input_info.ulUSBRoots);

    fields[2].type = XML_TYPE_CHILD;
    fields[2].child = malloc(sizeof(struct xml_information_block));
    if (!fields[2].child)
        return;
    memset(fields[2].child, 0, sizeof(struct xml_information_block));
    fields[2].child->tag_name = L"GamePortDevices";
    fill_input_related_devices(dxdiag_info->input_info.gameports, fields[1].child->data, dxdiag_info->input_info.ulGameports);

    fields[3].type = XML_TYPE_CHILD;
    fields[3].child = malloc(sizeof(struct xml_information_block));
    if (!fields[3].child)
        return;
    memset(fields[3].child, 0, sizeof(struct xml_information_block));
    fields[3].child->tag_name = L"PS2Devices";
    fill_input_related_devices(dxdiag_info->input_info.ps2devices, fields[1].child->data, dxdiag_info->input_info.ulPS2Devices);

    fields[4].type = XML_TYPE_FIELD;
    fields[4].field.tag_name = L"PollWithInterrupt";
    wcscpy_s(fields[4].field.value, sizeof(fields[4].field.value), dxdiag_info->input_info.bPollFlags ? L"Yes" : L"No");

    // NT5 only
    fields[5].type = XML_TYPE_FIELD;
    fields[5].field.tag_name = L"Registry";
    wcscpy_s(fields[5].field.value, sizeof(fields[5].field.value), L"TODO: Fix");
}

static inline void fill_logical_disk(struct dxdiag_information* info, struct xml_information_data* fields, ULONG current)
{
    struct logical_disk* disk = &info->logical_disks[current];
    DWORD id = 0;

    FIELD(L"DriveLetter", disk->szDriveLetter);
    FIELD(L"FreeSpace", disk->szFreeSpace);
    FIELD(L"MaxSpace", disk->szMaxSpace);
    FIELD(L"FileSystem", disk->szFileSystem);
    FIELD(L"Model", disk->szModel);
    FIELD(L"PNPDeviceID", disk->szPNPDeviceID);
    FIELD_DWORD(L"HardDriveIndex", disk->dwHardDriveIndex);
    FIELD_TODO(L"Drivers");
}

static inline void fill_logical_disks(struct dxdiag_information* info, struct xml_information_data* fields)
{
    ULONG i = 0;

    for (; i < info->input_info.ulInputs; i++)
    {
        fields[i].type = XML_TYPE_CHILD;
        fields[i].child = malloc(sizeof(struct xml_information_block));
        if (!fields[i].child)
            return;
        memset(fields[i].child, 0, sizeof(struct xml_information_block));
        fields[i].child->tag_name = L"LogicalDisk";
        fill_logical_disk(info, fields[i].child->data, i);
    }
}

static inline void fill_system_device(struct dxdiag_information* info, struct xml_information_data* fields, ULONG current)
{
    struct system_device* disk = &info->system_devices[current];
    DWORD id = 0;

    FIELD(L"Name", disk->szDescription);
    FIELD(L"DeviceKey", disk->szDeviceID);
    FIELD_TODO(L"Drivers");
}

static inline void fill_system_devices(struct dxdiag_information* dxdiag, struct xml_information_data* fields)
{
    ULONG i = 0;

    for (; i < dxdiag->input_info.ulInputs; i++)
    {
        fields[i].type = XML_TYPE_CHILD;
        fields[i].child = malloc(sizeof(struct xml_information_block));
        if (!fields[i].child)
            return;
        memset(fields[i].child, 0, sizeof(struct xml_information_block));
        fields[i].child->tag_name = L"SystemDevice";
        fill_system_device(dxdiag, fields[i].child->data, i);
    }
}

static inline void fill_filter_devices(struct dxdiag_information* dxdiag, struct xml_information_data* fields)
{
    ULONG i = 0;

    for (; i < dxdiag->input_info.ulInputs; i++)
    {
        fields[i].type = XML_TYPE_CHILD;
        fields[i].child = malloc(sizeof(struct xml_information_block));
        if (!fields[i].child)
            return;
        memset(fields[i].child, 0, sizeof(struct xml_information_block));
        fields[i].child->tag_name = L"Filter";
        fill_system_device(dxdiag, fields[i].child->data, i);
    }
}

static inline void fill_net_service_provider(struct dxdiag_information* dxdiag, struct xml_information_data* fields, ULONG i)
{
    struct net_sp* sp = &dxdiag->network_info.service_provider[i];
    ULONG id = 0;

    FIELD(L"Name", sp->szNameEnglish);
    FIELD_TODO(L"Registry");
    FIELD(L"File", sp->szFile);
    FIELD(L"Version", sp->szVersionEnglish);
}

static inline void fill_net_service_providers(struct dxdiag_information* dxdiag, struct xml_information_data* fields)
{
    ULONG i = 0;

    for (; i < dxdiag->network_info.ulServiceProviders; i++)
    {
        fields[i].type = XML_TYPE_CHILD;
        fields[i].child = malloc(sizeof(struct xml_information_block));
        if (!fields[i].child)
            return;
        memset(fields[i].child, 0, sizeof(struct xml_information_block));
        fields[i].child->tag_name = L"DirectPlayServiceProvider";
        fill_net_service_provider(dxdiag, fields[i].child->data, i);
    }
}

static inline void fill_net_adapter(struct dxdiag_information* dxdiag, struct xml_information_data* fields, ULONG i)
{
    struct net_adapters* sp = &dxdiag->network_info.adapters[i];
    ULONG id = 0;

    FIELD(L"Name", sp->szAdapterName);
    FIELD(L"SPName", sp->szSPNameEnglish);
    FIELD(L"GUID", sp->szGuid);
    FIELD_DWORD(L"Flags", sp->dwFlags);
}

static inline void fill_net_adapters(struct dxdiag_information* dxdiag, struct xml_information_data* fields)
{
    ULONG i = 0;

    for (; i < dxdiag->network_info.ulAdapters; i++)
    {
        fields[i].type = XML_TYPE_CHILD;
        fields[i].child = malloc(sizeof(struct xml_information_block));
        if (!fields[i].child)
            return;
        memset(fields[i].child, 0, sizeof(struct xml_information_block));
        fields[i].child->tag_name = L"DirectPlayAdapters";
        fill_net_adapter(dxdiag, fields[i].child->data, i);
    }
}

static inline void fill_net_voicecodec(struct dxdiag_information* dxdiag, struct xml_information_data* fields, ULONG i)
{
    struct net_voicecodecs* sp = &dxdiag->network_info.voice_codecs[i];
    ULONG id = 0;

    FIELD(L"Name", sp->szName);
    FIELD(L"GUID", sp->szGuid);
    FIELD(L"Description", sp->szDescription);
    FIELD_DWORD(L"Flags", sp->dwFlags);
    FIELD_DWORD(L"MaxBitsPerSecond", sp->dwMaxBitsPerSecond);
}

static inline void fill_net_voicecodecs(struct dxdiag_information* dxdiag, struct xml_information_data* fields)
{
    ULONG i = 0;

    for (; i < dxdiag->network_info.ulVoiceCodecs; i++)
    {
        fields[i].type = XML_TYPE_CHILD;
        fields[i].child = malloc(sizeof(struct xml_information_block));
        if (!fields[i].child)
            return;
        memset(fields[i].child, 0, sizeof(struct xml_information_block));
        fields[i].child->tag_name = L"DirectPlayVoiceCodec";
        fill_net_voicecodec(dxdiag, fields[i].child->data, i);
    }
}

static inline void fill_network(struct dxdiag_information* dxdiag_info, struct xml_information_data* fields)
{
    fields[0].type = XML_TYPE_CHILD;
    fields[0].child = malloc(sizeof(struct xml_information_block));
    if (!fields[0].child)
        return;
    memset(fields[0].child, 0, sizeof(struct xml_information_block));
    fields[0].child->tag_name = L"DirectPlayServiceProviders";
    fill_net_service_providers(dxdiag_info, fields[0].child->data);

    fields[1].type = XML_TYPE_CHILD;
    fields[1].child = malloc(sizeof(struct xml_information_block));
    if (!fields[1].child)
        return;
    memset(fields[1].child, 0, sizeof(struct xml_information_block));
    fields[1].child->tag_name = L"DirectPlayLobbyableApps";
    // TODO!

    fields[2].type = XML_TYPE_CHILD;
    fields[2].child = malloc(sizeof(struct xml_information_block));
    if (!fields[2].child)
        return;
    memset(fields[2].child, 0, sizeof(struct xml_information_block));
    fields[2].child->tag_name = L"DirectPlayAdapters";
    fill_net_adapters(dxdiag_info, fields[0].child->data);

    fields[3].type = XML_TYPE_CHILD;
    fields[3].child = malloc(sizeof(struct xml_information_block));
    if (!fields[3].child)
        return;
    memset(fields[3].child, 0, sizeof(struct xml_information_block));
    fields[3].child->tag_name = L"DirectPlayVoiceCodecs";
    fill_net_voicecodecs(dxdiag_info, fields[0].child->data);

    fields[4].type = XML_TYPE_FIELD;
    fields[4].field.tag_name = L"Registry";
    wcscpy_s(fields[5].field.value, sizeof(fields[4].field.value), L"TODO: Fix");

    fields[4].type = XML_TYPE_FIELD;
    fields[4].field.tag_name = L"TestResults";
    wcscpy_s(fields[5].field.value, sizeof(fields[5].field.value), dxdiag_info->network_info.szTestResultEnglish);

    fields[5].type = XML_TYPE_FIELD;
    fields[5].field.tag_name = L"VoiceWizardFullDuplexTest";
    wcscpy_s(fields[5].field.value, sizeof(fields[5].field.value), dxdiag_info->network_info.szVoiceWizardFullDuplexTestEnglish);

    fields[6].type = XML_TYPE_FIELD;
    fields[6].field.tag_name = L"VoiceWizardHalfDuplexTest";
    wcscpy_s(fields[6].field.value, sizeof(fields[6].field.value), dxdiag_info->network_info.szVoiceWizardHalfDuplexTestEnglish);

    fields[7].type = XML_TYPE_FIELD;
    fields[7].field.tag_name = L"VoiceWizardMicTest";
    wcscpy_s(fields[7].field.value, sizeof(fields[7].field.value), dxdiag_info->network_info.szVoiceWizardMicTestEnglish);
}

static inline void fill_video_filter(struct dxdiag_information* dxdiag, struct xml_information_data* fields, ULONG i)
{
    struct video_showfilters* sp = &dxdiag->video_filters[i];
    ULONG id = 0;

    FIELD(L"Name", sp->szName);
    FIELD(L"FilterCatagory", sp->szCatName);
    FIELD_DWORD(L"Merit", sp->dwMerit);
    FIELD_DWORD(L"Inputs", sp->dwInputs);
    FIELD_DWORD(L"Outputs", sp->dwOutputs);
    FIELD(L"File", sp->szFileName);
    FIELD(L"FileVersion", sp->szFileVersion);
}

static inline void fill_video_render(struct dxdiag_information* dxdiag, struct xml_information_data* fields)
{
    ULONG id = 0;

    FIELD_TODO(L"PreferredDShowFilters");

    for (; id < dxdiag->ulVideoFilters; id++)
    {
        fields[id].type = XML_TYPE_CHILD;
        fields[id].child = malloc(sizeof(struct xml_information_block));
        if (!fields[id].child)
            return;
        memset(fields[id].child, 0, sizeof(struct xml_information_block));
        fields[id].child->tag_name = L"Filter";
        fill_video_filter(dxdiag, fields[id].child->data, id);
    }
}

static inline void fill_component(struct dxdiag_information* dxdiag, struct xml_information_data* fields, ULONG i)
{
    struct dx_components* sp = &dxdiag->files.components[i];
    ULONG id = 0;

    FIELD(L"Name", sp->szName);
    FIELD(L"Version", sp->szVersion);
    FIELD(L"Language", sp->szLanguageEnglish);
    FIELD_DWORD(L"Beta", sp->bBeta);
    FIELD_BOOL(L"Debug", sp->bDebug);
    FIELD(L"Date", sp->szDatestampEnglish);
    FIELD_DWORD(L"Size", sp->lNumBytes);
    FIELD_BOOL(L"Exists", sp->bExists);
    FIELD_BOOL(L"Problem", sp->bProblem);
}

static inline void fill_components(struct dxdiag_information* dxdiag, struct xml_information_data* fields)
{
    ULONG id = 0;

    for (; id < dxdiag->files.ulComponents; id++)
    {
        fields[id].type = XML_TYPE_CHILD;
        fields[id].child = malloc(sizeof(struct xml_information_block));
        if (!fields[id].child)
            return;
        memset(fields[id].child, 0, sizeof(struct xml_information_block));
        fields[id].child->tag_name = L"File";
        fill_component(dxdiag, fields[id].child->data, id);
    }
}

static BOOL serialize_field(IXMLDOMDocument* xmldoc, IXMLDOMElement* parent_element, struct xml_information_block* table)
{
    IXMLDOMElement* info_element = xml_create_element(xmldoc, table->tag_name);
    const struct xml_information_data* fields = table->data;
    unsigned int j = 0;
    HRESULT hr;

    if (!info_element)
        return FALSE;

    hr = IXMLDOMElement_appendChild(parent_element, (IXMLDOMNode*)info_element, NULL);
    if (FAILED(hr))
    {
        IXMLDOMElement_Release(info_element);
        return FALSE;
    }

    for (j = 0; fields[j].type; j++)
    {
        if (fields[j].type == XML_TYPE_FIELD)
        {
            IXMLDOMElement* field_element = xml_create_element(xmldoc, fields[j].field.tag_name);

            if (!field_element)
            {
                IXMLDOMElement_Release(info_element);
                return FALSE;
            }

            hr = xml_put_element_text(field_element, fields[j].field.value);
            if (FAILED(hr))
            {
                IXMLDOMElement_Release(field_element);
                IXMLDOMElement_Release(info_element);
                return FALSE;
            }

            hr = IXMLDOMElement_appendChild(info_element, (IXMLDOMNode*)field_element, NULL);
            if (FAILED(hr))
            {
                IXMLDOMElement_Release(field_element);
                IXMLDOMElement_Release(info_element);
                return FALSE;
            }

            IXMLDOMElement_Release(field_element);
        }
        else if (fields[j].type == XML_TYPE_CHILD)
        {
            if (!serialize_field(xmldoc, info_element, fields[j].child))
            {
                IXMLDOMElement_Release(info_element);
                return FALSE;
            }
        }
    }

    IXMLDOMElement_Release(info_element);
    return TRUE;
}

static void free_field(struct xml_information_block* blk)
{
    unsigned int j = 0;

    for (j = 0; blk->data[j].type; j++)
    {
        if (blk->data[j].type == XML_TYPE_CHILD)
        {
            free_field(blk->data[j].child);
            free(blk->data[j].child);
        }
    }
}

BOOL output_xml_information(struct dxdiag_information* dxdiag_info, const WCHAR* filename)
{
    struct xml_information_block output_table[] =
    {
        {L"SystemInformation"},
        {L"DxDiagNotes"},
        {L"DirectXDebugLevels"},
        {L"DisplayDevices"},
        {L"DirectSound"},
        {L"DirectMusic"}, // nt5 only
        {L"VideoCaptureDevices"}, // nt6+
        {L"DirectInput"},
        {L"DirectPlay"}, // nt5 only
        {L"LogicalDisks"}, // nt6+
        {L"SystemDevices"}, // nt6+
        {L"DirectXComponents"}, // nt5 only
        {L"DirectShow"},
        {L"MediaFoundation"}, // nt6+
        {L"EvrPowerInformation"}, // nt6+
        {L"Diagnostics"}, // nt6+
    };

    IXMLDOMDocument* xmldoc = NULL;
    IXMLDOMElement* dxdiag_element = NULL;
    HRESULT hr;
    size_t i;

    fill_system_xml_output_table(dxdiag_info, output_table[0].data);
    fill_dxdiag_notes(dxdiag_info, output_table[1].data);
    fill_dxdebug_levels(dxdiag_info, output_table[2].data);
    fill_display_devices(dxdiag_info, output_table[3].data);
    fill_sound(dxdiag_info, output_table[4].data);
    fill_music(dxdiag_info, output_table[5].data);
    //fill_videocap_device(dxdiag_info, output_table[6].data);
    fill_input(dxdiag_info, output_table[7].data);
    fill_network(dxdiag_info, output_table[8].data);
    fill_logical_disks(dxdiag_info, output_table[9].data);
    fill_system_devices(dxdiag_info, output_table[10].data);
    fill_components(dxdiag_info, output_table[11].data);
    fill_video_render(dxdiag_info, output_table[12].data);
    //fill_mediafond(dxdiag_info, output_table[13].data);
    //fill_powerinfo(dxdiag_info, output_table[14].data);
    //fill_diagnostics(dxdiag_info, output_table[15].data);

    hr = CoCreateInstance(&CLSID_DOMDocument, NULL, CLSCTX_INPROC_SERVER,
        &IID_IXMLDOMDocument, (void**)&xmldoc);
    if (FAILED(hr))
    {
        WINE_ERR("IXMLDOMDocument instance creation failed with 0x%08lx\n", hr);
        goto error;
    }

    if (!(dxdiag_element = xml_create_element(xmldoc, L"DxDiag")))
        goto error;

    hr = IXMLDOMDocument_appendChild(xmldoc, (IXMLDOMNode*)dxdiag_element, NULL);
    if (FAILED(hr))
        goto error;


    for (i = 0; i < ARRAY_SIZE(output_table); i++)
    {
        if (!serialize_field(xmldoc, dxdiag_element, &output_table[i]))
            goto error;
    }

    hr = save_xml_document(xmldoc, filename);
    if (FAILED(hr))
        goto error;

    IXMLDOMElement_Release(dxdiag_element);
    IXMLDOMDocument_Release(xmldoc);
    return TRUE;
error:
    for (i = 0; i < ARRAY_SIZE(output_table); i++)
    {
        free_field(&output_table[i]);
    }
    if (dxdiag_element) IXMLDOMElement_Release(dxdiag_element);
    if (xmldoc) IXMLDOMDocument_Release(xmldoc);
    return FALSE;
}
