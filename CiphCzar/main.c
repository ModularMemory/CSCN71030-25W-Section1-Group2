#include "app_state.h"
#include "main_ui.h"
#include "recipe.h"
#include "utils.h"

//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
//#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

int main(void) {
    // TEMPS!!!
    bool TEMP_QUIET = false;
    char* TEMP_OUTPUT_PATH = NULL;

    app_state_t app_state = { 0 };
    status_t populate_stat = create_app_state(&app_state, TEMP_QUIET, TEMP_OUTPUT_PATH);
    if (!populate_stat.success) {
        fprintf(stderr, "Error: %s", populate_stat.message);
        return 1;
    }

    // Run REPL
    print_intro();
    main_menu(&app_state);

    // Free memory
    destroy_algorithm_list();
    destroy_app_state(app_state);

    //_CrtDumpMemoryLeaks();

    return 0;
}
