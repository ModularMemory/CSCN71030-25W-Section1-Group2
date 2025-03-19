#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "trim_spaces.h"
#include "utils.h"

status_t trim_spaces_execute(const data_t input, const pargument_t args, data_t* output) {
    long long start = 0;
    while (start < (long long)input.len && isspace(input.data[start])) {
        start++;
    }

    long long end = input.len - 1;
    while (end >= 0 && isspace(input.data[end])) {
        end--;
    }

    end++;

    // Alloc output
    size_t alloc_size = (size_t)max(0, end - start);
    result_t out_res = allocate_string(alloc_size);
    if (!out_res.success) {
        return to_status(out_res);
    }

    assert(out_res.data);
    char* out_data = out_res.data;

    memcpy_s(out_data, alloc_size, input.data + start, alloc_size);

    *output = create_data(out_data, alloc_size);

    return status_ok();
}

status_t trim_spaces_validate_args(const pargument_t args) {
    return status_ok();
}

void trim_spaces_reset_args(algorithm_t* alg) {}
