#pragma once

#include "algorithm.h"

status_t rot_13_execute(const data_t input, const pargument_t args, data_t* output);

status_t rot_13_validate_args(const pargument_t args);

void rot_13_reset_args(algorithm_t* alg);

#define CREATE_ALG_ROT_13(void)\
{\
    .name = "ROT 13",\
    .description = "Rotates the alphabetical characters in the input buffer by 13 positions.",\
    .execute = rot_13_execute,\
    .validate_args = rot_13_validate_args,\
    .additional_args = NULL,\
    .reset_args = rot_13_reset_args\
}