#pragma once

#include <stddef.h>

#include "status_result.h"

/// <summary>
/// Stores a pointer to a buffer + the length of the buffer.
/// </summary>
typedef struct {
    char* data;
    size_t len;
} data_t;

data_t create_data(char* data, size_t len);

status_t clone_data(const data_t source, data_t* dest);