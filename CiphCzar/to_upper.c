#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>

#include "to_upper.h"
#include "utils.h"

static result_t execute(const data_t input, pargument_t args, data_t* output) {
    result_t out_res = allocate_string(input.len);
    if (!out_res.success) {
        return out_res;
    }

    assert(out_res.data);
    char* out_data = out_res.data;

    for (size_t i = 0; i < input.len; i++) {
        char c = input.data[i];
        if (c >= 'a' && c <= 'z') {
            c = (char)toupper(c);
        }

        out_data[i] = c;
    }

    *output = create_data(out_data, input.len);

    return result_ok(NULL);
}

static result_t validate_args(pargument_t args) {
    return result_ok(NULL);
}

algorithm_t create_alg_to_upper(void) {
    algorithm_t alg = { 0 };

    alg.name = "To Upper";
    alg.description = "Uppercases all of the readable characters in the input buffer.";
    alg.execute = execute;
    alg.validate_args = validate_args;
    alg.additional_args = NULL;

    return alg;
}