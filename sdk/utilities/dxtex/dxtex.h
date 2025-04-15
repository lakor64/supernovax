//--------------------------------------------------------------------------------------
// DirectX Texture Tool (dxtex.exe)
//
// File: dxtex.h
//
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------

#pragma once

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#ifndef ReleasePpo
    #define ReleasePpo(ppo) \
        if (*(ppo) != nullptr) \
        { \
            (*(ppo))->Release(); \
            *(ppo) = nullptr; \
        } \
        else (void)0
#endif

/////////////////////////////////////////////////////////////////////////////
// CDxtexDocManager:
// I override this class to customize DoPromptFileName to allow importing of
// BMPs as well as DDSs into CDxtexDocs.
//
class CDxtexDocManager : public CDocManager
{
public:
    virtual BOOL DoPromptFileName(CString& fileName, UINT nIDSTitle,
            DWORD lFlags, BOOL bOpenFileDialog, CDocTemplate* pTemplate);
};

/////////////////////////////////////////////////////////////////////////////
// CDxtexCommandLineInfo:
// I override this class to handle custom command-line options
//
class CDxtexCommandLineInfo : public CCommandLineInfo
{
public:
    CString m_strFileNameAlpha;
    CString m_strFileNameSave;
    D3DFORMAT m_fmt;
    BOOL m_bAlphaComing;
    BOOL m_bMipMap;

    CDxtexCommandLineInfo();
    virtual void ParseParam(const TCHAR* pszParam, BOOL bFlag, BOOL bLast);

};

/////////////////////////////////////////////////////////////////////////////
// CDxtexApp:
// See dxtex.cpp for the implementation of this class
//

class CDxtexApp : public CWinApp
{
public:
    CDxtexApp();
    virtual ~CDxtexApp();
    LPDIRECT3D9 Pd3d() const noexcept { return m_pd3d; }
    LPDIRECT3DDEVICE9 Pd3ddev() const noexcept { return m_pd3ddev; }
    BOOL HandlePossibleLostDevice();
    void DeviceIsLost() noexcept { m_bDeviceLost = TRUE; }
    HRESULT InvalidateDeviceObjects();
    HRESULT RestoreDeviceObjects();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDxtexApp)
    public:
    virtual BOOL InitInstance();
    //}}AFX_VIRTUAL

// Implementation
    //{{AFX_MSG(CDxtexApp)
    afx_msg void OnAppAbout();
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
private:
    LPDIRECT3D9 m_pd3d;
    LPDIRECT3DDEVICE9 m_pd3ddev;
    BOOL m_bDeviceLost;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
