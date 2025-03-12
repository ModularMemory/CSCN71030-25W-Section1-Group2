#pragma once

#include <stdbool.h>
#include <stddef.h>

#include "argument.h"

typedef struct {
    char* name;
    char* description;
    size_t (*execute)(char*, size_t, argument_t*, char*);
    validation_result_t (*validate_args)(argument_t*);
    argument_t* additional_args;
} algorithm_t;

typedef struct {
    bool success;
    char* message;
} validation_result_t;