 /*
  * PROJECT:     SupernovaX Diagnostic Tool
  * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
  * PURPOSE:     XML Output
  * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
  *              Copyright 2011 Andrew Nguyen
  */
#pragma once

#define wcsdup _wcsdup

#define XML_INFORMATION_DATA_MAX_BUFFER 90 // TODO: should this be replaced to dynamic init?

static inline void fill_dword(PWSTR* output, ULONG val)
{
    WCHAR tmp[20];
    swprintf_s(tmp, sizeof(tmp), L"%lu", val);
    *output = wcsdup(tmp);
}

enum xml_info
{
    XML_TYPE_NONE,
    XML_TYPE_FIELD,
    XML_TYPE_CHILD,
};

typedef struct _XML_INFORMATION_FIELD
{
    LPCWSTR tag_name;
    LPWSTR value;
    BOOL owner;
} XML_INFORMATION_FIELD, *PXML_INFORMATION_FIELD;

typedef struct _XML_INFORMATION_DATA
{
    unsigned int type;
    union 
    {
        struct _XML_INFORMATION_BLOCK* child;
        XML_INFORMATION_FIELD field;
    };
} XML_INFORMATION_DATA, *PXML_INFORMATION_DATA;

typedef struct _XML_INFORMATION_BLOCK
{
    LPCWSTR tag_name;
    XML_INFORMATION_DATA data[XML_INFORMATION_DATA_MAX_BUFFER];
} XML_INFORMATION_BLOCK, *PXML_INFORMATION_BLOCK;

static inline BOOL xml_new_child(PXML_INFORMATION_DATA pData, LPCWSTR child_tag)
{
    pData->type = XML_TYPE_CHILD;
    pData->child = (PXML_INFORMATION_BLOCK)malloc(sizeof(XML_INFORMATION_BLOCK));
    if (!pData->child)
        return FALSE;
    memset(pData->child, 0, sizeof(XML_INFORMATION_BLOCK));
    pData->child->tag_name = child_tag;
    return TRUE;
}

static inline BOOL xml_new_field(PXML_INFORMATION_DATA pData, LPCWSTR tag_name, LPCWSTR value)
{
    if (!value)
        value = L"";

    pData->type = XML_TYPE_FIELD;
    pData->field.tag_name = tag_name;
    pData->field.value = wcsdup(value);
    pData->field.owner = TRUE;
    return pData->field.value != NULL;
}

static inline void xml_new_field_nochild(PXML_INFORMATION_DATA pData, LPCWSTR tag_name, LPCWSTR value)
{
    pData->type = XML_TYPE_FIELD;
    pData->field.tag_name = tag_name;
    pData->field.value = (LPWSTR)value;
    pData->field.owner = FALSE;
}

static inline void xml_new_block(PXML_INFORMATION_BLOCK pBlock, LPCWSTR tag_name)
{
    pBlock->tag_name = tag_name;
    memset(pBlock->data, 0, sizeof(pBlock->data));
}

#define FIELD(name, val) if (!xml_new_field(&fields[id++], name, val)) return FALSE;
#define FIELD_NW(name, val) xml_new_field_nochild(&fields[id++], name, val);
#define FIELD_BOOL(name, val) FIELD_NW(name, val ? L"1" : L"0")
#define FIELD_TODO(name) FIELD_NW(name, L"TODO: Fix")

// manually done to avoid a second wcsdup
#define FIELD_DWORD(name, val) \
    fields[id].type = XML_TYPE_FIELD; \
    fields[id].field.tag_name = name; \
    fields[id].field.owner = TRUE; \
    fill_dword(&fields[id].field.value, val); \
    if (!fields[id++].field.value) return FALSE;

void fill_system(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk);
void fill_display_devices(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk);
void fill_dxdiag_notes(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk);
void fill_dx_debug_levels(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk);
void fill_direct_sound(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk);
void fill_direct_music(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk);
void fill_video_capture_dev(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk);
void fill_direct_input(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk);
void fill_direct_play(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk);
void fill_logical_disk(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk);
void fill_system_devices(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk);
void fill_dx_components(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk);
void fill_direct_show(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk);
void fill_media_foundation(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk);
void fill_evr_power_info(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk);
void fill_diagnostics(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk);
