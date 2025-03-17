#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "num_conv_common.h"
#include "utils.h"

static size_t get_encoded_len(const data_t input, unsigned char number_len) {
    size_t in_len = input.len;

    return in_len * number_len + in_len - 1;
}

status_t to_number_string(const data_t input, const char* format_str, unsigned char number_len, data_t* output) {
    const char* in_data = input.data;
    size_t in_len = input.len;

    // Alloc output
    size_t out_len = get_encoded_len(input, number_len);
    result_t out_res = allocate_string(out_len);
    if (!out_res.success) {
        return to_status(out_res);
    }

    assert(out_res.data);
    char* out_data = out_res.data;

    size_t written = 0;
    for (size_t i = 0; i < in_len; i++) {
        unsigned int c = (unsigned int)((unsigned char)input.data[i]);
        int w = sprintf(out_data + written, format_str, c);
        if (w <= 0) {
            free(out_data);
            return status_error("Failed to write data.");
        }

        written += w;

        if (written < out_len) {
            out_data[written] = ' ';
            written++;
        }
    }

    *output = create_data(out_data, out_len);

    return status_ok();
}
