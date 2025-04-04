#include "common.h"
#include "CppUnitTest.h"

extern "C" {
    #include <string.h>
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

data_t create_test_data(const char* str) {
    size_t len = strlen(str);
    char* new_str = (char*)malloc(len + 1);
    if (!new_str) {
        Assert::Fail(L"Failed to allocate test data string.");
    }

    strncpy_s(new_str, len + 1, str, len);

    return create_data(new_str, len);
}