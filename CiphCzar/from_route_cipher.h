#pragma once

#include "algorithm.h"

status_t from_route_cipher_execute(const data_t input, const pargument_t args, data_t* output);

status_t from_route_cipher_validate_args(const pargument_t args);

void from_route_cipher_reset_args(algorithm_t* alg);

#define CREATE_ALG_FROM_ROUTE_CIPHER(void)\
{\
    .name = "To Route Cipher",\
    .description = "Transposes the input buffer backwards through a route cipher.",\
    .execute = from_route_cipher_execute,\
    .validate_args = from_route_cipher_validate_args,\
    .additional_args = NULL,\
    .reset_args = from_route_cipher_reset_args\
}