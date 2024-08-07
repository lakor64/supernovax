

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue Aug 06 13:02:26 2024
 */
/* Compiler settings for dxdiag_private.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __dxdiag_private_h__
#define __dxdiag_private_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IDxDiagProviderPrivate_FWD_DEFINED__
#define __IDxDiagProviderPrivate_FWD_DEFINED__
typedef interface IDxDiagProviderPrivate IDxDiagProviderPrivate;
#endif 	/* __IDxDiagProviderPrivate_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_dxdiag_private_0000_0000 */
/* [local] */ 

#define DXDIAG_INIT_RESERVED_MAGIC 0x0B
typedef struct _DXDIAG_INIT_RESERVED_DATA
    {
    WORD wMagic;
    CHAR abReserved[ 6 ];
    BOOL bUsePrivateInterface;
    } 	DXDIAG_INIT_RESERVED_DATA;



extern RPC_IF_HANDLE __MIDL_itf_dxdiag_private_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_dxdiag_private_0000_0000_v0_0_s_ifspec;

#ifndef __IDxDiagProviderPrivate_INTERFACE_DEFINED__
#define __IDxDiagProviderPrivate_INTERFACE_DEFINED__

/* interface IDxDiagProviderPrivate */
/* [uuid][local][object] */ 


EXTERN_C const IID IID_IDxDiagProviderPrivate;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7D0F462F-4064-4862-BC7F-933E5058C10E")
    IDxDiagProviderPrivate : public IUnknown
    {
    public:
        virtual int STDMETHODCALLTYPE ExecMethod( 
            /* [in] */ LPCWSTR lpActionName,
            /* [in] */ VARIANT *lpValue) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDxDiagProviderPrivateVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDxDiagProviderPrivate * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDxDiagProviderPrivate * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDxDiagProviderPrivate * This);
        
        int ( STDMETHODCALLTYPE *ExecMethod )( 
            IDxDiagProviderPrivate * This,
            /* [in] */ LPCWSTR lpActionName,
            /* [in] */ VARIANT *lpValue);
        
        END_INTERFACE
    } IDxDiagProviderPrivateVtbl;

    interface IDxDiagProviderPrivate
    {
        CONST_VTBL struct IDxDiagProviderPrivateVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDxDiagProviderPrivate_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDxDiagProviderPrivate_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDxDiagProviderPrivate_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDxDiagProviderPrivate_ExecMethod(This,lpActionName,lpValue)	\
    ( (This)->lpVtbl -> ExecMethod(This,lpActionName,lpValue) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDxDiagProviderPrivate_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


