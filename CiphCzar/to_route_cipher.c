#include <assert.h>

#include "route_cipher_common.h"
#include "to_route_cipher.h"

status_t to_route_cipher_execute(const data_t input, const pargument_t args, data_t* output) {
    status_t validate_stat = to_route_cipher_validate_args(args);
    if (!validate_stat.success) {
        return validate_stat;
    }

    assert(args);
    assert(args->arg_type == INTEGER_ARG);
    int block_width = args->arg_union.integer;

    assert(args->next);
    assert(args->next->arg_type == INTEGER_ARG);
    int block_height = args->next->arg_union.integer;

    data_t out_data = { 0 };
    status_t stat = route_cipher_encode(input, block_width, block_height, &out_data);
    if (!stat.success) {
        return stat;
    }

    *output = out_data;

    return status_ok();
}

status_t to_route_cipher_validate_args(const pargument_t args) {
    if (!args || !args->next || args->next->next) {
        return status_error("Route cipher must have only 2 args.");
    }

    assert(args->arg_type == INTEGER_ARG);
    if (args->arg_union.integer < 1) {
        return status_error("Block width cannot be less than 1.");
    }

    assert(args->next->arg_type == INTEGER_ARG);
    if (args->next->arg_union.integer < 1) {
        return status_error("Block height cannot be less than 1.");
    }

    return status_ok();
}

void to_route_cipher_reset_args(algorithm_t* alg) {
    destroy_argument_list(alg->additional_args);

    pargument_t args = NULL;
    append_integer_arg(&args, "Block width", 3);
    append_integer_arg(&args, "Block height", 2);

    alg->additional_args = args;
}
