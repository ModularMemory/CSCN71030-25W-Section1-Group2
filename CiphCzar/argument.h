#pragma once

#include <stdbool.h>

#include "status_result.h"

typedef enum {
    INTEGER_ARG,
    STRING_ARG,
    FLOAT_ARG
} argument_type_t;

typedef union {
    int integer;
    float fp;
    char* string;
} argument_union_t;

typedef struct argument {
    /// @brief The next argument in the list, or NULL.
    struct argument* next;
    /// @brief A short description of the argument.
    const char* description;
    /// @brief The type of the argument.
    argument_type_t arg_type;
    /// @brief The value of the argument.
    argument_union_t arg_union;
} argument_t, *pargument_t;

status_t append_integer_arg(pargument_t* list, const char* description, int initial_val);

status_t append_float_arg(pargument_t* list, const char* description, float initial_val);

status_t append_string_arg(pargument_t* list, const char* description, const char* initial_val);

RESULT(pargument_t) clone_argument_list(const pargument_t source_list);

void print_argument(const pargument_t arg);

void destroy_argument(pargument_t arg);

void destroy_argument_list(pargument_t list);