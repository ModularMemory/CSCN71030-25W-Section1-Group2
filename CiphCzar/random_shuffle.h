#pragma once

#include "algorithm.h"

status_t random_shuffle_execute(const data_t input, const pargument_t args, data_t* output);

status_t random_shuffle_validate_args(const pargument_t args);

void random_shuffle_reset_args(algorithm_t* alg);

#define CREATE_ALG_RANDOM_SHUFFLE(void)\
{\
    .name = "Random Shuffle",\
    .description = "Randomly shuffles the characters in the input buffer.",\
    .execute = random_shuffle_execute,\
    .validate_args = random_shuffle_validate_args,\
    .additional_args = NULL,\
    .reset_args = random_shuffle_reset_args\
}