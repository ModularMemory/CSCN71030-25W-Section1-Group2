#pragma once

#include <stdbool.h>

typedef struct {
    bool success;
    const char* message;
} result_t;

result_t result_ok(void);

result_t result_error(const char* message);