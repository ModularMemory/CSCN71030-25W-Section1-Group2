#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "argument.h"

static pargument_t create_arg(const char* description, argument_type_t arg_type, argument_union_t arg_union) {
    pargument_t arg = (pargument_t)malloc(sizeof(argument_t));
    if (!arg) {
        fprintf(stderr, "Error: Failed to allocate new argument.\n");
        return NULL;
    }

    arg->next = NULL;
    arg->description = description;
    arg->arg_type = arg_type;
    arg->arg_union = arg_union;

    return arg;
}

static void append_arg(pargument_t* list, pargument_t arg) {
    assert(list);
    assert(!arg->next);

    // List is empty
    if (!*list) {
        *list = arg;
        return;
    }

    // Append to end of list
    pargument_t current = *list;
    while (current->next) {
        current = current->next;
    }

    current->next = arg;
}

bool append_integer_arg(pargument_t* list, const char* description, int initial_val) {
    if (!list) {
        fprintf(stderr, "Error: List cannot be NULL!\n");
        return false;
    }

    argument_union_t arg_union = (argument_union_t){ .integer = initial_val };
    pargument_t arg = create_arg(description, INTEGER_ARG, arg_union);
    if (!arg) {
        return false;
    }

    append_arg(list, arg);
}

bool append_float_arg(pargument_t* list, const char* description, float initial_val) {
    if (!list) {
        fprintf(stderr, "Error: List cannot be NULL!\n");
        return false;
    }

    argument_union_t arg_union = (argument_union_t){ .fp = initial_val };
    pargument_t arg = create_arg(description, FLOAT_ARG, arg_union);
    if (!arg) {
        return false;
    }

    append_arg(list, arg);
}

bool append_string_arg(pargument_t* list, const char* description, char* initial_val) {
    if (!list) {
        fprintf(stderr, "Error: List cannot be NULL!\n");
        return false;
    }

    // TODO: Copy the string?
    argument_union_t arg_union = (argument_union_t){ .string = initial_val };
    pargument_t arg = create_arg(description, STRING_ARG, arg_union);
    if (!arg) {
        return false;
    }

    append_arg(list, arg);
}

void destroy_argument_list(pargument_t list) {
    argument_t* current = list;
    while (current) {
        argument_t* temp = current->next;
        free(current);
        current = temp;
    }
}