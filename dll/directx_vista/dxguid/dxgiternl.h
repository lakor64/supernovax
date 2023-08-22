

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 04:14:07 2038
 */
/* Compiler settings for dxgiternl.idl:
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

#ifndef __dxgiternl_h__
#define __dxgiternl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IDXGIDebugProducer_FWD_DEFINED__
#define __IDXGIDebugProducer_FWD_DEFINED__
typedef interface IDXGIDebugProducer IDXGIDebugProducer;

#endif 	/* __IDXGIDebugProducer_FWD_DEFINED__ */


#ifndef __IDXGISwapChainInternal_FWD_DEFINED__
#define __IDXGISwapChainInternal_FWD_DEFINED__
typedef interface IDXGISwapChainInternal IDXGISwapChainInternal;

#endif 	/* __IDXGISwapChainInternal_FWD_DEFINED__ */


#ifndef __IDXGISwapChainTest_FWD_DEFINED__
#define __IDXGISwapChainTest_FWD_DEFINED__
typedef interface IDXGISwapChainTest IDXGISwapChainTest;

#endif 	/* __IDXGISwapChainTest_FWD_DEFINED__ */


#ifndef __IDXGIResourceInternal2_FWD_DEFINED__
#define __IDXGIResourceInternal2_FWD_DEFINED__
typedef interface IDXGIResourceInternal2 IDXGIResourceInternal2;

#endif 	/* __IDXGIResourceInternal2_FWD_DEFINED__ */


#ifndef __IDXGIAdapterInternal_FWD_DEFINED__
#define __IDXGIAdapterInternal_FWD_DEFINED__
typedef interface IDXGIAdapterInternal IDXGIAdapterInternal;

#endif 	/* __IDXGIAdapterInternal_FWD_DEFINED__ */


#ifndef __IDXGIAdapterInternal1_FWD_DEFINED__
#define __IDXGIAdapterInternal1_FWD_DEFINED__
typedef interface IDXGIAdapterInternal1 IDXGIAdapterInternal1;

#endif 	/* __IDXGIAdapterInternal1_FWD_DEFINED__ */


#ifndef __IDXGIAdapterInternal2_FWD_DEFINED__
#define __IDXGIAdapterInternal2_FWD_DEFINED__
typedef interface IDXGIAdapterInternal2 IDXGIAdapterInternal2;

#endif 	/* __IDXGIAdapterInternal2_FWD_DEFINED__ */


#ifndef __IDXGIFenceInternal_FWD_DEFINED__
#define __IDXGIFenceInternal_FWD_DEFINED__
typedef interface IDXGIFenceInternal IDXGIFenceInternal;

#endif 	/* __IDXGIFenceInternal_FWD_DEFINED__ */


#ifndef __IDXGIDeviceTest_FWD_DEFINED__
#define __IDXGIDeviceTest_FWD_DEFINED__
typedef interface IDXGIDeviceTest IDXGIDeviceTest;

#endif 	/* __IDXGIDeviceTest_FWD_DEFINED__ */


#ifndef __IDXGIDeviceInternal_FWD_DEFINED__
#define __IDXGIDeviceInternal_FWD_DEFINED__
typedef interface IDXGIDeviceInternal IDXGIDeviceInternal;

#endif 	/* __IDXGIDeviceInternal_FWD_DEFINED__ */


#ifndef __IDXGIDeviceInternal2_FWD_DEFINED__
#define __IDXGIDeviceInternal2_FWD_DEFINED__
typedef interface IDXGIDeviceInternal2 IDXGIDeviceInternal2;

#endif 	/* __IDXGIDeviceInternal2_FWD_DEFINED__ */


#ifndef __IDXGIDeviceInternal3_FWD_DEFINED__
#define __IDXGIDeviceInternal3_FWD_DEFINED__
typedef interface IDXGIDeviceInternal3 IDXGIDeviceInternal3;

#endif 	/* __IDXGIDeviceInternal3_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "dxgi.h"
#include "usecounted.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_dxgiternl_0000_0000 */
/* [local] */ 

#ifndef _D3DKMTHK_H_
typedef 
enum _KMTUMDVERSION
    {
        KMTUMDVERSION_DX9	= 0,
        KMTUMDVERSION_DX10	= 1,
        KMTUMDVERSION_DX11	= 2,
        KMTUMDVERSION_DX12	= 3,
        KMTUMDVERSION_DX12_WSA32	= 4,
        KMTUMDVERSION_DX12_WSA64	= 5,
        NUM_KMTUMDVERSIONS	= 6
    } 	KMTUMDVERSION;

#endif
#ifndef _D3DUKMDT_H_
typedef UINT D3DKMT_HANDLE;

typedef UINT D3DDDI_VIDEO_PRESENT_SOURCE_ID;

#endif
typedef struct _D3DKMT_PRESENT *PD3DKMT_PRESENT;

typedef 
enum _DXGI_THUNKS_VERSION
    {
        DXGI_THUNKS_VERSION_NONE	= 0,
        DXGI_THUNKS_VERSION_1	= 1,
        DXGI_THUNKS_VERSION_2	= 2,
        DXGI_THUNKS_VERSION_3	= 3,
        DXGI_THUNKS_VERSION_4	= 4
    } 	DXGI_THUNKS_VERSION;

typedef struct _DXGI_PRESENT_BLT_TEST
    {
    DWORD dstSubId;
    DWORD srcSubid;
    } 	DXGI_PRESENT_BLT_TEST;

typedef struct _DXGI_PRESENT_BLT_MAP
    {
    DWORD Count;
    DXGI_PRESENT_BLT_TEST *Test;
    } 	DXGI_PRESENT_BLT_MAP;

typedef struct _DXGI_ADAPTER_CAPABILITIES
    {
    unsigned char unk;
    } 	DXGI_ADAPTER_CAPABILITIES;

typedef struct _DXGI_PRESENTSURFACE
    {
    ULONG Version;
    } 	DXGI_PRESENTSURFACE;

typedef 
enum _DXGI_DEVICE_PRESENT_FLAGS
    {
        DXGI_DEVICE_PRESENT_FLAGS_NONE	= 0,
        DXGI_DEVICE_PRESENT_FLAGS_UNKNOWN	= ( 1 << 0 ) ,
        DXGI_DEVICE_PRESENT_FLAGS_UNKNOWN_2	= ( 1 << 1 ) 
    } 	DXGI_DEVICE_PRESENT_FLAGS;



extern RPC_IF_HANDLE __MIDL_itf_dxgiternl_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_dxgiternl_0000_0000_v0_0_s_ifspec;

#ifndef __IDXGIDebugProducer_INTERFACE_DEFINED__
#define __IDXGIDebugProducer_INTERFACE_DEFINED__

/* interface IDXGIDebugProducer */
/* [uuid][local][object] */ 


