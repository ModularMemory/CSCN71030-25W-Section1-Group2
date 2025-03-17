#include "executor.h"
#include "recipe_enumerator.h"

void execute_recipe(app_state_t* app_state) {
    result_t raw_enum =
        create_recipe_enumerator(app_state->recipe, app_state->current_input);
    result_t res = { 0 };

    if (!raw_enum.success) {
        fprintf(stderr, "Error: %s\n", raw_enum.message);
        return;
    }

    recipe_enumerator_t enumerator = raw_enum.data;

    if (recipe_enumerator_is_empty(enumerator)) {
        fprintf(stderr, "Recipe is empty!\n");
        return;
    }

    while (recipe_enumerator_move_next(enumerator)) {
        status_t execute_stat = recipe_enumerator_execute(enumerator);
        res = recipe_enumerator_current_result(enumerator);
        if (!execute_stat.success) {
            fprintf(stderr, "Error: %s\n", execute_stat.message);
            return;
        }
    }

    if (app_state->current_output.data) {
        // Free previous execution result
        free(app_state->current_output.data);
    }


    const data_t* dat = (const data_t*)res.data;
    status_t clone_status = clone_data(*dat, &app_state->current_output);

    if (!clone_status.success) {
        fprintf(stderr, "Error: %s\n", clone_status.message);
        return;
    }

    printf("Recipe executed successfully, check output for results!\n");
}