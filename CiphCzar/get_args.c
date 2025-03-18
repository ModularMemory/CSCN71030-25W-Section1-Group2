#include "get_args.h"
#include "user_input.h"

#include <stdio.h>

status_t get_algo_args(algorithm_t* alg) {
    if (alg->additional_args == NULL) {
        return status_ok();
    }

    pargument_t cur = alg->additional_args;
    while (1) {
        switch (cur->arg_type) {
        case INTEGER_ARG:
            printf("\nPlease input a value for %s (integer, default: %d)\n", cur->description, cur->arg_union.integer);

            int user_int;
            status_t get_int_status = get_user_int(&user_int);
            if (!get_int_status.success) {
                fprintf(stderr, "Error: %s\nUsing default arg.\n", get_int_status.message);
                break;
            }

            cur->arg_union = (argument_union_t) { .integer = user_int };
            break;

        case STRING_ARG:
            printf("\nPlease input a value for %s (string, default: %s)\n", cur->description, cur->arg_union.string);

            result_t get_str_result = get_user_string();
            if (!get_str_result.success) {
                fprintf(stderr, "Error: %s", get_str_result.message);
                return status_error("Error when getting user input");
            }

            cur->arg_union = (argument_union_t) { .string = get_str_result.data };
            break;

        case FLOAT_ARG:
            printf("\nPlease input a value for %s (float, default: %.3f)\n", cur->description, cur->arg_union.fp);

            float user_flt;
            status_t get_flt_status = get_user_flt(&user_flt);
            if (!get_flt_status.success) {
                fprintf(stderr, "Error: %s\nUsing default arg.\n", get_flt_status.message);
                break;
            }

            cur->arg_union = (argument_union_t) { .fp = user_flt };
            break;
        }

        cur = cur->next;
        if (!cur) {
            status_t validation_stat = alg->validate_args(alg->additional_args);
            if (!validation_stat.success) {
                fprintf(stderr, "Error: %s\nPlease re-enter the arguments.\n", validation_stat.message);
                
                // Reset arguments to default value
                alg->reset_args(alg);

                // Reset iterator to first arg
                cur = alg->additional_args;

                continue;
            }

            break;
        }
    }

    return status_ok();
}
