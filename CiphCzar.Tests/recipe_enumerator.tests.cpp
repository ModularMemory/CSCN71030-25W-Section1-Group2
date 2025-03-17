#include "common.h"
#include "CppUnitTest.h"

extern "C" {
    #include "../CiphCzar/algorithm.h"
    #include "../CiphCzar/recipe_enumerator.h"
    #include "../CiphCzar/rot_13.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CiphCzarTests
{
    TEST_CLASS(RecipeEnumeratorTests)
    {
        static algorithm_t create_test_algorithm() {
            algorithm_t alg = {0};

            alg.name = "Name";
            alg.description = "Desc";
            alg.execute = rot_13_execute;
            alg.validate_args = rot_13_validate_args;
            alg.additional_args = NULL;
            alg.reset_args = rot_13_reset_args;

            alg.reset_args(&alg);

            return alg;
        }

        static recipe_t create_test_recipe() {
            result_t res = create_recipe();
            Assert::IsTrue(res.success);
            Assert::IsNotNull(res.data);

            recipe_t rec = (recipe_t)res.data;
            Assert::IsTrue(recipe_push(rec, create_test_algorithm()).success);
            Assert::IsTrue(recipe_push(rec, create_test_algorithm()).success);
            Assert::IsTrue(recipe_push(rec, create_test_algorithm()).success);

            return rec;
        }

        static recipe_enumerator_t create_test_enumerator(recipe_t recipe, data_t data) {
            result_t res = create_recipe_enumerator(recipe, data);
            Assert::IsTrue(res.success);
            Assert::IsNotNull(res.data);
            
            return (recipe_enumerator_t)res.data;
        }

    public:
        TEST_METHOD(Enumerator_Execute_Produces_Ouput)
        {
            // Arrange
            recipe_t recipe = create_test_recipe();
            data_t test_data = create_test_data("ABC123 foo");
            recipe_enumerator_t enumerator = create_test_enumerator(recipe, test_data);

            const char* expected = "NOP123 sbb";

            // Act
            Assert::IsTrue(recipe_enumerator_move_next(enumerator));
            Assert::IsTrue(recipe_enumerator_execute(enumerator).success);

            result_t actual_res = recipe_enumerator_current_result(enumerator);
            Assert::IsTrue(actual_res.success);
            Assert::IsNotNull(actual_res.data);

            const data_t* actual = (const data_t*)actual_res.data;

            // Assert
            for (size_t i = 0; i < actual->len; i++) {
                Assert::AreEqual(expected[i], actual->data[i]);
            }

            // Cleanup
            free(test_data.data);
            destroy_recipe_enumerator(enumerator);
        }
    };
}
