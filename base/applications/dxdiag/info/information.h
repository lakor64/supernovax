/*
 * PROJECT:     SupernovaX Diagnostic Tool
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     Information parsing
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 *              Copyright 2011 Andrew Nguyen
 */
#pragma once

typedef union _DXDIAG_INFO_PROPERTY_OUTPUT
{
    LPWSTR* wchar;
    PULONG ulong;
    PBOOL boool;
} DXDIAG_INFO_PROPERTY_OUTPUT, *PDXDIAG_INFO_PROPERTY_OUTPUT;

typedef struct _DXDIAG_INFO_PROPERTY_LIST
{
    LPCWSTR property_name;
    DXDIAG_INFO_PROPERTY_OUTPUT output;
} DXDIAG_INFO_PROPERTY_LIST, *PDXDIAG_INFO_PROPERTY_LIST;

void property_to_data(IDxDiagContainer* container, LPCWSTR property, PDXDIAG_INFO_PROPERTY_OUTPUT output);
BOOL exec_method(PDXDIAG_INFO_CONTEXT ctx, LPCWSTR name, UINT up);
IDxDiagContainer* get_child_container(PDXDIAG_INFO_CONTEXT ctx, LPCWSTR name);

#define refresh_root(x) if (x->root) { IDxDiagContainer_Release(x->root); x->root = NULL; }

// action: system
void free_system_information(PDXDIAG_INFO system_info);
BOOL fill_system_information(PDXDIAG_INFO_CONTEXT ctx, PDXDIAG_INFO dxdiag_info);

// action: display
BOOL refresh_display_container(PDXDIAG_INFO_CONTEXT ctx, PDXDIAG_INFO dxdiag_info);
void free_display_information(PDXDIAG_INFO dxdiag_info, ULONG id);
BOOL fill_display_information(PDXDIAG_INFO_CONTEXT ctx, PDXDIAG_INFO dxdiag_info, ULONG id);
BOOL fill_display_information_notes_only(PDXDIAG_INFO_CONTEXT ctx, PDXDIAG_INFO dxdiag_info, ULONG id);

// global
void free_dxdiag_information(PDXDIAG_INFO system_info);
BOOL init_dxdiag_context(PDXDIAG_INFO_CONTEXT ctx, BOOL whql);
void free_dxdiag_context(PDXDIAG_INFO_CONTEXT ctx);
