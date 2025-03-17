#include "data_options.h"
#include "user_input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void data_options_menu(app_state_t* app_state) {
    char exit_con = false;

    do {
        char response = '\0';
        printf("\n-+-+-+-+-+ Data options +-+-+-+-+-\n");
        printf("A: Change input string\n");
        printf("B: Change output file name \n");
        printf("C: View current input/output name\n");
        printf("D: Return to main menu\n\n");

        while ('a' > response || 'd' < response) {
            get_user_char(&response);
            response = tolower(response);
        }

        switch (response) {
        case 'a':
            printf("Please enter the new input string, or hit enter to cancel\n");

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
            printf("Please enter the new output file's name, or hit enter to cancel\n");
            printf("Current output file: \"%s\"\n", app_state->output_file);

            result_t new_filename = get_user_string();

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
            if (app_state->current_input.data != NULL)
                printf("Current input string: \"%s\"\n", app_state->current_input.data);
            else 
                printf("No input string.\n");

            if (app_state->output_file != NULL)
                printf("Output file path: \"%s\"\n", app_state->output_file);
            else
                printf("No output file.\n");

            break;

        case 'd':
            exit_con = true;
            break;
        }

    } while (exit_con == false);
    return;
}
