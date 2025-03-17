#pragma once

#include "algorithm.h"

status_t to_hex_execute(const data_t input, const pargument_t args, data_t* output);

status_t to_hex_validate_args(const pargument_t args);

void to_hex_reset_args(algorithm_t* alg);

#define CREATE_ALG_TO_HEX(void)\
{\
    .name = "To Hex",\
    .description = "Converts the input buffer into a string of hex codes.",\
    .execute = to_hex_execute,\
    .validate_args = to_hex_validate_args,\
    .additional_args = NULL,\
    .reset_args = to_hex_reset_args\
}