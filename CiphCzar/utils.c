#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define NULL_TERMINATOR_LEN 1

result_t allocate_string(size_t length) {
    size_t allocSize = length + NULL_TERMINATOR_LEN;
    char* str = (char*)calloc(allocSize, sizeof(char));
    if (!str) {
        return result_error("Failed to allocate string.");
    }

    return result_ok(str);
}

result_t clone_string(const char* origin) {
    if (!origin) {
        return result_ok(NULL);
    }

    size_t len = strlen(origin);
    size_t allocSize = len + NULL_TERMINATOR_LEN;

    char* str = (char*)calloc(allocSize, sizeof(char));
    if (!str) {
        return result_error("Failed to allocate string.");
    }

    strncpy_s(str, allocSize, origin, len);

    return result_ok(str);
}