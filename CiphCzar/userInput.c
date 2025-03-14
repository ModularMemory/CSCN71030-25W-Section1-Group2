#include "userInput.h"
#include "utils.h"
    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VAR_STR_STARTING_LEN 5
#define VAR_STR_GROW_FACTOR 2
#define NULL_TERMINATOR_LEN 1
#define NEWLINE_LEN 1

// https://stackoverflow.com/a/7898516
static void flushStdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

status_t getUserInt(int* userInt) {
    if (scanf_s("%d", userInt) != 1) {
        fprintf(stderr, "Error: Invalid input.\n");
        return 1;
    }

    flushStdin();

    return 0;
}

status_t getUserFlt(float* userFlt) {
    if (scanf_s("%f", userFlt) != 1) {
        fprintf(stderr, "Error: Invalid input.\n");
        return 1;
    }

    flushStdin();

    return 0;
}

status_t getUserChar(char* userChar) {
    int c = getchar();
    if (c == EOF) {
        fprintf(stderr, "Error: Unexpected EOF.\n");
        return 1;
    }

    // If we got a newline, then flushing will require reading another newline,
    // which means the user will need to press enter again, which is not ideal.
    if (c != '\n') {
        flushStdin();
    }

    *userChar = (char)c;
    return 0;
}

char* getUserString(void) {
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
            fprintf(stderr, "Failed to allocate %zu bytes.\n", allocSize);
            return NULL;
        }

        // Read string contents
        if (!fgets(str + oldLen, (int)(newLen - oldLen), stdin)) {
            fprintf(stderr, "An unknown error occurred, or EOF was reached unexpectedly while reading string contents.\n");
            free(str);
            return NULL;
        }

        if (fgetpos(stdin, &pos) != 0) {
            fprintf(stderr, "An unknown error occurred while checking stdin pos.\n");
        }
    } while ((size_t)pos != strlen(str) + NEWLINE_LEN);

    str[strcspn(str, "\n")] = '\0'; // Trim newline

    return str;
}