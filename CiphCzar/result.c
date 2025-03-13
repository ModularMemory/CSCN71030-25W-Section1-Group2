#include <stddef.h>

#include "result.h"

result_t result_ok(void* data) {
    return (result_t) { .success = true, .data = data, .message = "Ok" };
}

result_t result_error(const char* message) {
    return (result_t) { .success = false, .data = NULL, .message = message };
}