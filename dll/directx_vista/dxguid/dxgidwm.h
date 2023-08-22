

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 04:14:07 2038
 */
/* Compiler settings for dxgidwm.idl:
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

#ifndef __dxgidwm_h__
#define __dxgidwm_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IDXGISwapChainDWM_FWD_DEFINED__
#define __IDXGISwapChainDWM_FWD_DEFINED__
typedef interface IDXGISwapChainDWM IDXGISwapChainDWM;

#endif 	/* __IDXGISwapChainDWM_FWD_DEFINED__ */


#ifndef __IDXGISwapChainDWM1_FWD_DEFINED__
#define __IDXGISwapChainDWM1_FWD_DEFINED__
typedef interface IDXGISwapChainDWM1 IDXGISwapChainDWM1;

#endif 	/* __IDXGISwapChainDWM1_FWD_DEFINED__ */


#ifndef __IDXGISwapChainDWM8_FWD_DEFINED__
#define __IDXGISwapChainDWM8_FWD_DEFINED__
typedef interface IDXGISwapChainDWM8 IDXGISwapChainDWM8;

#endif 	/* __IDXGISwapChainDWM8_FWD_DEFINED__ */


#ifndef __IDXGIAdapterDWM_FWD_DEFINED__
#define __IDXGIAdapterDWM_FWD_DEFINED__
typedef interface IDXGIAdapterDWM IDXGIAdapterDWM;

#endif 	/* __IDXGIAdapterDWM_FWD_DEFINED__ */


#ifndef __IDXGIFactoryDWM_FWD_DEFINED__
#define __IDXGIFactoryDWM_FWD_DEFINED__
typedef interface IDXGIFactoryDWM IDXGIFactoryDWM;

#endif 	/* __IDXGIFactoryDWM_FWD_DEFINED__ */


#ifndef __IDXGIFactoryDWM8_FWD_DEFINED__
#define __IDXGIFactoryDWM8_FWD_DEFINED__
typedef interface IDXGIFactoryDWM8 IDXGIFactoryDWM8;

#endif 	/* __IDXGIFactoryDWM8_FWD_DEFINED__ */


#ifndef __IDXGIDeviceDWM_FWD_DEFINED__
#define __IDXGIDeviceDWM_FWD_DEFINED__
typedef interface IDXGIDeviceDWM IDXGIDeviceDWM;

#endif 	/* __IDXGIDeviceDWM_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "dxgi.h"
#include "dxgi1_2.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IDXGISwapChainDWM_INTERFACE_DEFINED__
#define __IDXGISwapChainDWM_INTERFACE_DEFINED__

/* interface IDXGISwapChainDWM */
/* [uuid][local][object] */ 


