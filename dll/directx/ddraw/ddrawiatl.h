/*
 * PROJECT:     SupernovaX 2D Draw
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     ATL wrapper for DDraw internal structures
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */
#pragma once

/// Global thread lock of DirectX7
extern CRITICAL_SECTION g_dd_thread_lock;

 /**
 * This structures are designed to keep compatibility with DDRAWI_DIRECTDRAW_INT.
 *
 * There are a bunch of Windows applications (like DxWndEx or some very strange game wrappers/modernizer)
 * and Direct3D7 itself that relies on the proper functionality of this structures, therefore our
 * implementations will remain compatible with the internal documented structures from Windows CE
 */

 /**
 * ATL wrapper of GBL, this is done so we can easily keep reference counting
 */
class CDirectDrawGBL : public DDRAWI_DIRECTDRAW_GBL
	, public DDObjRoot
{
public:
	/**
	* Default constructor
	*/
	explicit CDirectDrawGBL()
	{
		// We zero memory all the data in GBL to avoid issues
		ZeroMemory(this, sizeof(DDRAWI_DIRECTDRAW_GBL));
	}

	/**
	* Default deconstructor
	*/
	~CDirectDrawGBL()
	{
		if (lpDDCBtmp)
			delete lpDDCBtmp;

		if (lpModeInfo)
			delete lpModeInfo;

		if (lpD3DHALCallbacks)
			delete (reinterpret_cast<LPD3DHAL_CALLBACKS>(lpD3DHALCallbacks));

		if (lpD3DGlobalDriverData)
			delete (reinterpret_cast<LPD3DHAL_GLOBALDRIVERDATA>(lpD3DGlobalDriverData));

		if (lpdwFourCC)
			delete[] lpdwFourCC;

		if (vmiData.pvmList)
			delete[] vmiData.pvmList;

		// let the GBL free the hDD object
		if (!(dwFlags & DDRAWI_NOHARDWARE) && hDD)
			DdDeleteDirectDrawObject(this);

	}

	/**
	* Extends the basic ATL AddRef to include reference counting of the GBL pointer
    * @return Number of references after the increase
	*/
	ULONG InternalAddRef()
	{
		DDModelRoot::Increment((LPLONG) & dwRefCnt);
		return DDObjRoot::InternalAddRef();
	}

	/**
	* Extends the basic ATL Release to include reference counting of the GBL pointer
	* @return Number of references after the decrease
	*/
	ULONG InternalRelease()
	{
		DDModelRoot::Decrement((LPLONG)&dwRefCnt);
		return DDObjRoot::InternalRelease();
	}

	/**
	* Stub implementation of QueryInterface as this object doesn't have
	*  any IID associated
	* <p>
	* Note: This is provided only to use CComObject, do not call
	* </p>
	* @param[in] iid Requested interface
	* @param[out] ppvObject Output object interface
	* @return Always E_NOINTERFACE
	*/
	HRESULT _InternalQueryInterface(
		_In_ REFIID iid,
		_COM_Outptr_ void** ppvObject) throw()
	{
		return E_NOINTERFACE;
	}
};
static_assert(offsetof(CDirectDrawGBL, dwRefCnt) == 0, "Internal structure offset mismatch");
static_assert(offsetof(CDirectDrawGBL, ddsCapsMore) == sizeof(DDRAWI_DIRECTDRAW_GBL) - sizeof(DDSCAPSEX), "Internal structure offset mismatch");

