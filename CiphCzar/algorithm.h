#pragma once

#include <stddef.h>

#include "argument.h"
#include "result.h"

typedef struct {
    const char* name;
    const char* description;
    size_t (*execute)(char*, size_t, argument_t*, char*);
    result_t (*validate_args)(argument_t*);
    argument_t* additional_args;
} algorithm_t;

