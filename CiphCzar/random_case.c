#include <assert.h>
#include <ctype.h>
#include <stdlib.h>

#include "random_case.h"
#include "substitution_cipher_common.h"

static char substitute_proc(char c, size_t i, void* state) {
    if ((rand() % 2) == 0) {
        return (char)tolower(c);
    }

    return (char)toupper(c);
}

status_t random_case_execute(const data_t input, const pargument_t args, data_t* output) {
    // Validate args
    status_t validate_stat = random_case_validate_args(args);
    if (!validate_stat.success) {
        return validate_stat;
    }

    // Get random seed from args
    assert(args);
    assert(args->arg_type == INTEGER_ARG);
    int random_seed = args->arg_union.integer;
    srand((unsigned int)random_seed);

    // Run substitution
    data_t out_data = { 0 };
    status_t sub_stat = run_substitution(input, NULL, substitute_proc, &out_data);
    if (!sub_stat.success) {
        return sub_stat;
    }

    *output = out_data;

    return status_ok();
}

status_t random_case_validate_args(const pargument_t args) {
    if (!args || args->next) {
        return status_error("Randomize Case must have only 1 arg.");
    }

    // We accept any integer
    return status_ok();
}

void random_case_reset_args(algorithm_t* alg) {
    destroy_argument_list(alg->additional_args);

    pargument_t args = NULL;
    append_integer_arg(&args, "Random seed", 1);

    alg->additional_args = args;
}
