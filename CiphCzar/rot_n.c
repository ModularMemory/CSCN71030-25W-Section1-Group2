#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "to_lower.h"
#include "utils.h"

status_t rot_n_execute(const data_t input, const pargument_t args, data_t* output) {
    result_t out_res = allocate_string(input.len);
    if (!out_res.success) {
        return to_status(out_res);
    }

    assert(args);
    assert(args->arg_type == INTEGER_ARG);
    int rotation_count = args->arg_union.integer;

    assert(out_res.data);
    char* out_data = out_res.data;

    for (size_t i = 0; i < input.len; i++) {
        // long long to ensure we don't overflow/underflow the type
        long long c = (long long)input.data[i];

        if (c >= 'a' && c <= 'z') {
            c += rotation_count;

            // Wrap char around range
            while (c < 'a') {
                c += 'a';
            }

            c %= 'z';
        }
        else if (c >= 'A' && c <= 'Z') {
            c += rotation_count;

            // Wrap char around range
            while (c < 'A') {
                c += 'A';
            }

            c %= 'Z';
        }

        out_data[i] = (char)c;
    }

    *output = create_data(out_data, input.len);

    return status_ok();
}

status_t rot_n_validate_args(const pargument_t args) {
    // We accept any integer
    return status_ok();
}

void rot_n_reset_args(algorithm_t* alg) {
    destroy_argument_list(alg->additional_args);

    pargument_t args = NULL;
    append_integer_arg(&args, "Rotation count", 1);

    alg->additional_args = args;
}