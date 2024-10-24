/*
 * PROJECT:     SupernovaX Diagnostic Tool
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     XML Music output
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */
#include "precomp.h"
#include "output_xml.h"
#include "info/information.h"

static BOOL fill_music_port(PDXDIAG_INFO dxdiag_info, PXML_INFORMATION_DATA fields, ULONG current)
{
    DWORD id = 0;
    PDXDIAG_MUSIC_PORTS_INFO port = &dxdiag_info->music_info.ports[current];

    FIELD_NW(L"Description", port->szDescription);
    FIELD_BOOL(L"Software", port->bSoftware);
    FIELD_BOOL(L"KernelMode", port->bKernelMode);
    FIELD_BOOL(L"OutputPort", port->bOutputPort)
    FIELD_BOOL(L"UsesDLS", port->bUsesDLS);
    FIELD_BOOL(L"External", port->bExternal);
    FIELD_BOOL(L"DefaultPort", port->bDefaultPort);

    return TRUE;
}

static BOOL fill_music_ports(PDXDIAG_INFO dxdiag_info, PXML_INFORMATION_DATA fields)
{
    ULONG i = 0;

    for (; i < dxdiag_info->music_info.ulPorts; i++)
    {
        if (!xml_new_child(&fields[i], L"Port"))
            return FALSE;

        if (!fill_music_port(dxdiag_info, fields[i].child->data, i))
            return FALSE;
    }

    return TRUE;
}

static BOOL fill_music(PDXDIAG_INFO dxdiag_info, PXML_INFORMATION_DATA fields)
{
    DWORD id = 0;
    PDXDIAG_DMUSIC_INFO music = &dxdiag_info->music_info;

    FIELD_NW(L"DLSPath", music->szGMFilePath);
    FIELD_NW(L"DLSVersion", music->szGMFileVersion);
    FIELD_TODO(L"Acceleration");

    if (!xml_new_child(&fields[id], L"Ports"))
        return FALSE;

    if (!fill_music_ports(dxdiag_info, fields[id++].child->data))
        return FALSE;

    FIELD_TODO(L"Registry");
    return TRUE;
}
 
void fill_direct_music(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk)
{
    xml_new_block(blk, L"DirectMusic");
    refresh_root((&ctx->info));

    // TODO: handle data

    if (!fill_music(&ctx->data, blk->data))
        goto error;

    return;

error:
    // TODO: handle error
    return;
}
