#include "make_recipe.h"

void make_recipe(app_state_t* app_state) {
    bool exit_con = false;
    algorithm_list_t alg_list = get_algorithms();
    algorithm_t* selected_alg = { 0 };

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
                exit_con = true;
                break;
            }

            else if ('b' == returned_string[0]) {
                print_recipe(app_state->recipe);
                break;
            }

            result_t raw_alg_response = get_algorithm_by_name(raw_response.data);

            // bad string
            if (raw_alg_response.success == false)
                printf("Error reading input string, please double check spelling and "
                    "try again\n");

            else {
                selected_alg = raw_alg_response.data;
                recipe_push(app_state->recipe, *selected_alg);
            }
        }
        else {
            int input_symbol = atoi(raw_response.data);

            if (0 < input_symbol && input_symbol < alg_list.len) {
                result_t raw_alg_response = get_algorithm_by_index(input_symbol - 1);

                if (raw_alg_response.success == false)
                    printf("Error when fetching from algorithm list.  This is a bug.\n");

                else {
                    selected_alg = raw_alg_response.data;
                    status_t push_status = recipe_push(app_state->recipe, *selected_alg);
                    if (push_status.success)
                        printf("Succesfully pushed %s\n", selected_alg->name);
                }
            }
            else
                printf(
                    "Error reading input symbol, please double check and try again\n");
        }
    } while (exit_con == false);
    return;
}