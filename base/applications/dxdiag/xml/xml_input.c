/*
 * PROJECT:     SupernovaX Diagnostic Tool
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     XML Input output
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */
#include "precomp.h"
#include "output_xml.h"
#include "info/information.h"

static BOOL fill_input_related_device(PDXDIAG_INPUT_RELATED_DEVICE_INFO device, PXML_INFORMATION_DATA fields)
{
    DWORD id = 0;

    FIELD_NW(L"Description", device->szDescription);
    FIELD_DWORD(L"VendorID", device->dwVendorID);
    FIELD_DWORD(L"ProductID", device->dwProductID);
    FIELD_NW(L"Location", device->szLocation);
    FIELD_NW(L"MatchingDeviceID", device->szMatchingDeviceId);
    FIELD_NW(L"UpperFilters", device->szUpperFilters);
    FIELD_NW(L"LowerFilters", device->szLowerFilters);
    FIELD_NW(L"Service", device->szService);
    FIELD_NW(L"OEMData", device->szOEMData);
    FIELD_NW(L"Flags1", device->szFlags1);
    FIELD_NW(L"Flags2", device->szFlags2);
    FIELD_TODO(L"Drivers");

    if (device->child)
    {
        if (!xml_new_child(&fields[id], L"InputRelatedDevice"))
            return FALSE;

        if (!fill_input_related_device(device->child, fields[id].child->data))
            return FALSE;
    }

    return TRUE;
}

static BOOL fill_input_related_devices(PDXDIAG_INPUT_RELATED_DEVICE_INFO devices, PXML_INFORMATION_DATA fields, ULONG len)
{
    ULONG i = 0;

    for (; i < len; i++)
    {
        if (!xml_new_child(&fields[i], L"InputRelatedDevice"))
            return FALSE;

        if (!fill_input_related_device(&devices[i], fields[i].child->data))
            return FALSE;
    }

    return TRUE;
}

static BOOL fill_input_device(PDXDIAG_INFO info, PXML_INFORMATION_DATA fields, ULONG current)
{
    PDXDIAG_DINPUT_DEVICE_INFO input = &info->input_info.inputs[current];
    DWORD id = 0;

    FIELD_NW(L"DeviceName", input->szInstanceName);
    FIELD_BOOL(L"Attached", input->bAttached);
    FIELD_DWORD(L"JoystickID", input->dwJoystickID);
    FIELD_DWORD(L"VendorID", input->dwVendorID);
    FIELD_DWORD(L"ProductID", input->dwProductID);
    FIELD_DWORD(L"DevType", input->dwDevType);
    FIELD_NW(L"FFDriverName", input->szFFDriverName);
    FIELD_NW(L"FFDriverDateEnglish", input->szFFDriverDateEnglish);
    FIELD_NW(L"FFDriverVersion", input->szFFDriverVersion);
    FIELD_DWORD(L"FFDriverSize", input->lFFDriverSize);

    return TRUE;
}

static BOOL fill_input_devices(PDXDIAG_INFO dxdiag, PXML_INFORMATION_DATA fields)
{
    ULONG i = 0;

    for (; i < dxdiag->input_info.ulInputs; i++)
    {
        if (!xml_new_child(&fields[i], L"DirectInputDevice"))
            return FALSE;

        if (!fill_input_device(dxdiag, fields[i].child->data, i))
            return FALSE;
    }

    return TRUE;
}

static BOOL fill_input(PDXDIAG_INFO dxdiag_info, PXML_INFORMATION_DATA fields)
{
    if (!xml_new_child(&fields[0], L"DirectInputDevices"))
        return FALSE;

    fill_input_devices(dxdiag_info, fields[0].child->data);

    if (!xml_new_child(&fields[1], L"USBRoot"))
        return FALSE;

    if (!fill_input_related_devices(dxdiag_info->input_info.usbroots, fields[1].child->data, dxdiag_info->input_info.ulUSBRoots))
        return FALSE;

    if (!xml_new_child(&fields[2], L"GamePortDevices"))
        return FALSE;

    if (!fill_input_related_devices(dxdiag_info->input_info.gameports, fields[1].child->data, dxdiag_info->input_info.ulGameports))
        return FALSE;

    if (!xml_new_child(&fields[3], L"PS2Devices"))
        return FALSE;

    if (!fill_input_related_devices(dxdiag_info->input_info.ps2devices, fields[1].child->data, dxdiag_info->input_info.ulPS2Devices))
        return FALSE;

    xml_new_field_nochild(&fields[4], L"PollWithInterrupt", dxdiag_info->input_info.bPollFlags ? L"Yes" : L"No");

    // NT5 only
    xml_new_field_nochild(&fields[5], L"Registry", L"TODO: Fix");
    return TRUE;
}

void fill_direct_input(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk)
{
    xml_new_block(blk, L"DirectInput");

    refresh_root((&ctx->info));

    // TODO: handle refresh

    if (!fill_input(&ctx->data, blk->data))
        goto error;

    return;

error:
    // TODO: handle error
    return;
}
