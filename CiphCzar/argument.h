#pragma once

/*

#include <stdbool.h>

#include "result.h"

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
    struct argument* next;
    const char* description;
    argument_type_t arg_type;
    argument_union_t arg_union;
} argument_t, *pargument_t;

result_t append_integer_arg(pargument_t* list, const char* description, int initial_val);

result_t append_float_arg(pargument_t* list, const char* description, float initial_val);

result_t append_string_arg(pargument_t* list, const char* description, char* initial_val);

void destroy_argument_list(pargument_t list);

*/