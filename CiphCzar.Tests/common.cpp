#include "common.h"
#include "CppUnitTest.h"

extern "C" {
    #include "string.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

data_t create_test_data(const char* str) {
    size_t len = strlen(str);
    char* alloced_str = (char*)malloc(len + 1);
    if (!alloced_str) {
        Assert::Fail(L"Failed to allocate test data string.");
    }

    strncpy_s(alloced_str, len + 1, str, len);

    return create_data(alloced_str, len);
}