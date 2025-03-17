#pragma once

#include "algorithm.h"

status_t alternate_case_execute(const data_t input, const pargument_t args, data_t* output);

status_t alternate_case_validate_args(const pargument_t args);

void alternate_case_reset_args(algorithm_t* alg);

#define CREATE_ALG_ALTERNATE_CASE(void)\
{\
    .name = "Alternate Case",\
    .description = "Alternates the casing of all readable characters in the input buffer.",\
    .execute = alternate_case_execute,\
    .validate_args = alternate_case_validate_args,\
    .additional_args = NULL,\
    .reset_args = alternate_case_reset_args\
}