/*
 * PROJECT:     ReactXDraw
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     DirectDraw HEL callback
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 *              Magnus Olsen (greatlrd)
 */
#include "ddrawhel.h"
#include "helcallbacks.h"

void SetupHELCallbacks(DDRAWI_DIRECTDRAW_GBL* pGbl)
{
    pGbl->lpDDCBtmp->HELDD.dwSize = sizeof(pGbl->lpDDCBtmp->HELDD);

    pGbl->lpDDCBtmp->HELDD.dwFlags = DDHAL_CB32_CANCREATESURFACE |
        DDHAL_CB32_CREATESURFACE |
        DDHAL_CB32_CREATEPALETTE |
        DDHAL_CB32_DESTROYDRIVER |
        DDHAL_CB32_FLIPTOGDISURFACE |
        DDHAL_CB32_GETSCANLINE |
        DDHAL_CB32_SETCOLORKEY |
        DDHAL_CB32_SETEXCLUSIVEMODE |
        DDHAL_CB32_SETMODE |
        DDHAL_CB32_WAITFORVERTICALBLANK;

    pGbl->lpDDCBtmp->HELDD.DestroyDriver = HelDdDestroyDriver;
    pGbl->lpDDCBtmp->HELDD.CreateSurface = HelDdCreateSurface;
    pGbl->lpDDCBtmp->HELDD.SetColorKey = HelDdSetColorKey;
    pGbl->lpDDCBtmp->HELDD.SetMode = HelDdSetMode;
    pGbl->lpDDCBtmp->HELDD.CanCreateSurface = HelDdCanCreateSurface;
    pGbl->lpDDCBtmp->HELDD.WaitForVerticalBlank = HelDdWaitForVerticalBlank;
    pGbl->lpDDCBtmp->HELDD.CreatePalette = HelDdCreatePalette;
    pGbl->lpDDCBtmp->HELDD.GetScanLine = HelDdGetScanLine;
    pGbl->lpDDCBtmp->HELDD.SetExclusiveMode = HelDdSetExclusiveMode;
    pGbl->lpDDCBtmp->HELDD.FlipToGDISurface = HelDdFlipToGDISurface;

    pGbl->lpDDCBtmp->HELDDSurface.dwSize = sizeof(pGbl->lpDDCBtmp->HELDDSurface);

    pGbl->lpDDCBtmp->HELDDSurface.dwFlags = DDHAL_SURFCB32_ADDATTACHEDSURFACE |
        DDHAL_SURFCB32_BLT |
        DDHAL_SURFCB32_DESTROYSURFACE |
        DDHAL_SURFCB32_FLIP |
        DDHAL_SURFCB32_GETBLTSTATUS |
        DDHAL_SURFCB32_GETFLIPSTATUS |
        DDHAL_SURFCB32_LOCK |
        DDHAL_SURFCB32_RESERVED4 |
        DDHAL_SURFCB32_SETCLIPLIST |
        DDHAL_SURFCB32_SETCOLORKEY |
        DDHAL_SURFCB32_SETOVERLAYPOSITION |
        DDHAL_SURFCB32_SETPALETTE |
        DDHAL_SURFCB32_UNLOCK |
        DDHAL_SURFCB32_UPDATEOVERLAY;

    pGbl->lpDDCBtmp->HELDDSurface.DestroySurface = HelDdSurfDestroySurface;
    pGbl->lpDDCBtmp->HELDDSurface.Flip = HelDdSurfFlip;
    pGbl->lpDDCBtmp->HELDDSurface.SetClipList = HelDdSurfSetClipList;
    pGbl->lpDDCBtmp->HELDDSurface.Lock = HelDdSurfLock;
    pGbl->lpDDCBtmp->HELDDSurface.Unlock = HelDdSurfUnlock;
    pGbl->lpDDCBtmp->HELDDSurface.Blt = HelDdSurfBlt;
    pGbl->lpDDCBtmp->HELDDSurface.SetColorKey = HelDdSurfSetColorKey;
    pGbl->lpDDCBtmp->HELDDSurface.AddAttachedSurface = HelDdSurfAddAttachedSurface;
    pGbl->lpDDCBtmp->HELDDSurface.GetBltStatus = HelDdSurfGetBltStatus;
    pGbl->lpDDCBtmp->HELDDSurface.GetFlipStatus = HelDdSurfGetFlipStatus;
    pGbl->lpDDCBtmp->HELDDSurface.UpdateOverlay = HelDdSurfUpdateOverlay;
    pGbl->lpDDCBtmp->HELDDSurface.SetOverlayPosition = HelDdSurfSetOverlayPosition;
    pGbl->lpDDCBtmp->HELDDSurface.reserved4 = HelDdSurfreserved4;
    pGbl->lpDDCBtmp->HELDDSurface.SetPalette = HelDdSurfSetPalette;
}
