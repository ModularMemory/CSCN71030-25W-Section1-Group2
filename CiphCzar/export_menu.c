#include "edit_recipe.h"
#include "user_input.h"
#include "fileIO.h"

#include <ctype.h>
#include <stdio.h>

void export_menu(const app_state_t state) {
    while (1) {
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
            write_data(state.output_file, state.current_output);
            break;

        case 'b':
            write_recipe(state.output_file, state.recipe);
            break;

        case 'c':
            return;
        }
    }
}