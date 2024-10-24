/*
 * PROJECT:     SupernovaX Diagnostic Tool
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     XML Display output
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */
#include "precomp.h"
#include "output_xml.h"
#include "info/information.h"

static inline LPWSTR get_step_name(DWORD step)
{
    if (step == 1)
        return L"KB";
    else if (step == 2)
        return L"MB";

    return L"B";
}

static LPWSTR translate_to_mb(DWORD p)
{
    DWORD step = 0, p2 = (DWORD)(p / 1024);
    LPWSTR buf = (LPWSTR)malloc(sizeof(LPWSTR) * 51);

    if (!buf)
        return NULL;

    memset(buf, 0, sizeof(LPWSTR) * 51);

    while (p2 > 0 && step < 2) // limit to MB
    {
        p = p2;
        p2 /= 1024;
        step++;
    }

    _snwprintf_s(buf, 51, 50, L"%u %s", p, get_step_name(step));
    return buf;
}

static LPWSTR merge_two_str(LPWSTR a, LPWSTR b)
{
    size_t rl;
    LPWSTR buf;

    if (!a || !b)
        return NULL;

    rl = wcslen(a) + wcslen(b) + 1;
    buf = (LPWSTR)malloc(sizeof(LPWSTR) * rl);
    if (!buf)
        return NULL;

    _snwprintf_s(buf, rl, rl - 1, L"%s%s", a, b);
    return buf;
}

static BOOL fill_single_dxva(PXML_INFORMATION_DATA fields, PDXDIAG_DISPLAY_DXVA_INFO dxva)
{
    DWORD id = 0;

    FIELD_NW(L"GUID", dxva->szGuid);
    FIELD_NW(L"D3DInputFormat", dxva->szD3DInputFormat);
    FIELD_NW(L"D3DOutputFormat", dxva->szD3DOutputFormat);
    FIELD_NW(L"Caps", dxva->szCaps);
    FIELD_DWORD(L"NumPreviousOutputFrames", dxva->dwNumPreviousOutputFrames);
    FIELD_DWORD(L"NumForwardRefSamples", dxva->dwNumForwardRefSamples);
    FIELD_DWORD(L"NumBackwardRefSamples", dxva->dwNumBackwardRefSamples);
    return TRUE;
}

static BOOL fill_dxva_caps(PXML_INFORMATION_DATA fields, PDXDIAG_DISPLAY_DXVA_INFO dxva, ULONG sz)
{
    ULONG i = 0;

    if (!dxva || sz < 1)
        return TRUE;

    for (; i < sz; i++)
    {
        if (!xml_new_child(&fields[i], L"DXVADeinterlaceCap"))
            return FALSE;

        if (!fill_single_dxva(fields[i].child->data, &dxva[i]))
            return FALSE;
    }

    return TRUE;
}

