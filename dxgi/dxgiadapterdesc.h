/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     GPU Adapter descriptor
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#pragma once

 /** Structure that holds adapter info */
struct DXGIAdapterDesc : public DXGI_ADAPTER_DESC1
{
	D3DKMT_HANDLE Handle;
};
