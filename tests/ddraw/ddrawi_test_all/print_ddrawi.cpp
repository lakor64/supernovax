#include "pch.h"

#define LCL_CAT(x) if (q & x) strcat_s(buffer, _countof(buffer), #x "|");

static const char* print_lcl_local_flags(DWORD q)
{
	static char buffer[1024] = { 0 };

	LCL_CAT(DDRAWILCL_HASEXCLUSIVEMODE);
	LCL_CAT(DDRAWILCL_ISFULLSCREEN);
	LCL_CAT(DDRAWILCL_SETCOOPCALLED);
	LCL_CAT(DDRAWILCL_ACTIVEYES);
	LCL_CAT(DDRAWILCL_ACTIVENO);
	LCL_CAT(DDRAWILCL_HOOKEDHWND);
	LCL_CAT(DDRAWILCL_ALLOWMODEX);
	LCL_CAT(DDRAWILCL_V1SCLBEHAVIOUR);
	LCL_CAT(DDRAWILCL_MODEHASBEENCHANGED);
	LCL_CAT(DDRAWILCL_CREATEDWINDOW);
	LCL_CAT(DDRAWILCL_DIRTYDC);
	LCL_CAT(DDRAWILCL_DISABLEINACTIVATE);
	LCL_CAT(DDRAWILCL_CURSORCLIPPED);
	LCL_CAT(DDRAWILCL_EXPLICITMONITOR);
	LCL_CAT(DDRAWILCL_MULTITHREADED);
	LCL_CAT(DDRAWILCL_FPUSETUP);
	LCL_CAT(DDRAWILCL_POWEREDDOWN);
	LCL_CAT(DDRAWILCL_DIRECTDRAW7);
	LCL_CAT(DDRAWILCL_ATTEMPTEDD3DCONTEXT);
	LCL_CAT(DDRAWILCL_FPUPRESERVE);
	LCL_CAT(DDRAWILCL_DX8DRIVER);
	LCL_CAT(DDRAWILCL_DIRECTDRAW8);

	return buffer;
}

void _print_surface_int(LPDDRAWI_DDRAWSURFACE_INT surf)
{
	printf("DDSURF:\n"
		"\tthis: %x\n"
		"\tlpLcl: %x\n"
		"\tlpLink: %x\n"
		"\tdwIntRefCnt: %u\n",
		surf, surf->lpLcl, surf->lpLink, surf->dwIntRefCnt);
}

