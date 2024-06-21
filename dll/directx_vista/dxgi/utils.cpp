/*
 * PROJECT:     ReactX Graphics Infrastructure
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     Utility functions
 * COPYRIGHT:   Copyright 2023 Christian Rendina <pizzaiolo100@proton.me>
 */
#include "pch.h"
#include "utils.h"

/*
* Convert functions from Wine Copyright 2017 Alistair Leslie-Hughes
* wine\dll\mfplat\mediatype.c
*/

/***********************************************************************
 *      MFMapDXGIFormatToDX9Format (mfplat.@)
 */
D3DDDIFORMAT WINAPI DXGI_MFMapDXGIFormatToDX9Format(DXGI_FORMAT dxgi_format)
{
    switch (dxgi_format)
    {
    case DXGI_FORMAT_R32G32B32A32_FLOAT:
        return D3DDDIFMT_A32B32G32R32F;
    case DXGI_FORMAT_R16G16B16A16_FLOAT:
        return D3DDDIFMT_A16B16G16R16F;
    case DXGI_FORMAT_R16G16B16A16_UNORM:
        return D3DDDIFMT_A16B16G16R16;
    case DXGI_FORMAT_R16G16B16A16_SNORM:
        return D3DDDIFMT_Q16W16V16U16;
    case DXGI_FORMAT_R32G32_FLOAT:
        return D3DDDIFMT_G32R32F;
    case DXGI_FORMAT_R10G10B10A2_UNORM:
        return D3DDDIFMT_A2B10G10R10;
    case DXGI_FORMAT_R8G8B8A8_SNORM:
        return D3DDDIFMT_Q8W8V8U8;
    case DXGI_FORMAT_R16G16_FLOAT:
        return D3DDDIFMT_G16R16F;
    case DXGI_FORMAT_R16G16_UNORM:
        return D3DDDIFMT_G16R16;
    case DXGI_FORMAT_R16G16_SNORM:
        return D3DDDIFMT_V16U16;
    case DXGI_FORMAT_D32_FLOAT:
        return D3DDDIFMT_D32F_LOCKABLE;
    case DXGI_FORMAT_R32_FLOAT:
        return D3DDDIFMT_R32F;
    case DXGI_FORMAT_D24_UNORM_S8_UINT:
        return D3DDDIFMT_D24S8;
    case DXGI_FORMAT_R8G8_SNORM:
        return D3DDDIFMT_V8U8;
    case DXGI_FORMAT_R16_FLOAT:
        return D3DDDIFMT_R16F;
    case DXGI_FORMAT_D16_UNORM:
        return D3DDDIFMT_D16_LOCKABLE;
    case DXGI_FORMAT_R16_UNORM:
        return D3DDDIFMT_L16;
    case DXGI_FORMAT_R8_UNORM:
        return D3DDDIFMT_L8;
    case DXGI_FORMAT_A8_UNORM:
        return D3DDDIFMT_A8;
    case DXGI_FORMAT_BC1_UNORM:
    case DXGI_FORMAT_BC1_UNORM_SRGB:
        return D3DDDIFMT_DXT1;
    case DXGI_FORMAT_BC2_UNORM:
    case DXGI_FORMAT_BC2_UNORM_SRGB:
        return D3DDDIFMT_DXT2;
    case DXGI_FORMAT_BC3_UNORM:
    case DXGI_FORMAT_BC3_UNORM_SRGB:
        return D3DDDIFMT_DXT4;
    case DXGI_FORMAT_R8G8B8A8_UNORM:
        return D3DDDIFMT_A8B8G8R8;
    case DXGI_FORMAT_B8G8R8A8_UNORM:
    case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
    case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
        return D3DDDIFMT_A8R8G8B8;
    case DXGI_FORMAT_B8G8R8X8_UNORM:
    case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
        return D3DDDIFMT_X8R8G8B8;

#if !_WINSDK_7
    case DXGI_FORMAT_AYUV:
        return (D3DDDIFORMAT)MAKEFOURCC('A', 'Y', 'U', 'V');
    case DXGI_FORMAT_Y410:
        return (D3DDDIFORMAT)MAKEFOURCC('Y', '4', '1', '0');
    case DXGI_FORMAT_Y416:
        return (D3DDDIFORMAT)MAKEFOURCC('Y', '4', '1', '6');
    case DXGI_FORMAT_NV12:
        return (D3DDDIFORMAT)MAKEFOURCC('N', 'V', '1', '2');
    case DXGI_FORMAT_P010:
        return (D3DDDIFORMAT)MAKEFOURCC('P', '0', '1', '0');
    case DXGI_FORMAT_P016:
        return (D3DDDIFORMAT)MAKEFOURCC('P', '0', '1', '6');
    case DXGI_FORMAT_420_OPAQUE:
        return (D3DDDIFORMAT)MAKEFOURCC('4', '2', '0', 'O');
    case DXGI_FORMAT_YUY2:
        return D3DDDIFMT_YUY2;
    case DXGI_FORMAT_Y210:
        return (D3DDDIFORMAT)MAKEFOURCC('Y', '2', '1', '0');
    case DXGI_FORMAT_Y216:
        return (D3DDDIFORMAT)MAKEFOURCC('Y', '2', '1', '6');
    case DXGI_FORMAT_NV11:
        return (D3DDDIFORMAT)MAKEFOURCC('N', 'V', '1', '1');
    case DXGI_FORMAT_AI44:
        return (D3DDDIFORMAT)MAKEFOURCC('A', 'I', '4', '4');
    case DXGI_FORMAT_IA44:
        return (D3DDDIFORMAT)MAKEFOURCC('I', 'A', '4', '4');
    case DXGI_FORMAT_P8:
        return D3DDDIFMT_P8;
    case DXGI_FORMAT_A8P8:
        return D3DDDIFMT_A8P8;
#endif

    default:
        return D3DDDIFMT_UNKNOWN;
    }
}

