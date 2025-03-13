#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "argument.h"

static result_t create_arg(const char* description, argument_type_t arg_type, argument_union_t arg_union) {
    pargument_t arg = (pargument_t)malloc(sizeof(argument_t));
    if (!arg) {
        return result_error("Failed to allocate new argument.");
    }

    arg->next = NULL;
    arg->description = description;
    arg->arg_type = arg_type;
    arg->arg_union = arg_union;

    return result_ok(arg);
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

result_t append_integer_arg(pargument_t* list, const char* description, int initial_val) {
    if (!list) {
        return result_error("List cannot be NULL!");
    }

    argument_union_t arg_union = (argument_union_t){ .integer = initial_val };
    result_t res = create_arg(description, INTEGER_ARG, arg_union);
    if (!res.success) {
        return res;
    }

    assert(res.data);
    append_arg(list, (pargument_t)res.data);
}

result_t append_float_arg(pargument_t* list, const char* description, float initial_val) {
    if (!list) {
        return result_error("List cannot be NULL!");
    }

    argument_union_t arg_union = (argument_union_t){ .fp = initial_val };
    result_t res = create_arg(description, FLOAT_ARG, arg_union);
    if (!res.success) {
        return res;
    }

    assert(res.data);
    append_arg(list, (pargument_t)res.data);
}

result_t append_string_arg(pargument_t* list, const char* description, char* initial_val) {
    if (!list) {
        return result_error("List cannot be NULL!");
    }

    // TODO: Copy the string?
    argument_union_t arg_union = (argument_union_t){ .string = initial_val };
    result_t res = create_arg(description, STRING_ARG, arg_union);
    if (!res.success) {
        return res;
    }

    assert(res.data);
    append_arg(list, (pargument_t)res.data);
}

void destroy_argument_list(pargument_t list) {
    argument_t* current = list;
    while (current) {
        argument_t* temp = current->next;
        free(current);
        current = temp;
    }
}
