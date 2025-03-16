#include "user_input.h"
#include "utils.h"
    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VAR_STR_STARTING_LEN 5
#define VAR_STR_GROW_FACTOR 2
#define NULL_TERMINATOR_LEN 1
#define NEWLINE_LEN 1

// https://stackoverflow.com/a/7898516
static void flush_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

status_t get_user_int(int* user_int) {
    if (scanf_s("%d", user_int) != 1) {
        return status_error("Invalid input.");
    }

    flush_stdin();

    return status_ok();
}

status_t get_user_flt(float* user_flt) {
    if (scanf_s("%f", user_flt) != 1) {
        return status_error("Invalid input.");
    }

    flush_stdin();

    return status_ok();
}

status_t get_user_char(char* user_char) {
    int c = getchar();
    if (c == EOF) {
        return status_error("Unexpected EOF.");
    }

    // If we got a newline, then flushing will require reading another newline,
    // which means the user will need to press enter again, which is not ideal.
    if (c != '\n') {
        flush_stdin();
    }

    *user_char = (char)c;
    return status_ok();
}

RESULT(char*) get_user_string(void) {
    char* str = NULL;
    fpos_t pos = 0; 
    do {
        size_t oldLen = 0;
        size_t newLen = VAR_STR_STARTING_LEN;
        size_t allocSize;

        // Allocate string buffer
        if (!str) {
            allocSize = newLen * sizeof(char);
            str = (char*)malloc(allocSize);
        }
        else {
            oldLen = strlen(str);
            newLen = oldLen * VAR_STR_GROW_FACTOR + NULL_TERMINATOR_LEN;
            allocSize = newLen * sizeof(char);

            char* newStr = (char*)realloc(str, allocSize);
            if (!newStr) {
                free(str);
            }

            str = newStr;
        }

        // Check allocation failure
        if (!str) {
            return result_error("Failed to allocate string.");
        }

        // Read string contents
        if (!fgets(str + oldLen, (int)(newLen - oldLen), stdin)) {
            free(str);
            return result_error("EOF reached unexpectedly/unknown error.");
        }

        if (fgetpos(stdin, &pos) != 0) {
            if (str) {
                free(str);
            }

            return result_error("An unknown error occurred while checking stdin pos.");
        }
    } while ((size_t)pos != strlen(str) + NEWLINE_LEN);

    str[strcspn(str, "\n")] = '\0'; // Trim newline

    return result_ok(str);
}