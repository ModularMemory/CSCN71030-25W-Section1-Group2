#include "app_args.h"
#include "app_state.h"
#include "executor.h"
#include "main_ui.h"
#include "recipe.h"
#include "utils.h"

//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
//#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

int main(int argc, const char** argv) {
    app_args_t args = { 0 };
    if (!parse_app_arguments(argc, argv, &args)) {
        return 1;
    }

    app_state_t app_state = { 0 };
    status_t populate_stat = create_app_state(&app_state, args);
    if (!populate_stat.success) {
        fprintf(stderr, "Error: %s", populate_stat.message);
        return 1;
    }

    if (!app_state.quiet) {
        // Run REPL
        print_intro();
        main_menu(&app_state);
    }
    else {
        execute_recipe(&app_state);
        // TODO: Write result to output file
    }

    // Free memory
    destroy_algorithm_list();
    destroy_app_state(app_state);

    //_CrtDumpMemoryLeaks();

    return 0;
}
