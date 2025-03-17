#pragma once

#include "algorithm.h"

status_t swap_case_execute(const data_t input, const pargument_t args, data_t* output);

status_t swap_case_validate_args(const pargument_t args);

void swap_case_reset_args(algorithm_t* alg);

#define CREATE_ALG_SWAP_CASE(void)\
{\
    .name = "Swap Case",\
    .description = "Swaps the casing of all readable characters in the input buffer.",\
    .execute = swap_case_execute,\
    .validate_args = swap_case_validate_args,\
    .additional_args = NULL,\
    .reset_args = swap_case_reset_args\
}