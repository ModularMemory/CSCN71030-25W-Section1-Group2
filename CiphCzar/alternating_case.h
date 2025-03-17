#pragma once

#include "algorithm.h"

status_t alternating_case_execute(const data_t input, const pargument_t args, data_t* output);

status_t alternating_case_validate_args(const pargument_t args);

void alternating_case_reset_args(algorithm_t* alg);

#define CREATE_ALG_ALTERNATING_CASE(void)\
{\
    .name = "Alternating Case",\
    .description = "Alternates the casing of all readable characters in the input buffer.",\
    .execute = alternating_case_execute,\
    .validate_args = alternating_case_validate_args,\
    .additional_args = NULL,\
    .reset_args = alternating_case_reset_args\
}