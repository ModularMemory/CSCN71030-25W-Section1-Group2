#pragma once

#include "algorithm.h"

status_t to_upper_execute(const data_t input, const pargument_t args, data_t* output);

status_t to_upper_validate_args(const pargument_t args);

void to_upper_reset_args(algorithm_t* alg);

#define CREATE_ALG_TO_UPPER(void)\
{\
    .name = "To Upper",\
    .description = "Uppercases all of readable characters in the input buffer.",\
    .execute = to_upper_execute,\
    .validate_args = to_upper_validate_args,\
    .additional_args = NULL,\
    .reset_args = to_upper_reset_args\
}