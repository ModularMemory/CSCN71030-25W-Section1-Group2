#pragma once

#include "algorithm.h"

status_t from_hex_execute(const data_t input, const pargument_t args, data_t* output);

status_t from_hex_validate_args(const pargument_t args);

void from_hex_reset_args(algorithm_t* alg);

#define CREATE_ALG_FROM_HEX(void)\
{\
    .name = "From Hex",\
    .description = "Converts the input buffer from a sequence of hex codes into bytes.",\
    .execute = from_hex_execute,\
    .validate_args = from_hex_validate_args,\
    .additional_args = NULL,\
    .reset_args = from_hex_reset_args\
}