/*
 * PROJECT:     SupernovaX Diagnostic Tool
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     Format output functions
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */
#pragma once

BOOL output_xml_information(PDXDIAG_CONTEXT dxdiag_info, LPCWSTR filename);
BOOL output_text_information(PDXDIAG_CONTEXT dxdiag_info, LPCWSTR filename);
