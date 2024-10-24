/*
 * PROJECT:     SupernovaX Diagnostic Tool
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     XML Debug output
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */
#include "precomp.h"
#include "output_xml.h"
#include "info/information.h"

static BOOL fill_dxdebug_level(ULONG curr, ULONG _max, LPCWSTR runtime, PXML_INFORMATION_BLOCK blk)
{
    DWORD id = 0;
    PXML_INFORMATION_DATA fields = blk->data;
    FIELD_DWORD(L"Current", curr);
    FIELD_DWORD(L"Max", _max);
    FIELD_NW(L"Runtime", runtime);
    return TRUE;
}

#define DXDEBUG_LEVEL(tag, curr, _max, runtime) \
    if (!xml_new_child(&fields[id], tag)) \
        return FALSE; \
    if (!fill_dxdebug_level(curr, _max, runtime, fields[id++].child)) \
        return FALSE;

static BOOL fill_dxdebug_levels(PDXDIAG_INFO dxdiag_info, PXML_INFORMATION_DATA fields)
{
    DWORD id = 0;

    DXDEBUG_LEVEL(L"Direct3D", 0, 0, L"n/a");
    DXDEBUG_LEVEL(L"DirectDraw", dxdiag_info->system_info.nDDrawDebugLevel, 0, L"n/a");
    DXDEBUG_LEVEL(L"DirectInput", dxdiag_info->system_info.nDIDebugLevel, 0, L"n/a");
    DXDEBUG_LEVEL(L"DirectMusic", dxdiag_info->system_info.nDMusicDebugLevel, 0, L"n/a");
    DXDEBUG_LEVEL(L"DirectPlay", dxdiag_info->system_info.nDPlayDebugLevel, 0, L"n/a");
    DXDEBUG_LEVEL(L"DirectSound", dxdiag_info->system_info.nDSoundDebugLevel, 0, L"n/a");
    DXDEBUG_LEVEL(L"DirectShow", dxdiag_info->system_info.nDShowDebugLevel, 0, L"n/a");

    return TRUE;
}

void fill_dx_debug_levels(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk)
{
    xml_new_block(blk, L"DirectXDebugLevels");

    refresh_root((&ctx->info));

    // TODO: handle refresh of data

    if (!fill_dxdebug_levels(&ctx->data, blk->data))
        goto error;

    return;

error:

    // TODO: write something in the XML saying there was an error
    return;

}

