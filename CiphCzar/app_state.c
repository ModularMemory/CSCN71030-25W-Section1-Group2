#include <stdlib.h>
#include <string.h>

#include "app_state.h"
#include "fileIO.h"
#include "utils.h"

status_t create_app_state(app_state_t* app_state, app_args_t args) {
    result_t rec_res = create_recipe();
    if (!rec_res.success) {
        return to_status(rec_res);
    }

    recipe_t recipe = (recipe_t)rec_res.data;

    if (args.recipe_file) {
        recipe_t new_recipe = { 0 };
        status_t read_res = read_recipe(args.recipe_file, &new_recipe);
        if (read_res.success) {
            destroy_recipe(recipe);
            recipe = new_recipe;
        }
        else {
            fprintf(stderr, "Error: Failed to read recipe from %s: %s\n", args.recipe_file, read_res.message);
        }
    }

    app_state->recipe = recipe;
    app_state->headless = args.headless;

    if (args.output_file) {
        result_t str_res = clone_string(args.output_file);
        if (!str_res.success) {
            return to_status(str_res);
        }

        app_state->output_file = (char*)str_res.data;
    }

    if (args.default_input) {
        result_t str_res = clone_string(args.default_input);
        if (!str_res.success) {
            return to_status(str_res);
        }

        char* str = (char*)str_res.data;
        app_state->current_input = create_data(str, strlen(str));
    }
    else if (args.input_file) {
        data_t data = { 0 };
        status_t data_stat = read_data(args.input_file, &data);
        if (!data_stat.success) {
            return data_stat;
        }

        app_state->current_input = data;
    }

    return status_ok();
}

void destroy_app_state(app_state_t app_state) {
    if (app_state.current_input.data)
        free(app_state.current_input.data);

    if (app_state.current_output.data)
        free(app_state.current_output.data);

    if (app_state.output_file)
        free(app_state.output_file);

    if (app_state.recipe)
        destroy_recipe(app_state.recipe);
}