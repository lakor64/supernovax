/*
 * PROJECT:     SupernovaX Diagnostic Tool
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     XML Notes output
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */
#include "precomp.h"
#include "output_xml.h"
#include "info/information.h"

static BOOL fill_dxdiag_notes_data(PDXDIAG_INFO dxdiag_info, PXML_INFORMATION_DATA fields)
{
    DWORD id = 0;
    ULONG i = 0;

    FIELD_NW(L"DirectXFilesTab", dxdiag_info->files.szDXFileNotesEnglish);

    for (; i < dxdiag_info->ulDisplays; i++)
    {
        FIELD_NW(L"DisplayTab", dxdiag_info->display_devices[i].szNotesEnglish);
    }

    for (i = 0; i < dxdiag_info->sound_devices.ulOutputs; i++)
    {
        FIELD_NW(L"SoundTab", dxdiag_info->sound_devices.outputs[i].szNotesEnglish);
    }

    // not present in nt6
    FIELD_NW(L"MusicTab", dxdiag_info->music_info.szNotesEnglish);
    FIELD_NW(L"InputTab", dxdiag_info->input_info.szInputNotesEnglish);
    FIELD_NW(L"NetworkTab", dxdiag_info->network_info.szNetworkNotesEnglish);

    return TRUE;
}

void fill_dxdiag_notes(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk)
{
    ULONG i;

    xml_new_block(blk, L"DxDiagNotes");

    refresh_root((&ctx->info));

    if (!refresh_display_container(&ctx->info, &ctx->data))
    {
        goto error;
    }

    for (i = 0; i < ctx->data.ulDisplays; i++)
    {
        if (!fill_display_information_notes_only(&ctx->info, &ctx->data, i))
        {
            goto error;
        }
    }

    // TODO: handle refresh of data

    if (!fill_dxdiag_notes_data(&ctx->data, blk->data))
        goto error;

    return;

error:
    // TODO: write something in the XML saying there was an error
    for (i = 0; i < ctx->data.ulDisplays; i++)
    {
        free_display_information(&ctx->data, i);
    }
}
