#pragma once

#include "algorithm.h"
#include "recipe.h"

// Implementation not final
typedef struct {
    Recipe recipe;
    char* rolling_result;
} recipe_enumerator_t;

recipe_enumerator_t create_recipe_enumerator(Recipe recipe, const char* input_data);

void destroy_recipe_enumerator(recipe_enumerator_t enumerator);