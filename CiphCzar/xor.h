#pragma once

#include "algorithm.h"

status_t xor_execute(const data_t input, const pargument_t args, data_t* output);

status_t xor_validate_args(const pargument_t args);

void xor_reset_args(algorithm_t* alg);

#define CREATE_ALG_XOR(void)\
{\
    .name = "XOR",\
    .description = "XORs the input buffer against a given key.",\
    .execute = xor_execute,\
    .validate_args = xor_validate_args,\
    .additional_args = NULL,\
    .reset_args = xor_reset_args\
}