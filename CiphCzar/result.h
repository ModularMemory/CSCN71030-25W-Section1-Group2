#pragma once

#include <stdbool.h>

typedef struct {
    bool success;
    void* data;
    const char* message;
} result_t;

/// <summary>
/// Creates a success result with optional data
/// </summary>
result_t result_ok(void* data);

/// <summary>
/// Creates a non-success result with a message
/// </summary>
result_t result_error(const char* message);