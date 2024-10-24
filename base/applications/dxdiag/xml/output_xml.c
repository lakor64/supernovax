/*
 * PROJECT:     SupernovaX Diagnostic Tool
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     XML Output
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 *              Copyright 2011 Andrew Nguyen
 */
#include "precomp.h"
#include "output.h"
#include "output_xml.h"

#include <initguid.h>
#include <msxml2.h>

WINE_DEFAULT_DEBUG_CHANNEL(dxdiag);

static IXMLDOMElement* xml_create_element(IXMLDOMDocument* xmldoc, LPCWSTR name)
{
    BSTR bstr = SysAllocString(name);
    IXMLDOMElement* ret;
    HRESULT hr;

    if (!bstr)
        return NULL;

    hr = IXMLDOMDocument_createElement(xmldoc, bstr, &ret);
    SysFreeString(bstr);

    return SUCCEEDED(hr) ? ret : NULL;
}

static HRESULT xml_put_element_text(IXMLDOMElement* element, LPCWSTR text)
{
    BSTR bstr;
    HRESULT hr;

    if (!text)
        text = L"";

    bstr = SysAllocString(text);
    if (!bstr)
        return E_OUTOFMEMORY;

    hr = IXMLDOMElement_put_text(element, bstr);
    SysFreeString(bstr);

    return hr;
}

static HRESULT save_xml_document(IXMLDOMDocument* xmldoc, LPCWSTR filename)
{
    BSTR bstr = SysAllocString(filename);
    VARIANT destVar;
    HRESULT hr;

    if (!bstr)
        return E_OUTOFMEMORY;

    V_VT(&destVar) = VT_BSTR;
    V_BSTR(&destVar) = bstr;

    hr = IXMLDOMDocument_save(xmldoc, destVar);
    VariantClear(&destVar);

    return hr;
}

static BOOL serialize_field(IXMLDOMDocument* xmldoc, IXMLDOMElement* parent_element, PXML_INFORMATION_BLOCK table)
{
    IXMLDOMElement* info_element = xml_create_element(xmldoc, table->tag_name);
    const PXML_INFORMATION_DATA fields = table->data;
    unsigned int j = 0;
    HRESULT hr;

    if (!info_element)
        return FALSE;

    hr = IXMLDOMElement_appendChild(parent_element, (IXMLDOMNode*)info_element, NULL);
    if (FAILED(hr))
    {
        IXMLDOMElement_Release(info_element);
        return FALSE;
    }

    for (j = 0; fields[j].type; j++)
    {
        if (fields[j].type == XML_TYPE_FIELD)
        {
            IXMLDOMElement* field_element = xml_create_element(xmldoc, fields[j].field.tag_name);

            if (!field_element)
            {
                IXMLDOMElement_Release(info_element);
                return FALSE;
            }

            hr = xml_put_element_text(field_element, fields[j].field.value);
            if (FAILED(hr))
            {
                IXMLDOMElement_Release(field_element);
                IXMLDOMElement_Release(info_element);
                return FALSE;
            }

            hr = IXMLDOMElement_appendChild(info_element, (IXMLDOMNode*)field_element, NULL);
            if (FAILED(hr))
            {
                IXMLDOMElement_Release(field_element);
                IXMLDOMElement_Release(info_element);
                return FALSE;
            }

            IXMLDOMElement_Release(field_element);
        }
        else if (fields[j].type == XML_TYPE_CHILD)
        {
            if (!serialize_field(xmldoc, info_element, fields[j].child))
            {
                IXMLDOMElement_Release(info_element);
                return FALSE;
            }
        }
    }

    IXMLDOMElement_Release(info_element);
    return TRUE;
}

static void free_field(PXML_INFORMATION_BLOCK blk)
{
    unsigned int j = 0;

    for (j = 0; blk->data[j].type; j++)
    {
        if (blk->data[j].type == XML_TYPE_CHILD)
        {
            free_field(blk->data[j].child);
            free(blk->data[j].child);
        }
        else if (blk->data[j].type == XML_TYPE_FIELD)
        {
            if (blk->data[j].field.owner)
                free(blk->data[j].field.value);
        }
    }
}

static BOOL create_xml_document(LPCWSTR filename, IXMLDOMDocument** xmldoc, IXMLDOMElement** dxdiag_element)
{
    HRESULT hr;

    hr = CoCreateInstance(&CLSID_DOMDocument, NULL, CLSCTX_INPROC_SERVER,
        &IID_IXMLDOMDocument, (void**)xmldoc);
    if (FAILED(hr))
    {
        WINE_ERR("IXMLDOMDocument instance creation failed with 0x%08lx\n", hr);
        goto error;
    }

    *dxdiag_element = xml_create_element(*xmldoc, L"DxDiag");

    if (!*dxdiag_element)
        goto error;

    hr = IXMLDOMDocument_appendChild(*xmldoc, (IXMLDOMNode*)*dxdiag_element, NULL);
    if (FAILED(hr))
        goto error;

    return TRUE;

error:
    if (*dxdiag_element) IXMLDOMDocument_Release(*dxdiag_element); *dxdiag_element = NULL;
    if (*xmldoc) IXMLDOMDocument_Release(*xmldoc); *xmldoc = NULL;
    return FALSE;
}

void fill_video_capture_dev(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk)
{
    xml_new_block(blk, L"VideoCaptureDevices");
}

void fill_media_foundation(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk)
{
    xml_new_block(blk, L"MediaFoundation");
}

void fill_evr_power_info(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk)
{
    xml_new_block(blk, L"EvrPowerInformation");
}

void fill_diagnostics(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk)
{
    xml_new_block(blk, L"Diagnostics");
}

typedef void(*FILL_SYSTEM_FUNCTION)(PDXDIAG_CONTEXT ctx, PXML_INFORMATION_BLOCK blk);

BOOL output_xml_information(PDXDIAG_CONTEXT ctx, LPCWSTR filename)
{
    static FILL_SYSTEM_FUNCTION output_table[] =
    {
        fill_system,
        fill_dxdiag_notes,
        fill_dx_debug_levels,
        fill_display_devices,
        fill_direct_sound,
        fill_direct_music, // NT5 only
        fill_video_capture_dev, // NT6+
        fill_direct_input,
        fill_direct_play, // NT5 only
        fill_logical_disk, // NT6+
        fill_system_devices, // NT6+
        fill_dx_components, // NT5
        fill_direct_show,
        fill_media_foundation, // NT6
        fill_evr_power_info, // NT6
        fill_diagnostics, // NT6
    };

    IXMLDOMDocument* xmldoc = NULL;
    IXMLDOMElement* root = NULL;
    HRESULT hr;
    ULONG i = 0;
    XML_INFORMATION_BLOCK current;

    memset(&current, 0, sizeof(current));

    if (!create_xml_document(filename, &xmldoc, &root))
    {
        return FALSE;
    }

    for (; i < ARRAY_SIZE(output_table); i++)
    {
        memset(&current, 0, sizeof(current));

        output_table[i](ctx, &current);

        if (!serialize_field(xmldoc, root, &current))
        {
            free_field(&current);
            goto error;
        }

        free_field(&current);
    }

    hr = save_xml_document(xmldoc, filename);
    if (FAILED(hr))
        goto error;

    IXMLDOMElement_Release(root);
    IXMLDOMDocument_Release(xmldoc);
    return TRUE;
error:

    if (root) IXMLDOMElement_Release(root);
    if (xmldoc) IXMLDOMDocument_Release(xmldoc);
    return FALSE;
}