/**
* ATL wrapper of LCL, this is done so we can easily keep reference counting
*/
class CDirectDrawLCL : public DDRAWI_DIRECTDRAW_LCL
	, public DDObjRoot
{
public:
	/**
	* Default constructor
	*/
	explicit CDirectDrawLCL()
	{
		// We zero memory all the data in LCL to avoid issues
		ZeroMemory(this, sizeof(DDRAWI_DIRECTDRAW_LCL));
	}

	/**
	* Default deconstructor
	*/
	~CDirectDrawLCL()
	{
		// DO NOT RELEASE THE GBL POINTER HERE, AS IT'S DONE
		//  ALREADY IN CDirectDraw

		if (hDC)
			DeleteDC(reinterpret_cast<HDC>(hDC));
	}

	/**
	* Extends the basic ATL AddRef to include reference counting of the GBL pointer
	* @return Number of references after the increase
	*/
	ULONG InternalAddRef()
	{
		return DDModelRoot::Increment((LPLONG)&dwLocalRefCnt);
	}

	/**
	* Extends the basic ATL Release to include reference counting of the LCL pointer
	* @return Number of references after the decrease
	*/
	ULONG InternalRelease()
	{
		return DDModelRoot::Decrement((LPLONG)&dwLocalRefCnt);
	}

	/**
	* Stub implementation of QueryInterface as this object doesn't have
	*  any IID associated
	* <p>
	* Note: This is provided only to use CComObject, do not call
	* </p>
	* @param[in] iid Requested interface
	* @param[out] ppvObject Output object interface
	* @return Always E_NOINTERFACE
	*/
	HRESULT _InternalQueryInterface(
		_In_ REFIID iid,
		_COM_Outptr_ void** ppvObject) throw()
	{
		return E_NOINTERFACE;
	}
};
static_assert(offsetof(CDirectDrawLCL, lpDDMore) == 0, "Internal structure offset mismatch");
static_assert(offsetof(CDirectDrawLCL, lpGammaCalibrator) == sizeof(DDRAWI_DIRECTDRAW_LCL) - sizeof(LPDDGAMMACALIBRATORPROC), "Internal structure offset mismatch");

/**
* Internal structure of DirectDraw, some applications (like game extendor/forwarders) do actually
*  use this interface
* <p>
* Note: The internal structure is implemented this way to avoid the LPVOID vftable which would break C++
* </p>
*/
class CDirectDrawINT : public IDirectDraw7
{
public:
    /**
    * Link to the local directdraw data
    */
    CDirectDrawLCL* lpLcl;

    /**
    * Link to the parent structure
    */
    CDirectDrawINT* lpLink;

    /**
    * Internal reference counter
    */
    volatile LONG dwIntRefCnt;

	/**
	* Default constructor
	*/
    explicit CDirectDrawINT() : lpLcl(nullptr), lpLink(nullptr), dwIntRefCnt(0) {}

	/**
	* Increments the reference of the object by 1
	* @return Number of references after the increase
	*/
    ULONG InternalAddRef()
    {
        return DDModelRoot::Increment((LPLONG)&dwIntRefCnt);
    }

	/**
	* Decrements the reference of the object by 1
	* @return Number of references after the decrease
	*/
	ULONG InternalRelease()
    {
        return DDModelRoot::Decrement((LPLONG)&dwIntRefCnt);
    }
};
static_assert(sizeof(CDirectDrawINT) == sizeof(DDRAWI_DIRECTDRAW_INT), "Internal structure offset mismatch");
static_assert(offsetof(CDirectDrawINT, dwIntRefCnt) == sizeof(DDRAWI_DIRECTDRAW_INT) - sizeof(DWORD), "Internal structure offset mismatch");

/**
* std::lock_guard but with the global DirectDraw mutex
*/
class CDirectDrawScopedLock final
{
public:
	/**
	* Mutex scope locking
	*/
	explicit CDirectDrawScopedLock()
	{
		EnterCriticalSection(&g_dd_thread_lock);
	}

	/**
	* Mutex scope unlocking
	*/
	~CDirectDrawScopedLock()
	{
		LeaveCriticalSection(&g_dd_thread_lock);
	}
};


/**
* ATL wrapper of Surface GBL, this is done so we can easily keep reference counting
*/
class CDirectDrawSurfaceGBL : public DDRAWI_DDRAWSURFACE_GBL
	, public DDObjRoot
{
public:
	/**
	* Default constructor
	*/
	explicit CDirectDrawSurfaceGBL()
	{
		// We zero memory all the data in GBL to avoid issues
		ZeroMemory(this, sizeof(DDRAWI_DDRAWSURFACE_GBL));
	}

	/**
	* Default deconstructor
	*/
	~CDirectDrawSurfaceGBL()
	{
	}

	/**
	* Extends the basic ATL AddRef to include reference counting of the GBL pointer
	* @return Number of references after the increase
	*/
	ULONG InternalAddRef()
	{
		DDModelRoot::Increment((LPLONG)&dwRefCnt);
		return DDObjRoot::InternalAddRef();
	}

	/**
	* Extends the basic ATL Release to include reference counting of the GBL pointer
	* @return Number of references after the decrease
	*/
	ULONG InternalRelease()
	{
		DDModelRoot::Decrement((LPLONG)&dwRefCnt);
		return DDObjRoot::InternalRelease();
	}

	/**
	* Stub implementation of QueryInterface as this object doesn't have
	*  any IID associated
	* <p>
	* Note: This is provided only to use CComObject, do not call
	* </p>
	* @param[in] iid Requested interface
	* @param[out] ppvObject Output object interface
	* @return Always E_NOINTERFACE
	*/
	HRESULT _InternalQueryInterface(
		_In_ REFIID iid,
		_COM_Outptr_ void** ppvObject) throw()
	{
		return E_NOINTERFACE;
	}
};
static_assert(offsetof(CDirectDrawSurfaceGBL, dwRefCnt) == 0, "Internal structure offset mismatch");
static_assert(offsetof(CDirectDrawSurfaceGBL, ddpfSurface) == sizeof(DDRAWI_DDRAWSURFACE_GBL) - sizeof(DDPIXELFORMAT), "Internal structure offset mismatch");

