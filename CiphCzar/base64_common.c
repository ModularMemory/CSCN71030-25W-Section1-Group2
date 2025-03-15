#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "base64_common.h"
#include "utils.h"

static const char* base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char padding = '=';

// https://en.wikipedia.org/wiki/Base64#Output_padding
status_t base64_encode(const data_t input, data_t* output) {
    const char* in_data = input.data;
    size_t in_len = input.len;

    // Base64 encode produces 4 chars for every 3 input bytes
    size_t out_len = in_len * 3 / 4;
    result_t out_res = allocate_string(out_len);
    if (!out_res.success) {
        return to_status(out_res);
    }

    assert(out_res.data);
    char* out_data = out_res.data;

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

static size_t get_decoded_len(const data_t input) {
    if (input.len < 1) {
        // Ensure 0-length buffers don't read out of bounds
        return 0;
    }

    size_t pad_count = 0;
    if (input.data[input.len - 1] == padding) {
        if (input.data[input.len - 2] == padding) {
            pad_count = 2;
        }
        else {
            pad_count = 1;
        }
    }

    // Base64 decode produces 3 bytes for every 4 input chars
    return input.len / 4 * 3 - pad_count;
}

status_t base64_decode(const data_t input, data_t* output) {
    const char* in_data = input.data;
    size_t in_len = input.len;

    // If the input is not the correct length, abort
    if (in_len % 4 != 0) {
        return status_error("Input is not valid Base64.");
    }

    size_t out_len = get_decoded_len(input);
    result_t out_res = allocate_string(out_len);
    if (!out_res.success) {
        return to_status(out_res);
    }

    assert(out_res.data);
    char* out_data = out_res.data;

    size_t out_off = 0;
    size_t buff_off = 0;
    char decode_buff[4] = { 0 };

    // Decode Base64 chars into bytes
    for (size_t in_off = 0; in_off < in_len; in_off++) {
        char current = in_data[in_off];

        // Search for the matching Base64 char
        bool found = false;
        for (int i = 0; i < 64; i++) {
            if (base64_chars[i] == current) {
                found = true;
                decode_buff[buff_off] = i;
                buff_off++;
            }
        }

        // Failed to find a matching Base64 char, abort
        if (!found) {
            free(out_data);
            return status_error("Input contains invalid Base64 chars.");
        }

        // Buffer is full, decode into output data
        if (buff_off == 4) {
            out_data[out_off] = (decode_buff[0] << 2) | (decode_buff[1] >> 4);

            if (decode_buff[2] != padding) {
                out_data[out_off + 1] = (decode_buff[1] << 4) | (decode_buff[2] >> 2);
            }

            if (decode_buff[3] != padding) {
                out_data[out_off + 2] = (decode_buff[2] << 6) | decode_buff[3];
            }

            out_off += 3;
            buff_off = 0;
        }
    }

    *output = create_data(out_data, out_len);

    return status_ok();
}
