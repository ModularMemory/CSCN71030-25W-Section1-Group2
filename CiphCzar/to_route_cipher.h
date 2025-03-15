#pragma once

#include "algorithm.h"

status_t to_route_cipher_execute(const data_t input, const pargument_t args, data_t* output);

status_t to_route_cipher_validate_args(const pargument_t args);

void to_route_cipher_reset_args(algorithm_t* alg);

#define CREATE_ALG_TO_ROUTE_CIPHER(void)\
{\
    .name = "To Route Cipher",\
    .description = "Transposes the input buffer forwards through a route cipher.",\
    .execute = to_route_cipher_execute,\
    .validate_args = to_route_cipher_validate_args,\
    .additional_args = NULL,\
    .reset_args = to_route_cipher_reset_args\
}