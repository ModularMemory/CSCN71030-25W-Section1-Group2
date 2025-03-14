#include <assert.h>
#include <stdlib.h>

#include "to_lower.h"
#include "utils.h"

status_t rot_13_execute(const data_t input, const pargument_t args, data_t* output) {
    result_t out_res = allocate_string(input.len);
    if (!out_res.success) {
        return to_status(out_res);
    }

    assert(out_res.data);
    char* out_data = out_res.data;

    for (size_t i = 0; i < input.len; i++) {
        char c = input.data[i];
        if (c >= 'a' && c <= 'z') {
            c += 13;

            // Wrap char around range
            if (c > 'z') {
                c -= 'z';
            }
        }
        else if (c >= 'A' && c <= 'Z') {
            c += 13;

            // Wrap char around range
            if (c > 'Z') {
                c -= 'Z';
            }
        }

        out_data[i] = c;
    }

    *output = create_data(out_data, input.len);

    return status_ok();
}

status_t rot_13_validate_args(const pargument_t args) {
    return status_ok();
}

void rot_13_reset_args(algorithm_t* alg) {}
