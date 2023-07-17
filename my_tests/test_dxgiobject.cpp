#include "pch.h"
#include "test.h"
#include "myprivatedata.h"

#define FUN_ASSERT \
		printf("function check fail! (hr: %x file: %S line: %llu)\n", hr, __FILEW__, (ULONGLONG)__LINE__); \
		assert(false); \
		goto ss;

#define HR_CHECK if (FAILED(hr)) { FUN_ASSERT; }
#define FUN_CHECK(x) if (!(x)) { FUN_ASSERT; }

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

	HR_CHECK;

#if 0 // you can't call GetParent on a IDXGIFactory?
	hr = pFactory->GetParent(IID_MyPrivateData, (PVOID*)&pParent);

	FUN_CHECK(hr == DXGI_ERROR_NOT_FOUND);
#endif

	pData = new MyPrivateData();

	FUN_CHECK(pData != NULL);

	hr = pFactory->SetPrivateDataInterface(IID_MyPrivateData, pData);

	HR_CHECK;
	FUN_CHECK(pData->GetRefCount() == 2);

	hr = pFactory->GetPrivateData(IID_MyPrivateData, &nDataSize, NULL);

	HR_CHECK;
	FUN_CHECK(nDataSize == sizeof(void*));
	FUN_CHECK(pData2 == pData);
	//FUN_CHECK(pData->GetRefCount() == 3); // GetPrivateData from SPDI doesn't increment the count????

	hr = pFactory->SetPrivateData(IID_MyPrivateData, sizeof(ref), &ref);

	HR_CHECK;
	FUN_CHECK(pData->GetRefCount() == 2);

	FUN_CHECK(pParent->Release() == 1);
	pParent = NULL;

	hr = pFactory->SetPrivateData(IID_MyFakeData, sizeof(ref), &ref);

	HR_CHECK;

	hr = pFactory->GetPrivateData(IID_MyFakeData, &nDataSize, &refp);

	HR_CHECK;
	FUN_CHECK(nDataSize == sizeof(ref));
	FUN_CHECK(refp == ref);

	hr = pFactory->SetPrivateData(IID_MyFakeData, 0, NULL);

	HR_CHECK;

	hr = pFactory->GetPrivateData(IID_MyFakeData, &nDataSize, pData);


	HR_CHECK;
	FUN_CHECK(pData == NULL);
	FUN_CHECK(nDataSize == 0);

ss:
	if (pParent)
		pParent->Release();

	if (pData)
		pData->Release();

	if (pFactory)
		pFactory->Release();
}
