#pragma once

#include "algorithm.h"

status_t to_lower_execute(const data_t input, const pargument_t args, data_t* output);

status_t to_lower_validate_args(const pargument_t args);

void to_lower_reset_args(algorithm_t* alg);

#define CREATE_ALG_TO_LOWER(void)\
{\
    .name = "To Lower",\
    .description = "Lowercases all of readable characters in the input buffer.",\
    .execute = to_lower_execute,\
    .validate_args = to_lower_validate_args,\
    .additional_args = NULL,\
    .reset_args = to_lower_reset_args\
}