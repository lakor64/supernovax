/*
 * PROJECT:     SupernovaX Diagnostic Tool
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     Display information parsing
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */
#include "precomp.h"
#include "information.h"

WINE_DEFAULT_DEBUG_CHANNEL(dxdiag);

#define DISPLAY_CONTAINER_NAME L"DxDiag_DisplayDevices"
#define DISPLAY_ACTION_NAME L"GetDisplayInfo"

static void fill_display_property_list(PDXDIAG_DISPLAY_DEVICE_INFO var, PDXDIAG_INFO_PROPERTY_LIST list)
{
    list[0].property_name = L"szDescription";
    list[0].output.wchar = &var->szDescription;
    list[1].property_name = L"szManufacturer";
    list[1].output.wchar = &var->szManufacturer;
    list[2].property_name = L"szChipType";
    list[2].output.wchar = &var->szChipType;
    list[3].property_name = L"szDACType";
    list[3].output.wchar = &var->szDACType;
    list[4].property_name = L"szKeyDeviceID";
    list[4].output.wchar = &var->szKeyDeviceID;
    list[5].property_name = L"szNotesEnglish";
    list[5].output.wchar = &var->szNotesEnglish;
    list[6].property_name = L"szDisplayModeEnglish";
    list[6].output.wchar = &var->szDisplayModeEnglish;
    list[7].property_name = L"szDisplayModeLocalized";
    list[7].output.wchar = &var->szDisplayModeLocalized;
    list[8].property_name = L"szDriverModelEnglish";
    list[8].output.wchar = &var->szDriverModelEnglish;
    list[9].property_name = L"szVdd";
    list[9].output.wchar = &var->szVdd;
    list[10].property_name = L"szMiniVddDateEnglish";
    list[10].output.wchar = &var->szMiniVddDateEnglish;
    list[11].property_name = L"szDriverLanguageEnglish";
    list[11].output.wchar = &var->szDriverLanguageEnglish;
    list[12].property_name = L"szDisplayMemoryEnglish";
    list[12].output.wchar = &var->szDisplayMemoryEnglish;
    list[13].property_name = L"szDisplayMemoryLocalized";
    list[13].output.wchar = &var->szDisplayMemoryLocalized;
    list[14].property_name = L"szAGPStatusEnglish";
    list[14].output.wchar = &var->szAGPStatusEnglish;
    list[15].property_name = L"szD3DStatusEnglish";
    list[15].output.wchar = &var->szD3DStatusEnglish;
    list[16].property_name = L"szDXVAHDEnglish";
    list[16].output.wchar = &var->szDXVAHDEnglish;
    list[17].property_name = L"szDriverDateEnglish";
    list[17].output.wchar = &var->szDriverDateEnglish;
    list[18].property_name = L"szMiniVdd";
    list[18].output.wchar = &var->szMiniVdd;
    list[19].property_name = L"szVendorId";
    list[19].output.wchar = &var->szVendorId;
    list[20].property_name = L"szDeviceId";
    list[20].output.wchar = &var->szDeviceId;
    list[21].property_name = L"szSubSysId";
    list[21].output.wchar = &var->szSubSysId;
    list[22].property_name = L"szRevisionId";
    list[22].output.wchar = &var->szRevisionId;
    list[23].property_name = L"szDriverNodeStrongName";
    list[23].output.wchar = &var->szDriverNodeStrongName;
    list[24].property_name = L"szRankOfInstalledDriver";
    list[24].output.wchar = &var->szRankOfInstalledDriver;
    list[25].property_name = L"szDeviceIdentifier";
    list[25].output.wchar = &var->szDeviceIdentifier;
    list[26].property_name = L"szMonitorName";
    list[26].output.wchar = &var->szMonitorName;
    list[27].property_name = L"szMonitorMaxRes";
    list[27].output.wchar = &var->szMonitorMaxRes;
    list[28].property_name = L"szDriverName";
    list[28].output.wchar = &var->szDriverName;
    list[29].property_name = L"szDriverVersion";
    list[29].output.wchar = &var->szDriverVersion;
    list[30].property_name = L"szDriverAssemblyVersion";
    list[30].output.wchar = &var->szDriverAssemblyVersion;
    list[31].property_name = L"szDXVAModes";
    list[31].output.wchar = &var->szDXVAModes;
    list[32].property_name = L"szGuid";
    list[32].output.wchar = &var->szGuid;
    list[33].property_name = L"szOverlayEnglish";
    list[33].output.wchar = &var->szOverlayEnglish;
    list[34].property_name = L"szDriverSignDate";
    list[34].output.wchar = &var->szDriverSignDate;
    list[35].property_name = L"szDDIVersionEnglish";
    list[35].output.wchar = &var->szDDIVersionEnglish;
    list[36].property_name = L"szDDStatusEnglish";
    list[36].output.wchar = &var->szDDStatusEnglish;
    list[37].property_name = L"szTestResultDDEnglish";
    list[37].output.wchar = &var->szTestResultDDEnglish;
    list[38].property_name = L"szTestResultD3D7English";
    list[38].output.wchar = &var->szTestResultD3D7English;
    list[39].property_name = L"szTestResultD3D8English";
    list[39].output.wchar = &var->szTestResultD3D8English;
    list[40].property_name = L"szTestResultD3D9English";
    list[40].output.wchar = &var->szTestResultD3D9English;
    list[41].property_name = L"szDXVA2Modes";
    list[41].output.wchar = &var->szDXVA2Modes;
    list[42].property_name = L"szGraphicsPreemptionGranularity";
    list[42].output.wchar = &var->szGraphicsPreemptionGranularity;
    list[43].property_name = L"szComputePreemptionGranularity";
    list[43].output.wchar = &var->szComputePreemptionGranularity;
    list[44].property_name = L"szMiracast";
    list[44].output.wchar = &var->szMiracast;
    list[45].property_name = L"szHybridGraphicsGPUType";
    list[45].output.wchar = &var->szHybridGraphicsGPUType;
    list[46].property_name = L"szPowerManagementPStates";
    list[46].output.wchar = &var->szPowerManagementPStates;
    list[47].property_name = L"szMPOMaxPlanes";
    list[47].output.wchar = &var->szMPOMaxPlanes;
    list[48].property_name = L"szMPOCaps";
    list[48].output.wchar = &var->szMPOCaps;
    list[49].property_name = L"szMPOStretch";
    list[49].output.wchar = &var->szMPOStretch;
    list[50].property_name = L"szMPOHints";
    list[50].output.wchar = &var->szMPOHints;
    list[51].property_name = L"szMPOFormats";
    list[51].output.wchar = &var->szMPOFormats;
    list[52].property_name = L"szPanelFitterCaps";
    list[52].output.wchar = &var->szPanelFitterCaps;
    list[53].property_name = L"szPanelFitterStretch";
    list[53].output.wchar = &var->szPanelFitterStretch;
    list[54].property_name = L"szHardwareSchedulingAttributes";
    list[54].output.wchar = &var->szHardwareSchedulingAttributes;
    list[55].property_name = L"szDisplayableSupport";
    list[55].output.wchar = &var->szDisplayableSupport;
    list[56].property_name = L"szDriverCatalogAttributes";
    list[56].output.wchar = &var->szDriverCatalogAttributes;
    list[57].property_name = L"szBlockList";
    list[57].output.wchar = &var->szBlockList;
    list[58].property_name = L"szVirtualGPUSupport";
    list[58].output.wchar = &var->szVirtualGPUSupport;
    list[59].property_name = L"szDeviceProblemCode";
    list[59].output.wchar = &var->szDeviceProblemCode;
    list[60].property_name = L"szDriverProblemCode";
    list[60].output.wchar = &var->szDriverProblemCode;
    list[61].property_name = L"szDeviceStatus";
    list[61].output.wchar = &var->szDeviceStatus;
    list[62].property_name = L"szHDRSupportEnglish";
    list[62].output.wchar = &var->szHDRSupportEnglish;
    list[63].property_name = L"szTopology";
    list[63].output.wchar = &var->szTopology;
    list[64].property_name = L"szColorSpace";
    list[64].output.wchar = &var->szColorSpace;
    list[65].property_name = L"szColorPrimaries";
    list[65].output.wchar = &var->szColorPrimaries;
    list[66].property_name = L"szLuminance";
    list[66].output.wchar = &var->szLuminance;
    list[67].property_name = L"lMiniVddSize";
    list[67].output.ulong = &var->lMiniVddSize;
    list[68].property_name = L"lDriverSize";
    list[68].output.ulong = &var->lDriverSize;
    list[69].property_name = L"dwDedicatedVideoMemory";
    list[69].output.ulong = &var->dwDedicatedVideoMemory;
    list[70].property_name = L"dwSharedVideoMemory";
    list[70].output.ulong = &var->dwSharedVideoMemory;
    list[71].property_name = L"bDriverDebug";
    list[71].output.boool = &var->bDriverDebug;
    list[72].property_name = L"bDriverBeta";
    list[72].output.boool = &var->bDriverBeta;
    list[73].property_name = L"bDetachable";
    list[73].output.boool = &var->bDetachable;
    list[74].property_name = L"szFeatureLevelEnglish";
    list[74].output.wchar = &var->szFeatureLevelEnglish;
    list[75].property_name = L"bPostDevice";
    list[75].output.boool = &var->bPostDevice;
#if 0
    list[74].property_name = L"bEotf2084Supported";
    list[74].output.boool = &var->bEotf2048Supported;
    list[75].property_name = L"bBT2020YCC";
    list[75].output.boool = &var->bBT2020YCC;
    list[76].property_name = L"bBT2020RGB";
    list[76].output.boool = &var->bBT2020RGB;
    list[77].property_name = L"bAdvancedColorEnabled";
    list[77].output.boool = &var->bAdvancedColorEnabled;
    list[78].property_name = L"bAdvancedColorSupported";
    list[78].output.boool = &var->bAdvancedColorSupported;
    list[79].property_name = L"bCheckedMonitorCapabilities";
    list[79].output.boool = &var->bCheckedMonitorCapabilities;
    list[80].property_name = L"szPixelFormat";
    list[80].output.wchar = &var->szPixelFormat;
    list[81].property_name = L"szWmiUserFriendlyName";
    list[81].output.wchar = &var->szWmiUserFriendlyName;
    list[82].property_name = L"szWmiPerferredMonitorSourceMode";
    list[82].output.wchar = &var->szWmiPerferredMonitorSourceMode;
    list[83].property_name = L"szWmiManufacturerName";
    list[83].output.wchar = &var->szWmiManufacturerName;
    list[84].property_name = L"szWmiProductCodeID";
    list[84].output.wchar = &var->szWmiProductCodeID;
    list[85].property_name = L"szWmiVideoOutputTechnology";
    list[85].output.wchar = &var->szWmiVideoOutputTechnology;
#endif
}