void _print_ddrawi(LPDIRECTDRAW lpDD)
{
	LPDDRAWI_DIRECTDRAW_INT p = (LPDDRAWI_DIRECTDRAW_INT)lpDD;

	printf("DDINT:\n"
		"\tthis: %x\n"
		"\tlpVtbl: %x\n"
		"\tlpLcl: %x\n"
		"\tlpLink: %x\n"
		"\tdwRefCount: %u\n", 
		p,
		p->lpVtbl,
		p->lpLcl,
		p->lpLink,
		p->dwIntRefCnt
	);

	if (p->lpLcl)
	{
		printf("Current PID: %u\n"
			"DDLCL:\n"
			"\tlpDDMore: %u\n"
			"\tlpGbl: %x\n"
			"\tdwUnused0: %u\n"
			"\tdwLocalFlags: %s\n"
			"\tdwLocalRefCnt: %u\n"
			"\tdwProcessId: %u\n"
			"\tpUnkOuter: %x\n"
			"\tdwObsolete1: %u\n"
			"\thWnd: %x\n"
			"\thDC: %x\n"
			"\tdwErrorMode: %u\n"
			"\tlpPrimary: %x\n"
			"\tlpCB: %x\n"
			"\tdwPreferredMode: %u\n"
			"\thD3DInstance: %u\n"
			"\tpD3DIUnknown: %x\n"
			"\tlpDDCB: %x\n"
			"\thDDVxd: %x\n"
			"\tdwAppHackFlags: %u\n"
			"\thFocusWnd: %x\n"
			"\tdwHotTracking: %u\n"
			"\tdwIMEState: %u\n"
			"\thWndPopup: %x\n"
			"\thDD: %x\n"
			"\thGammaCalibrator: %x\n"
			"\tlpGammaCalibrator: %x\n",
			GetCurrentProcessId(),
			p->lpLcl->lpDDMore,
			p->lpLcl->lpGbl,
			p->lpLcl->dwUnused0,
			print_lcl_local_flags(p->lpLcl->dwLocalFlags),
			p->lpLcl->dwLocalRefCnt,
			p->lpLcl->dwProcessId,
			p->lpLcl->pUnkOuter,
			p->lpLcl->dwObsolete1,
			p->lpLcl->hWnd,
			p->lpLcl->hDC,
			p->lpLcl->dwErrorMode,
			p->lpLcl->lpPrimary,
			p->lpLcl->lpCB,
			p->lpLcl->dwPreferredMode,
			p->lpLcl->hD3DInstance,
			p->lpLcl->pD3DIUnknown,
			p->lpLcl->lpDDCB,
			p->lpLcl->hDDVxd,
			p->lpLcl->dwAppHackFlags,
			p->lpLcl->hFocusWnd,
			p->lpLcl->dwHotTracking,
			p->lpLcl->dwIMEState,
			p->lpLcl->hWndPopup,
			p->lpLcl->hDD,
			p->lpLcl->hGammaCalibrator,
			p->lpLcl->lpGammaCalibrator
		);

		if (p->lpLcl->lpGbl)
		{
			auto gbl = p->lpLcl->lpGbl;

			printf("DDGBL:\n"
			"\tdwRefCnt: %u\n"
			"\tdwFlags: %u\n"
			"\tfpPrimaryorig: %x\n"
			"\tdwInternal1: %u\n"
			"\tdwUnused1: %u %u %u %u %u %u %u %u %u\n"
			"\tlpDDCBtmp: %x\n"
			"\tdsList: %x\n"
			"\tpalList: %x\n"
			"\tclipperList: %x\n"
			"\tlp16DD: %x\n"
			"\tdwMaxOverlays: %u\n"
			"\tdwCurrOverlays: %u\n"
			"\tdwMonitorFrequency: %u\n"
			"\tlpDriverHandle: %x\n"
			"\tlpExclusiveOwner: %x\n"
			"\tdwModeIndex: %u\n"
			"\tdwModeIndexOrig: %u\n"
			"\tdwNumFourCC: %u\n"
			"\tlpdwFourCC: %x\n"
			"\tdwNumModes: %u\n"
			"\tlpModeInfo: %x\n"
			"\tdwSurfaceLockCount: %u\n"
			"\tdwAliasedLockCnt: %u\n"
			"\tdwReserved3: %u\n"
			"\thDCC: %u\n"
			"\tcObsolete: %s\n"
			"\tdwReserved1: %u\n"
			"\tdwReserved2: %u\n"
			"\tlpwPDeviceFlags: %u\n"
			"\tdwPDevice: %u\n"
			"\tdwWin16LockCnt: %u\n"
			"\tdwUnused3: %u\n"
			"\thInstance: %x\n"
			"\tdwEvent16: %x\n"
			"\tdwSaveNumModes: %u\n"
			"\tlpD3DGlobalDriverData: %x\n"
			"\tlpD3DHALCallbacks: %x\n"
			"\tlpDDVideoPortCaps: %x\n"
			"\tdvpList: %x\n"
			"\tlpD3DHALCallbacks2: %x\n"
			"\tcMonitors: %u\n"
			"\tgpbmiSrc: %x\n"
			"\tgpbmiDest: %x\n"
			"\tphaiHeapAliases: %x\n"
			"\thKernelHandle: %x\n"
			"\tpfnNotifyProc: %x\n"
			"\tlpDDKernelCaps: %x\n"
			"\tlpddNLVCaps: %x\n"
			"\tlpddNLVHELCaps: %x\n"
			"\tlpddNLVBothCaps: %x\n"
			"\tlpD3DExtendedCaps: %x\n"
			"\tdwDOSBoxEvent: %x\n"
			"\tcDriverName: %s\n"
			"\tlpD3DHALCallbacks3: %x\n"
			"\tdwNumZPixelFormats: %u\n"
			"\tlpZPixelFormats: %x\n"
			"\tmcList: %x\n"
			"\thDDVxd: %x\n",
				gbl->dwRefCnt,
				gbl->dwFlags,
				gbl->fpPrimaryOrig,
				gbl->dwInternal1,
				gbl->dwUnused1[0],
				gbl->dwUnused1[1], 
				gbl->dwUnused1[2], gbl->dwUnused1[3], 
				gbl->dwUnused1[4], gbl->dwUnused1[5], 
				gbl->dwUnused1[6], gbl->dwUnused1[7], 
				gbl->dwUnused1[8],
				gbl->lpDDCBtmp,
				gbl->dsList,
				gbl->palList,
				gbl->clipperList,
				gbl->lp16DD,
				gbl->dwMaxOverlays,
				gbl->dwCurrOverlays,
				gbl->dwMonitorFrequency,
				gbl->lpDriverHandle,
				gbl->lpExclusiveOwner,
				gbl->dwModeIndex,
				gbl->dwModeIndexOrig,
				gbl->dwNumFourCC,
				gbl->lpdwFourCC,
				gbl->dwNumModes,
				gbl->lpModeInfo,
				gbl->dwSurfaceLockCount,
				gbl->dwAliasedLockCnt,
				gbl->dwReserved3,
				gbl->hDD,
				gbl->cObsolete,
				gbl->dwReserved1,
				gbl->dwReserved2,
				gbl->lpwPDeviceFlags,
				gbl->dwPDevice,
				gbl->dwWin16LockCnt,
				gbl->dwUnused3,
				gbl->hInstance,
				gbl->dwEvent16,
				gbl->dwSaveNumModes,
				gbl->lpD3DGlobalDriverData,
				gbl->lpD3DHALCallbacks,
				gbl->lpDDVideoPortCaps,
				gbl->dvpList,
				gbl->lpD3DHALCallbacks2,
				gbl->cMonitors,
				gbl->gpbmiSrc,
				gbl->gpbmiDest,
				gbl->phaiHeapAliases,
				gbl->hKernelHandle,
				gbl->pfnNotifyProc,
				gbl->lpDDKernelCaps,
				gbl->lpddNLVCaps,
				gbl->lpddNLVHELCaps,
				gbl->lpddNLVBothCaps,
				gbl->lpD3DExtendedCaps,
				gbl->dwDOSBoxEvent,
				gbl->cDriverName,
				gbl->lpD3DHALCallbacks3,
				gbl->dwNumZPixelFormats,
				gbl->lpZPixelFormats,
				gbl->mcList,
				gbl->hDDVxd
				
				);
		}
	}
}
