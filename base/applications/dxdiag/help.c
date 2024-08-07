 /*
  * PROJECT:     ReactX Diagnosis Application
  * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
  * PURPOSE:     ReactX diagnosis help page
  * COPYRIGHT:   Copyright 2008 Johannes Anderwald
  */

#include "precomp.h"

INT_PTR CALLBACK
HelpPageWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    UNREFERENCED_PARAMETER(wParam);
    switch (message) {
        case WM_INITDIALOG:
        {
            SetWindowPos(hDlg, NULL, 10, 32, 0, 0, SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER);
            return TRUE;
        }
        case WM_COMMAND:
        {
            switch (LOWORD(wParam)) {
                case IDC_BUTTON_SYSINFO:
                    break;
                case IDC_BUTTON_DDRAW_REFRESH:
                    break;
            }
            break;
        }
    }

    return FALSE;
}
