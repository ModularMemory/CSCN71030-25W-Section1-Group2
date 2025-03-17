#pragma once

#include <stdio.h>

#include "argument.h"
#include "data.h"
#include "recipe.h"
#include "status_result.h"

status_t read_data(const char* filename, data_t* data);

status_t write_data(const char* filename, data_t data);

status_t read_recipe(const char* filename, recipe_t* recipe, pargument_t arguments);

status_t write_recipe(const char* filename, recipe_t recipe);

status_t write_string_to_stream(FILE* fp, char* data);

status_t write_int_to_stream(FILE* fp, int data);

status_t write_float_to_stream(FILE* fp, float data);

status_t read_string_from_stream(FILE* fp, char** data);

status_t read_int_from_stream(FILE* fp, int* data);

status_t read_float_from_file(FILE* fp, float* data);