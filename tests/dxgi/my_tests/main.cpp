#include "pch.h"
#include "test.h"
#include <cstring>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printf("Usage: [dxgi_my_tests] [testname]\n");
		return -1;
	}

	if (strcmp(argv[1], "object") == 0)
		test_dxgiobject();
	else if (strcmp(argv[1], "factory") == 0)
		test_factory();
	else if (strcmp(argv[1], "adapter") == 0)
		test_adapter();
	else if (strcmp(argv[1], "output") == 0)
		test_output();

	return 0;
}
