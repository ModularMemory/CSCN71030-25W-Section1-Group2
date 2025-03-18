#pragma once

#include "algorithm.h"

status_t to_decimal_execute(const data_t input, const pargument_t args, data_t* output);

status_t to_decimal_validate_args(const pargument_t args);

void to_decimal_reset_args(algorithm_t* alg);

#define CREATE_ALG_TO_DECIMAL(void)\
{\
    .name = "To Decimal",\
    .description = "Converts the input buffer into a string of decimal codes.",\
    .execute = to_decimal_execute,\
    .validate_args = to_decimal_validate_args,\
    .additional_args = NULL,\
    .reset_args = to_decimal_reset_args\
}