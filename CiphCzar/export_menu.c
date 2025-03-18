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
        printf("c: Return to main menu\n\n");

        while ('a' > response || 'c' < response) {
            get_user_char(&response);
            response = tolower(response);
        }

        switch (response) {
        case 'a':
            write_state = write_data(state.output_file, state.current_output);
            if (!write_state.success) fprintf(stderr, "%s", write_state.message);
            break;

        case 'b':
            write_state = write_recipe(state.output_file, state.recipe);
            if (!write_state.success) fprintf(stderr, "%s", write_state.message);
            break;

        case 'c':
            return;
        }
    }
}