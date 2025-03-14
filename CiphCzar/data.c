#include <stdlib.h>
#include <string.h>

#include "data.h"

data_t create_data(char* data, size_t len) {
    return (data_t) { .data = data, .len = len };
}

status_t clone_data(const data_t source, data_t* dest) {
    char* data = (char*)malloc(source.len);
    if (!data) {
        return status_error("Failed to allocate data clone buffer.");
    }

    memcpy_s(data, source.len, source.data, source.len);

    *dest = create_data(data, source.len);

    return status_ok();
}