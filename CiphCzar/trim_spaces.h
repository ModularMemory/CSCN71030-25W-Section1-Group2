#pragma once

#include "algorithm.h"

status_t trim_spaces_execute(const data_t input, const pargument_t args, data_t* output);

status_t trim_spaces_validate_args(const pargument_t args);

void trim_spaces_reset_args(algorithm_t* alg);

#define CREATE_ALG_TRIM_SPACES(void)\
{\
    .name = "Trim",\
    .description = "Trims leading and trailing spaces from the input buffer.",\
    .execute = trim_spaces_execute,\
    .validate_args = trim_spaces_validate_args,\
    .additional_args = NULL,\
    .reset_args = trim_spaces_reset_args\
}