static void fill_dxva_caps_data(PDXDIAG_DISPLAY_DXVA_INFO var, PDXDIAG_INFO_PROPERTY_LIST list)
{
    list[0].property_name = L"dwNumPreviousOutputFrames";
    list[0].output.ulong = &var->dwNumPreviousOutputFrames;
    list[1].property_name = L"dwNumForwardRefSamples";
    list[1].output.ulong = &var->dwNumForwardRefSamples;
    list[2].property_name = L"dwNumBackwardRefSamples";
    list[2].output.ulong = &var->dwNumBackwardRefSamples;
    list[3].property_name = L"szGuid";
    list[3].output.wchar = &var->szGuid;
    list[4].property_name = L"szCaps";
    list[4].output.wchar = &var->szCaps;
    list[5].property_name = L"szD3DInputFormat";
    list[5].output.wchar = &var->szD3DInputFormat;
    list[6].property_name = L"szD3DOutputFormat";
    list[6].output.wchar = &var->szD3DOutputFormat;
}

static void fill_dxva_caps(PDXDIAG_INFO_CONTEXT ctx, PDXDIAG_DISPLAY_DEVICE_INFO dev, IDxDiagContainer* root)
{
    HRESULT hr;
    DXDIAG_INFO_PROPERTY_LIST dxva_list[7];
    DWORD i = 0;
    IDxDiagContainer* child = NULL;
    WCHAR data[255];

    dev->dwDXVALength = 0;
    hr = IDxDiagContainer_GetNumberOfChildContainers(root, &dev->dwDXVALength);
    if (FAILED(hr))
    {
        WINE_ERR("DXVA Caps get number of childs fail 0x%08lx\n", hr);
        return;
    }

    dev->aDXVAInfo = (PDXDIAG_DISPLAY_DXVA_INFO)malloc(sizeof(DXDIAG_DISPLAY_DXVA_INFO) * dev->dwDXVALength);

    if (!dev->aDXVAInfo)
        return;

    for (i = 0; i < dev->dwDXVALength; i++)
    {
        DWORD q = 0;

        hr = IDxDiagContainer_EnumChildContainerNames(root, i, data, sizeof(data) / sizeof(WCHAR));
        if (FAILED(hr))
            return;

        hr = IDxDiagContainer_GetChildContainer(root, data, &child);
        if (FAILED(hr))
            return;

        fill_dxva_caps_data(&dev->aDXVAInfo[i], dxva_list);

        for (; q < ARRAY_SIZE(dxva_list); q++)
        {
            property_to_data(child, dxva_list[q].property_name, &dxva_list[q].output);
        }

        IDxDiagContainer_Release(child);
    }
}

