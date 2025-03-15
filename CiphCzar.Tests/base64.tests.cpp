#include "common.h"
#include "CppUnitTest.h"

extern "C" {
    #include "../CiphCzar/base64_common.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CiphCzarTests
{
    TEST_CLASS(Base64Tests)
    {
    public:

        TEST_METHOD(Encode_ProducesCorrectOutput_FromText)
        {
            // Arrange
            data_t input = create_test_data("The quick brown fox jumps over the lazy dog, 3 times.");
            const char* expected = "VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZywgMyB0aW1lcy4=";

            // Act
            data_t actual;
            status_t stat = base64_encode(input, &actual);
            Assert::IsTrue(stat.success);

            // Assert
            Assert::AreEqual(strlen(expected), actual.len);
            for (size_t i = 0; i < actual.len; i++) {
                Assert::AreEqual(expected[i], actual.data[i]);
            }

            // Cleanup
            free(input.data);
            free(actual.data);
        }

        TEST_METHOD(Encode_ProducesCorrectOutput_FromBinary)
        {
            // Arrange
            data_t input = create_test_data("\u0001\u0002\u0003\u0004\u0005\u0006\u0007\u0008\u0009\u000A");
            const char* expected = "AQIDBAUGBwgJCg==";

            // Act
            data_t actual;
            status_t stat = base64_encode(input, &actual);
            Assert::IsTrue(stat.success);

            // Assert
            Assert::AreEqual(strlen(expected), actual.len);
            for (size_t i = 0; i < actual.len; i++) {
                Assert::AreEqual(expected[i], actual.data[i]);
            }

            // Cleanup
            free(input.data);
            free(actual.data);
        }


        TEST_METHOD(Decode_ProducesCorrectOutput_ForText)
        {
            // Arrange
            data_t input = create_test_data("VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZywgMyB0aW1lcy4=");
            const char* expected = "The quick brown fox jumps over the lazy dog, 3 times.";

            // Act
            data_t actual;
            status_t stat = base64_decode(input, &actual);
            Assert::IsTrue(stat.success);

            // Assert
            Assert::AreEqual(strlen(expected), actual.len);
            for (size_t i = 0; i < actual.len; i++) {
                Assert::AreEqual(expected[i], actual.data[i]);
            }

            // Cleanup
            free(input.data);
            free(actual.data);
        }

        TEST_METHOD(Decode_ProducesCorrectOutput_ForBinary)
        {
            // Arrange
            data_t input = create_test_data("AQIDBAUGBwgJCg==");
            const char* expected = "\u0001\u0002\u0003\u0004\u0005\u0006\u0007\u0008\u0009\u000A";

            // Act
            data_t actual;
            status_t stat = base64_decode(input, &actual);
            Assert::IsTrue(stat.success);

            // Assert
            Assert::AreEqual(strlen(expected), actual.len);
            for (size_t i = 0; i < actual.len; i++) {
                Assert::AreEqual(expected[i], actual.data[i]);
            }

            // Cleanup
            free(input.data);
            free(actual.data);
        }
    };
}
