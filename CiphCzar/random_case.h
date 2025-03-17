#pragma once

#include "algorithm.h"

status_t random_case_execute(const data_t input, const pargument_t args, data_t* output);

status_t random_case_validate_args(const pargument_t args);

void random_case_reset_args(algorithm_t* alg);

#define CREATE_ALG_RANDOM_CASE(void)\
{\
    .name = "Randomize Case",\
    .description = "Randomizes the casing of all readable characters in the input buffer.",\
    .execute = random_case_execute,\
    .validate_args = random_case_validate_args,\
    .additional_args = NULL,\
    .reset_args = random_case_reset_args\
}