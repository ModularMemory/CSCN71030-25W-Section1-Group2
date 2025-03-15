#pragma once
#include "data.h"
#include "recipe.h"

typedef struct {
	data_t current_input;
	bool quiet;
	char *filename;
	recipe_t recipe;
} app_state_t;