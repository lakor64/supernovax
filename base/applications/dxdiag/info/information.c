/*
 * PROJECT:     SupernovaX Diagnostic Tool
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     Information parsing
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 *              Copyright 2011 Andrew Nguyen
 */
#include "precomp.h"
#include "information.h"

// Microsoft broken define in latest crt
#ifdef IDxDiagProvider_Initialize
#undef IDxDiagProvider_Initialize
#define IDxDiagProvider_Initialize(p,a)                       (p)->lpVtbl->Initialize(p,a)
#endif

#define wcsdup _wcsdup
WINE_DEFAULT_DEBUG_CHANNEL(dxdiag);

void property_to_data(IDxDiagContainer *container, LPCWSTR property, PDXDIAG_INFO_PROPERTY_OUTPUT output)
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
        case VT_UI4:
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

BOOL exec_method(PDXDIAG_INFO_CONTEXT ctx, LPCWSTR name, UINT up)
{
    VARIANT out;
    HRESULT hr;

    out.n1.n2.vt = VT_I4;
    out.n1.n2.n3.lVal = up;

    hr = IDxDiagProviderPrivate_ExecMethod(ctx->ddpp, name, &out);
    if (FAILED(hr))
    {
        WINE_ERR("Cannot execute method %S error 0x%08lx\n", name, hr);
        return FALSE;
    }

    return TRUE;
}

IDxDiagContainer* get_child_container(PDXDIAG_INFO_CONTEXT ctx, LPCWSTR name)
{
    IDxDiagContainer* child;
    HRESULT hr;

    if (!ctx->root)
    {
        hr = IDxDiagProvider_GetRootContainer(ctx->ddp, &ctx->root);
        if (FAILED(hr))
        {
            WINE_ERR("Root container get fail error 0x%08ln\n", hr);
            return NULL;
        }
    }

    hr = IDxDiagContainer_GetChildContainer(ctx->root, name, &child);
    if (SUCCEEDED(hr))
        return child;

    WINE_ERR("Child container get fail error 0x%08ln\n", hr);
    return NULL;
}

void free_dxdiag_information(PDXDIAG_INFO dxdiag_info)
{
    if (!dxdiag_info)
        return;

    free_system_information(dxdiag_info);

    for (ULONG i = 0; i < dxdiag_info->ulDisplays; i++)
    {
        free_display_information(dxdiag_info, i);
    }

    free(dxdiag_info->display_devices);
    dxdiag_info->display_devices = NULL;
}

void free_dxdiag_context(PDXDIAG_INFO_CONTEXT ctx)
{
    if (ctx->root)
    {
        IDxDiagContainer_Release(ctx->root);
        ctx->root = NULL;
    }

    if (ctx->ddpp)
    {
        IDxDiagProviderPrivate_Release(ctx->ddpp);
        ctx->ddpp = NULL;
    }

    if (ctx->ddp)
    {
        IDxDiagProvider_Release(ctx->ddp);
        ctx->ddp = NULL;
    }
}

BOOL init_dxdiag_context(PDXDIAG_INFO_CONTEXT ctx, BOOL whql)
{
    DXDIAG_INIT_PARAMS params = { sizeof(DXDIAG_INIT_PARAMS), DXDIAG_DX9_SDK_VERSION };
    DXDIAG_INIT_RESERVED_DATA reserved = { DXDIAG_INIT_RESERVED_MAGIC };
    HRESULT hr;

    /* use reserved interface to grab all info that are NT6+ */
    reserved.bUsePrivateInterface = TRUE;
    params.pReserved = &reserved;

    /* Initialize the DxDiag COM instances. */
    hr = CoCreateInstance(&CLSID_DxDiagProvider, NULL, CLSCTX_INPROC_SERVER,
        &IID_IDxDiagProvider, (void**)&ctx->ddp);

    if (FAILED(hr))
    {
        WINE_ERR("IDxDiagProvider instance creation failed with 0x%08lx\n", hr);
        return FALSE;
    }

    hr = IDxDiagProvider_QueryInterface(ctx->ddp, &IID_IDxDiagProviderPrivate, (void**)&ctx->ddpp);

    if (FAILED(hr))
    {
        WINE_ERR("IDxDiagProviaderPrivate instance query failed with 0x%08lx\n", hr);
        free_dxdiag_context(ctx);
        return FALSE;
    }

    params.bAllowWHQLChecks = whql;
    hr = IDxDiagProvider_Initialize(ctx->ddp, &params);
    if (FAILED(hr))
    {
        WINE_ERR("IDxDiagProvider_Initialize fail with 0x%08lx\n", hr);
        free_dxdiag_context(ctx);
        return FALSE;
    }

    ctx->root = NULL;

    return TRUE;
}
