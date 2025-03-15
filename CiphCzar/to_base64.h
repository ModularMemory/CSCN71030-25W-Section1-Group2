#pragma once

#include "algorithm.h"

status_t to_base64_execute(const data_t input, const pargument_t args, data_t* output);

status_t to_base64_validate_args(const pargument_t args);

void to_base64_reset_args(algorithm_t* alg);

#define CREATE_ALG_TO_BASE64(void)\
{\
    .name = "To Base64",\
    .description = "Converts the input buffer into Base64.",\
    .execute = to_base64_execute,\
    .validate_args = to_base64_validate_args,\
    .additional_args = NULL,\
    .reset_args = to_base64_reset_args\
}