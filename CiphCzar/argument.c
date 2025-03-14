#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "argument.h"
#include "utils.h"

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

status_t append_integer_arg(pargument_t* list, const char* description, int initial_val) {
    if (!list) {
        return status_error("List cannot be NULL!");
    }

    argument_union_t arg_union = (argument_union_t){ .integer = initial_val };
    result_t res = create_arg(description, INTEGER_ARG, arg_union);
    if (!res.success) {
        return to_status(res);
    }

    assert(res.data);
    append_arg(list, (pargument_t)res.data);

    return status_ok();
}

status_t append_float_arg(pargument_t* list, const char* description, float initial_val) {
    if (!list) {
        return status_error("List cannot be NULL!");
    }

    argument_union_t arg_union = (argument_union_t){ .fp = initial_val };
    result_t res = create_arg(description, FLOAT_ARG, arg_union);
    if (!res.success) {
        return to_status(res);
    }

    assert(res.data);
    append_arg(list, (pargument_t)res.data);

    return status_ok();
}

status_t append_string_arg(pargument_t* list, const char* description, const char* initial_val) {
    if (!list) {
        return status_error("List cannot be NULL!");
    }

    result_t copied_string = clone_string(initial_val);
    if (!copied_string.success) {
        return to_status(copied_string);
    }
    
    argument_union_t arg_union = (argument_union_t){ .string = (char*)copied_string.data };
    result_t res = create_arg(description, STRING_ARG, arg_union);
    if (!res.success) {
        return to_status(res);
    }

    assert(res.data);
    append_arg(list, (pargument_t)res.data);

    return status_ok();
}

void destroy_argument(pargument_t arg) {
    if (arg->arg_type == STRING_ARG) {
        free(arg->arg_union.string);
    }

    free(arg);
}

void destroy_argument_list(pargument_t list) {
    argument_t* current = list;
    while (current) {
        argument_t* temp = current->next;
        destroy_argument(current);
        current = temp;
    }
}
