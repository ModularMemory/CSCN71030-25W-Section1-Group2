#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "to_base64.h"
#include "utils.h"

status_t to_base64_execute(const data_t input, const pargument_t args, data_t* output) {
    size_t out_len = input.len * 3 / 4;
    result_t out_res = allocate_string(out_len);
    if (!out_res.success) {
        return to_status(out_res);
    }

    assert(out_res.data);
    char* out_data = out_res.data;

    size_t offset = 0;
    for (size_t i = 0; i < out_len; i += 3) {

    }

    *output = create_data(out_data, out_len);

    return status_error("Not implemented.");
}

status_t to_base64_validate_args(const pargument_t args) {
    return status_ok();
}

void to_base64_reset_args(algorithm_t* alg) {}