EXTERN_C const IID IID_IDXGIDebugProducer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9b7e4a00-342c-4106-a19f-4f2704f689f0")
    IDXGIDebugProducer : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE DumpProducer( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DumpObject( 
            IUnknown *__MIDL__IDXGIDebugProducer0000) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSummaryInfoQueueMessageID( 
            int *__MIDL__IDXGIDebugProducer0001) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDXGIDebugProducerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDXGIDebugProducer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDXGIDebugProducer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDXGIDebugProducer * This);
        
        HRESULT ( STDMETHODCALLTYPE *DumpProducer )( 
            IDXGIDebugProducer * This);
        
        HRESULT ( STDMETHODCALLTYPE *DumpObject )( 
            IDXGIDebugProducer * This,
            IUnknown *__MIDL__IDXGIDebugProducer0000);
        
        HRESULT ( STDMETHODCALLTYPE *GetSummaryInfoQueueMessageID )( 
            IDXGIDebugProducer * This,
            int *__MIDL__IDXGIDebugProducer0001);
        
        END_INTERFACE
    } IDXGIDebugProducerVtbl;

    interface IDXGIDebugProducer
    {
        CONST_VTBL struct IDXGIDebugProducerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDXGIDebugProducer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDXGIDebugProducer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDXGIDebugProducer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDXGIDebugProducer_DumpProducer(This)	\
    ( (This)->lpVtbl -> DumpProducer(This) ) 

#define IDXGIDebugProducer_DumpObject(This,__MIDL__IDXGIDebugProducer0000)	\
    ( (This)->lpVtbl -> DumpObject(This,__MIDL__IDXGIDebugProducer0000) ) 

#define IDXGIDebugProducer_GetSummaryInfoQueueMessageID(This,__MIDL__IDXGIDebugProducer0001)	\
    ( (This)->lpVtbl -> GetSummaryInfoQueueMessageID(This,__MIDL__IDXGIDebugProducer0001) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDXGIDebugProducer_INTERFACE_DEFINED__ */


#ifndef __IDXGISwapChainInternal_INTERFACE_DEFINED__
#define __IDXGISwapChainInternal_INTERFACE_DEFINED__

/* interface IDXGISwapChainInternal */
/* [uuid][local][object] */ 


EXTERN_C const IID IID_IDXGISwapChainInternal;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ffffffff-ffff-ffff-ffff-fffffffffffd")
    IDXGISwapChainInternal : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AcquireBuffer( 
            /* [in] */ IDXGIResource *Resource,
            /* [in] */ UINT unk) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetResourceParent( 
            /* [in] */ REFIID iid,
            /* [out] */ void **pOut) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentCommandQueue( 
            /* [in] */ REFIID iid,
            /* [out] */ void **pOut) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDXGISwapChainInternalVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDXGISwapChainInternal * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDXGISwapChainInternal * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDXGISwapChainInternal * This);
        
        HRESULT ( STDMETHODCALLTYPE *AcquireBuffer )( 
            IDXGISwapChainInternal * This,
            /* [in] */ IDXGIResource *Resource,
            /* [in] */ UINT unk);
        
        HRESULT ( STDMETHODCALLTYPE *GetResourceParent )( 
            IDXGISwapChainInternal * This,
            /* [in] */ REFIID iid,
            /* [out] */ void **pOut);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentCommandQueue )( 
            IDXGISwapChainInternal * This,
            /* [in] */ REFIID iid,
            /* [out] */ void **pOut);
        
        END_INTERFACE
    } IDXGISwapChainInternalVtbl;

    interface IDXGISwapChainInternal
    {
        CONST_VTBL struct IDXGISwapChainInternalVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDXGISwapChainInternal_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDXGISwapChainInternal_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDXGISwapChainInternal_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDXGISwapChainInternal_AcquireBuffer(This,Resource,unk)	\
    ( (This)->lpVtbl -> AcquireBuffer(This,Resource,unk) ) 

#define IDXGISwapChainInternal_GetResourceParent(This,iid,pOut)	\
    ( (This)->lpVtbl -> GetResourceParent(This,iid,pOut) ) 

#define IDXGISwapChainInternal_GetCurrentCommandQueue(This,iid,pOut)	\
    ( (This)->lpVtbl -> GetCurrentCommandQueue(This,iid,pOut) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDXGISwapChainInternal_INTERFACE_DEFINED__ */


#ifndef __IDXGISwapChainTest_INTERFACE_DEFINED__
#define __IDXGISwapChainTest_INTERFACE_DEFINED__

/* interface IDXGISwapChainTest */
/* [uuid][local][object] */ 


EXTERN_C const IID IID_IDXGISwapChainTest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ffffffff-ffff-ffff-ffff-fffffffffffa")
    IDXGISwapChainTest : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE HasProxyFrontBufferSurface( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFrameStatisticsTest( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EmulateXBOXBehavior( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetColorSpace1( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBufferLayoutInfoTest( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDFlipOutput( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBackBufferImplicitRotationCount( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDXGISwapChainTestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDXGISwapChainTest * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDXGISwapChainTest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDXGISwapChainTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *HasProxyFrontBufferSurface )( 
            IDXGISwapChainTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetFrameStatisticsTest )( 
            IDXGISwapChainTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *EmulateXBOXBehavior )( 
            IDXGISwapChainTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetColorSpace1 )( 
            IDXGISwapChainTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetBufferLayoutInfoTest )( 
            IDXGISwapChainTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetDFlipOutput )( 
            IDXGISwapChainTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetBackBufferImplicitRotationCount )( 
            IDXGISwapChainTest * This);
        
        END_INTERFACE
    } IDXGISwapChainTestVtbl;

    interface IDXGISwapChainTest
    {
        CONST_VTBL struct IDXGISwapChainTestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDXGISwapChainTest_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDXGISwapChainTest_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDXGISwapChainTest_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDXGISwapChainTest_HasProxyFrontBufferSurface(This)	\
    ( (This)->lpVtbl -> HasProxyFrontBufferSurface(This) ) 

#define IDXGISwapChainTest_GetFrameStatisticsTest(This)	\
    ( (This)->lpVtbl -> GetFrameStatisticsTest(This) ) 

#define IDXGISwapChainTest_EmulateXBOXBehavior(This)	\
    ( (This)->lpVtbl -> EmulateXBOXBehavior(This) ) 

#define IDXGISwapChainTest_GetColorSpace1(This)	\
    ( (This)->lpVtbl -> GetColorSpace1(This) ) 

#define IDXGISwapChainTest_GetBufferLayoutInfoTest(This)	\
    ( (This)->lpVtbl -> GetBufferLayoutInfoTest(This) ) 

#define IDXGISwapChainTest_GetDFlipOutput(This)	\
    ( (This)->lpVtbl -> GetDFlipOutput(This) ) 

#define IDXGISwapChainTest_GetBackBufferImplicitRotationCount(This)	\
    ( (This)->lpVtbl -> GetBackBufferImplicitRotationCount(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDXGISwapChainTest_INTERFACE_DEFINED__ */


#ifndef __IDXGIResourceInternal2_INTERFACE_DEFINED__
#define __IDXGIResourceInternal2_INTERFACE_DEFINED__

/* interface IDXGIResourceInternal2 */
/* [uuid][object][local] */ 


EXTERN_C const IID IID_IDXGIResourceInternal2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("79d2046c-22ef-451b-9e74-2245d9c760ea")
    IDXGIResourceInternal2 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetDDIHandle( 
            void **__MIDL__IDXGIResourceInternal20000) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPrimaryDesc( 
            void *__MIDL__IDXGIResourceInternal20001,
            UINT64 *__MIDL__IDXGIResourceInternal20002) = 0;
        
        virtual BOOL STDMETHODCALLTYPE IsDCOutstanding( void) = 0;
        
        virtual void *STDMETHODCALLTYPE GetSharedHandleInternal( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGlobalHandles( 
            void **__MIDL__IDXGIResourceInternal20003,
            void **__MIDL__IDXGIResourceInternal20004,
            void **__MIDL__IDXGIResourceInternal20005) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateSharedHandleInternal( 
            const SECURITY_ATTRIBUTES *SecAttr,
            ULONG __MIDL__IDXGIResourceInternal20006,
            const USHORT *__MIDL__IDXGIResourceInternal20007,
            void **__MIDL__IDXGIResourceInternal20008) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDXGIResourceInternal2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDXGIResourceInternal2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDXGIResourceInternal2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDXGIResourceInternal2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetDDIHandle )( 
            IDXGIResourceInternal2 * This,
            void **__MIDL__IDXGIResourceInternal20000);
        
        HRESULT ( STDMETHODCALLTYPE *GetPrimaryDesc )( 
            IDXGIResourceInternal2 * This,
            void *__MIDL__IDXGIResourceInternal20001,
            UINT64 *__MIDL__IDXGIResourceInternal20002);
        
        BOOL ( STDMETHODCALLTYPE *IsDCOutstanding )( 
            IDXGIResourceInternal2 * This);
        
        void *( STDMETHODCALLTYPE *GetSharedHandleInternal )( 
            IDXGIResourceInternal2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetGlobalHandles )( 
            IDXGIResourceInternal2 * This,
            void **__MIDL__IDXGIResourceInternal20003,
            void **__MIDL__IDXGIResourceInternal20004,
            void **__MIDL__IDXGIResourceInternal20005);
        
        HRESULT ( STDMETHODCALLTYPE *CreateSharedHandleInternal )( 
            IDXGIResourceInternal2 * This,
            const SECURITY_ATTRIBUTES *SecAttr,
            ULONG __MIDL__IDXGIResourceInternal20006,
            const USHORT *__MIDL__IDXGIResourceInternal20007,
            void **__MIDL__IDXGIResourceInternal20008);
        
        END_INTERFACE
    } IDXGIResourceInternal2Vtbl;

    interface IDXGIResourceInternal2
    {
        CONST_VTBL struct IDXGIResourceInternal2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDXGIResourceInternal2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDXGIResourceInternal2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDXGIResourceInternal2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDXGIResourceInternal2_GetDDIHandle(This,__MIDL__IDXGIResourceInternal20000)	\
    ( (This)->lpVtbl -> GetDDIHandle(This,__MIDL__IDXGIResourceInternal20000) ) 

#define IDXGIResourceInternal2_GetPrimaryDesc(This,__MIDL__IDXGIResourceInternal20001,__MIDL__IDXGIResourceInternal20002)	\
    ( (This)->lpVtbl -> GetPrimaryDesc(This,__MIDL__IDXGIResourceInternal20001,__MIDL__IDXGIResourceInternal20002) ) 

#define IDXGIResourceInternal2_IsDCOutstanding(This)	\
    ( (This)->lpVtbl -> IsDCOutstanding(This) ) 

#define IDXGIResourceInternal2_GetSharedHandleInternal(This)	\
    ( (This)->lpVtbl -> GetSharedHandleInternal(This) ) 

#define IDXGIResourceInternal2_GetGlobalHandles(This,__MIDL__IDXGIResourceInternal20003,__MIDL__IDXGIResourceInternal20004,__MIDL__IDXGIResourceInternal20005)	\
    ( (This)->lpVtbl -> GetGlobalHandles(This,__MIDL__IDXGIResourceInternal20003,__MIDL__IDXGIResourceInternal20004,__MIDL__IDXGIResourceInternal20005) ) 

#define IDXGIResourceInternal2_CreateSharedHandleInternal(This,SecAttr,__MIDL__IDXGIResourceInternal20006,__MIDL__IDXGIResourceInternal20007,__MIDL__IDXGIResourceInternal20008)	\
    ( (This)->lpVtbl -> CreateSharedHandleInternal(This,SecAttr,__MIDL__IDXGIResourceInternal20006,__MIDL__IDXGIResourceInternal20007,__MIDL__IDXGIResourceInternal20008) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDXGIResourceInternal2_INTERFACE_DEFINED__ */


#ifndef __IDXGIAdapterInternal_INTERFACE_DEFINED__
#define __IDXGIAdapterInternal_INTERFACE_DEFINED__

/* interface IDXGIAdapterInternal */
/* [uuid][local][object] */ 


EXTERN_C const IID IID_IDXGIAdapterInternal;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("bbfeb1e3-6f00-4ad0-a003-dc3c98c415e8")
    IDXGIAdapterInternal : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetUMDDeviceSize( 
            /* [in] */ UINT unk,
            /* [in] */ UINT unk2,
            /* [in] */ UINT unk3) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDXGIAdapterInternalVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDXGIAdapterInternal * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDXGIAdapterInternal * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDXGIAdapterInternal * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetUMDDeviceSize )( 
            IDXGIAdapterInternal * This,
            /* [in] */ UINT unk,
            /* [in] */ UINT unk2,
            /* [in] */ UINT unk3);
        
        END_INTERFACE
    } IDXGIAdapterInternalVtbl;

    interface IDXGIAdapterInternal
    {
        CONST_VTBL struct IDXGIAdapterInternalVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDXGIAdapterInternal_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDXGIAdapterInternal_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDXGIAdapterInternal_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDXGIAdapterInternal_GetUMDDeviceSize(This,unk,unk2,unk3)	\
    ( (This)->lpVtbl -> GetUMDDeviceSize(This,unk,unk2,unk3) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDXGIAdapterInternal_INTERFACE_DEFINED__ */


#ifndef __IDXGIAdapterInternal1_INTERFACE_DEFINED__
#define __IDXGIAdapterInternal1_INTERFACE_DEFINED__

/* interface IDXGIAdapterInternal1 */
/* [uuid][local][object] */ 


EXTERN_C const IID IID_IDXGIAdapterInternal1;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("712bd56d-86ff-4b71-91e1-c13b274ff2a2")
    IDXGIAdapterInternal1 : public IDXGIAdapterInternal
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IDXGIAdapterInternal1Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDXGIAdapterInternal1 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDXGIAdapterInternal1 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDXGIAdapterInternal1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetUMDDeviceSize )( 
            IDXGIAdapterInternal1 * This,
            /* [in] */ UINT unk,
            /* [in] */ UINT unk2,
            /* [in] */ UINT unk3);
        
        END_INTERFACE
    } IDXGIAdapterInternal1Vtbl;

    interface IDXGIAdapterInternal1
    {
        CONST_VTBL struct IDXGIAdapterInternal1Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDXGIAdapterInternal1_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDXGIAdapterInternal1_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDXGIAdapterInternal1_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDXGIAdapterInternal1_GetUMDDeviceSize(This,unk,unk2,unk3)	\
    ( (This)->lpVtbl -> GetUMDDeviceSize(This,unk,unk2,unk3) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDXGIAdapterInternal1_INTERFACE_DEFINED__ */


#ifndef __IDXGIAdapterInternal2_INTERFACE_DEFINED__
#define __IDXGIAdapterInternal2_INTERFACE_DEFINED__

/* interface IDXGIAdapterInternal2 */
/* [uuid][local][object] */ 


EXTERN_C const IID IID_IDXGIAdapterInternal2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7abb6563-02bc-47c4-8ef9-acc4795edbcf")
    IDXGIAdapterInternal2 : public IDXGIAdapterInternal1
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE LoadUMD( 
            /* [in] */ KMTUMDVERSION Version,
            /* [out] */ HINSTANCE *hUmdDLL) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InstanceThunks( 
            /* [in] */ DXGI_THUNKS_VERSION Version,
            /* [out] */ D3DKMT_HANDLE *pHandle,
            /* [in] */ UINT ThunksVer,
            /* [optional][out][in] */ void *Thunks) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RetireUsage( 
            /* [in] */ D3DKMT_HANDLE Adapter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAdapterCapabilities( 
            /* [in] */ DXGI_ADAPTER_CAPABILITIES *Capabilities) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAdapterCapabilities( 
            /* [out] */ DXGI_ADAPTER_CAPABILITIES *Capabilities) = 0;
        
        virtual BOOL STDMETHODCALLTYPE IsWARP( void) = 0;
        
        virtual D3DDDI_VIDEO_PRESENT_SOURCE_ID STDMETHODCALLTYPE GetPrimaryVidPnSourceId( void) = 0;
        
        virtual UINT STDMETHODCALLTYPE WddmVersion( void) = 0;
        
        virtual BOOL STDMETHODCALLTYPE MismatchedVendorLda( void) = 0;
        
        virtual BOOL STDMETHODCALLTYPE IsLda( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDXGIAdapterInternal2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDXGIAdapterInternal2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDXGIAdapterInternal2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDXGIAdapterInternal2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetUMDDeviceSize )( 
            IDXGIAdapterInternal2 * This,
            /* [in] */ UINT unk,
            /* [in] */ UINT unk2,
            /* [in] */ UINT unk3);
        
        HRESULT ( STDMETHODCALLTYPE *LoadUMD )( 
            IDXGIAdapterInternal2 * This,
            /* [in] */ KMTUMDVERSION Version,
            /* [out] */ HINSTANCE *hUmdDLL);
        
        HRESULT ( STDMETHODCALLTYPE *InstanceThunks )( 
            IDXGIAdapterInternal2 * This,
            /* [in] */ DXGI_THUNKS_VERSION Version,
            /* [out] */ D3DKMT_HANDLE *pHandle,
            /* [in] */ UINT ThunksVer,
            /* [optional][out][in] */ void *Thunks);
        
        HRESULT ( STDMETHODCALLTYPE *RetireUsage )( 
            IDXGIAdapterInternal2 * This,
            /* [in] */ D3DKMT_HANDLE Adapter);
        
        HRESULT ( STDMETHODCALLTYPE *SetAdapterCapabilities )( 
            IDXGIAdapterInternal2 * This,
            /* [in] */ DXGI_ADAPTER_CAPABILITIES *Capabilities);
        
        HRESULT ( STDMETHODCALLTYPE *GetAdapterCapabilities )( 
            IDXGIAdapterInternal2 * This,
            /* [out] */ DXGI_ADAPTER_CAPABILITIES *Capabilities);
        
        BOOL ( STDMETHODCALLTYPE *IsWARP )( 
            IDXGIAdapterInternal2 * This);
        
        D3DDDI_VIDEO_PRESENT_SOURCE_ID ( STDMETHODCALLTYPE *GetPrimaryVidPnSourceId )( 
            IDXGIAdapterInternal2 * This);
        
        UINT ( STDMETHODCALLTYPE *WddmVersion )( 
            IDXGIAdapterInternal2 * This);
        
        BOOL ( STDMETHODCALLTYPE *MismatchedVendorLda )( 
            IDXGIAdapterInternal2 * This);
        
        BOOL ( STDMETHODCALLTYPE *IsLda )( 
            IDXGIAdapterInternal2 * This);
        
        END_INTERFACE
    } IDXGIAdapterInternal2Vtbl;

    interface IDXGIAdapterInternal2
    {
        CONST_VTBL struct IDXGIAdapterInternal2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDXGIAdapterInternal2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDXGIAdapterInternal2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDXGIAdapterInternal2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDXGIAdapterInternal2_GetUMDDeviceSize(This,unk,unk2,unk3)	\
    ( (This)->lpVtbl -> GetUMDDeviceSize(This,unk,unk2,unk3) ) 



#define IDXGIAdapterInternal2_LoadUMD(This,Version,hUmdDLL)	\
    ( (This)->lpVtbl -> LoadUMD(This,Version,hUmdDLL) ) 

#define IDXGIAdapterInternal2_InstanceThunks(This,Version,pHandle,ThunksVer,Thunks)	\
    ( (This)->lpVtbl -> InstanceThunks(This,Version,pHandle,ThunksVer,Thunks) ) 

#define IDXGIAdapterInternal2_RetireUsage(This,Adapter)	\
    ( (This)->lpVtbl -> RetireUsage(This,Adapter) ) 

#define IDXGIAdapterInternal2_SetAdapterCapabilities(This,Capabilities)	\
    ( (This)->lpVtbl -> SetAdapterCapabilities(This,Capabilities) ) 

#define IDXGIAdapterInternal2_GetAdapterCapabilities(This,Capabilities)	\
    ( (This)->lpVtbl -> GetAdapterCapabilities(This,Capabilities) ) 

#define IDXGIAdapterInternal2_IsWARP(This)	\
    ( (This)->lpVtbl -> IsWARP(This) ) 

#define IDXGIAdapterInternal2_GetPrimaryVidPnSourceId(This)	\
    ( (This)->lpVtbl -> GetPrimaryVidPnSourceId(This) ) 

#define IDXGIAdapterInternal2_WddmVersion(This)	\
    ( (This)->lpVtbl -> WddmVersion(This) ) 

#define IDXGIAdapterInternal2_MismatchedVendorLda(This)	\
    ( (This)->lpVtbl -> MismatchedVendorLda(This) ) 

#define IDXGIAdapterInternal2_IsLda(This)	\
    ( (This)->lpVtbl -> IsLda(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDXGIAdapterInternal2_INTERFACE_DEFINED__ */


#ifndef __IDXGIFenceInternal_INTERFACE_DEFINED__
#define __IDXGIFenceInternal_INTERFACE_DEFINED__

/* interface IDXGIFenceInternal */
/* [uuid][local][object] */ 


EXTERN_C const IID IID_IDXGIFenceInternal;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ffffffff-ffff-ffff-ffff-ffffffffffe8")
    IDXGIFenceInternal : public IUnknown
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IDXGIFenceInternalVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDXGIFenceInternal * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDXGIFenceInternal * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDXGIFenceInternal * This);
        
        END_INTERFACE
    } IDXGIFenceInternalVtbl;

    interface IDXGIFenceInternal
    {
        CONST_VTBL struct IDXGIFenceInternalVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDXGIFenceInternal_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDXGIFenceInternal_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDXGIFenceInternal_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDXGIFenceInternal_INTERFACE_DEFINED__ */


#ifndef __IDXGIDeviceTest_INTERFACE_DEFINED__
#define __IDXGIDeviceTest_INTERFACE_DEFINED__

/* interface IDXGIDeviceTest */
/* [uuid][local][object] */ 


EXTERN_C const IID IID_IDXGIDeviceTest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ffffffff-ffff-ffff-ffff-ffffffffffe9")
    IDXGIDeviceTest : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CheckPresentDurationSupport( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDXGIDeviceTestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDXGIDeviceTest * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDXGIDeviceTest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDXGIDeviceTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *CheckPresentDurationSupport )( 
            IDXGIDeviceTest * This);
        
        END_INTERFACE
    } IDXGIDeviceTestVtbl;

    interface IDXGIDeviceTest
    {
        CONST_VTBL struct IDXGIDeviceTestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDXGIDeviceTest_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDXGIDeviceTest_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDXGIDeviceTest_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDXGIDeviceTest_CheckPresentDurationSupport(This)	\
    ( (This)->lpVtbl -> CheckPresentDurationSupport(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDXGIDeviceTest_INTERFACE_DEFINED__ */


#ifndef __IDXGIDeviceInternal_INTERFACE_DEFINED__
#define __IDXGIDeviceInternal_INTERFACE_DEFINED__

/* interface IDXGIDeviceInternal */
/* [uuid][local][object] */ 


EXTERN_C const IID IID_IDXGIDeviceInternal;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5a92ae4f-81fa-4cac-a1d8-ae479ac581cd")
    IDXGIDeviceInternal : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Present( 
            /* [in] */ IDXGISurface *__MIDL__IDXGIDeviceInternal0000,
            /* [in] */ IDXGISurface *__MIDL__IDXGIDeviceInternal0001,
            /* [in] */ PD3DKMT_PRESENT pPresentInfo,
            /* [in] */ UINT __MIDL__IDXGIDeviceInternal0002,
            /* [in] */ UINT __MIDL__IDXGIDeviceInternal0003) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RotateResourceIdentities( 
            IDXGISurface *__MIDL__IDXGIDeviceInternal0004,
            const IDXGISurface **__MIDL__IDXGIDeviceInternal0005,
            UINT __MIDL__IDXGIDeviceInternal0006) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetContextResolver( 
            void **__MIDL__IDXGIDeviceInternal0007) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateSurfaceInternal( 
            IUseCounted *__MIDL__IDXGIDeviceInternal0008,
            const DXGI_SURFACE_DESC *pDesc,
            UINT __MIDL__IDXGIDeviceInternal0009,
            UINT __MIDL__IDXGIDeviceInternal0010,
            void *__MIDL__IDXGIDeviceInternal0011,
            /* [out] */ IDXGISurface **pOutput) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Blt( 
            IDXGISurface *__MIDL__IDXGIDeviceInternal0012,
            const RECT *__MIDL__IDXGIDeviceInternal0013,
            IDXGISurface *__MIDL__IDXGIDeviceInternal0014,
            RECT *__MIDL__IDXGIDeviceInternal0015,
            UINT64 __MIDL__IDXGIDeviceInternal0016,
            UINT __MIDL__IDXGIDeviceInternal0017,
            UINT __MIDL__IDXGIDeviceInternal0018) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDisplayMode( 
            IDXGISurface *__MIDL__IDXGIDeviceInternal0019) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGammaCaps( 
            DXGI_GAMMA_CONTROL_CAPABILITIES *__MIDL__IDXGIDeviceInternal0020) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OpenSharedResource( 
            void *__MIDL__IDXGIDeviceInternal0021,
            int __MIDL__IDXGIDeviceInternal0022,
            REFIID __MIDL__IDXGIDeviceInternal0023,
            void **__MIDL__IDXGIDeviceInternal0024) = 0;
        
        virtual BOOL STDMETHODCALLTYPE IsValidScanoutFormat( 
            DXGI_FORMAT Format) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDXGIDeviceInternalVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDXGIDeviceInternal * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDXGIDeviceInternal * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDXGIDeviceInternal * This);
        
        HRESULT ( STDMETHODCALLTYPE *Present )( 
            IDXGIDeviceInternal * This,
            /* [in] */ IDXGISurface *__MIDL__IDXGIDeviceInternal0000,
            /* [in] */ IDXGISurface *__MIDL__IDXGIDeviceInternal0001,
            /* [in] */ PD3DKMT_PRESENT pPresentInfo,
            /* [in] */ UINT __MIDL__IDXGIDeviceInternal0002,
            /* [in] */ UINT __MIDL__IDXGIDeviceInternal0003);
        
        HRESULT ( STDMETHODCALLTYPE *RotateResourceIdentities )( 
            IDXGIDeviceInternal * This,
            IDXGISurface *__MIDL__IDXGIDeviceInternal0004,
            const IDXGISurface **__MIDL__IDXGIDeviceInternal0005,
            UINT __MIDL__IDXGIDeviceInternal0006);
        
        HRESULT ( STDMETHODCALLTYPE *GetContextResolver )( 
            IDXGIDeviceInternal * This,
            void **__MIDL__IDXGIDeviceInternal0007);
        
        HRESULT ( STDMETHODCALLTYPE *CreateSurfaceInternal )( 
            IDXGIDeviceInternal * This,
            IUseCounted *__MIDL__IDXGIDeviceInternal0008,
            const DXGI_SURFACE_DESC *pDesc,
            UINT __MIDL__IDXGIDeviceInternal0009,
            UINT __MIDL__IDXGIDeviceInternal0010,
            void *__MIDL__IDXGIDeviceInternal0011,
            /* [out] */ IDXGISurface **pOutput);
        
        HRESULT ( STDMETHODCALLTYPE *Blt )( 
            IDXGIDeviceInternal * This,
            IDXGISurface *__MIDL__IDXGIDeviceInternal0012,
            const RECT *__MIDL__IDXGIDeviceInternal0013,
            IDXGISurface *__MIDL__IDXGIDeviceInternal0014,
            RECT *__MIDL__IDXGIDeviceInternal0015,
            UINT64 __MIDL__IDXGIDeviceInternal0016,
            UINT __MIDL__IDXGIDeviceInternal0017,
            UINT __MIDL__IDXGIDeviceInternal0018);
        
        HRESULT ( STDMETHODCALLTYPE *SetDisplayMode )( 
            IDXGIDeviceInternal * This,
            IDXGISurface *__MIDL__IDXGIDeviceInternal0019);
        
        HRESULT ( STDMETHODCALLTYPE *GetGammaCaps )( 
            IDXGIDeviceInternal * This,
            DXGI_GAMMA_CONTROL_CAPABILITIES *__MIDL__IDXGIDeviceInternal0020);
        
        HRESULT ( STDMETHODCALLTYPE *OpenSharedResource )( 
            IDXGIDeviceInternal * This,
            void *__MIDL__IDXGIDeviceInternal0021,
            int __MIDL__IDXGIDeviceInternal0022,
            REFIID __MIDL__IDXGIDeviceInternal0023,
            void **__MIDL__IDXGIDeviceInternal0024);
        
        BOOL ( STDMETHODCALLTYPE *IsValidScanoutFormat )( 
            IDXGIDeviceInternal * This,
            DXGI_FORMAT Format);
        
        END_INTERFACE
    } IDXGIDeviceInternalVtbl;

    interface IDXGIDeviceInternal
    {
        CONST_VTBL struct IDXGIDeviceInternalVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDXGIDeviceInternal_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDXGIDeviceInternal_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDXGIDeviceInternal_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDXGIDeviceInternal_Present(This,__MIDL__IDXGIDeviceInternal0000,__MIDL__IDXGIDeviceInternal0001,pPresentInfo,__MIDL__IDXGIDeviceInternal0002,__MIDL__IDXGIDeviceInternal0003)	\
    ( (This)->lpVtbl -> Present(This,__MIDL__IDXGIDeviceInternal0000,__MIDL__IDXGIDeviceInternal0001,pPresentInfo,__MIDL__IDXGIDeviceInternal0002,__MIDL__IDXGIDeviceInternal0003) ) 

#define IDXGIDeviceInternal_RotateResourceIdentities(This,__MIDL__IDXGIDeviceInternal0004,__MIDL__IDXGIDeviceInternal0005,__MIDL__IDXGIDeviceInternal0006)	\
    ( (This)->lpVtbl -> RotateResourceIdentities(This,__MIDL__IDXGIDeviceInternal0004,__MIDL__IDXGIDeviceInternal0005,__MIDL__IDXGIDeviceInternal0006) ) 

#define IDXGIDeviceInternal_GetContextResolver(This,__MIDL__IDXGIDeviceInternal0007)	\
    ( (This)->lpVtbl -> GetContextResolver(This,__MIDL__IDXGIDeviceInternal0007) ) 

#define IDXGIDeviceInternal_CreateSurfaceInternal(This,__MIDL__IDXGIDeviceInternal0008,pDesc,__MIDL__IDXGIDeviceInternal0009,__MIDL__IDXGIDeviceInternal0010,__MIDL__IDXGIDeviceInternal0011,pOutput)	\
    ( (This)->lpVtbl -> CreateSurfaceInternal(This,__MIDL__IDXGIDeviceInternal0008,pDesc,__MIDL__IDXGIDeviceInternal0009,__MIDL__IDXGIDeviceInternal0010,__MIDL__IDXGIDeviceInternal0011,pOutput) ) 

#define IDXGIDeviceInternal_Blt(This,__MIDL__IDXGIDeviceInternal0012,__MIDL__IDXGIDeviceInternal0013,__MIDL__IDXGIDeviceInternal0014,__MIDL__IDXGIDeviceInternal0015,__MIDL__IDXGIDeviceInternal0016,__MIDL__IDXGIDeviceInternal0017,__MIDL__IDXGIDeviceInternal0018)	\
    ( (This)->lpVtbl -> Blt(This,__MIDL__IDXGIDeviceInternal0012,__MIDL__IDXGIDeviceInternal0013,__MIDL__IDXGIDeviceInternal0014,__MIDL__IDXGIDeviceInternal0015,__MIDL__IDXGIDeviceInternal0016,__MIDL__IDXGIDeviceInternal0017,__MIDL__IDXGIDeviceInternal0018) ) 

#define IDXGIDeviceInternal_SetDisplayMode(This,__MIDL__IDXGIDeviceInternal0019)	\
    ( (This)->lpVtbl -> SetDisplayMode(This,__MIDL__IDXGIDeviceInternal0019) ) 

#define IDXGIDeviceInternal_GetGammaCaps(This,__MIDL__IDXGIDeviceInternal0020)	\
    ( (This)->lpVtbl -> GetGammaCaps(This,__MIDL__IDXGIDeviceInternal0020) ) 

#define IDXGIDeviceInternal_OpenSharedResource(This,__MIDL__IDXGIDeviceInternal0021,__MIDL__IDXGIDeviceInternal0022,__MIDL__IDXGIDeviceInternal0023,__MIDL__IDXGIDeviceInternal0024)	\
    ( (This)->lpVtbl -> OpenSharedResource(This,__MIDL__IDXGIDeviceInternal0021,__MIDL__IDXGIDeviceInternal0022,__MIDL__IDXGIDeviceInternal0023,__MIDL__IDXGIDeviceInternal0024) ) 

#define IDXGIDeviceInternal_IsValidScanoutFormat(This,Format)	\
    ( (This)->lpVtbl -> IsValidScanoutFormat(This,Format) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDXGIDeviceInternal_INTERFACE_DEFINED__ */


#ifndef __IDXGIDeviceInternal2_INTERFACE_DEFINED__
#define __IDXGIDeviceInternal2_INTERFACE_DEFINED__

/* interface IDXGIDeviceInternal2 */
/* [uuid][local][object] */ 


EXTERN_C const IID IID_IDXGIDeviceInternal2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ffffffff-ffff-ffff-ffff-ffffffffffef")
    IDXGIDeviceInternal2 : public IDXGIDeviceInternal
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE FlushDeletion( 
            IDXGISurface *__MIDL__IDXGIDeviceInternal20000,
            const IDXGISurface **__MIDL__IDXGIDeviceInternal20001,
            UINT __MIDL__IDXGIDeviceInternal20002) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDXGIDeviceInternal2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDXGIDeviceInternal2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDXGIDeviceInternal2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDXGIDeviceInternal2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *Present )( 
            IDXGIDeviceInternal2 * This,
            /* [in] */ IDXGISurface *__MIDL__IDXGIDeviceInternal0000,
            /* [in] */ IDXGISurface *__MIDL__IDXGIDeviceInternal0001,
            /* [in] */ PD3DKMT_PRESENT pPresentInfo,
            /* [in] */ UINT __MIDL__IDXGIDeviceInternal0002,
            /* [in] */ UINT __MIDL__IDXGIDeviceInternal0003);
        
        HRESULT ( STDMETHODCALLTYPE *RotateResourceIdentities )( 
            IDXGIDeviceInternal2 * This,
            IDXGISurface *__MIDL__IDXGIDeviceInternal0004,
            const IDXGISurface **__MIDL__IDXGIDeviceInternal0005,
            UINT __MIDL__IDXGIDeviceInternal0006);
        
        HRESULT ( STDMETHODCALLTYPE *GetContextResolver )( 
            IDXGIDeviceInternal2 * This,
            void **__MIDL__IDXGIDeviceInternal0007);
        
        HRESULT ( STDMETHODCALLTYPE *CreateSurfaceInternal )( 
            IDXGIDeviceInternal2 * This,
            IUseCounted *__MIDL__IDXGIDeviceInternal0008,
            const DXGI_SURFACE_DESC *pDesc,
            UINT __MIDL__IDXGIDeviceInternal0009,
            UINT __MIDL__IDXGIDeviceInternal0010,
            void *__MIDL__IDXGIDeviceInternal0011,
            /* [out] */ IDXGISurface **pOutput);
        
        HRESULT ( STDMETHODCALLTYPE *Blt )( 
            IDXGIDeviceInternal2 * This,
            IDXGISurface *__MIDL__IDXGIDeviceInternal0012,
            const RECT *__MIDL__IDXGIDeviceInternal0013,
            IDXGISurface *__MIDL__IDXGIDeviceInternal0014,
            RECT *__MIDL__IDXGIDeviceInternal0015,
            UINT64 __MIDL__IDXGIDeviceInternal0016,
            UINT __MIDL__IDXGIDeviceInternal0017,
            UINT __MIDL__IDXGIDeviceInternal0018);
        
        HRESULT ( STDMETHODCALLTYPE *SetDisplayMode )( 
            IDXGIDeviceInternal2 * This,
            IDXGISurface *__MIDL__IDXGIDeviceInternal0019);
        
        HRESULT ( STDMETHODCALLTYPE *GetGammaCaps )( 
            IDXGIDeviceInternal2 * This,
            DXGI_GAMMA_CONTROL_CAPABILITIES *__MIDL__IDXGIDeviceInternal0020);
        
        HRESULT ( STDMETHODCALLTYPE *OpenSharedResource )( 
            IDXGIDeviceInternal2 * This,
            void *__MIDL__IDXGIDeviceInternal0021,
            int __MIDL__IDXGIDeviceInternal0022,
            REFIID __MIDL__IDXGIDeviceInternal0023,
            void **__MIDL__IDXGIDeviceInternal0024);
        
        BOOL ( STDMETHODCALLTYPE *IsValidScanoutFormat )( 
            IDXGIDeviceInternal2 * This,
            DXGI_FORMAT Format);
        
        HRESULT ( STDMETHODCALLTYPE *FlushDeletion )( 
            IDXGIDeviceInternal2 * This,
            IDXGISurface *__MIDL__IDXGIDeviceInternal20000,
            const IDXGISurface **__MIDL__IDXGIDeviceInternal20001,
            UINT __MIDL__IDXGIDeviceInternal20002);
        
        END_INTERFACE
    } IDXGIDeviceInternal2Vtbl;

    interface IDXGIDeviceInternal2
    {
        CONST_VTBL struct IDXGIDeviceInternal2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDXGIDeviceInternal2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDXGIDeviceInternal2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDXGIDeviceInternal2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDXGIDeviceInternal2_Present(This,__MIDL__IDXGIDeviceInternal0000,__MIDL__IDXGIDeviceInternal0001,pPresentInfo,__MIDL__IDXGIDeviceInternal0002,__MIDL__IDXGIDeviceInternal0003)	\
    ( (This)->lpVtbl -> Present(This,__MIDL__IDXGIDeviceInternal0000,__MIDL__IDXGIDeviceInternal0001,pPresentInfo,__MIDL__IDXGIDeviceInternal0002,__MIDL__IDXGIDeviceInternal0003) ) 

#define IDXGIDeviceInternal2_RotateResourceIdentities(This,__MIDL__IDXGIDeviceInternal0004,__MIDL__IDXGIDeviceInternal0005,__MIDL__IDXGIDeviceInternal0006)	\
    ( (This)->lpVtbl -> RotateResourceIdentities(This,__MIDL__IDXGIDeviceInternal0004,__MIDL__IDXGIDeviceInternal0005,__MIDL__IDXGIDeviceInternal0006) ) 

#define IDXGIDeviceInternal2_GetContextResolver(This,__MIDL__IDXGIDeviceInternal0007)	\
    ( (This)->lpVtbl -> GetContextResolver(This,__MIDL__IDXGIDeviceInternal0007) ) 

#define IDXGIDeviceInternal2_CreateSurfaceInternal(This,__MIDL__IDXGIDeviceInternal0008,pDesc,__MIDL__IDXGIDeviceInternal0009,__MIDL__IDXGIDeviceInternal0010,__MIDL__IDXGIDeviceInternal0011,pOutput)	\
    ( (This)->lpVtbl -> CreateSurfaceInternal(This,__MIDL__IDXGIDeviceInternal0008,pDesc,__MIDL__IDXGIDeviceInternal0009,__MIDL__IDXGIDeviceInternal0010,__MIDL__IDXGIDeviceInternal0011,pOutput) ) 

#define IDXGIDeviceInternal2_Blt(This,__MIDL__IDXGIDeviceInternal0012,__MIDL__IDXGIDeviceInternal0013,__MIDL__IDXGIDeviceInternal0014,__MIDL__IDXGIDeviceInternal0015,__MIDL__IDXGIDeviceInternal0016,__MIDL__IDXGIDeviceInternal0017,__MIDL__IDXGIDeviceInternal0018)	\
    ( (This)->lpVtbl -> Blt(This,__MIDL__IDXGIDeviceInternal0012,__MIDL__IDXGIDeviceInternal0013,__MIDL__IDXGIDeviceInternal0014,__MIDL__IDXGIDeviceInternal0015,__MIDL__IDXGIDeviceInternal0016,__MIDL__IDXGIDeviceInternal0017,__MIDL__IDXGIDeviceInternal0018) ) 

#define IDXGIDeviceInternal2_SetDisplayMode(This,__MIDL__IDXGIDeviceInternal0019)	\
    ( (This)->lpVtbl -> SetDisplayMode(This,__MIDL__IDXGIDeviceInternal0019) ) 

#define IDXGIDeviceInternal2_GetGammaCaps(This,__MIDL__IDXGIDeviceInternal0020)	\
    ( (This)->lpVtbl -> GetGammaCaps(This,__MIDL__IDXGIDeviceInternal0020) ) 

#define IDXGIDeviceInternal2_OpenSharedResource(This,__MIDL__IDXGIDeviceInternal0021,__MIDL__IDXGIDeviceInternal0022,__MIDL__IDXGIDeviceInternal0023,__MIDL__IDXGIDeviceInternal0024)	\
    ( (This)->lpVtbl -> OpenSharedResource(This,__MIDL__IDXGIDeviceInternal0021,__MIDL__IDXGIDeviceInternal0022,__MIDL__IDXGIDeviceInternal0023,__MIDL__IDXGIDeviceInternal0024) ) 

#define IDXGIDeviceInternal2_IsValidScanoutFormat(This,Format)	\
    ( (This)->lpVtbl -> IsValidScanoutFormat(This,Format) ) 


#define IDXGIDeviceInternal2_FlushDeletion(This,__MIDL__IDXGIDeviceInternal20000,__MIDL__IDXGIDeviceInternal20001,__MIDL__IDXGIDeviceInternal20002)	\
    ( (This)->lpVtbl -> FlushDeletion(This,__MIDL__IDXGIDeviceInternal20000,__MIDL__IDXGIDeviceInternal20001,__MIDL__IDXGIDeviceInternal20002) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDXGIDeviceInternal2_INTERFACE_DEFINED__ */


#ifndef __IDXGIDeviceInternal3_INTERFACE_DEFINED__
#define __IDXGIDeviceInternal3_INTERFACE_DEFINED__

/* interface IDXGIDeviceInternal3 */
/* [uuid][local][object] */ 


EXTERN_C const IID IID_IDXGIDeviceInternal3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("f74ee86f-7270-48e8-9d63-38af75f22d57")
    IDXGIDeviceInternal3 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Present( 
            IDXGIDebugProducer *pDebugProducer,
            IDXGIResource *__MIDL__IDXGIDeviceInternal30000,
            void *pPresent,
            UINT __MIDL__IDXGIDeviceInternal30001,
            UINT __MIDL__IDXGIDeviceInternal30002) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RotateResourceIdentities( 
            IDXGIResource *__MIDL__IDXGIDeviceInternal30003,
            const IDXGIResource **__MIDL__IDXGIDeviceInternal30004,
            UINT __MIDL__IDXGIDeviceInternal30005) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetContextResolver( 
            void **__MIDL__IDXGIDeviceInternal30006) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateSurfaceInternal( 
            /* [in] */ IUseCounted2 *SwapChain,
            /* [in] */ IUseCounted2 *__MIDL__IDXGIDeviceInternal30007,
            /* [in] */ void *__MIDL__IDXGIDeviceInternal30008,
            /* [in] */ const DXGI_SURFACE_DESC *pDesc,
            /* [in] */ UINT TextureArraySize,
            /* [in] */ UINT ResourceSize,
            /* [in] */ UINT BindFlags,
            /* [in] */ UINT MiscFlags,
            void *__MIDL__IDXGIDeviceInternal30009,
            /* [optional][out] */ IDXGIResource **pResourceArray) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Blt( 
            /* [in] */ IDXGIResource *Src,
            /* [in] */ const RECT *SrcRect,
            /* [in] */ const RECT *BltRects,
            /* [in] */ UINT BltRectsSize,
            /* [in] */ IDXGIResource *Dest,
            /* [in] */ RECT *DestRect,
            const DXGI_PRESENT_BLT_MAP *Map,
            UINT64 __MIDL__IDXGIDeviceInternal30010,
            UINT Flags,
            UINT __MIDL__IDXGIDeviceInternal30011) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDisplayMode( 
            IDXGIResource *__MIDL__IDXGIDeviceInternal30012) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGammaCaps( 
            DXGI_GAMMA_CONTROL_CAPABILITIES *__MIDL__IDXGIDeviceInternal30013) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OpenSharedResource( 
            /* [in] */ HANDLE hResource,
            /* [in] */ int __MIDL__IDXGIDeviceInternal30014,
            /* [in] */ REFIID ResType,
            /* [out] */ void **DXGIResourceOut) = 0;
        
        virtual BOOL STDMETHODCALLTYPE IsValidScanoutFormat( 
            DXGI_FORMAT Format) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FlushDeletion( 
            IDXGIResource *__MIDL__IDXGIDeviceInternal30015,
            const IDXGIResource **__MIDL__IDXGIDeviceInternal30016,
            UINT __MIDL__IDXGIDeviceInternal30017,
            UINT __MIDL__IDXGIDeviceInternal30018) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetContentProtection( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateTrackedFence( 
            UINT64 __MIDL__IDXGIDeviceInternal30019,
            const SECURITY_ATTRIBUTES *__MIDL__IDXGIDeviceInternal30020,
            ULONG __MIDL__IDXGIDeviceInternal30021,
            void **__MIDL__IDXGIDeviceInternal30022,
            void **__MIDL__IDXGIDeviceInternal30023) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Flush( 
            UINT __MIDL__IDXGIDeviceInternal30024) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AcquireResource( 
            IDXGIResource *__MIDL__IDXGIDeviceInternal30025) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReleaseResource( 
            IDXGIResource *__MIDL__IDXGIDeviceInternal30026) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCaps( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDesc( 
            IDXGIResource *__MIDL__IDXGIDeviceInternal30027,
            DXGI_SURFACE_DESC *__MIDL__IDXGIDeviceInternal30028,
            UINT *__MIDL__IDXGIDeviceInternal30029) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Map( 
            IDXGIResource *__MIDL__IDXGIDeviceInternal30030,
            UINT __MIDL__IDXGIDeviceInternal30031,
            DXGI_MAPPED_RECT *__MIDL__IDXGIDeviceInternal30032,
            UINT __MIDL__IDXGIDeviceInternal30033) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Unmap( 
            IDXGIResource *__MIDL__IDXGIDeviceInternal30034,
            UINT __MIDL__IDXGIDeviceInternal30035) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CheckDirectFlipSupport( 
            UINT __MIDL__IDXGIDeviceInternal30036,
            IDXGIResource *__MIDL__IDXGIDeviceInternal30037,
            IDXGIResource *__MIDL__IDXGIDeviceInternal30038,
            INT *__MIDL__IDXGIDeviceInternal30039) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDeviceRemovedReason( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFlipExSemaphoreHandle( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ValidateGetDisplaySurfaceDataDest( 
            IDXGIDebugProducer *__MIDL__IDXGIDeviceInternal30040,
            UINT __MIDL__IDXGIDeviceInternal30041,
            IDXGIResource *__MIDL__IDXGIDeviceInternal30042) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDXGIDeviceInternal3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDXGIDeviceInternal3 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDXGIDeviceInternal3 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDXGIDeviceInternal3 * This);
        
        HRESULT ( STDMETHODCALLTYPE *Present )( 
            IDXGIDeviceInternal3 * This,
            IDXGIDebugProducer *pDebugProducer,
            IDXGIResource *__MIDL__IDXGIDeviceInternal30000,
            void *pPresent,
            UINT __MIDL__IDXGIDeviceInternal30001,
            UINT __MIDL__IDXGIDeviceInternal30002);
        
        HRESULT ( STDMETHODCALLTYPE *RotateResourceIdentities )( 
            IDXGIDeviceInternal3 * This,
            IDXGIResource *__MIDL__IDXGIDeviceInternal30003,
            const IDXGIResource **__MIDL__IDXGIDeviceInternal30004,
            UINT __MIDL__IDXGIDeviceInternal30005);
        
        HRESULT ( STDMETHODCALLTYPE *GetContextResolver )( 
            IDXGIDeviceInternal3 * This,
            void **__MIDL__IDXGIDeviceInternal30006);
        
        HRESULT ( STDMETHODCALLTYPE *CreateSurfaceInternal )( 
            IDXGIDeviceInternal3 * This,
            /* [in] */ IUseCounted2 *SwapChain,
            /* [in] */ IUseCounted2 *__MIDL__IDXGIDeviceInternal30007,
            /* [in] */ void *__MIDL__IDXGIDeviceInternal30008,
            /* [in] */ const DXGI_SURFACE_DESC *pDesc,
            /* [in] */ UINT TextureArraySize,
            /* [in] */ UINT ResourceSize,
            /* [in] */ UINT BindFlags,
            /* [in] */ UINT MiscFlags,
            void *__MIDL__IDXGIDeviceInternal30009,
            /* [optional][out] */ IDXGIResource **pResourceArray);
        
        HRESULT ( STDMETHODCALLTYPE *Blt )( 
            IDXGIDeviceInternal3 * This,
            /* [in] */ IDXGIResource *Src,
            /* [in] */ const RECT *SrcRect,
            /* [in] */ const RECT *BltRects,
            /* [in] */ UINT BltRectsSize,
            /* [in] */ IDXGIResource *Dest,
            /* [in] */ RECT *DestRect,
            const DXGI_PRESENT_BLT_MAP *Map,
            UINT64 __MIDL__IDXGIDeviceInternal30010,
            UINT Flags,
            UINT __MIDL__IDXGIDeviceInternal30011);
        
        HRESULT ( STDMETHODCALLTYPE *SetDisplayMode )( 
            IDXGIDeviceInternal3 * This,
            IDXGIResource *__MIDL__IDXGIDeviceInternal30012);
        
        HRESULT ( STDMETHODCALLTYPE *GetGammaCaps )( 
            IDXGIDeviceInternal3 * This,
            DXGI_GAMMA_CONTROL_CAPABILITIES *__MIDL__IDXGIDeviceInternal30013);
        
        HRESULT ( STDMETHODCALLTYPE *OpenSharedResource )( 
            IDXGIDeviceInternal3 * This,
            /* [in] */ HANDLE hResource,
            /* [in] */ int __MIDL__IDXGIDeviceInternal30014,
            /* [in] */ REFIID ResType,
            /* [out] */ void **DXGIResourceOut);
        
        BOOL ( STDMETHODCALLTYPE *IsValidScanoutFormat )( 
            IDXGIDeviceInternal3 * This,
            DXGI_FORMAT Format);
        
        HRESULT ( STDMETHODCALLTYPE *FlushDeletion )( 
            IDXGIDeviceInternal3 * This,
            IDXGIResource *__MIDL__IDXGIDeviceInternal30015,
            const IDXGIResource **__MIDL__IDXGIDeviceInternal30016,
            UINT __MIDL__IDXGIDeviceInternal30017,
            UINT __MIDL__IDXGIDeviceInternal30018);
        
        HRESULT ( STDMETHODCALLTYPE *GetContentProtection )( 
            IDXGIDeviceInternal3 * This);
        
        HRESULT ( STDMETHODCALLTYPE *CreateTrackedFence )( 
            IDXGIDeviceInternal3 * This,
            UINT64 __MIDL__IDXGIDeviceInternal30019,
            const SECURITY_ATTRIBUTES *__MIDL__IDXGIDeviceInternal30020,
            ULONG __MIDL__IDXGIDeviceInternal30021,
            void **__MIDL__IDXGIDeviceInternal30022,
            void **__MIDL__IDXGIDeviceInternal30023);
        
        HRESULT ( STDMETHODCALLTYPE *Flush )( 
            IDXGIDeviceInternal3 * This,
            UINT __MIDL__IDXGIDeviceInternal30024);
        
        HRESULT ( STDMETHODCALLTYPE *AcquireResource )( 
            IDXGIDeviceInternal3 * This,
            IDXGIResource *__MIDL__IDXGIDeviceInternal30025);
        
        HRESULT ( STDMETHODCALLTYPE *ReleaseResource )( 
            IDXGIDeviceInternal3 * This,
            IDXGIResource *__MIDL__IDXGIDeviceInternal30026);
        
        HRESULT ( STDMETHODCALLTYPE *GetCaps )( 
            IDXGIDeviceInternal3 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetDesc )( 
            IDXGIDeviceInternal3 * This,
            IDXGIResource *__MIDL__IDXGIDeviceInternal30027,
            DXGI_SURFACE_DESC *__MIDL__IDXGIDeviceInternal30028,
            UINT *__MIDL__IDXGIDeviceInternal30029);
        
        HRESULT ( STDMETHODCALLTYPE *Map )( 
            IDXGIDeviceInternal3 * This,
            IDXGIResource *__MIDL__IDXGIDeviceInternal30030,
            UINT __MIDL__IDXGIDeviceInternal30031,
            DXGI_MAPPED_RECT *__MIDL__IDXGIDeviceInternal30032,
            UINT __MIDL__IDXGIDeviceInternal30033);
        
        HRESULT ( STDMETHODCALLTYPE *Unmap )( 
            IDXGIDeviceInternal3 * This,
            IDXGIResource *__MIDL__IDXGIDeviceInternal30034,
            UINT __MIDL__IDXGIDeviceInternal30035);
        
        HRESULT ( STDMETHODCALLTYPE *CheckDirectFlipSupport )( 
            IDXGIDeviceInternal3 * This,
            UINT __MIDL__IDXGIDeviceInternal30036,
            IDXGIResource *__MIDL__IDXGIDeviceInternal30037,
            IDXGIResource *__MIDL__IDXGIDeviceInternal30038,
            INT *__MIDL__IDXGIDeviceInternal30039);
        
        HRESULT ( STDMETHODCALLTYPE *GetDeviceRemovedReason )( 
            IDXGIDeviceInternal3 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetFlipExSemaphoreHandle )( 
            IDXGIDeviceInternal3 * This);
        
        HRESULT ( STDMETHODCALLTYPE *ValidateGetDisplaySurfaceDataDest )( 
            IDXGIDeviceInternal3 * This,
            IDXGIDebugProducer *__MIDL__IDXGIDeviceInternal30040,
            UINT __MIDL__IDXGIDeviceInternal30041,
            IDXGIResource *__MIDL__IDXGIDeviceInternal30042);
        
        END_INTERFACE
    } IDXGIDeviceInternal3Vtbl;

    interface IDXGIDeviceInternal3
    {
        CONST_VTBL struct IDXGIDeviceInternal3Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDXGIDeviceInternal3_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDXGIDeviceInternal3_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDXGIDeviceInternal3_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDXGIDeviceInternal3_Present(This,pDebugProducer,__MIDL__IDXGIDeviceInternal30000,pPresent,__MIDL__IDXGIDeviceInternal30001,__MIDL__IDXGIDeviceInternal30002)	\
    ( (This)->lpVtbl -> Present(This,pDebugProducer,__MIDL__IDXGIDeviceInternal30000,pPresent,__MIDL__IDXGIDeviceInternal30001,__MIDL__IDXGIDeviceInternal30002) ) 

#define IDXGIDeviceInternal3_RotateResourceIdentities(This,__MIDL__IDXGIDeviceInternal30003,__MIDL__IDXGIDeviceInternal30004,__MIDL__IDXGIDeviceInternal30005)	\
    ( (This)->lpVtbl -> RotateResourceIdentities(This,__MIDL__IDXGIDeviceInternal30003,__MIDL__IDXGIDeviceInternal30004,__MIDL__IDXGIDeviceInternal30005) ) 

#define IDXGIDeviceInternal3_GetContextResolver(This,__MIDL__IDXGIDeviceInternal30006)	\
    ( (This)->lpVtbl -> GetContextResolver(This,__MIDL__IDXGIDeviceInternal30006) ) 

#define IDXGIDeviceInternal3_CreateSurfaceInternal(This,SwapChain,__MIDL__IDXGIDeviceInternal30007,__MIDL__IDXGIDeviceInternal30008,pDesc,TextureArraySize,ResourceSize,BindFlags,MiscFlags,__MIDL__IDXGIDeviceInternal30009,pResourceArray)	\
    ( (This)->lpVtbl -> CreateSurfaceInternal(This,SwapChain,__MIDL__IDXGIDeviceInternal30007,__MIDL__IDXGIDeviceInternal30008,pDesc,TextureArraySize,ResourceSize,BindFlags,MiscFlags,__MIDL__IDXGIDeviceInternal30009,pResourceArray) ) 

#define IDXGIDeviceInternal3_Blt(This,Src,SrcRect,BltRects,BltRectsSize,Dest,DestRect,Map,__MIDL__IDXGIDeviceInternal30010,Flags,__MIDL__IDXGIDeviceInternal30011)	\
    ( (This)->lpVtbl -> Blt(This,Src,SrcRect,BltRects,BltRectsSize,Dest,DestRect,Map,__MIDL__IDXGIDeviceInternal30010,Flags,__MIDL__IDXGIDeviceInternal30011) ) 

#define IDXGIDeviceInternal3_SetDisplayMode(This,__MIDL__IDXGIDeviceInternal30012)	\
    ( (This)->lpVtbl -> SetDisplayMode(This,__MIDL__IDXGIDeviceInternal30012) ) 

#define IDXGIDeviceInternal3_GetGammaCaps(This,__MIDL__IDXGIDeviceInternal30013)	\
    ( (This)->lpVtbl -> GetGammaCaps(This,__MIDL__IDXGIDeviceInternal30013) ) 

#define IDXGIDeviceInternal3_OpenSharedResource(This,hResource,__MIDL__IDXGIDeviceInternal30014,ResType,DXGIResourceOut)	\
    ( (This)->lpVtbl -> OpenSharedResource(This,hResource,__MIDL__IDXGIDeviceInternal30014,ResType,DXGIResourceOut) ) 

#define IDXGIDeviceInternal3_IsValidScanoutFormat(This,Format)	\
    ( (This)->lpVtbl -> IsValidScanoutFormat(This,Format) ) 

#define IDXGIDeviceInternal3_FlushDeletion(This,__MIDL__IDXGIDeviceInternal30015,__MIDL__IDXGIDeviceInternal30016,__MIDL__IDXGIDeviceInternal30017,__MIDL__IDXGIDeviceInternal30018)	\
    ( (This)->lpVtbl -> FlushDeletion(This,__MIDL__IDXGIDeviceInternal30015,__MIDL__IDXGIDeviceInternal30016,__MIDL__IDXGIDeviceInternal30017,__MIDL__IDXGIDeviceInternal30018) ) 

#define IDXGIDeviceInternal3_GetContentProtection(This)	\
    ( (This)->lpVtbl -> GetContentProtection(This) ) 

#define IDXGIDeviceInternal3_CreateTrackedFence(This,__MIDL__IDXGIDeviceInternal30019,__MIDL__IDXGIDeviceInternal30020,__MIDL__IDXGIDeviceInternal30021,__MIDL__IDXGIDeviceInternal30022,__MIDL__IDXGIDeviceInternal30023)	\
    ( (This)->lpVtbl -> CreateTrackedFence(This,__MIDL__IDXGIDeviceInternal30019,__MIDL__IDXGIDeviceInternal30020,__MIDL__IDXGIDeviceInternal30021,__MIDL__IDXGIDeviceInternal30022,__MIDL__IDXGIDeviceInternal30023) ) 

#define IDXGIDeviceInternal3_Flush(This,__MIDL__IDXGIDeviceInternal30024)	\
    ( (This)->lpVtbl -> Flush(This,__MIDL__IDXGIDeviceInternal30024) ) 

#define IDXGIDeviceInternal3_AcquireResource(This,__MIDL__IDXGIDeviceInternal30025)	\
    ( (This)->lpVtbl -> AcquireResource(This,__MIDL__IDXGIDeviceInternal30025) ) 

#define IDXGIDeviceInternal3_ReleaseResource(This,__MIDL__IDXGIDeviceInternal30026)	\
    ( (This)->lpVtbl -> ReleaseResource(This,__MIDL__IDXGIDeviceInternal30026) ) 

#define IDXGIDeviceInternal3_GetCaps(This)	\
    ( (This)->lpVtbl -> GetCaps(This) ) 

#define IDXGIDeviceInternal3_GetDesc(This,__MIDL__IDXGIDeviceInternal30027,__MIDL__IDXGIDeviceInternal30028,__MIDL__IDXGIDeviceInternal30029)	\
    ( (This)->lpVtbl -> GetDesc(This,__MIDL__IDXGIDeviceInternal30027,__MIDL__IDXGIDeviceInternal30028,__MIDL__IDXGIDeviceInternal30029) ) 

#define IDXGIDeviceInternal3_Map(This,__MIDL__IDXGIDeviceInternal30030,__MIDL__IDXGIDeviceInternal30031,__MIDL__IDXGIDeviceInternal30032,__MIDL__IDXGIDeviceInternal30033)	\
    ( (This)->lpVtbl -> Map(This,__MIDL__IDXGIDeviceInternal30030,__MIDL__IDXGIDeviceInternal30031,__MIDL__IDXGIDeviceInternal30032,__MIDL__IDXGIDeviceInternal30033) ) 

#define IDXGIDeviceInternal3_Unmap(This,__MIDL__IDXGIDeviceInternal30034,__MIDL__IDXGIDeviceInternal30035)	\
    ( (This)->lpVtbl -> Unmap(This,__MIDL__IDXGIDeviceInternal30034,__MIDL__IDXGIDeviceInternal30035) ) 

#define IDXGIDeviceInternal3_CheckDirectFlipSupport(This,__MIDL__IDXGIDeviceInternal30036,__MIDL__IDXGIDeviceInternal30037,__MIDL__IDXGIDeviceInternal30038,__MIDL__IDXGIDeviceInternal30039)	\
    ( (This)->lpVtbl -> CheckDirectFlipSupport(This,__MIDL__IDXGIDeviceInternal30036,__MIDL__IDXGIDeviceInternal30037,__MIDL__IDXGIDeviceInternal30038,__MIDL__IDXGIDeviceInternal30039) ) 

#define IDXGIDeviceInternal3_GetDeviceRemovedReason(This)	\
    ( (This)->lpVtbl -> GetDeviceRemovedReason(This) ) 

#define IDXGIDeviceInternal3_GetFlipExSemaphoreHandle(This)	\
    ( (This)->lpVtbl -> GetFlipExSemaphoreHandle(This) ) 

#define IDXGIDeviceInternal3_ValidateGetDisplaySurfaceDataDest(This,__MIDL__IDXGIDeviceInternal30040,__MIDL__IDXGIDeviceInternal30041,__MIDL__IDXGIDeviceInternal30042)	\
    ( (This)->lpVtbl -> ValidateGetDisplaySurfaceDataDest(This,__MIDL__IDXGIDeviceInternal30040,__MIDL__IDXGIDeviceInternal30041,__MIDL__IDXGIDeviceInternal30042) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDXGIDeviceInternal3_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


