#pragma once
#include "data.h"
#include "recipe.h"

typedef struct {
	data_t current_input;
	data_t current_output;
	bool quiet;
	char *output_file;
	recipe_t recipe;
} app_state_t;