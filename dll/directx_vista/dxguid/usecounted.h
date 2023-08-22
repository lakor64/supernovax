

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 04:14:07 2038
 */
/* Compiler settings for usecounted.idl:
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

#ifndef __usecounted_h__
#define __usecounted_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IUseCounted_FWD_DEFINED__
#define __IUseCounted_FWD_DEFINED__
typedef interface IUseCounted IUseCounted;

#endif 	/* __IUseCounted_FWD_DEFINED__ */


#ifndef __IUseCounted2_FWD_DEFINED__
#define __IUseCounted2_FWD_DEFINED__
typedef interface IUseCounted2 IUseCounted2;

#endif 	/* __IUseCounted2_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IUseCounted_INTERFACE_DEFINED__
#define __IUseCounted_INTERFACE_DEFINED__

/* interface IUseCounted */
/* [uuid][local][object] */ 


EXTERN_C const IID IID_IUseCounted;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ffffffff-ffff-ffff-ffff-ffffffffffff")
    IUseCounted : public IUnknown
    {
    public:
        virtual ULONG STDMETHODCALLTYPE UCAddUse( void) = 0;
        
        virtual ULONG STDMETHODCALLTYPE UCReleaseUse( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UCBreakCyclicReferences( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UCEnstablishCyclicReferences( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UCDestroy( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUseCountedVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUseCounted * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUseCounted * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUseCounted * This);
        
        ULONG ( STDMETHODCALLTYPE *UCAddUse )( 
            IUseCounted * This);
        
        ULONG ( STDMETHODCALLTYPE *UCReleaseUse )( 
            IUseCounted * This);
        
        HRESULT ( STDMETHODCALLTYPE *UCBreakCyclicReferences )( 
            IUseCounted * This);
        
        HRESULT ( STDMETHODCALLTYPE *UCEnstablishCyclicReferences )( 
            IUseCounted * This);
        
        HRESULT ( STDMETHODCALLTYPE *UCDestroy )( 
            IUseCounted * This);
        
        END_INTERFACE
    } IUseCountedVtbl;

    interface IUseCounted
    {
        CONST_VTBL struct IUseCountedVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUseCounted_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUseCounted_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUseCounted_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUseCounted_UCAddUse(This)	\
    ( (This)->lpVtbl -> UCAddUse(This) ) 

#define IUseCounted_UCReleaseUse(This)	\
    ( (This)->lpVtbl -> UCReleaseUse(This) ) 

#define IUseCounted_UCBreakCyclicReferences(This)	\
    ( (This)->lpVtbl -> UCBreakCyclicReferences(This) ) 

#define IUseCounted_UCEnstablishCyclicReferences(This)	\
    ( (This)->lpVtbl -> UCEnstablishCyclicReferences(This) ) 

#define IUseCounted_UCDestroy(This)	\
    ( (This)->lpVtbl -> UCDestroy(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUseCounted_INTERFACE_DEFINED__ */


#ifndef __IUseCounted2_INTERFACE_DEFINED__
#define __IUseCounted2_INTERFACE_DEFINED__

/* interface IUseCounted2 */
/* [uuid][local][object] */ 


EXTERN_C const IID IID_IUseCounted2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ffffffff-ffff-ffff-ffff-fffffffffffe")
    IUseCounted2 : public IUseCounted
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE UCQueryInterface( 
            /* [in] */ UINT flags,
            /* [in] */ REFIID riid,
            /* [out] */ void **ppObj) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUseCounted2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUseCounted2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUseCounted2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUseCounted2 * This);
        
        ULONG ( STDMETHODCALLTYPE *UCAddUse )( 
            IUseCounted2 * This);
        
        ULONG ( STDMETHODCALLTYPE *UCReleaseUse )( 
            IUseCounted2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *UCBreakCyclicReferences )( 
            IUseCounted2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *UCEnstablishCyclicReferences )( 
            IUseCounted2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *UCDestroy )( 
            IUseCounted2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *UCQueryInterface )( 
            IUseCounted2 * This,
            /* [in] */ UINT flags,
            /* [in] */ REFIID riid,
            /* [out] */ void **ppObj);
        
        END_INTERFACE
    } IUseCounted2Vtbl;

    interface IUseCounted2
    {
        CONST_VTBL struct IUseCounted2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUseCounted2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUseCounted2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUseCounted2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUseCounted2_UCAddUse(This)	\
    ( (This)->lpVtbl -> UCAddUse(This) ) 

#define IUseCounted2_UCReleaseUse(This)	\
    ( (This)->lpVtbl -> UCReleaseUse(This) ) 

#define IUseCounted2_UCBreakCyclicReferences(This)	\
    ( (This)->lpVtbl -> UCBreakCyclicReferences(This) ) 

#define IUseCounted2_UCEnstablishCyclicReferences(This)	\
    ( (This)->lpVtbl -> UCEnstablishCyclicReferences(This) ) 

#define IUseCounted2_UCDestroy(This)	\
    ( (This)->lpVtbl -> UCDestroy(This) ) 


#define IUseCounted2_UCQueryInterface(This,flags,riid,ppObj)	\
    ( (This)->lpVtbl -> UCQueryInterface(This,flags,riid,ppObj) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUseCounted2_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


