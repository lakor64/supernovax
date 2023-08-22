

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 04:14:07 2038
 */
/* Compiler settings for dxgixaml.idl:
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

#ifndef __dxgixaml_h__
#define __dxgixaml_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IDXGISwapChainXAML_FWD_DEFINED__
#define __IDXGISwapChainXAML_FWD_DEFINED__
typedef interface IDXGISwapChainXAML IDXGISwapChainXAML;

#endif 	/* __IDXGISwapChainXAML_FWD_DEFINED__ */


#ifndef __IDXGIDeviceXAML_FWD_DEFINED__
#define __IDXGIDeviceXAML_FWD_DEFINED__
typedef interface IDXGIDeviceXAML IDXGIDeviceXAML;

#endif 	/* __IDXGIDeviceXAML_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "dxgi.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IDXGISwapChainXAML_INTERFACE_DEFINED__
#define __IDXGISwapChainXAML_INTERFACE_DEFINED__

/* interface IDXGISwapChainXAML */
/* [uuid][local][object] */ 


EXTERN_C const IID IID_IDXGISwapChainXAML;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ffffffff-ffff-ffff-ffff-fffffffffffb")
    IDXGISwapChainXAML : public IDXGIDeviceSubObject
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IDXGISwapChainXAMLVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDXGISwapChainXAML * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDXGISwapChainXAML * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDXGISwapChainXAML * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateData )( 
            IDXGISwapChainXAML * This,
            /* [annotation][in] */ 
            _In_  REFGUID Name,
            /* [in] */ UINT DataSize,
            /* [annotation][in] */ 
            _In_reads_bytes_(DataSize)  const void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateDataInterface )( 
            IDXGISwapChainXAML * This,
            /* [annotation][in] */ 
            _In_  REFGUID Name,
            /* [annotation][in] */ 
            _In_opt_  const IUnknown *pUnknown);
        
        HRESULT ( STDMETHODCALLTYPE *GetPrivateData )( 
            IDXGISwapChainXAML * This,
            /* [annotation][in] */ 
            _In_  REFGUID Name,
            /* [annotation][out][in] */ 
            _Inout_  UINT *pDataSize,
            /* [annotation][out] */ 
            _Out_writes_bytes_(*pDataSize)  void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *GetParent )( 
            IDXGISwapChainXAML * This,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][retval][out] */ 
            _COM_Outptr_  void **ppParent);
        
        HRESULT ( STDMETHODCALLTYPE *GetDevice )( 
            IDXGISwapChainXAML * This,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][retval][out] */ 
            _COM_Outptr_  void **ppDevice);
        
        END_INTERFACE
    } IDXGISwapChainXAMLVtbl;

    interface IDXGISwapChainXAML
    {
        CONST_VTBL struct IDXGISwapChainXAMLVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDXGISwapChainXAML_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDXGISwapChainXAML_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDXGISwapChainXAML_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDXGISwapChainXAML_SetPrivateData(This,Name,DataSize,pData)	\
    ( (This)->lpVtbl -> SetPrivateData(This,Name,DataSize,pData) ) 

#define IDXGISwapChainXAML_SetPrivateDataInterface(This,Name,pUnknown)	\
    ( (This)->lpVtbl -> SetPrivateDataInterface(This,Name,pUnknown) ) 

#define IDXGISwapChainXAML_GetPrivateData(This,Name,pDataSize,pData)	\
    ( (This)->lpVtbl -> GetPrivateData(This,Name,pDataSize,pData) ) 

#define IDXGISwapChainXAML_GetParent(This,riid,ppParent)	\
    ( (This)->lpVtbl -> GetParent(This,riid,ppParent) ) 


#define IDXGISwapChainXAML_GetDevice(This,riid,ppDevice)	\
    ( (This)->lpVtbl -> GetDevice(This,riid,ppDevice) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDXGISwapChainXAML_INTERFACE_DEFINED__ */


#ifndef __IDXGIDeviceXAML_INTERFACE_DEFINED__
#define __IDXGIDeviceXAML_INTERFACE_DEFINED__

/* interface IDXGIDeviceXAML */
/* [uuid][local][object] */ 


EXTERN_C const IID IID_IDXGIDeviceXAML;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ffffffff-ffff-ffff-ffff-ffffffffffea")
    IDXGIDeviceXAML : public IDXGIDeviceSubObject
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetInProcessGPUPriority( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetInProcessGPUPriority( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDXGIDeviceXAMLVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDXGIDeviceXAML * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDXGIDeviceXAML * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDXGIDeviceXAML * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateData )( 
            IDXGIDeviceXAML * This,
            /* [annotation][in] */ 
            _In_  REFGUID Name,
            /* [in] */ UINT DataSize,
            /* [annotation][in] */ 
            _In_reads_bytes_(DataSize)  const void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateDataInterface )( 
            IDXGIDeviceXAML * This,
            /* [annotation][in] */ 
            _In_  REFGUID Name,
            /* [annotation][in] */ 
            _In_opt_  const IUnknown *pUnknown);
        
        HRESULT ( STDMETHODCALLTYPE *GetPrivateData )( 
            IDXGIDeviceXAML * This,
            /* [annotation][in] */ 
            _In_  REFGUID Name,
            /* [annotation][out][in] */ 
            _Inout_  UINT *pDataSize,
            /* [annotation][out] */ 
            _Out_writes_bytes_(*pDataSize)  void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *GetParent )( 
            IDXGIDeviceXAML * This,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][retval][out] */ 
            _COM_Outptr_  void **ppParent);
        
        HRESULT ( STDMETHODCALLTYPE *GetDevice )( 
            IDXGIDeviceXAML * This,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][retval][out] */ 
            _COM_Outptr_  void **ppDevice);
        
        HRESULT ( STDMETHODCALLTYPE *SetInProcessGPUPriority )( 
            IDXGIDeviceXAML * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetInProcessGPUPriority )( 
            IDXGIDeviceXAML * This);
        
        END_INTERFACE
    } IDXGIDeviceXAMLVtbl;

    interface IDXGIDeviceXAML
    {
        CONST_VTBL struct IDXGIDeviceXAMLVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDXGIDeviceXAML_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDXGIDeviceXAML_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDXGIDeviceXAML_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDXGIDeviceXAML_SetPrivateData(This,Name,DataSize,pData)	\
    ( (This)->lpVtbl -> SetPrivateData(This,Name,DataSize,pData) ) 

#define IDXGIDeviceXAML_SetPrivateDataInterface(This,Name,pUnknown)	\
    ( (This)->lpVtbl -> SetPrivateDataInterface(This,Name,pUnknown) ) 

#define IDXGIDeviceXAML_GetPrivateData(This,Name,pDataSize,pData)	\
    ( (This)->lpVtbl -> GetPrivateData(This,Name,pDataSize,pData) ) 

#define IDXGIDeviceXAML_GetParent(This,riid,ppParent)	\
    ( (This)->lpVtbl -> GetParent(This,riid,ppParent) ) 


#define IDXGIDeviceXAML_GetDevice(This,riid,ppDevice)	\
    ( (This)->lpVtbl -> GetDevice(This,riid,ppDevice) ) 


#define IDXGIDeviceXAML_SetInProcessGPUPriority(This)	\
    ( (This)->lpVtbl -> SetInProcessGPUPriority(This) ) 

#define IDXGIDeviceXAML_GetInProcessGPUPriority(This)	\
    ( (This)->lpVtbl -> GetInProcessGPUPriority(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDXGIDeviceXAML_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