/***********************************************************************
 *      MFMapDX9FormatToDXGIFormat (mfplat.@)
 */
DXGI_FORMAT WINAPI DXGI_MFMapDX9FormatToDXGIFormat(D3DDDIFORMAT format)
{
    switch (format)
    {
    case D3DDDIFMT_A32B32G32R32F:
        return DXGI_FORMAT_R32G32B32A32_FLOAT;
    case D3DDDIFMT_A16B16G16R16F:
        return DXGI_FORMAT_R16G16B16A16_FLOAT;
    case D3DDDIFMT_A16B16G16R16:
        return DXGI_FORMAT_R16G16B16A16_UNORM;
    case D3DDDIFMT_Q16W16V16U16:
        return DXGI_FORMAT_R16G16B16A16_SNORM;
    case D3DDDIFMT_G32R32F:
        return DXGI_FORMAT_R32G32_FLOAT;
    case D3DDDIFMT_A2B10G10R10:
        return DXGI_FORMAT_R10G10B10A2_UNORM;
    case D3DDDIFMT_Q8W8V8U8:
        return DXGI_FORMAT_R8G8B8A8_SNORM;
    case D3DDDIFMT_G16R16F:
        return DXGI_FORMAT_R16G16_FLOAT;
    case D3DDDIFMT_G16R16:
        return DXGI_FORMAT_R16G16_UNORM;
    case D3DDDIFMT_V16U16:
        return DXGI_FORMAT_R16G16_SNORM;
    case D3DDDIFMT_D32F_LOCKABLE:
        return DXGI_FORMAT_D32_FLOAT;
    case D3DDDIFMT_R32F:
        return DXGI_FORMAT_R32_FLOAT;
    case D3DDDIFMT_D24S8:
        return DXGI_FORMAT_D24_UNORM_S8_UINT;
    case D3DDDIFMT_V8U8:
        return DXGI_FORMAT_R8G8_SNORM;
    case D3DDDIFMT_R16F:
        return DXGI_FORMAT_R16_FLOAT;
    case D3DDDIFMT_L16:
        return DXGI_FORMAT_R16_UNORM;
    case D3DDDIFMT_L8:
        return DXGI_FORMAT_R8_UNORM;
    case D3DDDIFMT_A8:
        return DXGI_FORMAT_A8_UNORM;
    case D3DDDIFMT_DXT1:
        return DXGI_FORMAT_BC1_UNORM;
    case D3DDDIFMT_DXT2:
        return DXGI_FORMAT_BC2_UNORM;
    case D3DDDIFMT_DXT4:
        return DXGI_FORMAT_BC3_UNORM;
    case D3DDDIFMT_A8R8G8B8:
        return DXGI_FORMAT_B8G8R8A8_UNORM;
    case D3DDDIFMT_X8R8G8B8:
        return DXGI_FORMAT_B8G8R8X8_UNORM;
#if !_WINSDK_7
    case MAKEFOURCC('A', 'Y', 'U', 'V'):
        return DXGI_FORMAT_AYUV;
    case MAKEFOURCC('Y', '4', '1', '0'):
        return DXGI_FORMAT_Y410;
    case MAKEFOURCC('Y', '4', '1', '6'):
        return DXGI_FORMAT_Y416;
    case MAKEFOURCC('N', 'V', '1', '2'):
        return DXGI_FORMAT_NV12;
    case MAKEFOURCC('P', '0', '1', '0'):
        return DXGI_FORMAT_P010;
    case MAKEFOURCC('P', '0', '1', '6'):
        return DXGI_FORMAT_P016;
    case MAKEFOURCC('4', '2', '0', 'O'):
        return DXGI_FORMAT_420_OPAQUE;
    case D3DDDIFMT_YUY2:
        return DXGI_FORMAT_YUY2;
    case MAKEFOURCC('Y', '2', '1', '0'):
        return DXGI_FORMAT_Y210;
    case MAKEFOURCC('Y', '2', '1', '6'):
        return DXGI_FORMAT_Y216;
    case MAKEFOURCC('N', 'V', '1', '1'):
        return DXGI_FORMAT_NV11;
    case MAKEFOURCC('A', 'I', '4', '4'):
        return DXGI_FORMAT_AI44;
    case MAKEFOURCC('I', 'A', '4', '4'):
        return DXGI_FORMAT_IA44;
    case D3DDDIFMT_P8:
        return DXGI_FORMAT_P8;
    case D3DDDIFMT_A8P8:
        return DXGI_FORMAT_A8P8;
#endif
    default:
        return DXGI_FORMAT_UNKNOWN;
    }
}

// Based from experiments, it might miss things
HRESULT WINAPI NtErrorToDxgiError(NTSTATUS status)
{
    if (NT_SUCCESS(status))
        return S_OK;

    switch (status)
    {
    case STATUS_INVALID_PARAMETER:
        return DXGI_ERROR_INVALID_CALL;
    case STATUS_NOT_SUPPORTED:
        return DXGI_ERROR_UNSUPPORTED;
    default:
        break;
    }

    return DXGI_ERROR_DRIVER_INTERNAL_ERROR;
}
