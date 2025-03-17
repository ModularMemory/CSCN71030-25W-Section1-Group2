#include "get_args.h"
#include "user_input.h"

#include <stdio.h>

status_t get_algo_args(algorithm_t *alg) {
  if (alg->additional_args == NULL)
    return status_ok();

  pargument_t cur = alg->additional_args;
  argument_union_t arg_union;
  status_t valid_args;
  int user_int;
  float user_flt;

  while (cur != NULL) {
    switch (cur->arg_type) {
    case INTEGER_ARG:

      do {
        printf("\nPlease input a value for %s (integer, default: %d)\n",
               cur->description, cur->arg_union.integer);
        status_t get_int_status = get_user_int(&user_int);

        if (!get_int_status.success) {
          fprintf(
              stderr, "Error: %s\nUsing default arg.\n",
              get_int_status.message); // Currently this essentailly ruins the
                                       // entire algorithm if it happens :p
        }

        valid_args = alg->validate_args(alg->additional_args);
      } while (!valid_args.success);

      arg_union = (argument_union_t){ .integer = user_int };
      cur->arg_union = arg_union;
      break;

    case STRING_ARG:

      printf("\nPlease input a value for %s (string, default: %s)\n",
             cur->description, cur->arg_union.string);
      result_t get_str_result = get_user_string();

      if (!get_str_result.success) {
        fprintf(stderr, "Error: %s", get_str_result.message);
        return status_error("Error when getting user input");
      }
      arg_union = (argument_union_t){.string = get_str_result.data};
      cur->arg_union = arg_union;
      break;

    case FLOAT_ARG:

      printf("\nPlease input a value for %s (float, default: %f)\n",
             cur->description, cur->arg_union.fp);
      status_t get_flt_status = get_user_flt(&user_flt);

      if (!get_flt_status.success) {
        fprintf(stderr, "Error: %s", get_flt_status.message);
        return status_error("Error when getting user input");
      }
      arg_union = (argument_union_t){.fp = user_flt};
      cur->arg_union = arg_union;
      break;
    }

    cur = cur->next;
  }

  return status_ok();
}