static BOOL fill_display_device(PDXDIAG_INFO dxdiag_info, PXML_INFORMATION_DATA fields, ULONG current)
{
    PDXDIAG_DISPLAY_DEVICE_INFO display = &dxdiag_info->display_devices[current];
    DWORD id = 0;

    FIELD_NW(L"CardName", display->szDescription);
    FIELD_NW(L"Manufacturer", display->szManufacturer);
    FIELD_NW(L"ChipType", display->szChipType);
    FIELD_NW(L"DACType", display->szDACType);
    FIELD_NW(L"DeviceType", display->bPostDevice ? L"Full Device (POST)" : L"TODO: Fix");
    FIELD_NW(L"DeviceKey", display->szKeyDeviceID);
    FIELD_NW(L"DeviceStatus", display->szDeviceStatus); // nt6+
    FIELD_NW(L"DeviceProblemCode", display->szDeviceProblemCode); // nt6+
    FIELD_NW(L"DriverProblemCode", display->szDriverProblemCode); // nt6+
    FIELD_NW(L"DisplayMemory", display->szDisplayMemoryEnglish);
    FIELD(L"DedicatedMemory", translate_to_mb(display->dwDedicatedVideoMemory)); // nt6+
    FIELD(L"SharedMemory", translate_to_mb(display->dwSharedVideoMemory)); // nt6+
    FIELD_NW(L"CurrentMode", display->szDisplayModeEnglish);
    FIELD_NW(L"HDRSupport", display->szHDRSupportEnglish); // nt6+
    FIELD_NW(L"Topology", display->szTopology); // nt6+
    FIELD_NW(L"ColorSpace", display->szColorSpace); // nt6+
    FIELD_NW(L"ColorPrimaries", display->szColorPrimaries); // nt6+
    FIELD_NW(L"Luminance", display->szLuminance); // nt6+
    FIELD_NW(L"MonitorName", display->szMonitorName); // nt6+

    // from monitor info
    FIELD_TODO(L"Monitor"); // nt5 only
    FIELD_NW(L"MonitorModel", display->szWmiUserFriendlyName); // nt6+
    FIELD(L"MonitorId", merge_two_str(display->szWmiManufacturerName, display->szWmiProductCodeID)); // nt6+
    FIELD_NW(L"NativeMode", display->szWmiPerferredMonitorSourceMode); // nt6+
    FIELD_NW(L"OutputType", display->szWmiVideoOutputTechnology); // nt6+
    FIELD_BOOL(L"Eotf2084Supported", display->bEotf2048Supported); // nt6+
    FIELD_BOOL(L"BT2020YCC", display->bBT2020YCC); // nt6+
    FIELD_BOOL(L"BT2020RGB", display->bBT2020RGB); // nt6+
    FIELD_BOOL(L"AdvancedColorEnabled", display->bAdvancedColorEnabled); // nt6+
    FIELD_BOOL(L"AdvancedColorSupported", display->bAdvancedColorSupported); // nt6+
    FIELD_BOOL(L"bCheckedMonitorCapabilities", display->bCheckedMonitorCapabilities); // nt6+
    FIELD_NW(L"PixelFormat", display->szPixelFormat); // nt6+
    // end of monitor info

    FIELD_NW(L"MonitorMaxRes", display->szMonitorMaxRes);
    FIELD_NW(L"DriverName", display->szDriverName);
    FIELD_NW(L"DriverFileVersion", display->szDriverVersion); // nt6+
    FIELD_NW(L"DriverVersion", display->szDriverAssemblyVersion);
    FIELD_NW(L"DriverLanguage", display->szDriverLanguageEnglish);
    FIELD_NW(L"DDIVersion", display->szDDIVersionEnglish);
    FIELD(L"FeatureLevels", display->szFeatureLevelEnglish); // nt6+
    FIELD_NW(L"DriverModel", display->szDriverModelEnglish); // nt6+
    FIELD_BOOL(L"DriverBeta", display->bDriverBeta);
    FIELD_BOOL(L"DriverDebug", display->bDriverDebug);
    FIELD_NW(L"DriverDate", display->szDriverDateEnglish);
    FIELD_DWORD(L"DriverSize", display->lDriverSize);
    FIELD_TODO(L"DriverWHQLLogo");
    FIELD_NW(L"WHQLDateStamp", display->szDriverSignDate);
    FIELD_NW(L"VDD", display->szVdd);
    FIELD_NW(L"MiniVDD", display->szMiniVdd);
    FIELD_NW(L"MiniVDDDate", display->szMiniVddDateEnglish);
    FIELD_DWORD(L"MiniVDDSize", display->lMiniVddSize);
    FIELD_NW(L"DeviceIdentifier", display->szDeviceIdentifier);
    FIELD_NW(L"VendorID", display->szVendorId);
    FIELD_NW(L"DeviceID", display->szDeviceId);
    FIELD_NW(L"SubSysID", display->szSubSysId);
    FIELD_NW(L"RevisionID", display->szRevisionId);
    FIELD_NW(L"DriverNodeStrongName", display->szDriverNodeStrongName); // nt6+
    FIELD_NW(L"RankOfInstalledDriver", display->szRankOfInstalledDriver); // nt6+
    FIELD_NW(L"DXVAModes", display->szDXVAModes);
    FIELD_NW(L"DXVA2Modes", display->szDXVA2Modes); // nt6+
    FIELD_NW(L"GraphicsPreemption", display->szGraphicsPreemptionGranularity); // nt6+
    FIELD_NW(L"ComputePreemption", display->szComputePreemptionGranularity); // nt6+
    FIELD_NW(L"Miracast", display->szMiracast); // nt6+
    FIELD_NW(L"DetachableGPU", display->bDetachable ? L"Yes" : L"No"); // nt6+
    FIELD_NW(L"HybridGraphicsGPUType", display->szHybridGraphicsGPUType); // nt6+
    FIELD_NW(L"PowerManagementPStates", display->szPowerManagementPStates); // nt6+
    FIELD_NW(L"VirtualGPUSupport", display->szVirtualGPUSupport); // nt6+
    FIELD_NW(L"BlockList", display->szBlockList); // nt6+
    FIELD_NW(L"DriverCatalogAttributes", display->szDriverCatalogAttributes); // nt6+
    FIELD_NW(L"MPOMaxPlanes", display->szMPOMaxPlanes); // nt6+
    FIELD_NW(L"MPOCaps", display->szMPOCaps); // nt6+
    FIELD_NW(L"MPOStretch", display->szMPOStretch); // nt6+
    FIELD_NW(L"MPOMediaHints", display->szMPOHints); // nt6+
    FIELD_NW(L"MPOFormats", display->szMPOFormats); // nt6+
    FIELD_NW(L"PanelFitterCaps", display->szPanelFitterCaps); // nt6+
    FIELD_NW(L"PanelFitterStretch", display->szPanelFitterStretch); // nt6+
    FIELD_NW(L"HardwareSchedulingAttributes", display->szHardwareSchedulingAttributes); // nt6+
    FIELD_NW(L"DisplayableSupport", display->szDisplayableSupport); // nt6+

    if (!xml_new_child(&fields[id], L"DXVADeinterlaceCaps"))
        return FALSE;
    
    if (!fill_dxva_caps(fields[id].child->data, display->aDXVAInfo, display->dwDXVALength))
        return FALSE;

    id++;

    FIELD_NW(L"D3D9Overlay", display->szOverlayEnglish); // nt6+
    FIELD_NW(L"DXVAHD", display->szDXVAHDEnglish); // nt6+
    FIELD_NW(L"DDrawStatus", display->szDDStatusEnglish);
    FIELD_NW(L"D3DStatus", display->szD3DStatusEnglish);
    FIELD_NW(L"AGPStatus", display->szAGPStatusEnglish);
    FIELD_NW(L"DDrawTestResult", display->szTestResultDDEnglish); // nt5 only
    FIELD_NW(L"D3D7TestResult", display->szTestResultD3D7English); // nt5 only
    FIELD_NW(L"D3D8TestResult", display->szTestResultD3D8English); // nt5 only
    FIELD_NW(L"D3D9TestResult", display->szTestResultD3D9English); // nt5 only

    return TRUE;
}

void fill_display_devices(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk)
{
    ULONG i = 0;

    xml_new_block(blk, L"DisplayDevices");

    refresh_root((&ctx->info));

    if (!refresh_display_container(&ctx->info, &ctx->data))
    {
        goto error;
    }

    for (; i < ctx->data.ulDisplays; i++)
    {
        if (!fill_display_information(&ctx->info, &ctx->data, i))
        {
            goto error;
        }

        if (!xml_new_child(&blk->data[i], L"DisplayDevice"))
        {
            goto error;
        }

        if (!fill_display_device(&ctx->data, blk->data[i].child->data, i))
        {
            goto error;
        }
    }

    return;

error:
    for (i = 0; i < ctx->data.ulDisplays; i++)
    {
        free_display_information(&ctx->data, i);
    }

    // TODO: write something in the XML saying there was an error

}
