/*
 * PROJECT:     SupernovaX Diagnostic Tool
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     Diagnosis gui entry
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 *				Copyright 2008 Johannes Anderwald
 */
#include "precomp.h"
#include "gui.h"
#include <Uxtheme.h>

HWND hTabCtrlWnd = NULL;

 //
typedef HRESULT(WINAPI* ETDTProc) (HWND, DWORD);

 //
 //	Try to call EnableThemeDialogTexture, if uxtheme.dll is present
 //
BOOL EnableDialogTheme(HWND hwnd)
{
    HMODULE hUXTheme;
    ETDTProc fnEnableThemeDialogTexture;

    hUXTheme = LoadLibraryA("uxtheme.dll");

    if (hUXTheme)
    {
        fnEnableThemeDialogTexture =
            (ETDTProc)GetProcAddress(hUXTheme, "EnableThemeDialogTexture");

        if (fnEnableThemeDialogTexture)
        {
            fnEnableThemeDialogTexture(hwnd, ETDT_ENABLETAB);

            FreeLibrary(hUXTheme);
            return TRUE;
        }
        else
        {
            // Failed to locate API!
            FreeLibrary(hUXTheme);
            return FALSE;
        }
    }
    else
    {
        // Not running under XP? Just fail gracefully
        return FALSE;
    }
}


//---------------------------------------------------------------
VOID
DestroyTabCtrlDialogs(PDXDIAG_CONTEXT pContext)
{
    UINT Index;

    /* destroy default dialogs */
    for (Index = 0; Index < sizeof(pContext->gui.hDialogs) / sizeof(HWND); Index++)
    {
        if (pContext->gui.hDialogs[Index])
            DestroyWindow(pContext->gui.hDialogs[Index]);
    }

    /* destroy display dialogs */
    for (Index = 0; Index < pContext->data.ulDisplays; Index++)
    {
        if (pContext->gui.hDisplayWnd[Index])
            DestroyWindow(pContext->gui.hDisplayWnd[Index]);
    }

    /* destroy audio dialogs */
    for (Index = 0; Index < pContext->data.sound_devices.ulOutputs; Index++)
    {
        if (pContext->gui.hSoundWnd[Index])
            DestroyWindow(pContext->gui.hSoundWnd[Index]);
    }

}

//---------------------------------------------------------------
VOID
InsertTabCtrlItem(HWND hDlgCtrl, INT Position, LPWSTR uId)
{
    WCHAR szName[100];
    TCITEMW item;

    /* setup item info */
    memset(&item, 0, sizeof(TCITEMW));
    item.mask = TCIF_TEXT;

    /* load item name */
    if (!HIWORD(uId))
    {
        szName[0] = L'\0';
        if (!LoadStringW(hInstance, LOWORD(uId), szName, 100))
            return;
        szName[99] = L'\0';
        item.pszText = szName;
    }
    else
    {
        item.pszText = uId;
    }


    SendMessageW(hDlgCtrl, TCM_INSERTITEM, Position, (LPARAM)&item);
}

VOID
TabCtrl_OnSelChange(PDXDIAG_CONTEXT pContext)
{
    ULONG Index;
    ULONG CurSel;

    /* retrieve new page */
    CurSel = TabCtrl_GetCurSel(hTabCtrlWnd);
    if (CurSel < 0 || CurSel > pContext->data.ulDisplays + pContext->data.sound_devices.ulOutputs + 5)
        return;

    /* hide all windows */
    for (Index = 0; Index < 5; Index++)
        ShowWindow(pContext->gui.hDialogs[Index], SW_HIDE);

    for (Index = 0; Index < pContext->data.ulDisplays; Index++)
        ShowWindow(pContext->gui.hDisplayWnd[Index], SW_HIDE);

    for (Index = 0; Index < pContext->data.sound_devices.ulOutputs; Index++)
        ShowWindow(pContext->gui.hSoundWnd[Index], SW_HIDE);


    if (CurSel == 0 || CurSel > pContext->data.ulDisplays + pContext->data.sound_devices.ulOutputs)
    {
        if (CurSel)
            CurSel -= pContext->data.ulDisplays + pContext->data.sound_devices.ulOutputs;
        ShowWindow(pContext->gui.hDialogs[CurSel], SW_SHOW);
        return;
    }

    if (CurSel - 1 < pContext->data.ulDisplays)
    {
        ShowWindow(pContext->gui.hDisplayWnd[CurSel - 1], SW_SHOW);
        return;
    }

    CurSel -= pContext->data.ulDisplays + 1;
    ShowWindow(pContext->gui.hSoundWnd[CurSel], SW_SHOW);
}