/**
* ATL wrapper of Surface LCL, this is done so we can easily keep reference counting
*/
class CDirectDrawSurfaceLCL : public DDRAWI_DDRAWSURFACE_LCL
	, public DDObjRoot
{
public:
	/**
	* Default constructor
	*/
	explicit CDirectDrawSurfaceLCL()
	{
		// We zero memory all the data in LCL to avoid issues
		ZeroMemory(this, sizeof(DDRAWI_DDRAWSURFACE_LCL));
	}

	/**
	* Default deconstructor
	*/
	~CDirectDrawSurfaceLCL()
	{
		// DO NOT RELEASE THE GBL POINTER HERE, AS IT'S DONE
		//  ALREADY IN CDirectDrawSurface
	}

	/**
	* Extends the basic ATL AddRef to include reference counting of the GBL pointer
	* @return Number of references after the increase
	*/
	ULONG InternalAddRef()
	{
		return DDModelRoot::Increment((LPLONG)&dwLocalRefCnt);
	}

	/**
	* Extends the basic ATL Release to include reference counting of the LCL pointer
	* @return Number of references after the decrease
	*/
	ULONG InternalRelease()
	{
		return DDModelRoot::Decrement((LPLONG)&dwLocalRefCnt);
	}

	/**
	* Stub implementation of QueryInterface as this object doesn't have
	*  any IID associated
	* <p>
	* Note: This is provided only to use CComObject, do not call
	* </p>
	* @param[in] iid Requested interface
	* @param[out] ppvObject Output object interface
	* @return Always E_NOINTERFACE
	*/
	HRESULT _InternalQueryInterface(
		_In_ REFIID iid,
		_COM_Outptr_ void** ppvObject) throw()
	{
		return E_NOINTERFACE;
	}
};
static_assert(offsetof(CDirectDrawSurfaceLCL, lpSurfMore) == 0, "Internal structure offset mismatch");
static_assert(offsetof(CDirectDrawSurfaceLCL, lOverlayY) == sizeof(DDRAWI_DDRAWSURFACE_LCL) - sizeof(LONG), "Internal structure offset mismatch");

/**
* Internal structure of DirectDraw surface
* </p>
*/
class CDirectDrawSurfaceINT : public IDirectDrawSurface7
{
public:
	/**
	* Link to the local directdraw data
	*/
	CDirectDrawSurfaceLCL* lpLcl;

	/**
	* Link to the parent structure
	*/
	CDirectDrawSurfaceINT* lpLink;

	/**
	* Internal reference counter
	*/
	volatile LONG dwIntRefCnt;

	/**
	* Default constructor
	*/
	explicit CDirectDrawSurfaceINT() : lpLcl(nullptr), lpLink(nullptr), dwIntRefCnt(0) {}

	/**
	* Increments the reference of the object by 1
	* @return Number of references after the increase
	*/
	ULONG InternalAddRef()
	{
		return DDModelRoot::Increment((LPLONG)&dwIntRefCnt);
	}

	/**
	* Decrements the reference of the object by 1
	* @return Number of references after the decrease
	*/
	ULONG InternalRelease()
	{
		return DDModelRoot::Decrement((LPLONG)&dwIntRefCnt);
	}
};
static_assert(sizeof(CDirectDrawSurfaceINT) == sizeof(DDRAWI_DDRAWSURFACE_INT), "Internal structure offset mismatch");
static_assert(offsetof(CDirectDrawSurfaceINT, dwIntRefCnt) == sizeof(DDRAWI_DDRAWSURFACE_INT) - sizeof(DWORD), "Internal structure offset mismatch");
