#include "make_recipe.h"

#include <stdlib.h>

void make_recipe(app_state_t* app_state) {
    algorithm_list_t alg_list = get_algorithms();
    algorithm_t* selected_alg = { 0 };
    status_t push_status;
    status_t get_arg_status;

    do {
        char response = '\0';
        printf("\n-+-+-+-+-+ Recipe builder +-+-+-+-+-\n");
        printf("A: Return to recipe options\n");
        printf("B: View current recipe\n\n");

        for (int i = 0; i < (int)alg_list.len; i++) {
            printf("%d: %s\n", i + 1, alg_list.algorithms[i].name);
        }

        result_t raw_response = get_user_string();

        // Read error
        if (!raw_response.success) {
            fprintf(stderr, "Error: %s", raw_response.message);
        }

        // atoi fails = probably a string/char
        if (!atoi(raw_response.data)) {
            char* returned_string = raw_response.data;

            if ('a' == returned_string[0]) {
                return;
            }

            else if ('b' == returned_string[0]) {
                print_recipe_long(app_state->recipe);
                continue;
            }

            result_t raw_alg_response = get_algorithm_by_name(raw_response.data);

            // bad string
            if (raw_alg_response.success == false)
                printf("Error reading input string, please double check spelling and "
                    "try again\n");

            else {
                selected_alg = raw_alg_response.data;

                get_arg_status = get_algo_args(selected_alg);

                push_status = recipe_push(app_state->recipe, *selected_alg);
                if (push_status.success)
                    printf("Successfully added %s\n", selected_alg->name);
            }
        }
        else {
            int input_symbol = atoi(raw_response.data);

            if (0 < input_symbol && input_symbol <= alg_list.len) {
                result_t raw_alg_response = get_algorithm_by_index(input_symbol - 1);

                if (raw_alg_response.success == false)
                    printf("Error when fetching from algorithm list.  This is a bug.\n");

                else {
                    selected_alg = raw_alg_response.data;

                    get_arg_status = get_algo_args(selected_alg);

                    push_status = recipe_push(app_state->recipe, *selected_alg);
                    if (push_status.success)
                        printf("\nSuccessfully added %s\n", selected_alg->name);
                }
            }
            else
                printf(
                    "Error reading input symbol, please double check and try again\n");
        }
    } while (1);
}
