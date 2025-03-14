#include <stddef.h>

#include "status_result.h"

status_t status_ok(void) {
    return (status_t) { .success = true, .message = "Ok" };
}

status_t status_error(const char* message) {
    return (status_t) { .success = false, .message = message };
}

result_t result_ok(void* data) {
    return (result_t) { .success = true, .message = "Ok", .data = data };
}

result_t result_error(const char* message) {
    return (result_t) { .success = false, .message = message, .data = NULL };
}

status_t to_status(result_t res) {
    return (status_t) { .success = res.success, .message = res.message };
}

result_t to_result(status_t stat) {
    return (result_t) { .success = stat.success, .message = stat.message };
}
