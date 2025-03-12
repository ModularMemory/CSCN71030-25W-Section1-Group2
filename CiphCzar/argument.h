#pragma once

typedef enum {
    INTEGER_ARG,
    STRING_ARG,
    FLOAT_ARG
} argument_type_t;

typedef struct argument {
    struct argument* next;
    char* arg_description;
    argument_type_t arg_type;
    arugment_union_t arg_union;
} argument_t;

typedef union {
    int integer;
    char* string;
    float fp;
} arugment_union_t;