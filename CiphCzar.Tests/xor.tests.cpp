#include "common.h"
#include "CppUnitTest.h"

extern "C" {
    #include "../CiphCzar/xor.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CiphCzarTests
{
    TEST_CLASS(XorTests)
    {
    public:
        TEST_METHOD(Xor_ProducesCorrectOutput_ForText)
        {
            // Arrange
            data_t input = create_test_data("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
            const char expected[] = "\u0000#\"\u0005\u0004'&\t\b+*\r\f/.\u0011\u001032\u0015\u001476\u0019\u0018;\u0000#\"\u0005\u0004'&\t\b+*\r\f/.\u0011\u001032\u0015\u001476\u0019\u0018;";
            size_t expected_len = __crt_countof(expected) - 1; // Count minus NULL terminator
            pargument_t args = NULL;
            status_t arg_stat = append_string_arg(&args, "Key", "AaaA");
            Assert::IsTrue(arg_stat.success);

            // Act
            data_t actual;
            status_t exe_stat = xor_execute(input, args, &actual);
            Assert::IsTrue(exe_stat.success);

            // Assert
            Assert::AreEqual(expected_len, actual.len);
            for (size_t i = 0; i < actual.len; i++) {
                Assert::AreEqual(expected[i], actual.data[i]);
            }

            // Cleanup
            free(input.data);
            free(actual.data);
        }
    };
}
