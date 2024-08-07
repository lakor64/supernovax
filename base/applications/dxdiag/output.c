/*
 * DxDiag file information output
 *
 * Copyright 2011 Andrew Nguyen
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */
#include "precomp.h"

WINE_DEFAULT_DEBUG_CHANNEL(dxdiag);

static struct output_backend
{
    const WCHAR filename_ext[5];
    BOOL (*output_handler)(struct dxdiag_information *, const WCHAR *filename);
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

const WCHAR *get_output_extension(enum output_type type)
{
    assert(type > OUTPUT_NONE && type <= ARRAY_SIZE(output_backends));

    return output_backends[type - 1].filename_ext;
}

BOOL output_dxdiag_information(struct dxdiag_information *dxdiag_info, const WCHAR *filename, enum output_type type)
{
    assert(type > OUTPUT_NONE && type <= ARRAY_SIZE(output_backends));

    return output_backends[type - 1].output_handler(dxdiag_info, filename);
}
