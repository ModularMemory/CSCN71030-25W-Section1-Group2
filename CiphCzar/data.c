#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
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

void print_data(const data_t data) {
    bool wrote_unprintable = false;

    for (int i = 0; i < data.len; i++) {
        char c = data.data[i];

        if (!iscntrl((unsigned char)c)) {
            // If the char isn't a control char, print it
            printf("%c", c);
        }
        else {
            // Else print a substitution
            wrote_unprintable = true;
            printf("\x1b[31m0\x1b[0m");
        }
    }

    printf("\n");
    if (wrote_unprintable) {
        printf("Buffer contained unprintable characters. These have been substituted with \x1b[31m0\x1b[0m.\n");
    }
}