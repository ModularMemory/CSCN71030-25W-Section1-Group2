#include <stdlib.h>

#include "recipe_enumerator.h"

RESULT(recipe_enumerator_t) create_recipe_enumerator(recipe_t recipe, const data_t input_data) {
    recipe_enumerator_t enumerator = (recipe_enumerator_t)malloc(sizeof(struct recipe_enumerator));
    if (!enumerator) {
        return result_error("Failed to allocate enumerator.");
    }

    result_t recipe2_res = copy_recipe(recipe);
    if (!recipe2_res.success) {
        return recipe2_res;
    }

    data_t rolling_result = { 0 };
    status_t clone_stat = clone_data(input_data, &rolling_result);
    if (!clone_stat.success) {
        return to_result(clone_stat);
    }

    enumerator->has_moved = false;
    enumerator->recipe = (recipe_t)recipe2_res.data;
    enumerator->rolling_result = rolling_result;

    return result_error("Not implemented.");
}

bool recipe_enumerator_move_next(recipe_enumerator_t enumerator) {
    return false;
}

status_t recipe_enumerator_execute(recipe_enumerator_t enumerator) {
    return status_error("Not implemented.");
}

RESULT(const data_t*) recipe_enumerator_current_result(recipe_enumerator_t enumerator) {
    if (!enumerator->has_moved) {
        return result_error("Enumerator has not moved yet.");
    }

    // Not required to access rolling result, but maintains consistency with current_name
    if (!enumerator->recipe->head) {
        return result_error("Enumerator is empty.");
    }

    return result_ok(&enumerator->rolling_result);
}

RESULT(const char*) recipe_enumerator_current_name(recipe_enumerator_t enumerator) {
    if (!enumerator->has_moved) {
        return result_error("Enumerator has not moved yet.");
    }

    if (!enumerator->recipe->head) {
        return result_error("Enumerator is empty.");
    }

    return result_ok(enumerator->recipe->head->algorithm.name);
}

void destroy_recipe_enumerator(recipe_enumerator_t enumerator) {
    destroy_recipe(enumerator->recipe);

    free(enumerator->rolling_result.data);

    free(enumerator);
}
