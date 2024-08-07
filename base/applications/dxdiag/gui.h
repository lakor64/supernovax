/*
 * PROJECT:     ReactX Diagnosis Application
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     ReactX diagnosis gui entry
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 *				Copyright 2008 Johannes Anderwald
 */

#ifndef _DXDIAG_GUI_H_
#define _DXDIAG_GUI_H_

/* globals */
extern HWND hTabCtrlWnd;
extern struct dxdiag_information* DxDiagInfo;

/* theming hack */
BOOL EnableDialogTheme(HWND hwnd);

/* dialog wnd proc */
INT_PTR CALLBACK SystemPageWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK DisplayPageWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK SoundPageWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK MusicPageWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK InputPageWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK NetworkPageWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK HelpPageWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

/* DirectSound initialization */
void InitializeDirectSoundPage(PDXDIAG_CONTEXT pContext);

/* display adapter initialization */
void InitializeDisplayAdapters(PDXDIAG_CONTEXT pContext);

VOID InsertTabCtrlItem(HWND hDlgCtrl, INT Position, LPWSTR uId);

#endif
