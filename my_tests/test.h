#pragma once


#define FUN_ASSERT \
		printf("function check fail! (hr: %x file: %S line: %llu)\n", hr, __FILEW__, (ULONGLONG)__LINE__); \
		assert(false); \
		goto ss;

#define HR_CHECK if (FAILED(hr)) { FUN_ASSERT; }
#define FUN_CHECK(x) if (!(x)) { FUN_ASSERT; }

void test_dxgiobject(void);
void test_factory(void);
void test_adapter(void);
void test_output(void);
void test_parent(void);