BOOL fill_display_information_notes_only(PDXDIAG_INFO_CONTEXT ctx, PDXDIAG_INFO dxdiag_info, ULONG id)
{
    DXDIAG_INFO_PROPERTY_LIST property_list;
    WCHAR data[255];
    IDxDiagContainer* child, * root;
    HRESULT hr;

    if (dxdiag_info->ulDisplays < 1)
        return TRUE;

    if (!dxdiag_info->display_devices || dxdiag_info->ulDisplays < id)
        return FALSE;
    
    if (!exec_method(ctx, DISPLAY_ACTION_NAME, 1))
    {
        return FALSE;
    }

    root = get_child_container(ctx, DISPLAY_CONTAINER_NAME);

    hr = IDxDiagContainer_EnumChildContainerNames(root, id, data, sizeof(data) / sizeof(WCHAR));
    if (FAILED(hr))
    {
        WINE_ERR("Cannot enum display child name 0x%08lx\n", hr);
        IDxDiagContainer_Release(root);
        return FALSE;
    }

    hr = IDxDiagContainer_GetChildContainer(root, data, &child);
    if (FAILED(hr))
    {
        WINE_ERR("Cannot enum display child container 0x%08lx\n", hr);
        IDxDiagContainer_Release(root);
        return FALSE;
    }

    property_list.property_name = L"szNotesEnglish";
    property_list.output.wchar = &dxdiag_info->display_devices[id].szNotesEnglish;

    property_to_data(child, property_list.property_name, &property_list.output);

    IDxDiagContainer_Release(root);
    IDxDiagContainer_Release(child);

    return TRUE;
}

