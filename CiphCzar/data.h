#pragma once

#include <stddef.h>

/// <summary>
/// Stores a pointer to a buffer + the length of the buffer.
/// 
/// Does not handle allocation!
/// </summary>
typedef struct {
    char* data;
    size_t len;
} data_t;

data_t create_data(char* data, size_t len);