#pragma once

#include <stddef.h>

#include "argument.h"
#include "data.h"
#include "result.h"

typedef struct {
    const char* name;
    const char* description;
    result_t (*execute)(const data_t, pargument_t, data_t*);
    result_t (*validate_args)(pargument_t);
    pargument_t additional_args;
} algorithm_t;
