#pragma once

#include "algorithm.h"

status_t from_decimal_execute(const data_t input, const pargument_t args, data_t* output);

status_t from_decimal_validate_args(const pargument_t args);

void from_decimal_reset_args(algorithm_t* alg);

#define CREATE_ALG_FROM_DECIMAL(void)\
{\
    .name = "From Decimal",\
    .description = "Converts the input buffer into a string of decimal codes.",\
    .execute = from_decimal_execute,\
    .validate_args = from_decimal_validate_args,\
    .additional_args = NULL,\
    .reset_args = from_decimal_reset_args\
}