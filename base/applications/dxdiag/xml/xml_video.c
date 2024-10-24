/*
 * PROJECT:     SupernovaX Diagnostic Tool
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     XML Video output
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */
#include "precomp.h"
#include "output_xml.h"

static BOOL fill_video_filter(PDXDIAG_INFO dxdiag, PXML_INFORMATION_DATA fields, ULONG i)
{
    PDXDIAG_DSHOWFILTERS_INFO sp = &dxdiag->video_filters[i];
    ULONG id = 0;

    FIELD_NW(L"Name", sp->szName);
    FIELD_NW(L"FilterCatagory", sp->szCatName);
    FIELD_DWORD(L"Merit", sp->dwMerit);
    FIELD_DWORD(L"Inputs", sp->dwInputs);
    FIELD_DWORD(L"Outputs", sp->dwOutputs);
    FIELD_NW(L"File", sp->szFileName);
    FIELD_NW(L"FileVersion", sp->szFileVersion);

    return FALSE;
}

static BOOL fill_video_render(PDXDIAG_INFO dxdiag, PXML_INFORMATION_DATA fields)
{
    ULONG id = 0;

    FIELD_TODO(L"PreferredDShowFilters");

    for (; id < dxdiag->ulVideoFilters; id++)
    {
        if (!xml_new_child(&fields[id], L"Filter"))
            return FALSE;

        if (!fill_video_filter(dxdiag, fields[id].child->data, id))
            return FALSE;
    }

    return TRUE;
}

void fill_direct_show(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk)
{
    xml_new_block(blk, L"DirectShow");

    // TODO: handle refresh

    if (!fill_video_render(&ctx->data, blk->data))
        goto error;

    return;

error:
    // TODO: handle error
    return;
}
