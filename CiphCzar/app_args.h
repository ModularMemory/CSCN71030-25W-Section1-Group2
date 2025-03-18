#pragma once

#include <stdbool.h>

typedef struct {
    bool quiet;
    const char* recipe_file;
    const char* output_file;
    const char* default_input;
    const char* input_file;
} app_args_t;

bool parse_app_arguments(int argc, const char** argv, app_args_t* args);