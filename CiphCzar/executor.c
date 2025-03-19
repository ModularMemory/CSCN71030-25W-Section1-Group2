#include <stdlib.h>
#include <stdio.h>

#include "executor.h"
#include "recipe_enumerator.h"

bool execute_recipe(app_state_t* app_state) {
    // If the input data is NULL then we dont execute
    if (!app_state->current_input.data) {
        printf("No input data.  Please navigate to the data options to set some.\n");
        return false;
    }

    result_t raw_enum = create_recipe_enumerator(app_state->recipe, app_state->current_input);
    if (!raw_enum.success) {
        fprintf(stderr, "Error: %s\n", raw_enum.message);
        return false;
    }
    
    recipe_enumerator_t enumerator = raw_enum.data;

    if (recipe_enumerator_is_empty(enumerator)) {
        fprintf(stderr, "Recipe is empty!\n");
        destroy_recipe_enumerator(enumerator);
        return false;
    }

    while (recipe_enumerator_move_next(enumerator)) {
        status_t execute_stat = recipe_enumerator_execute(enumerator);
        if (!execute_stat.success) {
            fprintf(stderr, "Error: %s\n", execute_stat.message);
            destroy_recipe_enumerator(enumerator);
            return false;
        }
    }

    result_t res = recipe_enumerator_current_result(enumerator);
    if (!res.success) {
        fprintf(stderr, "Error: %s\nStored result has not been updated.\n", res.message);
        destroy_recipe_enumerator(enumerator);
        return false;
    }

    if (app_state->current_output.data) {
        // Free previous execution result
        free(app_state->current_output.data);
    }

    const data_t* dat = (const data_t*)res.data;
    status_t clone_status = clone_data(*dat, &app_state->current_output);

    if (!clone_status.success) {
        fprintf(stderr, "Error: %s\nStored result has not been updated.\n", clone_status.message);
        destroy_recipe_enumerator(enumerator);
        return false;
    }
    
    printf("Recipe executed successfully, check output for results!\n");

    destroy_recipe_enumerator(enumerator);
    return true;
}