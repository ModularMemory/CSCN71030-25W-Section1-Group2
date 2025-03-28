#include "edit_recipe.h"
#include "user_input.h"
#include "fileIO.h"
#include "colour_codes.h"

#include <ctype.h>
#include <stdio.h>

void export_menu(const app_state_t state) {
    while (1) {
        status_t write_state = { 0 };
        char response = '\0';

        printf("\n-+-+-+-+-+ Export options +-+-+-+-+-\n");
        printf(CYAN "A: " RESET "Write output to file\n");
        printf(CYAN "B: " RESET "Write recipe to file\n");
        printf(RED "C: " RESET "Return to main menu\n\n");

        while ('a' > response || 'c' < response) {
            get_user_char(&response);
            response = tolower(response);
        }

        switch (response) {
        case 'a':
            if (!state.output_file) {
                printf(RED "Error: " RESET "No data output file set, please set one and try again\n");
                break;
            }

            write_state = write_data(state.output_file, state.current_output);
            if (!write_state.success) fprintf(stderr, RED "Error: " RESET "%s\n" , write_state.message);
            break;

        case 'b':
            if (!state.output_recipe_file) {
                printf(RED "Error: " RESET "No recipe output file set, please set one and try again\n");
                break;
            }

            write_state = write_recipe(state.output_recipe_file, state.recipe);
            if (!write_state.success) fprintf(stderr, RED "Error: " RESET "% s\n", write_state.message);
            break;

        case 'c':
            return;
        }
    }
}