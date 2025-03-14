#pragma once

#include <stdbool.h>

typedef struct {
    bool success;
    const char* message;
} status_t;

/// <summary>
/// Creates a success status
/// </summary>
status_t status_ok(void);

/// <summary>
/// Creates a non-success status with a message
/// </summary>
status_t status_error(const char* message);

typedef struct {
    bool success;
    const char* message;
    void* data;
} result_t;

// Denotes the data type of a result struct
#define RESULT(type) result_t

/// <summary>
/// Creates a success result with data
/// </summary>
result_t result_ok(void* data);

/// <summary>
/// Creates a non-success result with a message
/// </summary>
result_t result_error(const char* message);

/// <summary>
/// Converts a result struct to a status struct
/// </summary>
status_t to_status(result_t res);

/// <summary>
/// Converts a status struct to a result struct
/// </summary>
result_t to_result(status_t stat);