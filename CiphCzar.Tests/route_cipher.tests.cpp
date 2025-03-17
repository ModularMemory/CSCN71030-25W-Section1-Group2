#include "common.h"
#include "CppUnitTest.h"

extern "C" {
    #include "../CiphCzar/route_cipher_common.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CiphCzarTests
{
    TEST_CLASS(RouteCipherTests)
    {
    public:
        TEST_METHOD(Encode_ProducesCorrectOutput_For4By2)
        {
            // Arrange
            data_t input = create_test_data("Surprise");

            // Surp
            // rise
            const char* expected = "Sruirspe";

            // Act
            data_t actual;
            status_t stat = route_cipher_encode(input, 4, 2, &actual);
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

        TEST_METHOD(Encode_ProducesCorrectOutput_For3By3)
        {
            // Arrange
            data_t input = create_test_data("Surprise!");

            // Sur
            // pri
            // se!
            const char* expected = "Spsureri!";

            // Act
            data_t actual;
            status_t stat = route_cipher_encode(input, 3, 3, &actual);
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

        TEST_METHOD(Encode_ProducesCorrectOutput_For3By3_WithLongInput)
        {
            // Arrange
            data_t input = create_test_data("Meet at midnight");

            // Mee
            // t a
            // 
            // t m
            // idn
            //
            // igh
            // t  
            const char* expected = "Mte eati dmnitg h ";

            // Act
            data_t actual;
            status_t stat = route_cipher_encode(input, 3, 2, &actual);
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

        TEST_METHOD(Decode_ProducesCorrectOutput_For4By2)
        {
            // Arrange
            data_t input = create_test_data("Sruirspe");

            // Surp
            // rise
            const char* expected = "Surprise";

            // Act
            data_t actual;
            status_t stat = route_cipher_decode(input, 4, 2, &actual);
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

        TEST_METHOD(Decode_ProducesCorrectOutput_For3By3)
        {
            // Arrange
            data_t input = create_test_data("Spsureri!");

            // Sur
            // pri
            // se!
            const char* expected = "Surprise!";

            // Act
            data_t actual;
            status_t stat = route_cipher_decode(input, 3, 3, &actual);
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

        TEST_METHOD(Decode_ProducesCorrectOutput_For3By3_WithLongInput)
        {
            // Arrange
            data_t input = create_test_data("Mte eati dmnitg h");

            // Mte
            //  ea
            // 
            // ti 
            // dmn
            //
            // nit
            // g h 
            const char* expected = "Meet at midnight  ";

            // Act
            data_t actual;
            status_t stat = route_cipher_decode(input, 3, 2, &actual);
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