EXTERN_C const IID IID_IDXGISwapChainDWM;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("f69f223b-45d3-4aa0-98c8-c40c2b231029")
    IDXGISwapChainDWM : public IDXGIDeviceSubObject
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Present( 
            /* [in] */ UINT SyncInterval,
            /* [in] */ UINT Flags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBuffer( 
            /* [in] */ UINT Buffer,
            /* [in] */ REFIID riid,
            /* [out] */ void **ppSurface) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDesc( 
            /* [out] */ DXGI_SWAP_CHAIN_DESC *pDesc) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ResizeBuffers( 
            /* [in] */ UINT BufferCount,
            /* [in] */ UINT Width,
            /* [in] */ UINT Height,
            /* [in] */ DXGI_FORMAT NewFormat,
            /* [in] */ UINT SwapChainFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ResizeTarget( 
            /* [in] */ DXGI_MODE_DESC *pNewTargetParameters) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetContainingOutput( 
            /* [out] */ IDXGIOutput **ppOutput) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFrameStatistics( 
            /* [out] */ DXGI_FRAME_STATISTICS *pStats) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLastPresentCount( 
            /* [out] */ UINT *pLastPresentCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFullscreenState( 
            /* [in] */ BOOL Fullscreen,
            /* [in] */ IDXGIOutput *pTarget) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFullscreenState( 
            /* [out] */ BOOL *pFullscreen,
            /* [out] */ IDXGIOutput **ppTarget) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDXGISwapChainDWMVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDXGISwapChainDWM * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDXGISwapChainDWM * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDXGISwapChainDWM * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateData )( 
            IDXGISwapChainDWM * This,
            /* [annotation][in] */ 
            _In_  REFGUID Name,
            /* [in] */ UINT DataSize,
            /* [annotation][in] */ 
            _In_reads_bytes_(DataSize)  const void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateDataInterface )( 
            IDXGISwapChainDWM * This,
            /* [annotation][in] */ 
            _In_  REFGUID Name,
            /* [annotation][in] */ 
            _In_opt_  const IUnknown *pUnknown);
        
        HRESULT ( STDMETHODCALLTYPE *GetPrivateData )( 
            IDXGISwapChainDWM * This,
            /* [annotation][in] */ 
            _In_  REFGUID Name,
            /* [annotation][out][in] */ 
            _Inout_  UINT *pDataSize,
            /* [annotation][out] */ 
            _Out_writes_bytes_(*pDataSize)  void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *GetParent )( 
            IDXGISwapChainDWM * This,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][retval][out] */ 
            _COM_Outptr_  void **ppParent);
        
        HRESULT ( STDMETHODCALLTYPE *GetDevice )( 
            IDXGISwapChainDWM * This,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][retval][out] */ 
            _COM_Outptr_  void **ppDevice);
        
        HRESULT ( STDMETHODCALLTYPE *Present )( 
            IDXGISwapChainDWM * This,
            /* [in] */ UINT SyncInterval,
            /* [in] */ UINT Flags);
        
        HRESULT ( STDMETHODCALLTYPE *GetBuffer )( 
            IDXGISwapChainDWM * This,
            /* [in] */ UINT Buffer,
            /* [in] */ REFIID riid,
            /* [out] */ void **ppSurface);
        
        HRESULT ( STDMETHODCALLTYPE *GetDesc )( 
            IDXGISwapChainDWM * This,
            /* [out] */ DXGI_SWAP_CHAIN_DESC *pDesc);
        
        HRESULT ( STDMETHODCALLTYPE *ResizeBuffers )( 
            IDXGISwapChainDWM * This,
            /* [in] */ UINT BufferCount,
            /* [in] */ UINT Width,
            /* [in] */ UINT Height,
            /* [in] */ DXGI_FORMAT NewFormat,
            /* [in] */ UINT SwapChainFlags);
        
        HRESULT ( STDMETHODCALLTYPE *ResizeTarget )( 
            IDXGISwapChainDWM * This,
            /* [in] */ DXGI_MODE_DESC *pNewTargetParameters);
        
        HRESULT ( STDMETHODCALLTYPE *GetContainingOutput )( 
            IDXGISwapChainDWM * This,
            /* [out] */ IDXGIOutput **ppOutput);
        
        HRESULT ( STDMETHODCALLTYPE *GetFrameStatistics )( 
            IDXGISwapChainDWM * This,
            /* [out] */ DXGI_FRAME_STATISTICS *pStats);
        
        HRESULT ( STDMETHODCALLTYPE *GetLastPresentCount )( 
            IDXGISwapChainDWM * This,
            /* [out] */ UINT *pLastPresentCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetFullscreenState )( 
            IDXGISwapChainDWM * This,
            /* [in] */ BOOL Fullscreen,
            /* [in] */ IDXGIOutput *pTarget);
        
        HRESULT ( STDMETHODCALLTYPE *GetFullscreenState )( 
            IDXGISwapChainDWM * This,
            /* [out] */ BOOL *pFullscreen,
            /* [out] */ IDXGIOutput **ppTarget);
        
        END_INTERFACE
    } IDXGISwapChainDWMVtbl;

    interface IDXGISwapChainDWM
    {
        CONST_VTBL struct IDXGISwapChainDWMVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDXGISwapChainDWM_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDXGISwapChainDWM_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDXGISwapChainDWM_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDXGISwapChainDWM_SetPrivateData(This,Name,DataSize,pData)	\
    ( (This)->lpVtbl -> SetPrivateData(This,Name,DataSize,pData) ) 

#define IDXGISwapChainDWM_SetPrivateDataInterface(This,Name,pUnknown)	\
    ( (This)->lpVtbl -> SetPrivateDataInterface(This,Name,pUnknown) ) 

#define IDXGISwapChainDWM_GetPrivateData(This,Name,pDataSize,pData)	\
    ( (This)->lpVtbl -> GetPrivateData(This,Name,pDataSize,pData) ) 

#define IDXGISwapChainDWM_GetParent(This,riid,ppParent)	\
    ( (This)->lpVtbl -> GetParent(This,riid,ppParent) ) 


#define IDXGISwapChainDWM_GetDevice(This,riid,ppDevice)	\
    ( (This)->lpVtbl -> GetDevice(This,riid,ppDevice) ) 


#define IDXGISwapChainDWM_Present(This,SyncInterval,Flags)	\
    ( (This)->lpVtbl -> Present(This,SyncInterval,Flags) ) 

#define IDXGISwapChainDWM_GetBuffer(This,Buffer,riid,ppSurface)	\
    ( (This)->lpVtbl -> GetBuffer(This,Buffer,riid,ppSurface) ) 

#define IDXGISwapChainDWM_GetDesc(This,pDesc)	\
    ( (This)->lpVtbl -> GetDesc(This,pDesc) ) 

#define IDXGISwapChainDWM_ResizeBuffers(This,BufferCount,Width,Height,NewFormat,SwapChainFlags)	\
    ( (This)->lpVtbl -> ResizeBuffers(This,BufferCount,Width,Height,NewFormat,SwapChainFlags) ) 

#define IDXGISwapChainDWM_ResizeTarget(This,pNewTargetParameters)	\
    ( (This)->lpVtbl -> ResizeTarget(This,pNewTargetParameters) ) 

#define IDXGISwapChainDWM_GetContainingOutput(This,ppOutput)	\
    ( (This)->lpVtbl -> GetContainingOutput(This,ppOutput) ) 

#define IDXGISwapChainDWM_GetFrameStatistics(This,pStats)	\
    ( (This)->lpVtbl -> GetFrameStatistics(This,pStats) ) 

#define IDXGISwapChainDWM_GetLastPresentCount(This,pLastPresentCount)	\
    ( (This)->lpVtbl -> GetLastPresentCount(This,pLastPresentCount) ) 

#define IDXGISwapChainDWM_SetFullscreenState(This,Fullscreen,pTarget)	\
    ( (This)->lpVtbl -> SetFullscreenState(This,Fullscreen,pTarget) ) 

#define IDXGISwapChainDWM_GetFullscreenState(This,pFullscreen,ppTarget)	\
    ( (This)->lpVtbl -> GetFullscreenState(This,pFullscreen,ppTarget) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDXGISwapChainDWM_INTERFACE_DEFINED__ */


#ifndef __IDXGISwapChainDWM1_INTERFACE_DEFINED__
#define __IDXGISwapChainDWM1_INTERFACE_DEFINED__

/* interface IDXGISwapChainDWM1 */
/* [uuid][local][object] */ 


EXTERN_C const IID IID_IDXGISwapChainDWM1;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ffffffff-ffff-ffff-ffff-fffffffffffc")
    IDXGISwapChainDWM1 : public IDXGIDeviceSubObject
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Present( 
            /* [in] */ UINT SyncInterval,
            /* [in] */ UINT Flags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBuffer( 
            /* [in] */ UINT Buffer,
            /* [in] */ REFIID riid,
            /* [out] */ void **ppSurface) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDesc( 
            /* [out] */ DXGI_SWAP_CHAIN_DESC *pDesc) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ResizeBuffers( 
            /* [in] */ UINT BufferCount,
            /* [in] */ UINT Width,
            /* [in] */ UINT Height,
            /* [in] */ DXGI_FORMAT NewFormat,
            /* [in] */ UINT SwapChainFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ResizeTarget( 
            /* [in] */ DXGI_MODE_DESC *pNewTargetParameters) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetContainingOutput( 
            /* [out] */ IDXGIOutput **ppOutput) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFrameStatistics( 
            /* [out] */ DXGI_FRAME_STATISTICS *pStats) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLastPresentCount( 
            /* [out] */ UINT *pLastPresentCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PresentDWM( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLogicalSurfaceHandle( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CheckDirectFlipSupport( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCompositionSurface( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFrameStatisticsDWM( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMultiplaneOverlayCaps( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PresentMultiplaneOverlay( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CheckPresentDurationSupport( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPrivateFrameDuration( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetHardwareProtection( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetHardwareProtection( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetLatencyHint( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SwapBuffers( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CheckDwmVidPnOvership( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentBackBufferIndex( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBackBufferImplicitRotationCount( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFrontBufferRenderingCapability( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDXGISwapChainDWM1Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDXGISwapChainDWM1 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDXGISwapChainDWM1 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDXGISwapChainDWM1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateData )( 
            IDXGISwapChainDWM1 * This,
            /* [annotation][in] */ 
            _In_  REFGUID Name,
            /* [in] */ UINT DataSize,
            /* [annotation][in] */ 
            _In_reads_bytes_(DataSize)  const void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateDataInterface )( 
            IDXGISwapChainDWM1 * This,
            /* [annotation][in] */ 
            _In_  REFGUID Name,
            /* [annotation][in] */ 
            _In_opt_  const IUnknown *pUnknown);
        
        HRESULT ( STDMETHODCALLTYPE *GetPrivateData )( 
            IDXGISwapChainDWM1 * This,
            /* [annotation][in] */ 
            _In_  REFGUID Name,
            /* [annotation][out][in] */ 
            _Inout_  UINT *pDataSize,
            /* [annotation][out] */ 
            _Out_writes_bytes_(*pDataSize)  void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *GetParent )( 
            IDXGISwapChainDWM1 * This,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][retval][out] */ 
            _COM_Outptr_  void **ppParent);
        
        HRESULT ( STDMETHODCALLTYPE *GetDevice )( 
            IDXGISwapChainDWM1 * This,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][retval][out] */ 
            _COM_Outptr_  void **ppDevice);
        
        HRESULT ( STDMETHODCALLTYPE *Present )( 
            IDXGISwapChainDWM1 * This,
            /* [in] */ UINT SyncInterval,
            /* [in] */ UINT Flags);
        
        HRESULT ( STDMETHODCALLTYPE *GetBuffer )( 
            IDXGISwapChainDWM1 * This,
            /* [in] */ UINT Buffer,
            /* [in] */ REFIID riid,
            /* [out] */ void **ppSurface);
        
        HRESULT ( STDMETHODCALLTYPE *GetDesc )( 
            IDXGISwapChainDWM1 * This,
            /* [out] */ DXGI_SWAP_CHAIN_DESC *pDesc);
        
        HRESULT ( STDMETHODCALLTYPE *ResizeBuffers )( 
            IDXGISwapChainDWM1 * This,
            /* [in] */ UINT BufferCount,
            /* [in] */ UINT Width,
            /* [in] */ UINT Height,
            /* [in] */ DXGI_FORMAT NewFormat,
            /* [in] */ UINT SwapChainFlags);
        
        HRESULT ( STDMETHODCALLTYPE *ResizeTarget )( 
            IDXGISwapChainDWM1 * This,
            /* [in] */ DXGI_MODE_DESC *pNewTargetParameters);
        
        HRESULT ( STDMETHODCALLTYPE *GetContainingOutput )( 
            IDXGISwapChainDWM1 * This,
            /* [out] */ IDXGIOutput **ppOutput);
        
        HRESULT ( STDMETHODCALLTYPE *GetFrameStatistics )( 
            IDXGISwapChainDWM1 * This,
            /* [out] */ DXGI_FRAME_STATISTICS *pStats);
        
        HRESULT ( STDMETHODCALLTYPE *GetLastPresentCount )( 
            IDXGISwapChainDWM1 * This,
            /* [out] */ UINT *pLastPresentCount);
        
        HRESULT ( STDMETHODCALLTYPE *PresentDWM )( 
            IDXGISwapChainDWM1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetLogicalSurfaceHandle )( 
            IDXGISwapChainDWM1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *CheckDirectFlipSupport )( 
            IDXGISwapChainDWM1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetCompositionSurface )( 
            IDXGISwapChainDWM1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetFrameStatisticsDWM )( 
            IDXGISwapChainDWM1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetMultiplaneOverlayCaps )( 
            IDXGISwapChainDWM1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *PresentMultiplaneOverlay )( 
            IDXGISwapChainDWM1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *CheckPresentDurationSupport )( 
            IDXGISwapChainDWM1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateFrameDuration )( 
            IDXGISwapChainDWM1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetHardwareProtection )( 
            IDXGISwapChainDWM1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetHardwareProtection )( 
            IDXGISwapChainDWM1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetLatencyHint )( 
            IDXGISwapChainDWM1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SwapBuffers )( 
            IDXGISwapChainDWM1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *CheckDwmVidPnOvership )( 
            IDXGISwapChainDWM1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentBackBufferIndex )( 
            IDXGISwapChainDWM1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetBackBufferImplicitRotationCount )( 
            IDXGISwapChainDWM1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetFrontBufferRenderingCapability )( 
            IDXGISwapChainDWM1 * This);
        
        END_INTERFACE
    } IDXGISwapChainDWM1Vtbl;

    interface IDXGISwapChainDWM1
    {
        CONST_VTBL struct IDXGISwapChainDWM1Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDXGISwapChainDWM1_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDXGISwapChainDWM1_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDXGISwapChainDWM1_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDXGISwapChainDWM1_SetPrivateData(This,Name,DataSize,pData)	\
    ( (This)->lpVtbl -> SetPrivateData(This,Name,DataSize,pData) ) 

#define IDXGISwapChainDWM1_SetPrivateDataInterface(This,Name,pUnknown)	\
    ( (This)->lpVtbl -> SetPrivateDataInterface(This,Name,pUnknown) ) 

#define IDXGISwapChainDWM1_GetPrivateData(This,Name,pDataSize,pData)	\
    ( (This)->lpVtbl -> GetPrivateData(This,Name,pDataSize,pData) ) 

#define IDXGISwapChainDWM1_GetParent(This,riid,ppParent)	\
    ( (This)->lpVtbl -> GetParent(This,riid,ppParent) ) 


#define IDXGISwapChainDWM1_GetDevice(This,riid,ppDevice)	\
    ( (This)->lpVtbl -> GetDevice(This,riid,ppDevice) ) 


#define IDXGISwapChainDWM1_Present(This,SyncInterval,Flags)	\
    ( (This)->lpVtbl -> Present(This,SyncInterval,Flags) ) 

#define IDXGISwapChainDWM1_GetBuffer(This,Buffer,riid,ppSurface)	\
    ( (This)->lpVtbl -> GetBuffer(This,Buffer,riid,ppSurface) ) 

#define IDXGISwapChainDWM1_GetDesc(This,pDesc)	\
    ( (This)->lpVtbl -> GetDesc(This,pDesc) ) 

#define IDXGISwapChainDWM1_ResizeBuffers(This,BufferCount,Width,Height,NewFormat,SwapChainFlags)	\
    ( (This)->lpVtbl -> ResizeBuffers(This,BufferCount,Width,Height,NewFormat,SwapChainFlags) ) 

#define IDXGISwapChainDWM1_ResizeTarget(This,pNewTargetParameters)	\
    ( (This)->lpVtbl -> ResizeTarget(This,pNewTargetParameters) ) 

#define IDXGISwapChainDWM1_GetContainingOutput(This,ppOutput)	\
    ( (This)->lpVtbl -> GetContainingOutput(This,ppOutput) ) 

#define IDXGISwapChainDWM1_GetFrameStatistics(This,pStats)	\
    ( (This)->lpVtbl -> GetFrameStatistics(This,pStats) ) 

#define IDXGISwapChainDWM1_GetLastPresentCount(This,pLastPresentCount)	\
    ( (This)->lpVtbl -> GetLastPresentCount(This,pLastPresentCount) ) 

#define IDXGISwapChainDWM1_PresentDWM(This)	\
    ( (This)->lpVtbl -> PresentDWM(This) ) 

#define IDXGISwapChainDWM1_GetLogicalSurfaceHandle(This)	\
    ( (This)->lpVtbl -> GetLogicalSurfaceHandle(This) ) 

#define IDXGISwapChainDWM1_CheckDirectFlipSupport(This)	\
    ( (This)->lpVtbl -> CheckDirectFlipSupport(This) ) 

#define IDXGISwapChainDWM1_GetCompositionSurface(This)	\
    ( (This)->lpVtbl -> GetCompositionSurface(This) ) 

#define IDXGISwapChainDWM1_GetFrameStatisticsDWM(This)	\
    ( (This)->lpVtbl -> GetFrameStatisticsDWM(This) ) 

#define IDXGISwapChainDWM1_GetMultiplaneOverlayCaps(This)	\
    ( (This)->lpVtbl -> GetMultiplaneOverlayCaps(This) ) 

#define IDXGISwapChainDWM1_PresentMultiplaneOverlay(This)	\
    ( (This)->lpVtbl -> PresentMultiplaneOverlay(This) ) 

#define IDXGISwapChainDWM1_CheckPresentDurationSupport(This)	\
    ( (This)->lpVtbl -> CheckPresentDurationSupport(This) ) 

#define IDXGISwapChainDWM1_SetPrivateFrameDuration(This)	\
    ( (This)->lpVtbl -> SetPrivateFrameDuration(This) ) 

#define IDXGISwapChainDWM1_SetHardwareProtection(This)	\
    ( (This)->lpVtbl -> SetHardwareProtection(This) ) 

#define IDXGISwapChainDWM1_GetHardwareProtection(This)	\
    ( (This)->lpVtbl -> GetHardwareProtection(This) ) 

#define IDXGISwapChainDWM1_SetLatencyHint(This)	\
    ( (This)->lpVtbl -> SetLatencyHint(This) ) 

#define IDXGISwapChainDWM1_SwapBuffers(This)	\
    ( (This)->lpVtbl -> SwapBuffers(This) ) 

#define IDXGISwapChainDWM1_CheckDwmVidPnOvership(This)	\
    ( (This)->lpVtbl -> CheckDwmVidPnOvership(This) ) 

#define IDXGISwapChainDWM1_GetCurrentBackBufferIndex(This)	\
    ( (This)->lpVtbl -> GetCurrentBackBufferIndex(This) ) 

#define IDXGISwapChainDWM1_GetBackBufferImplicitRotationCount(This)	\
    ( (This)->lpVtbl -> GetBackBufferImplicitRotationCount(This) ) 

#define IDXGISwapChainDWM1_GetFrontBufferRenderingCapability(This)	\
    ( (This)->lpVtbl -> GetFrontBufferRenderingCapability(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDXGISwapChainDWM1_INTERFACE_DEFINED__ */


#ifndef __IDXGISwapChainDWM8_INTERFACE_DEFINED__
#define __IDXGISwapChainDWM8_INTERFACE_DEFINED__

/* interface IDXGISwapChainDWM8 */
/* [uuid][local][object] */ 


EXTERN_C const IID IID_IDXGISwapChainDWM8;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ffffffff-ffff-ffff-ffff-fffffffffffd")
    IDXGISwapChainDWM8 : public IDXGIObject
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetDevice( 
            /* [in] */ REFIID riid,
            /* [out] */ void **ppvObject) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Present( 
            /* [in] */ UINT SyncInterval,
            /* [in] */ UINT Flags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBuffer( 
            /* [in] */ UINT Buffer,
            /* [in] */ REFIID riid,
            /* [out] */ void **ppSurface) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDesc( 
            /* [out] */ DXGI_SWAP_CHAIN_DESC *pDesc) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ResizeBuffers( 
            /* [in] */ UINT BufferCount,
            /* [in] */ UINT Width,
            /* [in] */ UINT Height,
            /* [in] */ DXGI_FORMAT NewFormat,
            /* [in] */ UINT SwapChainFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ResizeTarget( 
            /* [in] */ DXGI_MODE_DESC *pNewTargetParameters) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetContainingOutput( 
            /* [out] */ IDXGIOutput **ppOutput) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFrameStatistics( 
            /* [out] */ DXGI_FRAME_STATISTICS *pStats) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLastPresentCount( 
            /* [out] */ UINT *pLastPresentCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Present1( 
            /* [in] */ UINT SyncInterval,
            /* [in] */ UINT Flags,
            /* [in] */ UINT DirtyRectsCount,
            /* [in] */ RECT *pDirtyRects,
            /* [in] */ RECT *pScrollRect,
            /* [in] */ POINT *pScrollOffset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLogicalSurfaceHandle( 
            /* [out] */ LPVOID pVoid) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CheckDirectFlipSupport( 
            /* [in] */ ULONG __MIDL__IDXGISwapChainDWM80000,
            /* [in] */ IDXGIResource *pResource,
            /* [in] */ ULONG *__MIDL__IDXGISwapChainDWM80001) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Present2( 
            /* [in] */ UINT SyncInterval,
            /* [in] */ UINT Flags,
            /* [in] */ UINT DirtyRectsCount,
            /* [in] */ RECT *pDirtyRects,
            /* [in] */ RECT *pScrollRect,
            /* [in] */ POINT *pScrollOffset,
            /* [in] */ IDXGIResource *pResource) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCompositionSurface( 
            /* [out] */ LPVOID *ppVoid) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDXGISwapChainDWM8Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDXGISwapChainDWM8 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDXGISwapChainDWM8 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDXGISwapChainDWM8 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateData )( 
            IDXGISwapChainDWM8 * This,
            /* [annotation][in] */ 
            _In_  REFGUID Name,
            /* [in] */ UINT DataSize,
            /* [annotation][in] */ 
            _In_reads_bytes_(DataSize)  const void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateDataInterface )( 
            IDXGISwapChainDWM8 * This,
            /* [annotation][in] */ 
            _In_  REFGUID Name,
            /* [annotation][in] */ 
            _In_opt_  const IUnknown *pUnknown);
        
        HRESULT ( STDMETHODCALLTYPE *GetPrivateData )( 
            IDXGISwapChainDWM8 * This,
            /* [annotation][in] */ 
            _In_  REFGUID Name,
            /* [annotation][out][in] */ 
            _Inout_  UINT *pDataSize,
            /* [annotation][out] */ 
            _Out_writes_bytes_(*pDataSize)  void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *GetParent )( 
            IDXGISwapChainDWM8 * This,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][retval][out] */ 
            _COM_Outptr_  void **ppParent);
        
        HRESULT ( STDMETHODCALLTYPE *GetDevice )( 
            IDXGISwapChainDWM8 * This,
            /* [in] */ REFIID riid,
            /* [out] */ void **ppvObject);
        
        HRESULT ( STDMETHODCALLTYPE *Present )( 
            IDXGISwapChainDWM8 * This,
            /* [in] */ UINT SyncInterval,
            /* [in] */ UINT Flags);
        
        HRESULT ( STDMETHODCALLTYPE *GetBuffer )( 
            IDXGISwapChainDWM8 * This,
            /* [in] */ UINT Buffer,
            /* [in] */ REFIID riid,
            /* [out] */ void **ppSurface);
        
        HRESULT ( STDMETHODCALLTYPE *GetDesc )( 
            IDXGISwapChainDWM8 * This,
            /* [out] */ DXGI_SWAP_CHAIN_DESC *pDesc);
        
        HRESULT ( STDMETHODCALLTYPE *ResizeBuffers )( 
            IDXGISwapChainDWM8 * This,
            /* [in] */ UINT BufferCount,
            /* [in] */ UINT Width,
            /* [in] */ UINT Height,
            /* [in] */ DXGI_FORMAT NewFormat,
            /* [in] */ UINT SwapChainFlags);
        
        HRESULT ( STDMETHODCALLTYPE *ResizeTarget )( 
            IDXGISwapChainDWM8 * This,
            /* [in] */ DXGI_MODE_DESC *pNewTargetParameters);
        
        HRESULT ( STDMETHODCALLTYPE *GetContainingOutput )( 
            IDXGISwapChainDWM8 * This,
            /* [out] */ IDXGIOutput **ppOutput);
        
        HRESULT ( STDMETHODCALLTYPE *GetFrameStatistics )( 
            IDXGISwapChainDWM8 * This,
            /* [out] */ DXGI_FRAME_STATISTICS *pStats);
        
        HRESULT ( STDMETHODCALLTYPE *GetLastPresentCount )( 
            IDXGISwapChainDWM8 * This,
            /* [out] */ UINT *pLastPresentCount);
        
        HRESULT ( STDMETHODCALLTYPE *Present1 )( 
            IDXGISwapChainDWM8 * This,
            /* [in] */ UINT SyncInterval,
            /* [in] */ UINT Flags,
            /* [in] */ UINT DirtyRectsCount,
            /* [in] */ RECT *pDirtyRects,
            /* [in] */ RECT *pScrollRect,
            /* [in] */ POINT *pScrollOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetLogicalSurfaceHandle )( 
            IDXGISwapChainDWM8 * This,
            /* [out] */ LPVOID pVoid);
        
        HRESULT ( STDMETHODCALLTYPE *CheckDirectFlipSupport )( 
            IDXGISwapChainDWM8 * This,
            /* [in] */ ULONG __MIDL__IDXGISwapChainDWM80000,
            /* [in] */ IDXGIResource *pResource,
            /* [in] */ ULONG *__MIDL__IDXGISwapChainDWM80001);
        
        HRESULT ( STDMETHODCALLTYPE *Present2 )( 
            IDXGISwapChainDWM8 * This,
            /* [in] */ UINT SyncInterval,
            /* [in] */ UINT Flags,
            /* [in] */ UINT DirtyRectsCount,
            /* [in] */ RECT *pDirtyRects,
            /* [in] */ RECT *pScrollRect,
            /* [in] */ POINT *pScrollOffset,
            /* [in] */ IDXGIResource *pResource);
        
        HRESULT ( STDMETHODCALLTYPE *GetCompositionSurface )( 
            IDXGISwapChainDWM8 * This,
            /* [out] */ LPVOID *ppVoid);
        
        END_INTERFACE
    } IDXGISwapChainDWM8Vtbl;

    interface IDXGISwapChainDWM8
    {
        CONST_VTBL struct IDXGISwapChainDWM8Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDXGISwapChainDWM8_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDXGISwapChainDWM8_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDXGISwapChainDWM8_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDXGISwapChainDWM8_SetPrivateData(This,Name,DataSize,pData)	\
    ( (This)->lpVtbl -> SetPrivateData(This,Name,DataSize,pData) ) 

#define IDXGISwapChainDWM8_SetPrivateDataInterface(This,Name,pUnknown)	\
    ( (This)->lpVtbl -> SetPrivateDataInterface(This,Name,pUnknown) ) 

#define IDXGISwapChainDWM8_GetPrivateData(This,Name,pDataSize,pData)	\
    ( (This)->lpVtbl -> GetPrivateData(This,Name,pDataSize,pData) ) 

#define IDXGISwapChainDWM8_GetParent(This,riid,ppParent)	\
    ( (This)->lpVtbl -> GetParent(This,riid,ppParent) ) 


#define IDXGISwapChainDWM8_GetDevice(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> GetDevice(This,riid,ppvObject) ) 

#define IDXGISwapChainDWM8_Present(This,SyncInterval,Flags)	\
    ( (This)->lpVtbl -> Present(This,SyncInterval,Flags) ) 

#define IDXGISwapChainDWM8_GetBuffer(This,Buffer,riid,ppSurface)	\
    ( (This)->lpVtbl -> GetBuffer(This,Buffer,riid,ppSurface) ) 

#define IDXGISwapChainDWM8_GetDesc(This,pDesc)	\
    ( (This)->lpVtbl -> GetDesc(This,pDesc) ) 

#define IDXGISwapChainDWM8_ResizeBuffers(This,BufferCount,Width,Height,NewFormat,SwapChainFlags)	\
    ( (This)->lpVtbl -> ResizeBuffers(This,BufferCount,Width,Height,NewFormat,SwapChainFlags) ) 

#define IDXGISwapChainDWM8_ResizeTarget(This,pNewTargetParameters)	\
    ( (This)->lpVtbl -> ResizeTarget(This,pNewTargetParameters) ) 

#define IDXGISwapChainDWM8_GetContainingOutput(This,ppOutput)	\
    ( (This)->lpVtbl -> GetContainingOutput(This,ppOutput) ) 

#define IDXGISwapChainDWM8_GetFrameStatistics(This,pStats)	\
    ( (This)->lpVtbl -> GetFrameStatistics(This,pStats) ) 

#define IDXGISwapChainDWM8_GetLastPresentCount(This,pLastPresentCount)	\
    ( (This)->lpVtbl -> GetLastPresentCount(This,pLastPresentCount) ) 

#define IDXGISwapChainDWM8_Present1(This,SyncInterval,Flags,DirtyRectsCount,pDirtyRects,pScrollRect,pScrollOffset)	\
    ( (This)->lpVtbl -> Present1(This,SyncInterval,Flags,DirtyRectsCount,pDirtyRects,pScrollRect,pScrollOffset) ) 

#define IDXGISwapChainDWM8_GetLogicalSurfaceHandle(This,pVoid)	\
    ( (This)->lpVtbl -> GetLogicalSurfaceHandle(This,pVoid) ) 

#define IDXGISwapChainDWM8_CheckDirectFlipSupport(This,__MIDL__IDXGISwapChainDWM80000,pResource,__MIDL__IDXGISwapChainDWM80001)	\
    ( (This)->lpVtbl -> CheckDirectFlipSupport(This,__MIDL__IDXGISwapChainDWM80000,pResource,__MIDL__IDXGISwapChainDWM80001) ) 

#define IDXGISwapChainDWM8_Present2(This,SyncInterval,Flags,DirtyRectsCount,pDirtyRects,pScrollRect,pScrollOffset,pResource)	\
    ( (This)->lpVtbl -> Present2(This,SyncInterval,Flags,DirtyRectsCount,pDirtyRects,pScrollRect,pScrollOffset,pResource) ) 

#define IDXGISwapChainDWM8_GetCompositionSurface(This,ppVoid)	\
    ( (This)->lpVtbl -> GetCompositionSurface(This,ppVoid) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDXGISwapChainDWM8_INTERFACE_DEFINED__ */


#ifndef __IDXGIAdapterDWM_INTERFACE_DEFINED__
#define __IDXGIAdapterDWM_INTERFACE_DEFINED__

/* interface IDXGIAdapterDWM */
/* [uuid][local][object] */ 


EXTERN_C const IID IID_IDXGIAdapterDWM;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ffffffff-ffff-ffff-ffff-ffffffffffee")
    IDXGIAdapterDWM : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OpenKernelHandle( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CloseKernelHandle( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumOutputs2( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDXGIAdapterDWMVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDXGIAdapterDWM * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDXGIAdapterDWM * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDXGIAdapterDWM * This);
        
        HRESULT ( STDMETHODCALLTYPE *OpenKernelHandle )( 
            IDXGIAdapterDWM * This);
        
        HRESULT ( STDMETHODCALLTYPE *CloseKernelHandle )( 
            IDXGIAdapterDWM * This);
        
        HRESULT ( STDMETHODCALLTYPE *EnumOutputs2 )( 
            IDXGIAdapterDWM * This);
        
        END_INTERFACE
    } IDXGIAdapterDWMVtbl;

    interface IDXGIAdapterDWM
    {
        CONST_VTBL struct IDXGIAdapterDWMVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDXGIAdapterDWM_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDXGIAdapterDWM_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDXGIAdapterDWM_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDXGIAdapterDWM_OpenKernelHandle(This)	\
    ( (This)->lpVtbl -> OpenKernelHandle(This) ) 

#define IDXGIAdapterDWM_CloseKernelHandle(This)	\
    ( (This)->lpVtbl -> CloseKernelHandle(This) ) 

#define IDXGIAdapterDWM_EnumOutputs2(This)	\
    ( (This)->lpVtbl -> EnumOutputs2(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDXGIAdapterDWM_INTERFACE_DEFINED__ */


#ifndef __IDXGIFactoryDWM_INTERFACE_DEFINED__
#define __IDXGIFactoryDWM_INTERFACE_DEFINED__

/* interface IDXGIFactoryDWM */
/* [uuid][local][object] */ 


EXTERN_C const IID IID_IDXGIFactoryDWM;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("713f394e-92ca-47e7-ab81-1159c2791e54")
    IDXGIFactoryDWM : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateSwapChain( 
            /* [in] */ IUnknown *pDevice,
            /* [in] */ DXGI_SWAP_CHAIN_DESC *pDesc,
            /* [in] */ IDXGIOutput *pOutput,
            /* [out] */ IDXGISwapChainDWM **ppSwapChainDWM) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDXGIFactoryDWMVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDXGIFactoryDWM * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDXGIFactoryDWM * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDXGIFactoryDWM * This);
        
        HRESULT ( STDMETHODCALLTYPE *CreateSwapChain )( 
            IDXGIFactoryDWM * This,
            /* [in] */ IUnknown *pDevice,
            /* [in] */ DXGI_SWAP_CHAIN_DESC *pDesc,
            /* [in] */ IDXGIOutput *pOutput,
            /* [out] */ IDXGISwapChainDWM **ppSwapChainDWM);
        
        END_INTERFACE
    } IDXGIFactoryDWMVtbl;

    interface IDXGIFactoryDWM
    {
        CONST_VTBL struct IDXGIFactoryDWMVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDXGIFactoryDWM_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDXGIFactoryDWM_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDXGIFactoryDWM_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDXGIFactoryDWM_CreateSwapChain(This,pDevice,pDesc,pOutput,ppSwapChainDWM)	\
    ( (This)->lpVtbl -> CreateSwapChain(This,pDevice,pDesc,pOutput,ppSwapChainDWM) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDXGIFactoryDWM_INTERFACE_DEFINED__ */


#ifndef __IDXGIFactoryDWM8_INTERFACE_DEFINED__
#define __IDXGIFactoryDWM8_INTERFACE_DEFINED__

/* interface IDXGIFactoryDWM8 */
/* [uuid][local][object] */ 


EXTERN_C const IID IID_IDXGIFactoryDWM8;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1ddd77aa-9a4a-4cc8-9e55-98c196bafc8f")
    IDXGIFactoryDWM8 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateSwapChainDWM( 
            /* [in] */ IUnknown *pDevice,
            /* [in] */ DXGI_SWAP_CHAIN_DESC1 *pSwapChainDesc1,
            /* [in] */ DXGI_SWAP_CHAIN_FULLSCREEN_DESC *pSwapChainFullScreenDesc1,
            /* [in] */ IDXGIOutput *pOutput,
            /* [out] */ IDXGISwapChainDWM8 **ppSwapChainDWM1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateSwapChainDDA( 
            /* [in] */ IUnknown *pDevice,
            /* [in] */ DXGI_SWAP_CHAIN_DESC1 *pSwapChainDesc1,
            /* [in] */ IDXGIOutput *pOutput,
            /* [out] */ IDXGISwapChainDWM8 **ppSwapChainDWM1) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDXGIFactoryDWM8Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDXGIFactoryDWM8 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDXGIFactoryDWM8 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDXGIFactoryDWM8 * This);
        
        HRESULT ( STDMETHODCALLTYPE *CreateSwapChainDWM )( 
            IDXGIFactoryDWM8 * This,
            /* [in] */ IUnknown *pDevice,
            /* [in] */ DXGI_SWAP_CHAIN_DESC1 *pSwapChainDesc1,
            /* [in] */ DXGI_SWAP_CHAIN_FULLSCREEN_DESC *pSwapChainFullScreenDesc1,
            /* [in] */ IDXGIOutput *pOutput,
            /* [out] */ IDXGISwapChainDWM8 **ppSwapChainDWM1);
        
        HRESULT ( STDMETHODCALLTYPE *CreateSwapChainDDA )( 
            IDXGIFactoryDWM8 * This,
            /* [in] */ IUnknown *pDevice,
            /* [in] */ DXGI_SWAP_CHAIN_DESC1 *pSwapChainDesc1,
            /* [in] */ IDXGIOutput *pOutput,
            /* [out] */ IDXGISwapChainDWM8 **ppSwapChainDWM1);
        
        END_INTERFACE
    } IDXGIFactoryDWM8Vtbl;

    interface IDXGIFactoryDWM8
    {
        CONST_VTBL struct IDXGIFactoryDWM8Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDXGIFactoryDWM8_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDXGIFactoryDWM8_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDXGIFactoryDWM8_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDXGIFactoryDWM8_CreateSwapChainDWM(This,pDevice,pSwapChainDesc1,pSwapChainFullScreenDesc1,pOutput,ppSwapChainDWM1)	\
    ( (This)->lpVtbl -> CreateSwapChainDWM(This,pDevice,pSwapChainDesc1,pSwapChainFullScreenDesc1,pOutput,ppSwapChainDWM1) ) 

#define IDXGIFactoryDWM8_CreateSwapChainDDA(This,pDevice,pSwapChainDesc1,pOutput,ppSwapChainDWM1)	\
    ( (This)->lpVtbl -> CreateSwapChainDDA(This,pDevice,pSwapChainDesc1,pOutput,ppSwapChainDWM1) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDXGIFactoryDWM8_INTERFACE_DEFINED__ */


#ifndef __IDXGIDeviceDWM_INTERFACE_DEFINED__
#define __IDXGIDeviceDWM_INTERFACE_DEFINED__

/* interface IDXGIDeviceDWM */
/* [uuid][local][object] */ 


EXTERN_C const IID IID_IDXGIDeviceDWM;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ffffffff-ffff-ffff-ffff-ffffffffffe8")
    IDXGIDeviceDWM : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE PinResources( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnpinResources( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDXGIDeviceDWMVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDXGIDeviceDWM * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDXGIDeviceDWM * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDXGIDeviceDWM * This);
        
        HRESULT ( STDMETHODCALLTYPE *PinResources )( 
            IDXGIDeviceDWM * This);
        
        HRESULT ( STDMETHODCALLTYPE *UnpinResources )( 
            IDXGIDeviceDWM * This);
        
        END_INTERFACE
    } IDXGIDeviceDWMVtbl;

    interface IDXGIDeviceDWM
    {
        CONST_VTBL struct IDXGIDeviceDWMVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDXGIDeviceDWM_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDXGIDeviceDWM_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDXGIDeviceDWM_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDXGIDeviceDWM_PinResources(This)	\
    ( (This)->lpVtbl -> PinResources(This) ) 

#define IDXGIDeviceDWM_UnpinResources(This)	\
    ( (This)->lpVtbl -> UnpinResources(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDXGIDeviceDWM_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


