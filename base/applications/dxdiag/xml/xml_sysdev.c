/*
 * PROJECT:     SupernovaX Diagnostic Tool
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     XML System devices output
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */
#include "precomp.h"
#include "output_xml.h"
#include "info/information.h"

static BOOL fill_system_device(PDXDIAG_INFO info, PXML_INFORMATION_DATA fields, ULONG current)
{
    PDXDIAG_SYSTEM_DEVICE_INFO disk = &info->system_devices[current];
    DWORD id = 0;

    FIELD_NW(L"Name", disk->szDescription);
    FIELD_NW(L"DeviceKey", disk->szDeviceID);
    FIELD_TODO(L"Drivers");

    return TRUE;
}

void fill_system_devices(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk)
{
    ULONG i = 0;

    xml_new_block(blk, L"SystemDevices");

    refresh_root((&ctx->info));

    for (; i < ctx->data.ulSystemDevices; i++)
    {
        if (!xml_new_child(&blk->data[i], L"SystemDevice"))
            goto error;

        if (!fill_system_device(&ctx->data, blk->data[i].child->data, i))
        {
            goto error;
        }
    }

    return;

error:
    // TODO: handle error
    return;
}
