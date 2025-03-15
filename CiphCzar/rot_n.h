#pragma once

#include "algorithm.h"

status_t rot_n_execute(const data_t input, const pargument_t args, data_t* output);

status_t rot_n_validate_args(const pargument_t args);

void rot_n_reset_args(algorithm_t* alg);

#define CREATE_ALG_ROT_N(void)\
{\
    .name = "ROT N",\
    .description = "Rotates the alphabetical characters in the input buffer by a specified number of positions.",\
    .execute = rot_n_execute,\
    .validate_args = rot_n_validate_args,\
    .additional_args = NULL,\
    .reset_args = rot_n_reset_args\
}