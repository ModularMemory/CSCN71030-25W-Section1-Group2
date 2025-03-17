#include "app_state.h"
#include "main_ui.h"
#include "recipe.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    result_t rec = create_recipe();
    if (!rec.success) {
        fprintf(stderr, "Error: %s", rec.message);
        return 1;
    }

    app_state_t app_state = { 0 };
    app_state.recipe = rec.data;
    app_state.quiet = false;
    app_state.output_file = NULL;

    // TEMPS!!!
    bool QUIET_BOOL_PLACEHOLDER = false;
    bool NAME_GIVEN = false;

    // Plug it in when arg passing is implemented
    if (QUIET_BOOL_PLACEHOLDER == true)
        app_state.quiet = true;
    if (NAME_GIVEN == true)
        app_state.output_file = "put the filename given in arg here";

    // Run REPL
    print_intro();
    main_menu(&app_state);

    // Free memory
    destroy_algorithm_list();
    if (app_state.current_input.data) free(app_state.current_input.data);
    if (app_state.current_output.data) free(app_state.current_output.data);
    if (app_state.output_file) free(app_state.output_file);
    if (app_state.recipe) destroy_recipe(app_state.recipe);

    return 0;
}
