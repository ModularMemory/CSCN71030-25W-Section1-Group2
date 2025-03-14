#pragma once

#include <stdbool.h>
#include <stddef.h>

/// @brief Copies the chars from the source buffer to the destination buffer while rotating them as a caesar cipher
/// @param source The source buffer
/// @param dest The destination buffer
/// @param len The length of the buffers
/// @param do_lower Whether to rotate lowercase letters
/// @param do_upper Whether to rotate uppercase letters
/// @param do_num Whether to rotate numbers
/// @param rot_count The amount of places to rotate each char by
void rotate_impl(const char* source, char* dest, size_t len, bool do_lower, bool do_upper, bool do_num, int rot_count);