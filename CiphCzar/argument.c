#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "argument.h"
#include "utils.h"

static RESULT(pargument_t) create_arg(const char* description, argument_type_t arg_type, argument_union_t arg_union) {
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

    argument_union_t arg_union = (argument_union_t) { .integer = initial_val };
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

    argument_union_t arg_union = (argument_union_t) { .fp = initial_val };
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

    argument_union_t arg_union = (argument_union_t) { .string = (char*)copied_string.data };
    result_t res = create_arg(description, STRING_ARG, arg_union);
    if (!res.success) {
        return to_status(res);
    }

    assert(res.data);
    append_arg(list, (pargument_t)res.data);

    return status_ok();
}

RESULT(pargument_t) clone_argument_list(const pargument_t source_list) {
    pargument_t new_list = NULL;

    pargument_t source_current = source_list;
    while (source_current) {
        status_t append_stat;
        switch (source_current->arg_type) {
        case INTEGER_ARG:
            append_stat = append_integer_arg(&new_list, source_current->description, source_current->arg_union.integer);
            break;
        case FLOAT_ARG:
            append_stat = append_float_arg(&new_list, source_current->description, source_current->arg_union.fp);
            break;
        case STRING_ARG:
            append_stat = append_string_arg(&new_list, source_current->description, source_current->arg_union.string);
            break;
        default:
            append_stat = status_error("Unknown arg type.");
            break;
        }

        if (!append_stat.success) {
            destroy_argument_list(new_list);
            return to_result(append_stat);
        }

        source_current = source_current->next;
    }

    return result_ok(new_list);
}

void print_argument(const pargument_t arg) {
    printf("%s ", arg->description);

    switch (arg->arg_type) {
    case INTEGER_ARG:
        printf("(Integer) - %d", arg->arg_union.integer);
        break;
    case FLOAT_ARG:
        printf("(Float) - %f", arg->arg_union.fp);
        break;
    case STRING_ARG:
        printf("(String) - %s", arg->arg_union.string);
        break;
    default:
        printf("(Unknown Type)");
        break;
    }
}

void destroy_argument(pargument_t arg) {
    if (arg->arg_type == STRING_ARG) {
        free(arg->arg_union.string);
    }

    free(arg);
}

void destroy_argument_list(pargument_t list) {
    pargument_t current = list;
    while (current) {
        pargument_t temp = current->next;
        destroy_argument(current);
        current = temp;
    }
}
