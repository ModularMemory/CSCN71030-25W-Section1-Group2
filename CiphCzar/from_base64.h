#pragma once

#include "algorithm.h"

status_t from_base64_execute(const data_t input, const pargument_t args, data_t* output);

status_t from_base64_validate_args(const pargument_t args);

void from_base64_reset_args(algorithm_t* alg);

#define CREATE_ALG_FROM_BASE64(void)\
{\
    .name = "Fom Base64",\
    .description = "Converts the input buffer from base64 into bytes.",\
    .execute = from_base64_execute,\
    .validate_args = from_base64_validate_args,\
    .additional_args = NULL,\
    .reset_args = from_base64_reset_args\
}