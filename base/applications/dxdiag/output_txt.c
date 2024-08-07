/*
 * DxDiag txt file information output
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

static char output_buffer[1024];
static const char crlf[2] = "\r\n";

struct text_information_field
{
    const char* field_name;
    const WCHAR* value;
};

static BOOL output_text_header(HANDLE hFile, const char* caption)
{
    DWORD len = strlen(caption);
    DWORD total_len = 3 * (len + sizeof(crlf));
    char* ptr = output_buffer;
    DWORD bytes_written;

    assert(total_len <= sizeof(output_buffer));

    memset(ptr, '-', len);
    ptr += len;

    memcpy(ptr, crlf, sizeof(crlf));
    ptr += sizeof(crlf);

    memcpy(ptr, caption, len);
    ptr += len;

    memcpy(ptr, crlf, sizeof(crlf));
    ptr += sizeof(crlf);

    memset(ptr, '-', len);
    ptr += len;

    memcpy(ptr, crlf, sizeof(crlf));

    return WriteFile(hFile, output_buffer, total_len, &bytes_written, NULL);
}

static BOOL output_text_field(HANDLE hFile, const char* field_name, DWORD field_width, const WCHAR* value)
{
    DWORD value_lenW = lstrlenW(value);
    DWORD value_lenA = WideCharToMultiByte(CP_ACP, 0, value, value_lenW, NULL, 0, NULL, NULL);
    DWORD total_len = field_width + sizeof(": ") - 1 + value_lenA + sizeof(crlf);
    char sprintf_fmt[1 + 10 + 3 + 1];
    char* ptr = output_buffer;
    DWORD bytes_written;

    assert(total_len <= sizeof(output_buffer));

    sprintf(sprintf_fmt, "%%%lus: ", field_width);
    ptr += sprintf(ptr, sprintf_fmt, field_name);

    ptr += WideCharToMultiByte(CP_ACP, 0, value, value_lenW, ptr, value_lenA, NULL, NULL);
    memcpy(ptr, crlf, sizeof(crlf));

    return WriteFile(hFile, output_buffer, total_len, &bytes_written, NULL);
}

static BOOL output_crlf(HANDLE hFile)
{
    DWORD bytes_written;
    return WriteFile(hFile, crlf, sizeof(crlf), &bytes_written, NULL);
}

static inline void fill_system_text_output_table(struct dxdiag_information* dxdiag_info, struct text_information_field* fields)
{
    fields[0].field_name = "Time of this report";
    fields[0].value = dxdiag_info->system_info.szTimeEnglish;
    fields[1].field_name = "Machine name";
    fields[1].value = dxdiag_info->system_info.szMachineNameEnglish;
    fields[2].field_name = "Operating System";
    fields[2].value = dxdiag_info->system_info.szOSExLongEnglish;
    fields[3].field_name = "Language";
    fields[3].value = dxdiag_info->system_info.szLanguagesEnglish;
    fields[4].field_name = "System Manufacturer";
    fields[4].value = dxdiag_info->system_info.szSystemManufacturerEnglish;
    fields[5].field_name = "System Model";
    fields[5].value = dxdiag_info->system_info.szSystemModelEnglish;
    fields[6].field_name = "BIOS";
    fields[6].value = dxdiag_info->system_info.szBIOSEnglish;
    fields[7].field_name = "Processor";
    fields[7].value = dxdiag_info->system_info.szProcessorEnglish;
    fields[8].field_name = "Memory";
    fields[8].value = dxdiag_info->system_info.szPhysicalMemoryEnglish;
    fields[9].field_name = "Page File";
    fields[9].value = dxdiag_info->system_info.szPageFileEnglish;
    fields[10].field_name = "Windows Dir";
    fields[10].value = dxdiag_info->system_info.szWindowsDir;
    fields[11].field_name = "DirectX Version";
    fields[11].value = dxdiag_info->system_info.szDirectXVersionLongEnglish;
    fields[12].field_name = "DX Setup Parameters";
    fields[12].value = dxdiag_info->system_info.szSetupParamEnglish;
    fields[13].field_name = "DxDiag Version";
    fields[13].value = dxdiag_info->system_info.szDxDiagVersion;
}

BOOL output_text_information(struct dxdiag_information* dxdiag_info, const WCHAR* filename)
{
    struct information_block
    {
        const char* caption;
        const size_t field_width;
        struct text_information_field fields[50];
    } output_table[] =
    {
        {"System Information", 19},
    };

    HANDLE hFile;
    size_t i;

    fill_system_text_output_table(dxdiag_info, output_table[0].fields);

    hFile = CreateFileW(filename, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        WINE_ERR("File creation failed, last error %lu\n", GetLastError());
        return FALSE;
    }

    for (i = 0; i < ARRAY_SIZE(output_table); i++)
    {
        const struct text_information_field* fields = output_table[i].fields;
        unsigned int j;

        output_text_header(hFile, output_table[i].caption);
        for (j = 0; fields[j].field_name; j++)
            output_text_field(hFile, fields[j].field_name, output_table[i].field_width, fields[j].value);
        output_crlf(hFile);
    }

    CloseHandle(hFile);
    return FALSE;
}
