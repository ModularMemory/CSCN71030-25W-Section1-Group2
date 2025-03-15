#include "edit_recipe.h"
#include "make_recipe.h"

void edit_recipe_menu(app_state_t* app_state) {
    bool exit_con = false;

    do {
        char response = '\0';
        printf("\n-+-+-+-+-+ Recipe options +-+-+-+-+-\n");
        printf("A: Remake recipe\n");
        printf("B: View current recipe\n");
        printf("C: Return to main menu\n\n");

        while ('a' > response || 'd' < response) {
            get_user_char(&response);
        }

        switch (response) {
        case 'a':
            make_recipe(app_state);
            break;

        case 'b':
            print_recipe(app_state->recipe);
            break;

        case 'c':
            exit_con = true;
            break;
        }

    } while (exit_con == false);
    return;
}