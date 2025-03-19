#include "app_args.h"
#include "app_state.h"
#include "executor.h"
#include "fileIO.h"
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

    //_CrtSetBreakAlloc(106);

    app_state_t app_state = { 0 };
    status_t populate_stat = create_app_state(&app_state, args);
    if (!populate_stat.success) {
        fprintf(stderr, "Error: %s", populate_stat.message);
        return 1;
    }

    if (!app_state.headless) {
        // Run REPL
        print_intro();
        main_menu(&app_state);
    }
    else {
        if (!execute_recipe(&app_state)) {
            destroy_algorithm_list();
            destroy_app_state(app_state);
            return 1;
        }

        status_t write_stat = write_data(app_state.output_file, app_state.current_output);
        if (!write_stat.success) {
            fprintf(stderr, "Error: %s\n", write_stat.message);
            destroy_algorithm_list();
            destroy_app_state(app_state);
            return 1;
        }
    }

    // Free memory
    destroy_algorithm_list();
    destroy_app_state(app_state);

    //_CrtDumpMemoryLeaks();

    return 0;
}
