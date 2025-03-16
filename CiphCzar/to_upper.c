#include <assert.h>
#include <ctype.h>

#include "substitution_cipher_common.h"
#include "to_upper.h"

static char substitute_proc(char c, size_t i, void* state) {
    return (char)toupper(c);
}

status_t to_upper_execute(const data_t input, const pargument_t args, data_t* output) {
    // Run substitution
    data_t out_data = { 0 };
    status_t sub_stat = run_substitution(input, NULL, substitute_proc, &out_data);
    if (!sub_stat.success) {
        return sub_stat;
    }

    *output = out_data;

    return status_ok();
}

status_t to_upper_validate_args(const pargument_t args) {
    return status_ok();
}

void to_upper_reset_args(algorithm_t* alg) {}