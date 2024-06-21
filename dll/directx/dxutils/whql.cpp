/*
 * PROJECT:     ReactX Utilities
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     WHQL control functions
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 *              Copyright 2008 Johannes Anderwald
 */
#include "dxutils.h"
#include <SoftPub.h>
#include <mscat.h>

static bool GetCatInfoFromDriverPath(LPCWSTR szFileName, WINTRUST_CATALOG_INFO* lpCatalog)
{
    GUID VerifyGuid = DRIVER_ACTION_VERIFY;
    HCATINFO hCatInfo;
    HCATADMIN hActAdmin;
    CATALOG_INFO CatInfo;

    // attempt to open file
    lpCatalog->pcwszMemberFilePath = szFileName;
    lpCatalog->hMemberFile = CreateFileW(szFileName, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (lpCatalog->hMemberFile == INVALID_HANDLE_VALUE)
        return false;

    // calculate hash from file handle
    if (!CryptCATAdminCalcHashFromFileHandle(lpCatalog->hMemberFile, &lpCatalog->cbCalculatedFileHash, nullptr, 0))
        return false;

    lpCatalog->pbCalculatedFileHash = new BYTE[lpCatalog->cbCalculatedFileHash];
    if (!lpCatalog->pbCalculatedFileHash)
        return false;

    if (!CryptCATAdminCalcHashFromFileHandle(lpCatalog->hMemberFile, &lpCatalog->cbCalculatedFileHash, lpCatalog->pbCalculatedFileHash, 0))
        return false;

    // try open the CAT admin
    if (!CryptCATAdminAcquireContext(&hActAdmin, &VerifyGuid, 0))
        return false;

    // search catalog to find for catalog containing this hash
    hCatInfo = CryptCATAdminEnumCatalogFromHash(hActAdmin, lpCatalog->pbCalculatedFileHash, lpCatalog->cbCalculatedFileHash, 0, nullptr);
    if (hCatInfo != nullptr)
    {
        // theres a catalog get the filename
        if (CryptCATCatalogInfoFromContext(hCatInfo, &CatInfo, 0))
        {
            auto len = wcslen(CatInfo.wszCatalogFile) + 1;
            lpCatalog->pcwszCatalogFilePath = new WCHAR[len];
            if (lpCatalog->pcwszCatalogFilePath)
                wcscpy_s((LPWSTR)lpCatalog->pcwszCatalogFilePath, len * 2, CatInfo.wszCatalogFile);
        }

        CryptCATAdminReleaseCatalogContext(hActAdmin, hCatInfo, 0);
    }

    // perform cleanup
    CryptCATAdminReleaseContext(hActAdmin, 0);
    return lpCatalog->pcwszCatalogFilePath != nullptr;
}

static void FreeCatInfo(WINTRUST_CATALOG_INFO* lpCat)
{
    if (lpCat->pcwszCatalogFilePath)
        delete[] lpCat->pcwszCatalogFilePath;

    if (lpCat->pbCalculatedFileHash)
        delete[] lpCat->pbCalculatedFileHash;

    if (lpCat->hMemberFile != INVALID_HANDLE_VALUE)
        CloseHandle(lpCat->hMemberFile);
}

bool IsDriverWHQL(LPCWSTR szFileName)
{
    WINTRUST_CATALOG_INFO cat = { 0 };
    cat.cbStruct = sizeof(cat);

    // get the driver's cat file
    if (!GetCatInfoFromDriverPath(szFileName, &cat))
    {
        // driver has no cat so it's definitely not WHQL signed
        FreeCatInfo(&cat);
        return false;
    }

    WINTRUST_DATA data = { 0 };
    data.cbStruct = sizeof(data);
    data.dwUIChoice = WTD_UI_NONE;
    data.fdwRevocationChecks = WTD_REVOKE_NONE;
    data.dwUnionChoice = WTD_CHOICE_CATALOG;
    data.pCatalog = &cat;
    data.dwStateAction = WTD_STATEACTION_VERIFY;

    GUID act = DRIVER_ACTION_VERIFY;
    ULONG m = WinVerifyTrust((HWND)INVALID_HANDLE_VALUE, &act, &data);
    FreeCatInfo(&cat);

    return m == 0;
}

bool IsDriverWHQL(LPCSTR driverPath)
{
	auto len = MultiByteToWideChar(CP_ACP, 0, driverPath, -1, nullptr, 0);

	if (len < 1)
	{
		return false;
	}

	LPWSTR driverPathW = new WCHAR[len+1];
	if (MultiByteToWideChar(CP_ACP, 0, driverPath, -1, driverPathW, len) != len)
	{
		delete[] driverPathW;
		return false;
	}

	auto b = IsDriverWHQL(driverPathW);
	delete[] driverPathW;
	return b;
}