VOID
InitializeTabCtrl(HWND hwndDlg, PDXDIAG_CONTEXT pContext)
{
    /* get tabctrl */
    hTabCtrlWnd = GetDlgItem(hwndDlg, IDC_TAB_CONTROL);
    pContext->gui.hTabCtrl = hTabCtrlWnd;

    /* create the dialogs */
    pContext->gui.hDialogs[0] = CreateDialogParamW(hInstance, MAKEINTRESOURCEW(IDD_SYSTEM_DIALOG), pContext->gui.hTabCtrl, SystemPageWndProc, (LPARAM)pContext); EnableDialogTheme(pContext->gui.hDialogs[0]);
    pContext->gui.hDialogs[1] = CreateDialogParamW(hInstance, MAKEINTRESOURCEW(IDD_MUSIC_DIALOG), pContext->gui.hTabCtrl, MusicPageWndProc, (LPARAM)pContext); EnableDialogTheme(pContext->gui.hDialogs[1]);
    pContext->gui.hDialogs[2] = CreateDialogParamW(hInstance, MAKEINTRESOURCEW(IDD_INPUT_DIALOG), pContext->gui.hTabCtrl, InputPageWndProc, (LPARAM)pContext); EnableDialogTheme(pContext->gui.hDialogs[2]);
    pContext->gui.hDialogs[3] = CreateDialogParamW(hInstance, MAKEINTRESOURCEW(IDD_NETWORK_DIALOG), pContext->gui.hTabCtrl, NetworkPageWndProc, (LPARAM)pContext); EnableDialogTheme(pContext->gui.hDialogs[3]);
    pContext->gui.hDialogs[4] = CreateDialogParamW(hInstance, MAKEINTRESOURCEW(IDD_HELP_DIALOG), pContext->gui.hTabCtrl, HelpPageWndProc, (LPARAM)pContext); EnableDialogTheme(pContext->gui.hDialogs[4]);

#if 0
    /* insert tab ctrl items */
    InsertTabCtrlItem(hTabCtrlWnd, 0, MAKEINTRESOURCEW(IDS_SYSTEM_DIALOG));
    InitializeDisplayAdapters(pContext);
    InitializeDirectSoundPage(pContext);
    InsertTabCtrlItem(hTabCtrlWnd, pContext->data.ulDisplays + pContext->data.sound_devices.ulOutputs + 1, MAKEINTRESOURCEW(IDS_MUSIC_DIALOG));
    InsertTabCtrlItem(hTabCtrlWnd, pContext->data.ulDisplays + pContext->data.sound_devices.ulOutputs + 2, MAKEINTRESOURCEW(IDS_INPUT_DIALOG));
    InsertTabCtrlItem(hTabCtrlWnd, pContext->data.ulDisplays + pContext->data.sound_devices.ulOutputs + 3, MAKEINTRESOURCEW(IDS_NETWORK_DIALOG));
    InsertTabCtrlItem(hTabCtrlWnd, pContext->data.ulDisplays + pContext->data.sound_devices.ulOutputs + 4, MAKEINTRESOURCEW(IDS_HELP_DIALOG));
    TabCtrl_OnSelChange(pContext);
#endif
}

VOID
InitializeDxDiagDialog(PDXDIAG_CONTEXT pContext, HWND hwndDlg)
{
    HICON hIcon;

    /* store window handle */
    pContext->gui.hMainDialog = hwndDlg;

    /* store the context */
    SetWindowLongPtr(hwndDlg, DWLP_USER, (LONG_PTR)pContext);

    /* initialize the tab ctrl */
    InitializeTabCtrl(hwndDlg, pContext);

    /* load application icon */
    hIcon = LoadImageW(hInstance, MAKEINTRESOURCEW(IDI_APPICON), IMAGE_ICON, 16, 16, 0);
    if (!hIcon)
        return;
    /* display icon */
    SendMessage(hwndDlg, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
}


INT_PTR CALLBACK
DxDiagWndProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    LPNMHDR         pnmh;
    PDXDIAG_CONTEXT pContext;

    pContext = (PDXDIAG_CONTEXT)GetWindowLongPtr(hwndDlg, DWLP_USER);

    switch (message)
    {
    case WM_INITDIALOG:
        InitializeDxDiagDialog((PDXDIAG_CONTEXT)lParam, hwndDlg);
        return TRUE;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDC_BUTTON_SAVE_INFO)
        {
            //TODO
            /* handle save information */
            return TRUE;
        }

        if (LOWORD(wParam) == IDC_BUTTON_NEXT)
        {
            INT CurSel;

            /* retrieve current page */
            CurSel = TabCtrl_GetCurSel(hTabCtrlWnd);
            CurSel++;

            /* enable/disable next button */
            EnableWindow(GetDlgItem(hwndDlg, IDC_BUTTON_NEXT),
                (CurSel != TabCtrl_GetItemCount(hTabCtrlWnd) - 1));

            /* switch to next tab */
            SendMessageW(hTabCtrlWnd, TCM_SETCURSEL, CurSel, 0L);

            /* show next page */
            TabCtrl_OnSelChange(pContext);
            return TRUE;
        }

        if (LOWORD(wParam) == IDC_BUTTON_HELP)
        {
            //TODO
            /* handle help button */
            return TRUE;
        }

        if (LOWORD(wParam) == IDCANCEL || LOWORD(wParam) == IDC_BUTTON_EXIT) {
            EndDialog(hwndDlg, LOWORD(wParam));
            return TRUE;
        }
        break;

    case WM_NOTIFY:
        pnmh = (LPNMHDR)lParam;
        if ((pnmh->hwndFrom == hTabCtrlWnd) && (pnmh->idFrom == IDC_TAB_CONTROL) && (pnmh->code == TCN_SELCHANGE))
        {
            INT CurSel = TabCtrl_GetCurSel(hTabCtrlWnd);

            /* enable/disable next button */
            EnableWindow(GetDlgItem(hwndDlg, IDC_BUTTON_NEXT),
                (CurSel != TabCtrl_GetItemCount(hTabCtrlWnd) - 1));

            TabCtrl_OnSelChange(pContext);
        }
        break;
    case WM_DESTROY:
        DestroyTabCtrlDialogs(pContext);
        return DefWindowProc(hwndDlg, message, wParam, lParam);
    }
    return 0;
}

void output_dxdiag_gui(PDXDIAG_CONTEXT dxdiag_info)
{
    DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_MAIN_DIALOG), NULL, DxDiagWndProc, (LPARAM)dxdiag_info);
}
