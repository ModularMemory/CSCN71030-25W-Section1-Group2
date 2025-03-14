#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>

#include "to_lower.h"
#include "utils.h"

static status_t execute(const data_t input, const pargument_t args, data_t* output) {
    result_t out_res = allocate_string(input.len);
    if (!out_res.success) {
        return to_status(out_res);
    }

    assert(out_res.data);
    char* out_data = out_res.data;

    for (size_t i = 0; i < input.len; i++) {
        char c = input.data[i];
        if (c >= 'A' && c <= 'Z') {
            c = (char)tolower(c);
        }

        out_data[i] = c;
    }

    *output = create_data(out_data, input.len);

    return status_ok();
}

static status_t validate_args(const pargument_t args) {
    return status_ok();
}

algorithm_t create_alg_to_lower(void) {
    algorithm_t alg = { 0 };

    alg.name = "To Lower";
    alg.description = "Lowercases all of the readable characters in the input buffer.";
    alg.execute = execute;
    alg.validate_args = validate_args;
    alg.additional_args = NULL;

    return alg;
}