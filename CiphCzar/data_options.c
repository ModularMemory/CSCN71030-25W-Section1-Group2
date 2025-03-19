#include "data_options.h"
#include "user_input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void data_options_menu(app_state_t* app_state) {
    do {
        result_t new_filename = { 0 };
        char response = '\0';
        printf("\n-+-+-+-+-+ Data options +-+-+-+-+-\n");
        printf("A: Change input string\n");
        printf("B: Change data output file name\n");
        printf("C: Change recipe output file name\n");
        printf("D: View input string & output filenames\n");
        printf("E: Return to main menu\n\n");

        while ('a' > response || 'e' < response) {
            get_user_char(&response);
            response = tolower(response);
        }

        switch (response) {
        case 'a':
            printf("Please enter the new input string.\n");

            if (app_state->current_input.data != NULL)
                printf("Current input string: \"%s\"\n", app_state->current_input.data);

            result_t new_input = get_user_string();

            if (!new_input.success) {
                fprintf(stderr, "Error: %s", new_input.message);
                break;
            }

            if (app_state->current_input.data) {
                free(app_state->current_input.data);
            }

            data_t new_data = create_data(new_input.data, strlen(new_input.data));
            app_state->current_input = new_data;
            break;

        case 'b':
            printf("Please enter the new data output file's name.\n");
            printf("Current output file: \"%s\"\n", app_state->output_file);

           new_filename = get_user_string();

            if (!new_filename.success) {
                fprintf(stderr, "Error: %s", new_filename.message);
                break;
            }

            if (app_state->output_file) {
                free(app_state->output_file);
            }

            app_state->output_file = new_filename.data;
            break;

        case 'c':
            printf("Please enter the new recipe output file's name\n");
            printf("Current output file: \"%s\"\n", app_state->output_recipe_file);

            new_filename = get_user_string();

            if (!new_filename.success) {
                fprintf(stderr, "Error: %s", new_filename.message);
                break;
            }

            if (app_state->output_recipe_file) {
                free(app_state->output_recipe_file);
            }

            app_state->output_recipe_file = new_filename.data;
            break;

        case 'd':
            if (app_state->current_input.data != NULL)
                printf("Current input string: \"%s\"\n", app_state->current_input.data);
            else 
                printf("No input string.\n");

            if (app_state->output_file != NULL)
                printf("Output data file path: \"%s\"\n", app_state->output_file);
            else
                printf("No data output file.\n");

            if (app_state->output_recipe_file != NULL)
                printf("Output recipe data file path: \"%s\"\n", app_state->output_recipe_file);
            else
                printf("No recipe output file.\n");

            break;

        case 'e':
            return;
        }
    } while (1);
}
