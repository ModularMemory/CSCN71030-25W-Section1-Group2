#include <stddef.h>

#include "result.h"

result_t result_ok(void) {
    return (result_t) { .success = true, .message = "Ok" };
}

result_t result_error(const char* message) {
    return (result_t) { .success = false, .message = message };
}