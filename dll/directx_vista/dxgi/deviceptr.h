/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     Device access functions
 * COPYRIGHT:   Copyright 2023 Christian Rendina <pizzaiolo100@proton.me>
 */
#pragma once

class CDevicePtr
{
public:
	explicit CDevicePtr(DXGIUseCountedType* parent) : m_pParent(parent), m_DevVersion(0), m_pDevice(nullptr)
	{
		m_uInternalDevice.D1 = nullptr;
	}

	~CDevicePtr()
	{
		if (m_uInternalDevice.D1 != 0)
		{
			m_uInternalDevice.D1->Release();
		}

		if (m_pDevice)
			m_pDevice->Release();
	}

	HRESULT CreateSurfaceInternal(DXGI_SURFACE_DESC* dsc, UINT texArraySize, UINT resSize, UINT bindFlags, UINT miscFlags, IDXGIResource** pOutput)
	{
		if (m_DevVersion == 3)
			return m_uInternalDevice.D3->CreateSurfaceInternal(m_pParent, nullptr, nullptr, dsc, texArraySize, resSize, bindFlags, miscFlags, nullptr, pOutput);

		return E_NOTIMPL;
	}

	HRESULT OpenSharedResource(HANDLE hResource, REFIID ResType, IDXGIResource** pOutput)
	{
		if (m_DevVersion == 3)
			return m_uInternalDevice.D3->OpenSharedResource(hResource, 1, ResType, (void**)pOutput);

		return E_NOTIMPL;
	}

	HRESULT Blt(IDXGIResource* pSource, const RECT* SrcRect, const RECT* SrcSubRects, UINT SubRectSize, IDXGIResource* pDest, RECT* DestRect, DXGI_PRESENT_SUBRESOURCES* SubRes, UINT Flags, DXGI_DDI_MODE_ROTATION RotationMode)
	{
		if (m_DevVersion == 3)
			return m_uInternalDevice.D3->Blt(pSource, SrcRect, SrcSubRects, SubRectSize, pDest, DestRect, SubRes, 0, Flags, RotationMode);

		return E_NOTIMPL;
	}

	HRESULT Present(IDXGIResource* pSource, IDXGIResource* pDest, D3DKMT_PRESENT* pContext, DXGI_DDI_PRESENT_FLAGS PresentFlags, DXGI_DDI_FLIP_INTERVAL_TYPE FlipInterval)
	{
		if (m_DevVersion == 3)
			return m_uInternalDevice.D3->Present(pSource, pDest, pContext, PresentFlags, FlipInterval);

		return E_NOTIMPL;
	}


	HRESULT GetAdapter(IDXGIAdapter** pAdapter)
	{
		return m_pDevice->GetAdapter(pAdapter);
	}

	HRESULT Initialize(IUnknown* dev)
	{
		auto hr = dev->QueryInterface(&m_pDevice);
		if (FAILED(hr))
			return hr; // cannot fail!

		hr = m_pDevice->QueryInterface(&m_uInternalDevice.D3);
		if (hr == E_NOINTERFACE)
		{
			// Windows 7 RTM
			hr = m_pDevice->QueryInterface(&m_uInternalDevice.D2);
			if (FAILED(hr))
			{
				// Vista RTM
				hr = m_pDevice->QueryInterface(&m_uInternalDevice.D1);
				if (FAILED(hr))
					return hr;

				m_DevVersion = 1;
			}
			else
				m_DevVersion = 2;
		}
		else
			// TODO: D4 Windows 10 fix...
			m_DevVersion = 3;

		return S_OK;
	}

private:
	/* Parent of the class */
	DXGIUseCountedType* m_pParent;

	/* Device version */
	uint8_t m_DevVersion;

	/* Main d3d device */
	IDXGIDevice* m_pDevice;

	/* Internal device */
	union
	{
		/* Vista RTM internal device */
		IDXGIDeviceInternal* D1;
		/* Windows 7 RTM internal device */
		IDXGIDeviceInternal2* D2;
		/* Windows 7 SP1+ internal device */
		IDXGIDeviceInternal3* D3;
		/* Windows 10+ internal device */
		void* D4; // TODO!
	} m_uInternalDevice;
};
