#pragma once

#include <stddef.h>

#include "argument.h"
#include "data.h"
#include "status_result.h"

typedef struct {
    const char* name;
    const char* description;
    status_t (*execute)(const data_t input, const pargument_t args, data_t* output);
    status_t (*validate_args)(const pargument_t args);
    pargument_t additional_args;
} algorithm_t;

typedef struct algorithm_list {
    struct algorithm_list* next;
    algorithm_t algorithm;
} algorithm_list_t, *palgorithm_list_t;

const palgorithm_list_t get_algorithms(void);

algorithm_t get_algorithm_by_name(const char* name);