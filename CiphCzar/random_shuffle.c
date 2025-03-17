#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "random_shuffle.h"
#include "utils.h"

status_t random_shuffle_execute(const data_t input, const pargument_t args, data_t* output) {
    // Validate args
    status_t validate_stat = random_shuffle_validate_args(args);
    if (!validate_stat.success) {
        return validate_stat;
    }

    // Alloc output
    size_t out_len = input.len;
    result_t out_res = allocate_string(out_len);
    if (!out_res.success) {
        return to_status(out_res);
    }

    // Get random seed from args
    assert(args);
    assert(args->arg_type == INTEGER_ARG);
    int random_seed = args->arg_union.integer;
    srand((unsigned int)random_seed);

    assert(out_res.data);
    char* out_data = out_res.data;

    // Copy input data to output buffer
    memcpy_s(out_data, out_len, input.data, input.len);

    // Run shuffle
    for (size_t i = 0; i < out_len; i++) {
        size_t swap_index = i;
        while (swap_index == i) {
            swap_index = rand() % out_len;
        }

        char temp = out_data[i];
        out_data[i] = out_data[swap_index];
        out_data[swap_index] = temp;
    }

    *output = create_data(out_data, input.len);

    return status_ok();
}

status_t random_shuffle_validate_args(const pargument_t args) {
    if (!args || args->next) {
        return status_error("Random Shuffle must have only 1 arg.");
    }

    // We accept any integer
    return status_ok();
}

void random_shuffle_reset_args(algorithm_t* alg) {
    destroy_argument_list(alg->additional_args);

    pargument_t args = NULL;
    append_integer_arg(&args, "Random seed", 1);

    alg->additional_args = args;
}
