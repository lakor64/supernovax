/*
 * PROJECT:     SupernovaX Diagnostic Tool
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     XML Logical disk output
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */
#include "precomp.h"
#include "output_xml.h"
#include "info/information.h"

static BOOL fill_logical_disk_data(PDXDIAG_INFO info, PXML_INFORMATION_DATA fields, ULONG current)
{
    PDXDIAG_LOGICAL_DISK_INFO disk = &info->logical_disks[current];
    DWORD id = 0;

    FIELD_NW(L"DriveLetter", disk->szDriveLetter);
    FIELD_NW(L"FreeSpace", disk->szFreeSpace);
    FIELD_NW(L"MaxSpace", disk->szMaxSpace);
    FIELD_NW(L"FileSystem", disk->szFileSystem);
    FIELD_NW(L"Model", disk->szModel);
    FIELD_NW(L"PNPDeviceID", disk->szPNPDeviceID);
    FIELD_DWORD(L"HardDriveIndex", disk->dwHardDriveIndex);
    FIELD_TODO(L"Drivers");

    return TRUE;
}

void fill_logical_disk(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk)
{
    ULONG i = 0;

    xml_new_block(blk, L"LogicalDisks");

    refresh_root((&ctx->info));

    // TODO: refresh logical disks

    for (; i < ctx->data.ulLogicalDisks; i++)
    {
        if (!xml_new_child(&blk->data[i], L"LogicalDisk"))
            goto error;

        if (!fill_logical_disk_data(&ctx->data, blk->data[i].child->data, i))
            goto error;
    }

    return;

error:
    // TODO: handle error
    return;
}
