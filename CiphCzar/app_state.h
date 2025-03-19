#pragma once

#include "app_args.h"
#include "data.h"
#include "recipe.h"

typedef struct {
	data_t current_input;
	data_t current_output;
	bool headless;
	char *output_file;
	char* output_recipe_file;
	recipe_t recipe;
} app_state_t;

status_t create_app_state(app_state_t* app_state, app_args_t args);

void destroy_app_state(app_state_t app_state);