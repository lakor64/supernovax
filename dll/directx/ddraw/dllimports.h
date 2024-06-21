/*
 * PROJECT:     ReactXDraw
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     DLL Imports
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */
#pragma once

#undef DdCreateDirectDrawObject
#undef DdDeleteDirectDrawObject
#undef DdQueryDirectDrawObject
#undef DdQueryDisplaySettingsUniqueness
#undef DdReenableDirectDrawObject

// gdi32.dll
typedef BOOL(NTAPI* DdCreateDirectDrawObject_)(_In_ LPDDRAWI_DIRECTDRAW_GBL pDirectDrawGlobal, _In_ HDC hdc);
typedef BOOL(NTAPI* DdDeleteDirectDrawObject_)(_In_ LPDDRAWI_DIRECTDRAW_GBL pDirectDrawGlobal);
typedef ULONG(NTAPI* DdQueryDisplaySettingsUniqueness_)(VOID);
typedef BOOL(NTAPI* DdQueryDirectDrawObject_)(_In_ LPDDRAWI_DIRECTDRAW_GBL pDirectDrawGlobal, _Out_ LPDDHALINFO pHalInfo, _Out_ LPDDHAL_DDCALLBACKS pDDCallbacks, _Out_ LPDDHAL_DDSURFACECALLBACKS pDDSurfaceCallbacks, _Out_ LPDDHAL_DDPALETTECALLBACKS pDDPaletteCallbacks, _Out_ LPD3DHAL_CALLBACKS pD3dCallbacks, _Out_ LPD3DHAL_GLOBALDRIVERDATA pD3dDriverData, _Out_ LPDDHAL_DDEXEBUFCALLBACKS pD3dBufferCallbacks, _Out_ LPDDSURFACEDESC pD3dTextureFormats, _Out_ LPDWORD pdwFourCC, _Out_ LPVIDMEM pvmList);
typedef BOOL(NTAPI* DdReenableDirectDrawObject_)(_In_ LPDDRAWI_DIRECTDRAW_GBL pDirectDrawGlobal, _Out_ BOOL* pbNewMode);

/// Global pointer to DdCreateDirectDrawObject
extern DdCreateDirectDrawObject_ DdCreateDirectDrawObject;

/// Global pointer to DdDeleteDirectDrawObject
extern DdDeleteDirectDrawObject_ DdDeleteDirectDrawObject;

/// Global pointer to DdQueryDisplaySettingsUniqueness
extern DdQueryDisplaySettingsUniqueness_ DdQueryDisplaySettingsUniqueness;

/// Global pointer to DdQueryDirectDrawObject
extern DdQueryDirectDrawObject_ DdQueryDirectDrawObject;

/// Global pointer to DdReenableDirectDrawObject
extern DdReenableDirectDrawObject_ DdReenableDirectDrawObject;
