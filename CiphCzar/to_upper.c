#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>

#include "to_upper.h"
#include "utils.h"



static result_t execute(const char* input, size_t input_len, pargument_t args, char** output, size_t* output_len) {
    result_t out_res = allocate_string(input_len);
    if (!out_res.success) {
        return out_res;
    }

    assert(out_res.data);
    *output = out_res.data;

    for (size_t i = 0; i < input_len; i++) {
        char c = input[i];
        if (c >= 'a' && c <= 'z') {
            c = (char)toupper(c);
        }

        *output[i] = c;
    }
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