BOOL fill_display_information(PDXDIAG_INFO_CONTEXT ctx, PDXDIAG_INFO dxdiag_info, ULONG id)
{
    size_t i;
    DXDIAG_INFO_PROPERTY_LIST property_list[88-12];
    WCHAR data[255];
    IDxDiagContainer* child, * root;
    HRESULT hr;
    DWORD subCount = 0;

    if (dxdiag_info->ulDisplays < 1)
        return TRUE;

    if (!dxdiag_info->display_devices || dxdiag_info->ulDisplays < id)
        return FALSE;

    for (i = 1; i < 6; i++)
    {
        if (!exec_method(ctx, DISPLAY_ACTION_NAME, i)) // probably this is the version
        {
            return FALSE;
        }
    }

    root = get_child_container(ctx, DISPLAY_CONTAINER_NAME);

    hr = IDxDiagContainer_EnumChildContainerNames(root, id, data, sizeof(data) / sizeof(WCHAR));
    if (FAILED(hr))
    {
        WINE_ERR("Cannot enum display child name 0x%08lx\n", hr);
        IDxDiagContainer_Release(root);
        return FALSE;
    }

    hr = IDxDiagContainer_GetChildContainer(root, data, &child);
    if (FAILED(hr))
    {
        WINE_ERR("Cannot enum display child container 0x%08lx\n", hr);
        IDxDiagContainer_Release(root);
        return FALSE;
    }

    fill_display_property_list(&dxdiag_info->display_devices[id], property_list);

    for (i = 0; i < ARRAY_SIZE(property_list); i++)
    {
        property_to_data(child, property_list[i].property_name, &property_list[i].output);

        hr = IDxDiagContainer_GetNumberOfChildContainers(child, &subCount);

        while (SUCCEEDED(hr) && subCount > 0)
        {
            hr = IDxDiagContainer_EnumChildContainerNames(child, 0, data, sizeof(data) / sizeof(WCHAR));
            if (SUCCEEDED(hr))
            {
                IDxDiagContainer* subdata = NULL;

                if (wcscmp(data, L"DXVADeinterlaceCaps") == 0)
                {
                    hr = IDxDiagContainer_GetChildContainer(child, data, &subdata);
                    if (SUCCEEDED(hr))
                    {
                        fill_dxva_caps(ctx, &dxdiag_info->display_devices[id], subdata);
                        IDxDiagContainer_Release(subdata);
                    }
                }
                else
                {
                    WINE_TRACE("Unknown display device child: %S\n", data);
                }
            }

            subCount--;
        }
    }

    IDxDiagContainer_Release(root);
    IDxDiagContainer_Release(child);

    return TRUE;
}

