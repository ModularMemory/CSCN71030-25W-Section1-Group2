#include <assert.h>

#include "rot_common.h"
#include "to_lower.h"
#include "utils.h"

status_t rot_n_execute(const data_t input, const pargument_t args, data_t* output) {
    // Validate args
    status_t validate_stat = rot_n_validate_args(args);
    if (!validate_stat.success) {
        return validate_stat;
    }

    // Alloc output
    result_t out_res = allocate_string(input.len);
    if (!out_res.success) {
        return to_status(out_res);
    }

    // Get rotate count from args
    assert(args);
    assert(args->arg_type == INTEGER_ARG);
    int rotate_count = args->arg_union.integer;

    assert(out_res.data);
    char* out_data = out_res.data;

    // Run rotation
    rotate_impl(input.data, out_data, input.len, true, true, false, rotate_count);

    *output = create_data(out_data, input.len);

    return status_ok();
}

status_t rot_n_validate_args(const pargument_t args) {
    if (!args || args->next) {
        return status_error("ROT N must have only 1 arg.");
    }

    // We accept any integer
    return status_ok();
}

void rot_n_reset_args(algorithm_t* alg) {
    destroy_argument_list(alg->additional_args);

    pargument_t args = NULL;
    append_integer_arg(&args, "Rotation count", 1);

    alg->additional_args = args;
}