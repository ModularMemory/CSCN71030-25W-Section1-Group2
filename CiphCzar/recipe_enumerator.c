#include <assert.h>
#include <stdlib.h>

#include "recipe_enumerator.h"

RESULT(recipe_enumerator_t) create_recipe_enumerator(const recipe_t recipe, const data_t input_data) {
    recipe_enumerator_t enumerator = (recipe_enumerator_t)malloc(sizeof(struct recipe_enumerator));
    if (!enumerator) {
        return result_error("Failed to allocate enumerator.");
    }

    result_t recipe2_res = clone_recipe(recipe);
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

    return result_ok(enumerator);
}

bool recipe_enumerator_has_moved(const recipe_enumerator_t enumerator) {
    return enumerator->has_moved;
}

bool recipe_enumerator_is_empty(const recipe_enumerator_t enumerator) {
    return recipe_is_empty(enumerator->recipe);
}

bool recipe_enumerator_move_next(recipe_enumerator_t enumerator) {
    if (!enumerator->has_moved) {
        // No-op to allow while (move_next(enumerator)) { ... } instead of do { ... } while (move_next(enumerator))
        enumerator->has_moved = true;

        // Only return true if the enumerator is not empty
        return !recipe_enumerator_is_empty(enumerator);
    }

    algorithm_t discard;
    bool pop = recipe_pop(enumerator->recipe, &discard);
    assert(pop);
    
    // Because the first move_next is a no-op, return the emptiness of the
    // recipe rather than the success of the pop operation
    return !recipe_is_empty(enumerator->recipe);
}

status_t recipe_enumerator_execute(recipe_enumerator_t enumerator) {
    if (!recipe_enumerator_has_moved(enumerator)) {
        return status_error("Enumerator has not moved yet.");
    }

    if (recipe_enumerator_is_empty(enumerator)) {
        return status_error("Enumerator is empty.");
    }

    algorithm_t current_alg = enumerator->recipe->head->algorithm;

    data_t new_data = { 0 };
    status_t execute_stat = current_alg.execute(enumerator->rolling_result, current_alg.additional_args, &new_data);
    if (!execute_stat.success) {
        return execute_stat;
    }

    free(enumerator->rolling_result.data);
    enumerator->rolling_result = new_data;

    return status_ok();
}

RESULT(const data_t*) recipe_enumerator_current_result(const recipe_enumerator_t enumerator) {
    if (!recipe_enumerator_has_moved(enumerator)) {
        return result_error("Enumerator has not moved yet.");
    }

    return result_ok(&enumerator->rolling_result);
}

RESULT(const char*) recipe_enumerator_current_name(const recipe_enumerator_t enumerator) {
    if (!recipe_enumerator_has_moved(enumerator)) {
        return result_error("Enumerator has not moved yet.");
    }

    if (recipe_enumerator_is_empty(enumerator)) {
        return result_error("Enumerator is empty.");
    }

#pragma warning(suppress:4090) // Different const qualifiers
    return result_ok(enumerator->recipe->head->algorithm.name);
}

void destroy_recipe_enumerator(recipe_enumerator_t enumerator) {
    destroy_recipe(enumerator->recipe);

    free(enumerator->rolling_result.data);

    free(enumerator);
}
