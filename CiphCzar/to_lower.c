#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>

#include "to_lower.h"
#include "utils.h"

status_t to_lower_execute(const data_t input, const pargument_t args, data_t* output) {
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

status_t to_lower_validate_args(const pargument_t args) {
    return status_ok();
}

void to_lower_reset_args(algorithm_t* alg) {}
