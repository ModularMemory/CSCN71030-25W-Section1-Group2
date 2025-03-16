#include <assert.h>
#include <string.h>

#include "utils.h"
#include "xor.h"

status_t xor_execute(const data_t input, const pargument_t args, data_t* output) {
    result_t out_res = allocate_string(input.len);
    if (!out_res.success) {
        return to_status(out_res);
    }

    assert(args);
    assert(args->arg_type == STRING_ARG);
    const char* key = args->arg_union.string;
    size_t key_len = strlen(key);

    assert(out_res.data);
    char* out_data = out_res.data;

    for (size_t i = 0; i < input.len; i++) {
        char key_char = key[i % key_len];
        char res = (input.data[i]) ^ key_char;
        out_data[i] = res;
    }

    *output = create_data(out_data, input.len);

    return status_ok();
}

status_t xor_validate_args(const pargument_t args) {
    if (!args || args->next) {
        return status_error("XOR must have only 1 arg.");
    }

    assert(args->arg_type == STRING_ARG);
    if (strlen(args->arg_union.string) < 1) {
        return status_error("Key must be at least 1 char long.");
    }

    return status_ok();
}

void xor_reset_args(algorithm_t* alg) {
    destroy_argument_list(alg->additional_args);

    pargument_t args = NULL;
    append_string_arg(&args, "Key", "AaaA");

    alg->additional_args = args;
}
