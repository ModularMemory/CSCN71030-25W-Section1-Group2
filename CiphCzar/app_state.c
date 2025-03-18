#include <stdlib.h>

#include "app_state.h"
#include "utils.h"

status_t create_app_state(app_state_t* app_state, bool quiet, const char* output_file) {
    result_t rec_res = create_recipe();
    if (!rec_res.success) {
        return to_status(rec_res);
    }

    app_state->recipe = rec_res.data;
    app_state->quiet = quiet;

    if (output_file) {
        result_t str_res = clone_string(output_file);
        if (!str_res.success) {
            return to_status(str_res);
        }

        app_state->output_file = (char*)(str_res.data);
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