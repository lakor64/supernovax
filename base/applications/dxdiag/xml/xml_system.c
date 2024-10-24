/*
 * PROJECT:     SupernovaX Diagnostic Tool
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     XML System output
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 *              Copyright 2011 Andrew Nguyen
 */
#include "precomp.h"
#include "output_xml.h"
#include "info/information.h"

static BOOL fill_system_xml_output_table(PDXDIAG_INFO dxdiag_info, PXML_INFORMATION_DATA fields)
{
    DWORD id = 0;
    FIELD_NW(L"Time", dxdiag_info->system_info.szTimeEnglish);
    FIELD_NW(L"MachineName", dxdiag_info->system_info.szMachineNameEnglish);
    FIELD_TODO(L"MachineId");
    FIELD_NW(L"OperatingSystem", dxdiag_info->system_info.szOSExLongEnglish);
    FIELD_NW(L"Language", dxdiag_info->system_info.szLanguagesEnglish);
    FIELD_NW(L"SystemManufacturer", dxdiag_info->system_info.szSystemManufacturerEnglish);
    FIELD_NW(L"SystemModel", dxdiag_info->system_info.szSystemModelEnglish);
    FIELD_NW(L"BIOS", dxdiag_info->system_info.szBIOSEnglish);
    FIELD_NW(L"FirmwareType", dxdiag_info->system_info.szFirmwareType);
    FIELD_NW(L"Processor", dxdiag_info->system_info.szProcessorEnglish);
    FIELD_NW(L"Memory", dxdiag_info->system_info.szPhysicalMemoryEnglish);
    FIELD_NW(L"AvaliableOSMem", dxdiag_info->system_info.szPhysicalMemoryEnglishOS);
    FIELD_NW(L"PageFile", dxdiag_info->system_info.szPageFileEnglish);
    FIELD_NW(L"WindowsDir", dxdiag_info->system_info.szWindowsDir);
    FIELD_NW(L"DirectXVersion", dxdiag_info->system_info.szDirectXVersionLongEnglish);
    FIELD_NW(L"DXSetupParameters", dxdiag_info->system_info.szSetupParamEnglish);

    if (!dxdiag_info->system_info.szUserDPI || wcscmp(dxdiag_info->system_info.szUserDPI, L"Using System DPI") == 0)
    {
        FIELD_NW(L"UserDPISettings", dxdiag_info->system_info.szSystemDPI);
    }
    else
    {
        FIELD_NW(L"UserDPISettings", dxdiag_info->system_info.szUserDPI);
    }

    FIELD_NW(L"SystemDPISettings", dxdiag_info->system_info.szSystemDPI);
    FIELD_NW(L"DWMDPIScaling", dxdiag_info->system_info.szDWMScalingDPI);
    FIELD_NW(L"DxDiagVersion", dxdiag_info->system_info.szDxDiagVersion);
#ifdef _UNICODE
    FIELD_NW(L"DxDiagUnicode", L"1");
#else
    FIELD_NW(L"DxDiagUnicode", L"0");
#endif
    FIELD_BOOL(L"DxDiag64Bit", dxdiag_info->system_info.win64);
    FIELD_NW(L"Miracast", dxdiag_info->system_info.szMiracastAvailable);

    if (!dxdiag_info->system_info.szMSHybrid || dxdiag_info->system_info.szMSHybrid[0] == '\0')
    {
        FIELD_NW(L"MSHybrid", L"Not Supported");
    }
    else
    {
        FIELD_NW(L"MSHybrid", dxdiag_info->system_info.szMSHybrid);
    }

    FIELD_NW(L"DirectXDatabaseVersion", dxdiag_info->system_info.szDxDbVersion);

    return TRUE;
}

void fill_system(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk)
{    
    xml_new_block(blk, L"SystemInformation");

    refresh_root((&ctx->info));

    if (!fill_system_information(&ctx->info, &ctx->data))
        goto error;

    if (!fill_system_xml_output_table(&ctx->data, blk->data))
        goto error;

    free_system_information(&ctx->data);
    return;

error:
    free_system_information(&ctx->data);

    // TODO: write something in the XML saying there was an error

}
