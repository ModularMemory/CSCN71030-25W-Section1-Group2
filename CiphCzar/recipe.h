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
} *recipe_t;

RESULT(recipe_t) create_recipe(void);

bool recipe_is_empty(recipe_t recipe);

status_t recipe_push(recipe_t recipe, algorithm_t algorithm);

bool recipe_pop(recipe_t recipe, algorithm_t* algorithm);

RESULT(recipe_t) copy_recipe(recipe_t recipe);

void destroy_recipe(recipe_t recipe);