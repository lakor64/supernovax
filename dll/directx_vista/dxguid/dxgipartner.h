

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 04:14:07 2038
 */
/* Compiler settings for dxgipartner.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __dxgipartner_h__
#define __dxgipartner_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IDXGIAdapterPartner_FWD_DEFINED__
#define __IDXGIAdapterPartner_FWD_DEFINED__
typedef interface IDXGIAdapterPartner IDXGIAdapterPartner;

#endif 	/* __IDXGIAdapterPartner_FWD_DEFINED__ */


#ifndef __IDXGISwapChainPartner_FWD_DEFINED__
#define __IDXGISwapChainPartner_FWD_DEFINED__
typedef interface IDXGISwapChainPartner IDXGISwapChainPartner;

#endif 	/* __IDXGISwapChainPartner_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "dxgi.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IDXGIAdapterPartner_INTERFACE_DEFINED__
#define __IDXGIAdapterPartner_INTERFACE_DEFINED__

/* interface IDXGIAdapterPartner */
/* [uuid][local][object] */ 


EXTERN_C const IID IID_IDXGIAdapterPartner;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ffffffff-ffff-ffff-ffff-ffffffffffeb")
    IDXGIAdapterPartner : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetAdapterRole( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDXGIAdapterPartnerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDXGIAdapterPartner * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDXGIAdapterPartner * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDXGIAdapterPartner * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetAdapterRole )( 
            IDXGIAdapterPartner * This);
        
        END_INTERFACE
    } IDXGIAdapterPartnerVtbl;

    interface IDXGIAdapterPartner
    {
        CONST_VTBL struct IDXGIAdapterPartnerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDXGIAdapterPartner_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDXGIAdapterPartner_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDXGIAdapterPartner_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDXGIAdapterPartner_GetAdapterRole(This)	\
    ( (This)->lpVtbl -> GetAdapterRole(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDXGIAdapterPartner_INTERFACE_DEFINED__ */


#ifndef __IDXGISwapChainPartner_INTERFACE_DEFINED__
#define __IDXGISwapChainPartner_INTERFACE_DEFINED__

/* interface IDXGISwapChainPartner */
/* [uuid][local][object] */ 


EXTERN_C const IID IID_IDXGISwapChainPartner;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ffffffff-ffff-ffff-ffff-fffffffffffa")
    IDXGISwapChainPartner : public IDXGIDeviceSubObject
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetCompositionInterface( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAlphaMode( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFrameStatisticsPartner( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLogicalSurfaceHandle( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDXGISwapChainPartnerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDXGISwapChainPartner * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDXGISwapChainPartner * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDXGISwapChainPartner * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateData )( 
            IDXGISwapChainPartner * This,
            /* [annotation][in] */ 
            _In_  REFGUID Name,
            /* [in] */ UINT DataSize,
            /* [annotation][in] */ 
            _In_reads_bytes_(DataSize)  const void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateDataInterface )( 
            IDXGISwapChainPartner * This,
            /* [annotation][in] */ 
            _In_  REFGUID Name,
            /* [annotation][in] */ 
            _In_opt_  const IUnknown *pUnknown);
        
        HRESULT ( STDMETHODCALLTYPE *GetPrivateData )( 
            IDXGISwapChainPartner * This,
            /* [annotation][in] */ 
            _In_  REFGUID Name,
            /* [annotation][out][in] */ 
            _Inout_  UINT *pDataSize,
            /* [annotation][out] */ 
            _Out_writes_bytes_(*pDataSize)  void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *GetParent )( 
            IDXGISwapChainPartner * This,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][retval][out] */ 
            _COM_Outptr_  void **ppParent);
        
        HRESULT ( STDMETHODCALLTYPE *GetDevice )( 
            IDXGISwapChainPartner * This,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][retval][out] */ 
            _COM_Outptr_  void **ppDevice);
        
        HRESULT ( STDMETHODCALLTYPE *GetCompositionInterface )( 
            IDXGISwapChainPartner * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetAlphaMode )( 
            IDXGISwapChainPartner * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetFrameStatisticsPartner )( 
            IDXGISwapChainPartner * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetLogicalSurfaceHandle )( 
            IDXGISwapChainPartner * This);
        
        END_INTERFACE
    } IDXGISwapChainPartnerVtbl;

    interface IDXGISwapChainPartner
    {
        CONST_VTBL struct IDXGISwapChainPartnerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDXGISwapChainPartner_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDXGISwapChainPartner_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDXGISwapChainPartner_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDXGISwapChainPartner_SetPrivateData(This,Name,DataSize,pData)	\
    ( (This)->lpVtbl -> SetPrivateData(This,Name,DataSize,pData) ) 

#define IDXGISwapChainPartner_SetPrivateDataInterface(This,Name,pUnknown)	\
    ( (This)->lpVtbl -> SetPrivateDataInterface(This,Name,pUnknown) ) 

#define IDXGISwapChainPartner_GetPrivateData(This,Name,pDataSize,pData)	\
    ( (This)->lpVtbl -> GetPrivateData(This,Name,pDataSize,pData) ) 

#define IDXGISwapChainPartner_GetParent(This,riid,ppParent)	\
    ( (This)->lpVtbl -> GetParent(This,riid,ppParent) ) 


#define IDXGISwapChainPartner_GetDevice(This,riid,ppDevice)	\
    ( (This)->lpVtbl -> GetDevice(This,riid,ppDevice) ) 


#define IDXGISwapChainPartner_GetCompositionInterface(This)	\
    ( (This)->lpVtbl -> GetCompositionInterface(This) ) 

#define IDXGISwapChainPartner_SetAlphaMode(This)	\
    ( (This)->lpVtbl -> SetAlphaMode(This) ) 

#define IDXGISwapChainPartner_GetFrameStatisticsPartner(This)	\
    ( (This)->lpVtbl -> GetFrameStatisticsPartner(This) ) 

#define IDXGISwapChainPartner_GetLogicalSurfaceHandle(This)	\
    ( (This)->lpVtbl -> GetLogicalSurfaceHandle(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDXGISwapChainPartner_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


