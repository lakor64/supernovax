/*
 * PROJECT:     SupernovaX Diagnostic Tool
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     System information parsing
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 *              Copyright 2011 Andrew Nguyen
 */
#include "precomp.h"
#include "information.h"

#define SYSTEM_CONTAINER_NAME L"DxDiag_SystemInfo"
#define SYSTEM_ACTION_NAME L"GetSystemInfo"

static inline void fill_system_property_list(PDXDIAG_INFO dxdiag_info, PDXDIAG_INFO_PROPERTY_LIST list)
{
    PDXDIAG_SYSTEM_INFO system_info = &dxdiag_info->system_info;

    list[0].property_name = L"szTimeEnglish";
    list[0].output.wchar = &system_info->szTimeEnglish;
    list[1].property_name = L"szTimeLocalized";
    list[1].output.wchar = &system_info->szTimeLocalized;
    list[2].property_name = L"szMachineNameEnglish";
    list[2].output.wchar = &system_info->szMachineNameEnglish;
    list[3].property_name = L"szMachineNameLocalized";
    list[3].output.wchar = &system_info->szMachineNameLocalized;
    list[4].property_name = L"szOSExLongEnglish";
    list[4].output.wchar = &system_info->szOSExLongEnglish;
    list[5].property_name = L"szOSExLocalized";
    list[5].output.wchar = &system_info->szOSExLocalized;
    list[6].property_name = L"szLanguagesEnglish";
    list[6].output.wchar = &system_info->szLanguagesEnglish;
    list[7].property_name = L"szLanguagesLocalized";
    list[7].output.wchar = &system_info->szLanguagesLocalized;
    list[8].property_name = L"szSystemManufacturerEnglish";
    list[8].output.wchar = &system_info->szSystemManufacturerEnglish;
    list[9].property_name = L"szSystemModelEnglish";
    list[9].output.wchar = &system_info->szSystemModelEnglish;
    list[10].property_name = L"szBIOSEnglish";
    list[10].output.wchar = &system_info->szBIOSEnglish;
    list[11].property_name = L"szProcessorEnglish";
    list[11].output.wchar = &system_info->szProcessorEnglish;
    list[12].property_name = L"szPhysicalMemoryEnglish";
    list[12].output.wchar = &system_info->szPhysicalMemoryEnglish;
    list[13].property_name = L"szPageFileEnglish";
    list[13].output.wchar = &system_info->szPageFileEnglish;
    list[14].property_name = L"szPageFileLocalized";
    list[14].output.wchar = &system_info->szPageFileLocalized;
    list[15].property_name = L"szWindowsDir";
    list[15].output.wchar = &system_info->szWindowsDir;
    list[16].property_name = L"szDirectXVersionLongEnglish";
    list[16].output.wchar = &system_info->szDirectXVersionLongEnglish;
    list[17].property_name = L"szSetupParamEnglish";
    list[17].output.wchar = &system_info->szSetupParamEnglish;
    list[18].property_name = L"szDxDiagVersion";
    list[18].output.wchar = &system_info->szDxDiagVersion;
    list[19].property_name = L"szPhysicalMemoryEnglishOS";
    list[19].output.wchar = &system_info->szPhysicalMemoryEnglishOS;
    list[20].property_name = L"szSystemDPI";
    list[20].output.wchar = &system_info->szSystemDPI;
    list[21].property_name = L"szDWMScalingDPI";
    list[21].output.wchar = &system_info->szDWMScalingDPI;
    list[22].property_name = L"szDxDbVersion";
    list[22].output.wchar = &system_info->szDxDbVersion;
    list[23].property_name = L"szUserDPI";
    list[23].output.wchar = &system_info->szUserDPI;
    list[24].property_name = L"szMiracastAvailable";
    list[24].output.wchar = &system_info->szMiracastAvailable;
    list[25].property_name = L"szMSHybrid";
    list[25].output.wchar = &system_info->szMSHybrid;
    list[26].property_name = L"nDPlayDebugLevel";
    list[26].output.ulong = &system_info->nDPlayDebugLevel;
    list[27].property_name = L"nDDrawDebugLevel";
    list[27].output.ulong = &system_info->nDDrawDebugLevel;
    list[28].property_name = L"nDIDebugLevel";
    list[28].output.ulong = &system_info->nDIDebugLevel;
    list[29].property_name = L"nDMusicDebugLevel";
    list[29].output.ulong = &system_info->nDMusicDebugLevel;
    list[30].property_name = L"nDShowDebugLevel";
    list[30].output.ulong = &system_info->nDShowDebugLevel;
    list[31].property_name = L"nDSoundDebugLevel";
    list[31].output.ulong = &system_info->nDSoundDebugLevel;
    list[32].property_name = L"bIsDSoundDebugRuntime";
    list[32].output.ulong = &system_info->bIsDSoundDebugRuntime;
    list[33].property_name = L"bIsDPlayDebugRuntime";
    list[33].output.ulong = &system_info->bIsDPlayDebugRuntime;
    list[34].property_name = L"bIsDDrawDebugRuntime";
    list[34].output.ulong = &system_info->bIsDDrawDebugRuntime;
    list[35].property_name = L"bIsDMusicDebugRuntime";
    list[35].output.ulong = &system_info->bIsDMusicDebugRuntime;
    list[36].property_name = L"szFirmwareType";
    list[36].output.wchar = &system_info->szFirmwareType;
}

