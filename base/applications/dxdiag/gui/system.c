 /*
  * PROJECT:     SupernovaX Diagnostic Tool
  * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
  * PURPOSE:     Diagnosis system page
  * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
  *				 Copyright 2008 Johannes Anderwald
  */
#include "precomp.h"
#include "gui.h"
#include "info/information.h"

static
VOID
InitializeSystemPage(PDXDIAG_CONTEXT pContext, HWND hwndDlg)
{
    if (!fill_system_information(&pContext->info, &pContext->data))
        return;

    SendDlgItemMessageW(hwndDlg, IDC_STATIC_TIME, WM_SETTEXT, 0, (LPARAM)pContext->data.system_info.szTimeLocalized);
    SendDlgItemMessageW(hwndDlg, IDC_STATIC_COMPUTER, WM_SETTEXT, 0, (LPARAM)pContext->data.system_info.szMachineNameLocalized);
    SendDlgItemMessageW(hwndDlg, IDC_STATIC_OS, WM_SETTEXT, 0, (LPARAM)pContext->data.system_info.szOSExLocalized);
    SendDlgItemMessageW(hwndDlg, IDC_STATIC_LANG, WM_SETTEXT, 0, (LPARAM)pContext->data.system_info.szLanguagesLocalized);
    SendDlgItemMessageW(hwndDlg, IDC_STATIC_MANU, WM_SETTEXT, 0, (LPARAM)pContext->data.system_info.szSystemManufacturerEnglish);
    SendDlgItemMessageW(hwndDlg, IDC_STATIC_MODEL, WM_SETTEXT, 0, (LPARAM)pContext->data.system_info.szSystemModelEnglish);
    SendDlgItemMessageW(hwndDlg, IDC_STATIC_PROC, WM_SETTEXT, 0, (LPARAM)pContext->data.system_info.szProcessorEnglish);
    SendDlgItemMessageW(hwndDlg, IDC_STATIC_MEM, WM_SETTEXT, 0, (LPARAM)pContext->data.system_info.szPhysicalMemoryEnglish);
    SendDlgItemMessageW(hwndDlg, IDC_STATIC_SWAP, WM_SETTEXT, 0, (LPARAM)pContext->data.system_info.szPageFileLocalized);
    SendDlgItemMessageW(hwndDlg, IDC_STATIC_VERSION, WM_SETTEXT, 0, (LPARAM)pContext->data.system_info.szDirectXVersionLongEnglish);
    SendDlgItemMessageW(hwndDlg, IDC_STATIC_BIOS, WM_SETTEXT, 0, (LPARAM)pContext->data.system_info.szBIOSEnglish);

    free_system_information(&pContext->data);
}


INT_PTR CALLBACK
SystemPageWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    UNREFERENCED_PARAMETER(wParam);
    switch (message)
    {
        case WM_INITDIALOG:
        {
            SetWindowPos(hDlg, NULL, 10, 32, 0, 0, SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER);
            InitializeSystemPage((PDXDIAG_CONTEXT)lParam, hDlg);
            return TRUE;
        }
    }

    return FALSE;
}
