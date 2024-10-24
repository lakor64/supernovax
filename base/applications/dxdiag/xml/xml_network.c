/*
 * PROJECT:     SupernovaX Diagnostic Tool
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     XML Network output
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */
#include "precomp.h"
#include "output_xml.h"
#include "info/information.h"

static BOOL fill_net_service_provider(PDXDIAG_INFO dxdiag, PXML_INFORMATION_DATA fields, ULONG i)
{
    PDXDIAG_DPLAY_SP_INFO sp = &dxdiag->network_info.service_provider[i];
    ULONG id = 0;

    FIELD_NW(L"Name", sp->szNameEnglish);
    FIELD_TODO(L"Registry");
    FIELD_NW(L"File", sp->szFile);
    FIELD_NW(L"Version", sp->szVersionEnglish);

    return TRUE;
}

static BOOL fill_net_service_providers(PDXDIAG_INFO dxdiag, PXML_INFORMATION_DATA fields)
{
    ULONG i = 0;

    for (; i < dxdiag->network_info.ulServiceProviders; i++)
    {
        if (!xml_new_child(&fields[i], L"DirectPlayServiceProvider"))
            return FALSE;

        if (!fill_net_service_provider(dxdiag, fields[i].child->data, i))
            return FALSE;
    }

    return TRUE;
}

static BOOL fill_net_adapter(PDXDIAG_INFO dxdiag, PXML_INFORMATION_DATA fields, ULONG i)
{
    PDXDIAG_DPLAY_ADAPTER_INFO sp = &dxdiag->network_info.adapters[i];
    ULONG id = 0;

    FIELD_NW(L"Name", sp->szAdapterName);
    FIELD_NW(L"SPName", sp->szSPNameEnglish);
    FIELD_NW(L"GUID", sp->szGuid);
    FIELD_DWORD(L"Flags", sp->dwFlags);

    return TRUE;
}

static BOOL fill_net_adapters(PDXDIAG_INFO dxdiag, PXML_INFORMATION_DATA fields)
{
    ULONG i = 0;

    for (; i < dxdiag->network_info.ulAdapters; i++)
    {
        if (!xml_new_child(&fields[i], L"DirectPlayAdapters"))
            return FALSE;

        if (!fill_net_adapter(dxdiag, fields[i].child->data, i))
            return FALSE;
    }

    return TRUE;
}

static BOOL fill_net_voicecodec(PDXDIAG_INFO dxdiag, PXML_INFORMATION_DATA fields, ULONG i)
{
    PDXDIAG_NET_VOICE_CODEC_INFO sp = &dxdiag->network_info.voice_codecs[i];
    ULONG id = 0;

    FIELD_NW(L"Name", sp->szName);
    FIELD_NW(L"GUID", sp->szGuid);
    FIELD_NW(L"Description", sp->szDescription);
    FIELD_DWORD(L"Flags", sp->dwFlags);
    FIELD_DWORD(L"MaxBitsPerSecond", sp->dwMaxBitsPerSecond);

    return TRUE;
}

static BOOL fill_net_voicecodecs(PDXDIAG_INFO dxdiag, PXML_INFORMATION_DATA fields)
{
    ULONG i = 0;

    for (; i < dxdiag->network_info.ulVoiceCodecs; i++)
    {
        if (!xml_new_child(&fields[i], L"DirectPlayVoiceCodec"))
            return FALSE;
        
        if (!fill_net_voicecodec(dxdiag, fields[i].child->data, i))
            return FALSE;
    }

    return TRUE;
}

static BOOL fill_network(PDXDIAG_INFO dxdiag_info, PXML_INFORMATION_DATA fields)
{
    if (!xml_new_child(&fields[0], L"DirectPlayServiceProviders"))
        return FALSE;

    if (!fill_net_service_providers(dxdiag_info, fields[0].child->data))
        return FALSE;

    if (!xml_new_child(&fields[1], L"DirectPlayLobbyableApps"))
        return FALSE;

    // TODO!

    if (!xml_new_child(&fields[2], L"DirectPlayAdapters"))
        return FALSE;

    if (!fill_net_adapters(dxdiag_info, fields[0].child->data))
        return FALSE;

    if (!xml_new_child(&fields[3], L"DirectPlayVoiceCodecs"))
        return FALSE;

    if (!fill_net_voicecodecs(dxdiag_info, fields[0].child->data))
        return FALSE;

    xml_new_field_nochild(&fields[4], L"Registry", L"TODO: Fix");
    xml_new_field_nochild(&fields[5], L"TestResults", dxdiag_info->network_info.szTestResultEnglish);
    xml_new_field_nochild(&fields[6], L"VoiceWizardFullDuplexTest", dxdiag_info->network_info.szVoiceWizardFullDuplexTestEnglish);
    xml_new_field_nochild(&fields[7], L"VoiceWizardHalfDuplexTest", dxdiag_info->network_info.szVoiceWizardHalfDuplexTestEnglish);
    xml_new_field_nochild(&fields[8], L"VoiceWizardMicTest", dxdiag_info->network_info.szVoiceWizardMicTestEnglish);
    return TRUE;
}

void fill_direct_play(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk)
{
    xml_new_block(blk, L"DirectPlay");
    refresh_root((&ctx->info));

    // TODO: handle refresh

    if (!fill_network(&ctx->data, blk->data))
        goto error;

    return;

error:
    // TODO: handle error
    return;
}
