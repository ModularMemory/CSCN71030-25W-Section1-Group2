#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "route_cipher_common.h"

static const char padding = ' ';

/// @brief Allocates a route cipher block formatted in x, y
static bool alloc_block(size_t block_width, size_t block_height, char*** block) {
    // Actual buffer alloc
    char* block_alloc = (char*)malloc(block_width * block_height);
    if (!block_alloc) {
        return false;
    }

    // Pointer alloc to interpret first alloc as a 2D array
    char** block_2d = (char**)malloc(block_width * sizeof(char*));
    if (!block_2d) {
        free(block_alloc);
        return false;
    }

    // Fill 2D array
    for (size_t i = 0; i < block_width; i++) {
        block_2d[i] = &block_alloc[i * block_height];
    }

    *block = block_2d;

    return true;
}

static void free_block(char** block) {
    // Free actual buffer alloc
    free(block[0]);

    // Free 2D array alloc
    free(block);
}

static size_t get_output_len(const data_t input, size_t block_width, size_t block_height) {
    size_t in_len = input.len;

    // Round up to the nearest multiple of the block size
    size_t block_size = block_width * block_height;
    if (in_len % block_size != 0) {
        in_len += block_size - in_len % block_size;
    }

    return in_len;
}

static bool encode_block(const data_t input, size_t start_offset, size_t block_width, size_t block_height, char** block) {
    if (start_offset >= input.len) {
        return false;
    }

    // Ensure the block is filled with padding in case the input is not a multiple of the block size
    memset(block[0], padding, block_width * block_height);

    // Fill the block
    size_t in_off = start_offset;
    for (; in_off < input.len; in_off++) {
        size_t block_pos = in_off - start_offset;
        size_t x = block_pos % block_width;
        size_t y = block_pos / block_width;

        block[x][y] = input.data[in_off];
    }

    return true;
}

status_t route_cipher_encode(const data_t input, size_t block_width, size_t block_height, data_t* output) {
    char** block = NULL;
    if (!alloc_block(block_width, block_height, &block)) {
        return status_error("Failed to allocate route cipher block.");
    }

    // Alloc output
    size_t out_len = get_output_len(input, block_width, block_height);
    result_t out_res = allocate_string(out_len);
    if (!out_res.success) {
        return to_status(out_res);
    }

    assert(out_res.data);
    char* out_data = out_res.data;

    size_t out_off = 0;
    while (encode_block(input, out_off, block_width, block_height, block)) {
        // Copy the block contents to the output buffer in top-down, left-right order
        for (size_t x = 0; x < block_width; x++) {
            for (size_t y = 0; y < block_height; y++) {
                out_data[out_off] = block[x][y];
                out_off++;
            }
        }
    }

    *output = create_data(out_data, out_len);

    return status_ok();
}

static bool decode_block(const data_t input, size_t start_offset, size_t block_width, size_t block_height, char** block) {
    if (start_offset >= input.len) {
        return false;
    }

    // Ensure the block is filled with padding in case the input is not a multiple of the block size
    memset(block[0], padding, block_width * block_height);

    // Fill the block
    size_t in_off = start_offset;
    for (; in_off < input.len; in_off++) {
        size_t block_pos = in_off - start_offset;
        size_t x = (block_pos % (block_width * block_height)) / block_height;
        size_t y = block_pos % block_height;

        block[x][y] = input.data[in_off];
    }

    return true;
}

status_t route_cipher_decode(const data_t input, size_t block_width, size_t block_height, data_t* output) {
    char** block = NULL;
    if (!alloc_block(block_width, block_height, &block)) {
        return status_error("Failed to allocate route cipher block.");
    }

    // Alloc output
    size_t out_len = get_output_len(input, block_width, block_height);
    result_t out_res = allocate_string(out_len);
    if (!out_res.success) {
        return to_status(out_res);
    }

    assert(out_res.data);
    char* out_data = out_res.data;

    size_t out_off = 0;
    while (decode_block(input, out_off, block_width, block_height, block)) {
        // Copy the block contents to the output buffer in left-right, top-down order
        for (size_t y = 0; y < block_height; y++) {
            for (size_t x = 0; x < block_width; x++) {
                out_data[out_off] = block[x][y];
                out_off++;
            }
        }
    }

    *output = create_data(out_data, out_len);

    return status_ok();
}
