#pragma once

#include <stdbool.h>

typedef struct {
    bool quiet;
    char* recipe_file;
    char* output_file;
    char* default_input;
    char* input_file;
} app_args_t;

bool parse_app_arguments(int argc, const char** argv, app_args_t* args);