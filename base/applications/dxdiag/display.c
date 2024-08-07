 /*
  * PROJECT:     ReactX Diagnosis Application
  * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
  * PURPOSE:     ReactX diagnosis display page
  * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
  *				 Copyright 2008 Johannes Anderwald
  */

#include "precomp.h"
#include "gui.h"

#if 0
#include <d3d9.h>

BOOL
GetFileModifyTime(LPCWSTR pFullPath, WCHAR * szTime, int szTimeSize)
{
    HANDLE hFile;
    FILETIME AccessTime;
    SYSTEMTIME SysTime, LocalTime;
    UINT Length;

    hFile = CreateFileW(pFullPath, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (!hFile)
        return FALSE;

    if (!GetFileTime(hFile, NULL, NULL, &AccessTime))
    {
        CloseHandle(hFile);
        return FALSE;
    }
    CloseHandle(hFile);

    if (!FileTimeToSystemTime(&AccessTime, &SysTime))
        return FALSE;

    if (!SystemTimeToTzSpecificLocalTime(NULL, &SysTime, &LocalTime))
        return FALSE;

    Length = GetDateFormatW(LOCALE_USER_DEFAULT, DATE_SHORTDATE, &LocalTime, NULL, szTime, szTimeSize);
    szTime[Length-1] = L' ';
    return GetTimeFormatW(LOCALE_USER_DEFAULT, TIME_FORCE24HOURFORMAT, &LocalTime, NULL, &szTime[Length], szTimeSize-Length);
}



static UINT WINAPI
DriverFilesCallback(IN PVOID Context,
                              IN UINT Notification,
                              IN UINT_PTR Param1,
                              IN UINT_PTR Param2)
{
    LPCWSTR pFile;
    LPWSTR pBuffer;
    LPCWSTR pFullPath = (LPCWSTR)Param1;
    WCHAR szVer[60];
    LRESULT Length, fLength;
    HWND * hDlgCtrls = (HWND *)Context;

    if (wcsstr(pFullPath, L"\\DRIVERS\\"))
    {
        /* exclude files from drivers dir to have failsafe file version/date information */
        return NO_ERROR;
    }

    pFile = wcsrchr(pFullPath, L'\\');
    if (!pFile)
       return NO_ERROR;

    pFile++;
    fLength = wcslen(pFile) + 1;

    Length = SendMessageW(hDlgCtrls[0], WM_GETTEXTLENGTH, 0, 0) + 1;
    pBuffer = HeapAlloc(GetProcessHeap(), 0, (Length + fLength) * sizeof(WCHAR));
    if (!pBuffer)
        return ERROR_OUTOFMEMORY;

    Length = SendMessageW(hDlgCtrls[0], WM_GETTEXT, Length, (LPARAM)pBuffer);
    if (Length)
    {
        pBuffer[Length++] = L',';
    }
    else
    {
        /* set file version */
        if (GetFileVersion(pFullPath, szVer, sizeof(szVer)/sizeof(WCHAR)))
            SendMessageW(hDlgCtrls[1], WM_SETTEXT, 0, (LPARAM)szVer);
        /* set file time */
        if (GetFileModifyTime(pFullPath, szVer, sizeof(szVer)/sizeof(WCHAR)))
            SendMessageW(hDlgCtrls[2], WM_SETTEXT, 0, (LPARAM)szVer);
    }

    wcscpy(&pBuffer[Length], pFile);
    SendMessageW(hDlgCtrls[0], WM_SETTEXT, 0, (LPARAM)pBuffer);
    HeapFree(GetProcessHeap(), 0, pBuffer);
    return NO_ERROR;
}

VOID
EnumerateDrivers(PVOID Context, HDEVINFO hList, PSP_DEVINFO_DATA pInfoData)
{
    HSPFILEQ hQueue;
    SP_DEVINSTALL_PARAMS DeviceInstallParams = {0};
    SP_DRVINFO_DATA DriverInfoData;
    DWORD Result;

    DeviceInstallParams.cbSize = sizeof(DeviceInstallParams);
    if (!SetupDiGetDeviceInstallParamsW(hList, pInfoData, &DeviceInstallParams))
        return;

    DeviceInstallParams.FlagsEx |= (DI_FLAGSEX_INSTALLEDDRIVER | DI_FLAGSEX_ALLOWEXCLUDEDDRVS);
    if (!SetupDiSetDeviceInstallParams(hList, pInfoData, &DeviceInstallParams))
        return;

    if (!SetupDiBuildDriverInfoList(hList, pInfoData, SPDIT_CLASSDRIVER))
        return;

    DriverInfoData.cbSize = sizeof(DriverInfoData);
    if (!SetupDiEnumDriverInfoW(hList, pInfoData, SPDIT_CLASSDRIVER, 0, &DriverInfoData))
        return;

    DriverInfoData.cbSize = sizeof(DriverInfoData);
    if (!SetupDiSetSelectedDriverW(hList, pInfoData, &DriverInfoData))
         return;

    hQueue = SetupOpenFileQueue();
    if (hQueue == (HSPFILEQ)INVALID_HANDLE_VALUE)
        return;

    DeviceInstallParams.cbSize = sizeof(DeviceInstallParams);
    if (!SetupDiGetDeviceInstallParamsW(hList, pInfoData, &DeviceInstallParams))
    {
        SetupCloseFileQueue(hQueue);
        return;
    }

    DeviceInstallParams.FileQueue = hQueue;
    DeviceInstallParams.Flags |= DI_NOVCP;

    if (!SetupDiSetDeviceInstallParamsW(hList, pInfoData, &DeviceInstallParams))
    {
        SetupCloseFileQueue(hQueue);
        return;
    }

    if(!SetupDiCallClassInstaller(DIF_INSTALLDEVICEFILES, hList, pInfoData))
    {
        SetupCloseFileQueue(hQueue);
        return;
    }


    /* enumerate the driver files */
    SetupScanFileQueueW(hQueue, SPQ_SCAN_USE_CALLBACK, NULL, DriverFilesCallback, Context, &Result);
    SetupCloseFileQueue(hQueue);
}

static
void
DisplayPageSetDeviceDetails(HWND * hDlgCtrls, LPCGUID classGUID, LPGUID * deviceGUID)
{
    HDEVINFO hInfo;
    DWORD dwIndex = 0;
    SP_DEVINFO_DATA InfoData;
    WCHAR szText[100];

    /* create the setup list */
    hInfo = SetupDiGetClassDevsW(classGUID, NULL, NULL, DIGCF_PRESENT|DIGCF_PROFILE);
    if (hInfo == INVALID_HANDLE_VALUE)
        return;

    do
    {
        ZeroMemory(&InfoData, sizeof(InfoData));
        InfoData.cbSize = sizeof(InfoData);

        if (SetupDiEnumDeviceInfo(hInfo, dwIndex, &InfoData))
        {
            /* set device name */
            if (SetupDiGetDeviceRegistryPropertyW(hInfo, &InfoData, SPDRP_DEVICEDESC, NULL, (PBYTE)szText, sizeof(szText), NULL))
                SendMessageW(hDlgCtrls[0], WM_SETTEXT, 0, (LPARAM)szText);

            /* set the manufacturer name */
            if (SetupDiGetDeviceRegistryPropertyW(hInfo, &InfoData, SPDRP_MFG, NULL, (PBYTE)szText, sizeof(szText), NULL))
                SendMessageW(hDlgCtrls[1], WM_SETTEXT, 0, (LPARAM)szText);

            /* FIXME
             * we currently enumerate only the first adapter
             */
            EnumerateDrivers(&hDlgCtrls[2], hInfo, &InfoData);
            break;
        }

        if (GetLastError() == ERROR_NO_MORE_ITEMS)
            break;

        dwIndex++;
    }while(TRUE);

    /* destroy the setup list */
    SetupDiDestroyDeviceInfoList(hInfo);
}
#endif

static
BOOL
InitializeDialog(HWND hwndDlg, struct display_device* pDispDevice)
{
    WCHAR szText[100];
#if 0
    HWND hDlgCtrls[5];
#endif

    szText[0] = L'\0';

    // TODO!!
    LoadStringW(hInstance, IDS_NOT_APPLICABLE, szText, sizeof(szText)/sizeof(WCHAR));
    szText[(sizeof(szText)/sizeof(WCHAR))-1] = L'\0';
    SendDlgItemMessageW(hwndDlg, IDC_STATIC_ADAPTER_LOGO, WM_SETTEXT, 0, (LPARAM)szText);

    SendDlgItemMessageW(hwndDlg, IDC_STATIC_ADAPTER_CHIP, WM_SETTEXT, 0, (LPARAM)pDispDevice->szChipType);
    SendDlgItemMessageW(hwndDlg, IDC_STATIC_ADAPTER_DAC, WM_SETTEXT, 0, (LPARAM)pDispDevice->dacType);
    SendDlgItemMessageW(hwndDlg, IDS_FORMAT_ADAPTER_MEM, WM_SETTEXT, 0, (LPARAM)pDispDevice->szDisplayMemoryLocalized);
    SendDlgItemMessageW(hwndDlg, IDC_STATIC_ADAPTER_MODE, WM_SETTEXT, 0, (LPARAM)pDispDevice->szDisplayModeLocalized);
    SendDlgItemMessageW(hwndDlg, IDC_STATIC_ADAPTER_MONITOR, WM_SETTEXT, 0, (LPARAM)pDispDevice->szMonitorName);

#if 0
    hDlgCtrls[0] = GetDlgItem(hwndDlg, IDC_STATIC_ADAPTER_ID);
    hDlgCtrls[1] = GetDlgItem(hwndDlg, IDC_STATIC_ADAPTER_VENDOR);
    hDlgCtrls[2] = GetDlgItem(hwndDlg, IDC_STATIC_ADAPTER_DRIVER);
    hDlgCtrls[3] = GetDlgItem(hwndDlg, IDC_STATIC_ADAPTER_VERSION);
    hDlgCtrls[4] = GetDlgItem(hwndDlg, IDC_STATIC_ADAPTER_DATE);

    DisplayPageSetDeviceDetails(hDlgCtrls, &GUID_DEVCLASS_DISPLAY, NULL);
#endif

    return TRUE;
}

void InitializeDisplayAdapter(PDXDIAG_CONTEXT pContext, struct display_device* disp)
{
    HWND hwndDlg;
    WCHAR szDisplay[20];
    WCHAR szText[30];
    
    hwndDlg = CreateDialogParamW(hInstance, MAKEINTRESOURCEW(IDD_DISPLAY_DIALOG), pContext->hMainDialog, DisplayPageWndProc, (LPARAM)pContext); EnableDialogTheme(hwndDlg);
    if (!hwndDlg)
        return;

    /* initialize the dialog */
    InitializeDialog(hwndDlg, disp);

    szDisplay[0] = L'\0';
    LoadStringW(hInstance, IDS_DISPLAY_DIALOG, szDisplay, sizeof(szDisplay)/sizeof(WCHAR));
    szDisplay[(sizeof(szDisplay)/sizeof(WCHAR))-1] = L'\0';

    wsprintfW (szText, L"%s %u", szDisplay, pContext->NumDisplayAdapter + 1);
    InsertTabCtrlItem(GetDlgItem(pContext->hMainDialog, IDC_TAB_CONTROL), pContext->NumDisplayAdapter + 1, szText);

    pContext->hDisplayWnd[pContext->NumDisplayAdapter] = hwndDlg;
    pContext->NumDisplayAdapter++;

}

void InitializeDisplayAdapters(PDXDIAG_CONTEXT pContext)
{
    pContext->hDisplayWnd = HeapAlloc(GetProcessHeap(), 0, (DxDiagInfo->ulDisplays + 1) * sizeof(HWND));
    if (!pContext->hDisplayWnd)
        return;

    for (ULONG i = 0; i < DxDiagInfo->ulDisplays; i++)
    {
        InitializeDisplayAdapter(pContext, &DxDiagInfo->display_devices[i]);
    }
}


INT_PTR CALLBACK
DisplayPageWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT rect;
    PDXDIAG_CONTEXT pContext = (PDXDIAG_CONTEXT)GetWindowLongPtr(hDlg, DWLP_USER);
    switch (message)
    {
        case WM_INITDIALOG:
        {
            pContext = (PDXDIAG_CONTEXT) lParam;
            SetWindowLongPtr(hDlg, DWLP_USER, (LONG_PTR)pContext);
            SetWindowPos(hDlg, NULL, 10, 32, 0, 0, SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER);
            return TRUE;
        }
        case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case IDC_BUTTON_TESTDD:
                case IDC_BUTTON_TEST3D:
                    GetWindowRect(pContext->hMainDialog, &rect);

#if 0 // TODO: Use IDxDiagProviderPrivate for this!!
                    /* FIXME log result errors */
                    if (IDC_BUTTON_TESTDD == LOWORD(wParam))
                        DDTests();
                    else if (IDC_BUTTON_TEST3D == LOWORD(wParam))
                        D3DTests();
#endif

                    SetWindowPos(pContext->hMainDialog, NULL, rect.left, rect.top, rect.right, rect.bottom, SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER);
                    break;
            }
            break;
        }
    }

    return FALSE;
}
