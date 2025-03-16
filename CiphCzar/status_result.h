#pragma once

#include <stdbool.h>

typedef struct {
    /// @brief The success of the operation
    bool success;
    /// @brief A compile-time string message
    const char* message;
} status_t;

/// @brief Creates a success status
status_t status_ok(void);

/// @brief Creates a non-success status with a message
status_t status_error(const char* message);

typedef struct {
    /// @brief The success of the operation
    bool success;
    /// @brief A compile-time string message
    const char* message;
    /// @brief A pointer to data produced by the operation
    void* data;
} result_t;

/// @brief Denotes the data type held by the result struct
#define RESULT(type) result_t

/// @brief Creates a success result with data
result_t result_ok(void* data);

/// @brief Creates a non-success result with a message
result_t result_error(const char* message);

/// @brief Converts a result struct to a status struct
status_t to_status(result_t res);

/// @brief Converts a status struct to a result struct
result_t to_result(status_t stat);