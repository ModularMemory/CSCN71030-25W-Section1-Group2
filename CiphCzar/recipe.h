#pragma once

#include <stdbool.h>

#include "algorithm.h"

typedef struct recipe_node {
    struct recipe_node* next;
    algorithm_t algorithm;
} recipe_node_t, *precipe_node_t;

typedef struct recipe {
    precipe_node_t head;
    precipe_node_t tail;
} *Recipe;

result_t create_recipe(void);

bool recipe_is_empty(Recipe recipe);

result_t recipe_push(Recipe recipe, algorithm_t algorithm);

bool recipe_pop(Recipe recipe, algorithm_t* algorithm);

result_t copy_recipe(Recipe recipe);

void destroy_recipe(Recipe recipe);