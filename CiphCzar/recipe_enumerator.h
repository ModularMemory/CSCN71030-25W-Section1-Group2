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

RESULT(recipe_enumerator_t) create_recipe_enumerator(recipe_t recipe, const data_t input_data);

bool recipe_enumerator_move_next(recipe_enumerator_t enumerator);

status_t recipe_enumerator_execute(recipe_enumerator_t enumerator);

RESULT(const data_t*) recipe_enumerator_current_result(recipe_enumerator_t enumerator);

RESULT(const char*) recipe_enumerator_current_name(recipe_enumerator_t enumerator);

void destroy_recipe_enumerator(recipe_enumerator_t enumerator);