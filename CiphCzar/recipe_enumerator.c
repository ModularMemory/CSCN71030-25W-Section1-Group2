#include <stdlib.h>

#include "recipe_enumerator.h"

result_t create_recipe_enumerator(recipe_t recipe, const char* input_data) {
    return result_error("Not implemented.");
}

bool recipe_enumerator_move_next(recipe_enumerator_t enumerator) {
    return false;
}

status_t recipe_enumerator_execute(recipe_enumerator_t enumerator) {
    return status_error("Not implemented.");
}

result_t recipe_enumerator_current_result(recipe_enumerator_t enumerator) {
    return result_error("Not implemented.");
}

result_t recipe_enumerator_current_name(recipe_enumerator_t enumerator) {
    return result_error("Not implemented.");
}

void destroy_recipe_enumerator(recipe_enumerator_t enumerator) {
    destroy_recipe(enumerator->recipe);

    free(enumerator->rolling_result.data);

    free(enumerator);
}