BOOL fill_system_information(PDXDIAG_INFO_CONTEXT ctx, PDXDIAG_INFO dxdiag_info)
{
    PDXDIAG_SYSTEM_INFO system_info = &dxdiag_info->system_info;
    size_t i;
    DXDIAG_INFO_PROPERTY_LIST property_list[37];
    IDxDiagContainer* child;

    for (i = 1; i < 3; i++)
    {
        if (!exec_method(ctx, SYSTEM_ACTION_NAME, i)) // probably this is the version
        {
            return FALSE;
        }
    }

    child = get_child_container(ctx, SYSTEM_CONTAINER_NAME);

    fill_system_property_list(dxdiag_info, property_list);

    for (i = 0; i < ARRAY_SIZE(property_list); i++)
    {
        property_to_data(child, property_list[i].property_name, &property_list[i].output);
    }

#ifdef _WIN64
    system_info->win64 = TRUE;
#else
    system_info->win64 = FALSE;
#endif

    return TRUE;
}

void free_system_information(PDXDIAG_INFO dxdiag_info)
{
    PDXDIAG_SYSTEM_INFO system_info = &dxdiag_info->system_info;

    free(system_info->szTimeEnglish);
    free(system_info->szTimeLocalized);
    free(system_info->szMachineNameEnglish);
    free(system_info->szMachineNameLocalized);
    free(system_info->szOSExLongEnglish);
    free(system_info->szOSExLocalized);
    free(system_info->szLanguagesEnglish);
    free(system_info->szLanguagesLocalized);
    free(system_info->szSystemManufacturerEnglish);
    free(system_info->szSystemModelEnglish);
    free(system_info->szBIOSEnglish);
    free(system_info->szProcessorEnglish);
    free(system_info->szPhysicalMemoryEnglish);
    free(system_info->szPageFileEnglish);
    free(system_info->szPageFileLocalized);
    free(system_info->szWindowsDir);
    free(system_info->szDirectXVersionLongEnglish);
    free(system_info->szSetupParamEnglish);
    free(system_info->szDxDiagVersion);
    free(system_info->szPhysicalMemoryEnglishOS);
    free(system_info->szSystemDPI);
    free(system_info->szDWMScalingDPI);
    free(system_info->szDxDbVersion);
    free(system_info->szUserDPI);
    free(system_info->szMiracastAvailable);
    free(system_info->szMSHybrid);
    free(system_info->szFirmwareType);
}
