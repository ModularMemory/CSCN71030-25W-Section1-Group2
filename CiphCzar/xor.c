#include <assert.h>
#include <string.h>

#include "substitution_cipher_common.h"
#include "utils.h"
#include "xor.h"

static char substitute_proc(char input, size_t i, void* state) {
    const data_t* key = (data_t*)state;

    char key_char = key->data[i % key->len];
    return input ^ key_char;
}

status_t xor_execute(const data_t input, const pargument_t args, data_t* output) {
    // Get key from args
    assert(args);
    assert(args->arg_type == STRING_ARG);
    char* key = args->arg_union.string;
    size_t key_len = strlen(key);
    data_t key_data = create_data(key, key_len);

    // Run substitution
    data_t out_data = { 0 };
    status_t sub_stat = run_substitution(input, &key_data, substitute_proc, &out_data);
    if (!sub_stat.success) {
        return sub_stat;
    }

    *output = out_data;

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
