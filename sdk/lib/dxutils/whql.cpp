/*
 * PROJECT:     ReactX Utilities
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     WHQL control functions
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */
#include "dxutils.h"
#include <SoftPub.h>
#include <mscat.h>

bool IsDriverWHQL(LPCWSTR szFileName)
{
    return false;
}

bool IsDriverWHQL(LPCSTR driverPath)
{
    return false;
}
