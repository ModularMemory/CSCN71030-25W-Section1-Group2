#include "edit_recipe.h"
#include "user_input.h"
#include "fileIO.h"

#include <ctype.h>
#include <stdio.h>

void export_menu(const app_state_t state) {
    while (1) {
        status_t write_state = { 0 };
        char response = '\0';

        printf("\n-+-+-+-+-+ Export options +-+-+-+-+-\n");
        printf("A: Write output to file\n");
        printf("B: Write recipe to file\n");
        printf("C: Return to main menu\n\n");

        while ('a' > response || 'c' < response) {
            get_user_char(&response);
            response = tolower(response);
        }

        switch (response) {
        case 'a':
            if (!state.output_file) {
                printf("No data output file set, please set one and try again\n");
                break;
            }

            write_state = write_data(state.output_file, state.current_output);
            if (!write_state.success) fprintf(stderr, "%s", write_state.message);
            break;

        case 'b':
            if (!state.output_recipe_file) {
                printf("No recipe output file set, please set one and try again\n");
                break;
            }

            write_state = write_recipe(state.output_recipe_file, state.recipe);
            if (!write_state.success) fprintf(stderr, "%s", write_state.message);
            break;

        case 'c':
            return;
        }
    }
}