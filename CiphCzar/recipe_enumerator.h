#pragma once

#include <stdbool.h>

#include "algorithm.h"
#include "recipe.h"
#include "status_result.h"

typedef struct recipe_enumerator {
    bool has_moved;
    recipe_t recipe;
    data_t rolling_result;
} *recipe_enumerator_t;

RESULT(recipe_enumerator_t) create_recipe_enumerator(const recipe_t recipe, const data_t input_data);

/// @brief Returns true if the enumerator has moved at least once after being created
bool recipe_enumerator_has_moved(const recipe_enumerator_t enumerator);

/// @brief Returns true if the enumerator contains a "current" algorithm
bool recipe_enumerator_is_empty(const recipe_enumerator_t enumerator);

/// @brief Advances the enumerator to the next algorithm
/// @return True if the enumerator was advanced to the next algorithm, false if there were no more algorithms to advance to
bool recipe_enumerator_move_next(recipe_enumerator_t enumerator);

/// @brief Computes the result of the current algorithm with the rolling result as input
status_t recipe_enumerator_execute(recipe_enumerator_t enumerator);

/// @brief Gets the read-only current rolling result of the enumerator
RESULT(const data_t*) recipe_enumerator_current_result(const recipe_enumerator_t enumerator);

/// @brief Gets the read-only name of the current algorithm
RESULT(const char*) recipe_enumerator_current_name(const recipe_enumerator_t enumerator);

void destroy_recipe_enumerator(recipe_enumerator_t enumerator);