#include <assert.h>
#include <ctype.h>
#include <stdbool.h>

#include "alternating_case.h"
#include "substitution_cipher_common.h"

static char substitute_proc(char c, size_t i, void* state) {
    // Only alternate non-space chars
    if (isspace(c)) {
        return c;
    }

    bool* alternate = (bool*)state;
    *alternate = !*alternate;

    if (*alternate) {
        return (char)tolower(c);
    }

    return (char)toupper(c);
}

status_t alternate_case_execute(const data_t input, const pargument_t args, data_t* output) {
    bool alternate = true;

    // Run substitution
    data_t out_data = { 0 };
    status_t sub_stat = run_substitution(input, &alternate, substitute_proc, &out_data);
    if (!sub_stat.success) {
        return sub_stat;
    }

    *output = out_data;

    return status_ok();
}

status_t alternate_case_validate_args(const pargument_t args) {
    return status_ok();
}

void alternate_case_reset_args(algorithm_t* alg) {}
