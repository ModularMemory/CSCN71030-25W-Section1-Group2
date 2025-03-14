#pragma once

#include <stddef.h>

#include "argument.h"
#include "data.h"
#include "status_result.h"

typedef struct {
    const char* name;
    const char* description;
    status_t (*execute)(const data_t, pargument_t, data_t*);
    status_t (*validate_args)(pargument_t);
    pargument_t additional_args;
} algorithm_t;
