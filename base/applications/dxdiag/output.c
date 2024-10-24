 /*
  * PROJECT:     SupernovaX Diagnostic Tool
  * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
  * PURPOSE:     File information output
  * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
  *              Copyright 2011 Andrew Nguyen
  */
#include "precomp.h"
#include "output.h"
#include "gui/gui.h"

WINE_DEFAULT_DEBUG_CHANNEL(dxdiag);

static struct output_backend
{
    const WCHAR filename_ext[5];
    BOOL (*output_handler)(PDXDIAG_CONTEXT ctx, LPCWSTR filename);
} output_backends[] =
{
    /* OUTPUT_TEXT */
    {
        L".txt", output_text_information,
    },
    /* OUTPUT_XML */
    {
        L".xml", output_xml_information,
    },
};

LPCWSTR get_output_extension(enum output_type type)
{
    assert(type > OUTPUT_NONE && type <= ARRAY_SIZE(output_backends));

    return output_backends[type - 1].filename_ext;
}

BOOL output_dxdiag_information(PDXDIAG_CONTEXT ctx, LPCWSTR filename, enum output_type type)
{
    assert(type > OUTPUT_NONE && type <= ARRAY_SIZE(output_backends));

    return output_backends[type - 1].output_handler(ctx, filename);
}
