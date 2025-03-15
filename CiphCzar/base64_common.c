#include <assert.h>
#include <stdlib.h>

#include "base64_common.h"
#include "utils.h"

static const char* base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char padding = '=';

// https://en.wikipedia.org/wiki/Base64#Output_padding
status_t base64_encode(const data_t input, data_t* output) {
    const char* in_data = input.data;
    size_t in_len = input.len;

    size_t out_len = in_len * 3 / 4;
    result_t out_res = allocate_string(out_len);
    if (!out_res.success) {
        return to_status(out_res);
    }

    assert(out_res.data);
    char* out_data = out_res.data;

    // Base64 produces 4 chars for every 3 input bytes
    // Compute the number of input bytes over this threshold that will require padding
    size_t in_len_mod_3 = in_len % 3;

    // Compute the length minus the padded bytes
    size_t non_padded_len = in_len - in_len_mod_3;

    // Write the non-padded chars
    size_t out_off = 0;
    for (size_t in_off = 0; in_off < non_padded_len; in_off += 3) {
        out_data[out_off] = base64_chars[(in_data[in_off] & 0xFC) >> 2];
        out_data[out_off + 1] = base64_chars[((in_data[in_off] & 0x03) << 4) | ((in_data[in_off + 1] & 0xF0) >> 4)];
        out_data[out_off + 2] = base64_chars[((in_data[in_off + 1] & 0x0F) << 2) | ((in_data[in_off + 2] & 0xC0) >> 6)];
        out_data[out_off + 3] = base64_chars[in_data[in_off + 2] & 0x3F];

        out_off += 4;
    }

    // Write final chars with padding, if required
    if (in_len_mod_3 == 1) {
        // 1 byte over threshold, write 2 padded chars
        out_data[out_off] = base64_chars[(in_data[non_padded_len] & 0xFC) >> 2];
        out_data[out_off + 1] = base64_chars[(in_data[non_padded_len] & 0x03) << 4];
        out_data[out_off + 2] = padding;
        out_data[out_off + 3] = padding;
    }
    else if (in_len_mod_3 == 2) {
        // 2 bytes over threshold, write 1 padded char
        out_data[out_off] = base64_chars[(in_data[non_padded_len] & 0xFC) >> 2];
        out_data[out_off + 1] = base64_chars[((in_data[non_padded_len] & 0x03) << 4) | ((in_data[non_padded_len + 1] & 0xF0) >> 4)];
        out_data[out_off + 2] = base64_chars[(in_data[non_padded_len + 1] & 0x0F) << 2];
        out_data[out_off + 3] = padding;
    }

    *output = create_data(out_data, out_len);

    return status_ok();
}

status_t base64_decode(const data_t input, data_t* output) {
    return status_error("Not implemented.");
}
