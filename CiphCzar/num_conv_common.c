#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "num_conv_common.h"
#include "utils.h"

static size_t get_encoded_len(const data_t input, unsigned int number_len) {
    size_t in_len = input.len;

    assert(number_len < UINT_MAX);
    return in_len * (number_len + 1) - 1;
}

status_t to_number_string(const data_t input, const char* format_str, unsigned int number_len, data_t* output) {
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

static size_t get_decoded_len(const data_t input, unsigned int number_len) {
    size_t in_len = input.len;

    assert(number_len < UINT_MAX);
    return (in_len + 1) / (number_len + 1);
}

status_t from_number_string(const data_t input, const char* format_str, unsigned int number_len, data_t* output) {
    const char* in_data = input.data;
    size_t in_len = input.len;

    // Alloc output
    size_t out_len = get_decoded_len(input, number_len);
    result_t out_res = allocate_string(out_len);
    if (!out_res.success) {
        return to_status(out_res);
    }

    assert(out_res.data);
    char* out_data = out_res.data;

    size_t written = 0;
    assert(number_len < UINT_MAX);
    for (size_t i = 0; i < in_len;) {
        unsigned int decoded;
        int r = sscanf_s(in_data + i, format_str, &decoded);
        if (r <= 0) {
            free(out_data);
            return status_error("Failed to read number from input buffer.");
        }

        i += number_len;
        if (i < in_len && in_data[i] != ' ') {
            free(out_data);
            return status_error("Input buffer is not in the correct format.");
        }

        i++;

        assert(decoded < UCHAR_MAX);
        out_data[written] = (char)decoded;
        written++;
    }

    *output = create_data(out_data, out_len);

    return status_ok();
}