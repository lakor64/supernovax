/*
 * PROJECT:     SupernovaX Diagnostic Tool
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     XML DX Files output
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */
#include "precomp.h"
#include "output_xml.h"
#include "info/information.h"

static BOOL fill_component(PDXDIAG_INFO dxdiag, PXML_INFORMATION_DATA fields, ULONG i)
{
    PDXDIAG_COMPONENT_INFO sp = &dxdiag->files.components[i];
    ULONG id = 0;

    FIELD_NW(L"Name", sp->szName);
    FIELD_NW(L"Version", sp->szVersion);
    FIELD_NW(L"Language", sp->szLanguageEnglish);
    FIELD_DWORD(L"Beta", sp->bBeta);
    FIELD_BOOL(L"Debug", sp->bDebug);
    FIELD_NW(L"Date", sp->szDatestampEnglish);
    FIELD_DWORD(L"Size", sp->lNumBytes);
    FIELD_BOOL(L"Exists", sp->bExists);
    FIELD_BOOL(L"Problem", sp->bProblem);

    return TRUE;
}

void fill_dx_components(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk)
{
    ULONG id = 0;


    xml_new_block(blk, L"DisplayDevices"); // TODO: this is wrong

    refresh_root((&ctx->info));

    // TODO: implement refresh

    for (; id < ctx->data.files.ulComponents; id++)
    {
        if (!xml_new_child(&blk->data[id], L"File"))
            goto error;

        if (!fill_component(&ctx->data, blk->data[id].child->data, id))
            goto error;
    }

    return;

error:
    // TODO: handle error
    return;
}