void free_display_information(PDXDIAG_INFO dxdiag_info, ULONG id)
{
    PDXDIAG_DISPLAY_DEVICE_INFO var = NULL;

    if (!dxdiag_info->display_devices || dxdiag_info->ulDisplays > id)
        return;

    var = &dxdiag_info->display_devices[id];

    free(var->szDescription);
    free(var->szManufacturer);
    free(var->szChipType);
    free(var->szDACType);
    free(var->szKeyDeviceID);
    free(var->szNotesEnglish);
    free(var->szDisplayModeEnglish);
    free(var->szDisplayModeLocalized);
    free(var->szDriverModelEnglish);
    free(var->szVdd);
    free(var->szMiniVddDateEnglish);
    free(var->szDriverLanguageEnglish);
    free(var->szDisplayMemoryEnglish);
    free(var->szDisplayMemoryLocalized);
    free(var->szAGPStatusEnglish);
    free(var->szD3DStatusEnglish);
    free(var->szDXVAHDEnglish);
    free(var->szDriverDateEnglish);
    free(var->szMiniVdd);
    free(var->szVendorId);
    free(var->szDeviceId);
    free(var->szSubSysId);
    free(var->szRevisionId);
    free(var->szDriverNodeStrongName);
    free(var->szRankOfInstalledDriver);
    free(var->szDeviceIdentifier);
    free(var->szMonitorName);
    free(var->szMonitorMaxRes);
    free(var->szDriverName);
    free(var->szDriverVersion);
    free(var->szDriverAssemblyVersion);
    free(var->szDXVAModes);
    free(var->szGuid);
    free(var->szOverlayEnglish);
    free(var->szDriverSignDate);
    free(var->szDDIVersionEnglish);
    free(var->szDDStatusEnglish);
    free(var->szTestResultDDEnglish);
    free(var->szTestResultD3D7English);
    free(var->szTestResultD3D8English);
    free(var->szTestResultD3D9English);
    free(var->szDXVA2Modes);
    free(var->szGraphicsPreemptionGranularity);
    free(var->szComputePreemptionGranularity);
    free(var->szMiracast);
    free(var->szHybridGraphicsGPUType);
    free(var->szPowerManagementPStates);
    free(var->szMPOMaxPlanes);
    free(var->szMPOCaps);
    free(var->szMPOStretch);
    free(var->szMPOHints);
    free(var->szMPOFormats);
    free(var->szPanelFitterCaps);
    free(var->szPanelFitterStretch);
    free(var->szHardwareSchedulingAttributes);
    free(var->szDisplayableSupport);
    free(var->szDriverCatalogAttributes);
    free(var->szBlockList);
    free(var->szVirtualGPUSupport);
    free(var->szDeviceProblemCode);
    free(var->szDriverProblemCode);
    free(var->szDeviceStatus);
    free(var->szHDRSupportEnglish);
    free(var->szTopology);
    free(var->szColorSpace);
    free(var->szColorPrimaries);
    free(var->szLuminance);
    free(var->szPixelFormat);
    free(var->szWmiUserFriendlyName);
    free(var->szWmiPerferredMonitorSourceMode);
    free(var->szWmiManufacturerName);
    free(var->szWmiProductCodeID);
    free(var->szWmiVideoOutputTechnology);
    free(var->szFeatureLevelEnglish);

    memset(var, 0, sizeof(*var));
}

BOOL refresh_display_container(PDXDIAG_INFO_CONTEXT ctx, PDXDIAG_INFO dxdiag_info)
{
    IDxDiagContainer* child;
    DWORD count;
    HRESULT hr;
    ULONG i = 0;

    if (!exec_method(ctx, DISPLAY_ACTION_NAME, 1))
    {
        return FALSE;
    }

    child = get_child_container(ctx, DISPLAY_CONTAINER_NAME);
    if (!child)
    {
        return FALSE;
    }

    hr = IDxDiagContainer_GetNumberOfChildContainers(child, &count);

    if (FAILED(hr))
    {
        WINE_ERR("IDxDiagContainer_GetNumberOfChildContainers display fail HR=0x%08lx\n", hr);
        IDxDiagContainer_Release(child);
        return FALSE;
    }

    if (!dxdiag_info->display_devices || dxdiag_info->ulDisplays != count)
    {
        if (dxdiag_info->display_devices)
        {
            for (; i < dxdiag_info->ulDisplays; i++)
            {
                free_display_information(dxdiag_info, i);
            }

            free(dxdiag_info->display_devices);
        }

        dxdiag_info->ulDisplays = count;
        dxdiag_info->display_devices = (PDXDIAG_DISPLAY_DEVICE_INFO)malloc(sizeof(DXDIAG_DISPLAY_DEVICE_INFO) * count);
        memset(dxdiag_info->display_devices, 0, sizeof(DXDIAG_DISPLAY_DEVICE_INFO) * count);
    }

    IDxDiagContainer_Release(child);
    return dxdiag_info->display_devices != NULL;
}
