#pragma once

#include "data.h"
#include "status_result.h"

/// @brief Encodes the input data with route cipher
/// @param input The input data
/// @param block_width The width of a transposition block
/// @param block_height The height of a transposition block 
/// @param output The output buffer
/// @return The success of the operation
status_t route_cipher_encode(const data_t input, size_t block_width, size_t block_height, data_t* output);

/// @brief Decodes the input data with route cipher
/// @param input The input data
/// @param block_width The width of a transposition block
/// @param block_height The height of a transposition block 
/// @param output The output buffer
/// @return The success of the operation
status_t route_cipher_decode(const data_t input, size_t block_width, size_t block_height, data_t* output);