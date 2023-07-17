#include "pch.h"
#include "test.h"
#include "myprivatedata.h"

#define FUN_ASSERT \
		printf("function check fail! (hr: %x file: %S line: %llu)\n", hr, __FILEW__, (ULONGLONG)__LINE__); \
		assert(false); \
		goto ss;

#define HR_CHECK if (FAILED(hr)) { FUN_ASSERT; }
#define FUN_CHECK(x) if (!(x)) { FUN_ASSERT; }

static BYTE BPP_DATA[10] = {
	0x20, 0x20, 0x20, 0x20,
	0xFD, 0xFD, 0xFD, 0xFD,
	0xAA, 0xAA
};

void test_dxgiobject(void)
{
	IDXGIFactory* pFactory = NULL;
	HRESULT hr = CreateDXGIFactory(IID_IDXGIFactory, (void**)&pFactory);
	MyPrivateData* pData = NULL;
	ULONG ref = 1;
	MyPrivateData* pData2 = NULL;
	UINT nDataSize = 0;
	IUnknown* pParent = NULL;
	ULONG refp;
	BYTE* bpp;
	BYTE recv[10];

	HR_CHECK;

	hr = pFactory->GetParent(IID_MyPrivateData, (PVOID*)&pParent);
	FUN_CHECK(hr == E_NOINTERFACE);

	pData = new MyPrivateData();

	FUN_CHECK(pData != NULL);

	hr = pFactory->SetPrivateDataInterface(IID_MyPrivateData, pData);

	HR_CHECK;
	FUN_CHECK(pData->GetRefCount() == 2);

	nDataSize = sizeof(pData2);
	hr = pFactory->GetPrivateData(IID_MyPrivateData, &nDataSize, &pData2);

	HR_CHECK;
	FUN_CHECK(nDataSize == sizeof(void*));
	FUN_CHECK(pData2 == pData);
	FUN_CHECK(pData->GetRefCount() == 3);

	hr = pFactory->SetPrivateData(IID_MyPrivateData, sizeof(ref), &ref);

	HR_CHECK;
	FUN_CHECK(pData->GetRefCount() == 2);

	FUN_CHECK(pData2->Release() == 1);
	pData2 = NULL;
	FUN_CHECK(pData->GetRefCount() == 1);

	hr = pFactory->SetPrivateData(IID_MyFakeData, sizeof(ref), &ref);
	HR_CHECK;

	hr = pFactory->GetPrivateData(IID_MyFakeData, &nDataSize, &refp);
	HR_CHECK;
	FUN_CHECK(nDataSize == sizeof(ref));
	FUN_CHECK(refp == ref);

	hr = pFactory->SetPrivateData(IID_MyFakeData, 0, NULL);
	HR_CHECK;

	nDataSize = sizeof(pData2);
	hr = pFactory->GetPrivateData(IID_MyFakeData, &nDataSize, &pData2);

	FUN_CHECK(hr == DXGI_ERROR_NOT_FOUND);
	FUN_CHECK(nDataSize == 0);

	hr = pFactory->SetPrivateData(IID_MyFakeData, sizeof(ref), &ref);
	HR_CHECK;

	hr = pFactory->SetPrivateDataInterface(IID_MyFakeData, NULL);
	HR_CHECK;

	nDataSize = 0;
	hr = pFactory->GetPrivateData(IID_MyFakeData, &nDataSize, &pData2);
	FUN_CHECK(hr == DXGI_ERROR_MORE_DATA);

	nDataSize = sizeof(pData2);
	hr = pFactory->GetPrivateData(IID_MyFakeData, &nDataSize, &pData2);
	HR_CHECK;

	hr = pFactory->SetPrivateDataInterface(IID_MyFakeData, pData);
	HR_CHECK;
	FUN_CHECK(pData->GetRefCount() == 2);

	hr = pFactory->SetPrivateData(IID_MyFakeData, 9999, NULL);
	HR_CHECK;
	FUN_CHECK(pData->GetRefCount() == 1);

	hr = pFactory->SetPrivateData(IID_MyFakeData, 0, &ref);
	HR_CHECK;

	nDataSize = 999;
	hr = pFactory->GetPrivateData(IID_MyFakeData, &nDataSize, &pData2);
	HR_CHECK;

	hr = pFactory->SetPrivateDataInterface(IID_MyFakeData, pData);
	HR_CHECK;
	FUN_CHECK(pData->GetRefCount() == 2);
	hr = pFactory->SetPrivateDataInterface(IID_MyFakeData, pData);
	HR_CHECK;
	FUN_CHECK(pData->GetRefCount() == 2);

	bpp = new BYTE[10];
	memcpy_s(bpp, 10, BPP_DATA, 10);
	hr = pFactory->SetPrivateData(IID_MyFakeData, 10, bpp);
	HR_CHECK;

	delete[] bpp;
	bpp = NULL;
	nDataSize = 10;
	hr = pFactory->GetPrivateData(IID_MyFakeData, &nDataSize, recv);
	HR_CHECK;
	FUN_CHECK(memcmp(recv, BPP_DATA, 10) == 0);

ss:
	if (pParent)
		pParent->Release();

	if (pData)
		pData->Release();

	if (pFactory)
		pFactory->Release();
}
