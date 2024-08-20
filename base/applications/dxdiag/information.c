/*
 * DxDiag information collection
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

#ifdef __REACTOS__
#include "precomp.h"
#else
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <dxdiag.h>

#include "wine/debug.h"
#include "dxdiag_private.h"
#endif

#define TEST_DXDIAGN_NOT_FROM_COM 1

// Microsoft broken define in latest crt
#ifdef IDxDiagProvider_Initialize
#undef IDxDiagProvider_Initialize
#define IDxDiagProvider_Initialize(p,a)                       (p)->lpVtbl->Initialize(p,a)
#endif

#if TEST_DXDIAGN_NOT_FROM_COM
typedef HRESULT(WINAPI* DllGetClassObjectCb)(_In_ REFCLSID rclsid, _In_ REFIID riid, _Out_ LPVOID* ppv);
#endif

#define ARRAY_SIZE(A) (sizeof(A)/sizeof(*(A)))
#define wcsdup _wcsdup
WINE_DEFAULT_DEBUG_CHANNEL(dxdiag);

struct property_output
{
    WCHAR** wchar;
    union
    {
        ULONG* ulong;
    };
    BOOL count;
};

struct property_list
{
    const WCHAR *property_name;
    struct property_output output;
};

static void property_to_data(IDxDiagContainer *container, const WCHAR *property, struct property_output* output)
{
    VARIANT var;
    HRESULT hr;

    VariantInit(&var);

    hr = IDxDiagContainer_GetProp(container, property, &var);
    if (SUCCEEDED(hr))
    {
        switch (V_VT(&var))
        {
        case VT_BSTR:
        {
            WCHAR* bstr = V_BSTR(&var);

            *(output->wchar) = wcsdup(bstr);
            break;
        }

        case VT_I4:
        case VT_BOOL:
            *output->ulong = (ULONG)V_I4(&var);
            break;

        default:
            WINE_ERR("Unsupported property variant: %s\n", wine_dbgstr_variant(&var));
            break;
        }
    }
    else
    {
        // We might run this app on systems with older versions of dxdiagn.dll
        WINE_ERR("Cannot find property %s\n", wine_dbgstr_w(property));
    }

    VariantClear(&var);
}

static void free_system_information(struct dxdiag_information *dxdiag_info)
{
    struct system_information *system_info = &dxdiag_info->system_info;

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
}

static inline void fill_system_property_list(struct dxdiag_information *dxdiag_info, struct property_list *list)
{
    struct system_information *system_info = &dxdiag_info->system_info;

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
}

static BOOL fill_system_information(IDxDiagContainer *container, struct dxdiag_information *dxdiag_info)
{
    struct system_information *system_info = &dxdiag_info->system_info;
    size_t i;
    struct property_list property_list[36];

    fill_system_property_list(dxdiag_info, property_list);

    for (i = 0; i < ARRAY_SIZE(property_list); i++)
    {
        property_to_data(container, property_list[i].property_name, &property_list[i].output);
    }

#ifdef _WIN64
    system_info->win64 = TRUE;
#else
    system_info->win64 = FALSE;
#endif

    return TRUE;
}

static const struct information_fillers
{
    const WCHAR *child_container_name;
    BOOL (*fill_function)(IDxDiagContainer *, struct dxdiag_information *);
    void (*free_function)(struct dxdiag_information *);
} filler_list[] =
{
    {L"DxDiag_SystemInfo", fill_system_information, free_system_information},
};

void free_dxdiag_information(struct dxdiag_information *system_info)
{
    size_t i;

    if (!system_info)
        return;

    for (i = 0; i < ARRAY_SIZE(filler_list); i++)
        filler_list[i].free_function(system_info);

    free(system_info);
}

struct dxdiag_information *collect_dxdiag_information(BOOL whql_check)
{
    IDxDiagProvider *pddp = NULL;
    IDxDiagContainer *root = NULL;
    struct dxdiag_information *ret = NULL;
    DXDIAG_INIT_PARAMS params = {sizeof(DXDIAG_INIT_PARAMS), DXDIAG_DX9_SDK_VERSION};
    HRESULT hr;
    size_t i;

#if TEST_DXDIAGN_NOT_FROM_COM
    HMODULE w = NULL;
    DllGetClassObjectCb cb = NULL;
    IClassFactory* cfact = NULL;
#endif

#if !TEST_DXDIAGN_NOT_FROM_COM
    /* Initialize the DxDiag COM instances. */
    hr = CoCreateInstance(&CLSID_DxDiagProvider, NULL, CLSCTX_INPROC_SERVER,
                          &IID_IDxDiagProvider, (void **)&pddp);
#else
    w = LoadLibraryW(L"dxdiagn_proxy.dll");
    if (!w)
    {
        WINE_ERR("Cannot load dxdiagn.dll\n");
        goto error;
    }

    cb = (DllGetClassObjectCb)GetProcAddress(w, "DllGetClassObject");
    if (!cb)
    {
        WINE_ERR("Cannot load DllGetClassObject from dxdiagn.dll\n");
        goto error;
    }

    hr = cb(&CLSID_DxDiagProvider, &IID_IClassFactory, (void**)&cfact);
    if (FAILED(hr))
    {
        WINE_ERR("IClassFactory instance creation failed with 0x%08lx\n", hr);
        goto error;
    }

    hr = cfact->lpVtbl->CreateInstance(cfact, NULL, &IID_IDxDiagProvider, (void**)&pddp);
#endif

    if (FAILED(hr))
    {
        WINE_ERR("IDxDiagProvider instance creation failed with 0x%08lx\n", hr);
        goto error;
    }

    params.bAllowWHQLChecks = whql_check;
    hr = IDxDiagProvider_Initialize(pddp, &params);
    if (FAILED(hr))
        goto error;

    hr = IDxDiagProvider_GetRootContainer(pddp, &root);
    if (FAILED(hr))
        goto error;

    ret = calloc(1, sizeof(*ret));
    if (!ret)
        goto error;

    for (i = 0; i < ARRAY_SIZE(filler_list); i++)
    {
        IDxDiagContainer *child;
        BOOL success;

        hr = IDxDiagContainer_GetChildContainer(root, filler_list[i].child_container_name, &child);
        if (FAILED(hr))
            goto error;

        success = filler_list[i].fill_function(child, ret);
        IDxDiagContainer_Release(child);
        if (!success)
            goto error;
    }

    IDxDiagContainer_Release(root);
    IDxDiagProvider_Release(pddp);
    return ret;

error:
    free_dxdiag_information(ret);
    if (root) IDxDiagContainer_Release(root);
    if (pddp) IDxDiagProvider_Release(pddp);
#if TEST_DXDIAGN_NOT_FROM_COM
    if (w) FreeLibrary(w);
#endif

    return NULL;
}
