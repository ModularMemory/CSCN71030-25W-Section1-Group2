#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

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

status_t print_data(const data_t data) {
    char c = '\0';
    for (int i = 0; i < data.len; i++) {
        c = data.data[i];

        if (!isprint(c)) printf("\x1b[31m0\x1b[0m");
        else printf("%c", c);
    }
}