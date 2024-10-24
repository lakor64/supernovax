 /*
  * PROJECT:     SupernovaX Diagnostic Tool
  * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
  * PURPOSE:     Main entrypoint
  * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
  *              Copyright 2009 Austin English
  */
#include "precomp.h"
#include "info/information.h"
#include "resource.h"

#include <CommCtrl.h>

#define wcsnicmp _wcsnicmp
#define MAX_STRING_LEN          1024

WINE_DEFAULT_DEBUG_CHANNEL(dxdiag);

HINSTANCE hInstance = NULL;

struct command_line_info
{
    WCHAR outfile[MAX_PATH];
    enum output_type output_type;
    BOOL whql_check;
};

static void usage(void)
{
    WCHAR title[MAX_STRING_LEN];
    WCHAR usage[MAX_STRING_LEN];

    LoadStringW(hInstance, IDS_MAIN_DIALOG, title, ARRAY_SIZE(title));
    LoadStringW(hInstance, IDS_USAGE, usage, ARRAY_SIZE(usage));

    MessageBoxW(NULL, usage, title, MB_OK | MB_ICONWARNING);

    ExitProcess(0);
}

static BOOL process_file_name(const WCHAR *cmdline, enum output_type output_type, WCHAR *filename, size_t filename_len)
{
    const WCHAR *endptr;
    size_t len;

    /* Skip any intervening spaces. */
    while (*cmdline == ' ')
        cmdline++;

    /* Ignore filename quoting, if any. */
    if (*cmdline == '"' && (endptr = wcsrchr(cmdline, '"')))
    {
        /* Reject a string with only one quote. */
        if (cmdline == endptr)
            return FALSE;

        cmdline++;
    }
    else
        endptr = cmdline + lstrlenW(cmdline);

    len = endptr - cmdline;
    if (len == 0 || len >= filename_len)
        return FALSE;

    memcpy(filename, cmdline, len * sizeof(WCHAR));
    filename[len] = '\0';

    /* Append an extension appropriate for the output type if the filename does not have one. */
    if (!wcsrchr(filename, '.'))
    {
        const WCHAR *filename_ext = get_output_extension(output_type);

        if (len + lstrlenW(filename_ext) >= filename_len)
            return FALSE;

        lstrcatW(filename, filename_ext);
    }

    return TRUE;
}

/*
    Process options [/WHQL:ON|OFF][/X outfile|/T outfile]
    Returns TRUE if options were present, FALSE otherwise
    Only one of /X and /T is allowed, /WHQL must come before /X and /T,
    and the rest of the command line after /X or /T is interpreted as a
    filename. If a non-option portion of the command line is encountered,
    dxdiag assumes that the string is a filename for the /T option.

    Native does not interpret quotes, but quotes are parsed here because of how
    Wine handles the command line.
*/

static BOOL process_command_line(const WCHAR *cmdline, struct command_line_info *info)
{
    info->whql_check = FALSE;
    info->output_type = OUTPUT_NONE;

    while (*cmdline)
    {
        /* Skip whitespace before arg */
        while (*cmdline == ' ')
            cmdline++;

        /* If no option is specified, treat the command line as a filename. */
        if (*cmdline != '-' && *cmdline != '/')
        {
            info->output_type = OUTPUT_TEXT;
            return process_file_name(cmdline, OUTPUT_TEXT, info->outfile,
                                     ARRAY_SIZE(info->outfile));
        }

        cmdline++;

        switch (*cmdline)
        {
        case 'T':
        case 't':
            info->output_type = OUTPUT_TEXT;
            return process_file_name(cmdline + 1, OUTPUT_TEXT, info->outfile,
                                     ARRAY_SIZE(info->outfile));
        case 'X':
        case 'x':
            info->output_type = OUTPUT_XML;
            return process_file_name(cmdline + 1, OUTPUT_XML, info->outfile,
                                     ARRAY_SIZE(info->outfile));
        case 'W':
        case 'w':
            if (wcsnicmp(cmdline, L"whql:", 5))
                return FALSE;

            cmdline += 5;

            if (!wcsnicmp(cmdline, L"off", 3))
            {
                info->whql_check = FALSE;
                cmdline += 2;
            }
            else if (!wcsnicmp(cmdline, L"on", 2))
            {
                info->whql_check = TRUE;
                cmdline++;
            }
            else
                return FALSE;

            break;

        case '6':
            if (wcsnicmp(cmdline, L"64bit", 5))
                return FALSE;
            cmdline += 5;
            break;

        case 'd':
        case 'D':
            if (wcsnicmp(cmdline, L"dontskip", 8))
                return FALSE;
            cmdline += 8;
            break;

        default:
            return FALSE;
        }

        cmdline++;
    }

    return TRUE;
}

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR cmdline, int cmdshow)
{
    struct command_line_info info;
    struct dxdiag_context ctx;

    InitCommonControls();

    hInstance = hInst;

    if (!process_command_line(cmdline, &info))
        usage();

    WINE_TRACE("WHQL check: %s\n", info.whql_check ? "TRUE" : "FALSE");
    WINE_TRACE("Output type: %d\n", info.output_type);
    if (info.output_type != OUTPUT_NONE)
        WINE_TRACE("Output filename: %s\n", debugstr_output_type(info.output_type));

    memset(&ctx, 0, sizeof(ctx));

    CoInitialize(NULL);

    if (!init_dxdiag_context(&ctx.info, info.whql_check))
    {
        CoUninitialize();
        return 1;
    }

    if (!refresh_display_container(&ctx.info, &ctx.data))
    {
        CoUninitialize();
        return 1;
    }

    if (info.output_type != OUTPUT_NONE)
        output_dxdiag_information(&ctx, info.outfile, info.output_type);
    else
        output_dxdiag_gui(&ctx);

    free_dxdiag_context(&ctx.info);
    free_dxdiag_information(&ctx.data);

    CoUninitialize();
    return 0;
}
