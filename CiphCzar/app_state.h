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

status_t create_app_state(app_state_t* app_state, bool quiet, const char* output_file);

void destroy_app_state(app_state_t app_state);