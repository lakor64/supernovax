/*
 * PROJECT:     SupernovaX Diagnostic Tool
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     XML Sound output
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */
#include "precomp.h"
#include "output_xml.h"
#include "info/information.h"

static BOOL fill_sound_device(PDXDIAG_INFO dxdiag_info, PXML_INFORMATION_DATA fields, ULONG current)
{
    PDXDIAG_SOUND_DEVICE_INFO display = &dxdiag_info->sound_devices.outputs[current];
    DWORD id = 0;

    FIELD_NW(L"Description", display->szDescription);
    FIELD_NW(L"HardwareID", display->szHardwareID);
    FIELD_NW(L"ManufacturerID", display->szManufacturerID);
    FIELD_NW(L"ProductID", display->szProductID);
    FIELD_NW(L"Type", display->szType);
    FIELD_NW(L"DriverName", display->szDriverName);
    FIELD_NW(L"DriverVersion", display->szDriverVersion);
    FIELD_NW(L"DriverLanguage", display->szDriverLanguageEnglish);
    FIELD_BOOL(L"DriverBeta", display->bDriverBeta);
    FIELD_BOOL(L"DriverDebug", display->bDriverDebug);
    FIELD_TODO(L"DriverWHQLLogo");
    FIELD_NW(L"DriverDate", display->szDriverDateEnglish);
    FIELD_TODO(L"DriverSize");
    FIELD_TODO(L"DriverProvider"); // NT5 only
    FIELD_NW(L"OtherFiles", display->szOtherDrivers);
    FIELD_TODO(L"HwAccelLevel");
    FIELD_BOOL(L"DefaultSoundPlayback", display->bDefaultSoundPlayback);
    FIELD_BOOL(L"DefaultVoicePlayback", display->bDefaultVoicePlayback);
    FIELD_BOOL(L"VoiceManager", display->bVoiceManager);
    FIELD_BOOL(L"EAX20Listener", display->bEAX20Listener);
    FIELD_BOOL(L"EAX20Source", display->bEAX20Source);
    FIELD_BOOL(L"I3DL2Listener", display->bI3DL2Listener);
    FIELD_BOOL(L"I3DL2Source", display->bI3DL2Source);
    FIELD_BOOL(L"ZoomFX", display->bZoomFX);
    FIELD_DWORD(L"Flags", display->dwFlags);
    FIELD_DWORD(L"MinSecondarySampleRate", display->dwMinSecondarySampleRate);
    FIELD_DWORD(L"MaxSecondarySampleRate", display->dwMaxSecondarySampleRate);
    FIELD_DWORD(L"PrimaryBuffers", display->dwPrimaryBuffers);
    FIELD_DWORD(L"MaxHwMixingAllBuffers", display->dwMaxHwMixingAllBuffers);
    FIELD_DWORD(L"MaxHwMixingStaticBuffers", display->dwMaxHwMixingStaticBuffers);
    FIELD_DWORD(L"MaxHwMixingStreamingBuffers", display->dwMaxHwMixingStreamingBuffers);
    FIELD_DWORD(L"FreeHwMixingAllBuffers", display->dwFreeHwMixingAllBuffers);
    FIELD_DWORD(L"FreeHwMixingStaticBuffers", display->dwFreeHwMixingStaticBuffers);
    FIELD_DWORD(L"FreeHwMixingStreamingBuffers", display->dwFreeHwMixingStreamingBuffers);
    FIELD_DWORD(L"MaxHw3DAllBuffers", display->dwMaxHw3DAllBuffers);
    FIELD_DWORD(L"MaxHw3DStaticBuffers", display->dwMaxHw3DStaticBuffers);
    FIELD_DWORD(L"MaxHw3DStreamingBuffers", display->dwMaxHw3DStreamingBuffers);
    FIELD_DWORD(L"FreeHw3DAllBuffers", display->dwFreeHw3DAllBuffers);
    FIELD_DWORD(L"FreeHw3DStaticBuffers", display->dwFreeHw3DStaticBuffers);
    FIELD_DWORD(L"FreeHw3DStreamingBuffers", display->dwFreeHw3DStreamingBuffers);
    FIELD_DWORD(L"TotalHwMemBytes", display->dwTotalHwMemBytes);
    FIELD_DWORD(L"FreeHwMemBytes", display->dwFreeHwMemBytes);
    FIELD_DWORD(L"MaxContigFreeHwMemBytes", display->dwMaxContigFreeHwMemBytes);
    FIELD_DWORD(L"UnlockTransferRateHwBuffers", display->dwUnlockTransferRateHwBuffers);
    FIELD_DWORD(L"PlayCPUOverheadSwBuffers", display->dwPlayCpuOverheadSwBuffers);
    FIELD_TODO(L"Registry"); // NT5 only

    return TRUE;
}

static BOOL fill_sound_devices(PDXDIAG_INFO dxdiag_info, PXML_INFORMATION_DATA fields)
{
    for (ULONG i = 0; i < dxdiag_info->sound_devices.ulOutputs; i++)
    {
        if (!xml_new_child(&fields[i], L"SoundDevice"))
            return FALSE;

        if (!fill_sound_device(dxdiag_info, fields[i].child->data, i))
            return FALSE;
    }

    return TRUE;
}

static BOOL fill_sound_capture_device(PDXDIAG_INFO dxdiag_info, PXML_INFORMATION_DATA fields, ULONG current)
{
    PDXDIAG_SOUND_CAPTURE_DEVICE_INFO display = &dxdiag_info->sound_devices.inputs[current];
    DWORD id = 0;

    FIELD_NW(L"Description", display->szDescription);
    FIELD_NW(L"DriverName", display->szDriverName);
    FIELD_NW(L"DriverVersion", display->szDriverVersion);
    FIELD_NW(L"DriverLanguage", display->szDriverLanguageEnglish);
    FIELD_BOOL(L"DriverBeta", display->bDriverBeta);
    FIELD_BOOL(L"DriverDebug", display->bDriverDebug);
    FIELD_NW(L"DriverDate", display->szDriverDateEnglish);
    FIELD_TODO(L"DriverSize");
    FIELD_BOOL(L"DefaultSoundRecording", display->bDefaultSoundRecording);
    FIELD_BOOL(L"DefaultVoiceRecording", display->bDefaultVoiceRecording);
    FIELD_DWORD(L"Flags", display->dwFlags);
    FIELD_DWORD(L"Formats", display->dwFormats);

    return TRUE;
}

static BOOL fill_sound_capture_devices(PDXDIAG_INFO dxdiag_info, PXML_INFORMATION_DATA fields)
{
    ULONG i = 0;

    for (; i < dxdiag_info->sound_devices.ulInputs; i++)
    {
        if (!xml_new_child(&fields[i], L"SoundCaptureDevice"))
            return FALSE;

        if (!fill_sound_capture_device(dxdiag_info, fields[i].child->data, i))
            return FALSE;
    }

    return TRUE;
}

void fill_direct_sound(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk)
{
    xml_new_block(blk, L"DirectSound");

    refresh_root((&ctx->info));

    // TODO: handle refresh of data

    if (!xml_new_child(&blk->data[0], L"SoundDevices"))
        goto error;

    if (!fill_sound_devices(&ctx->data, blk->data[0].child->data))
        goto error;

    if (!xml_new_child(&blk->data[1], L"SoundCaptureDevices"))
        goto error;

    if (!fill_sound_capture_devices(&ctx->data, blk->data[1].child->data))
        goto error;

    return;

error:

    // TODO: write something in the XML saying there was an error
    return;
}
