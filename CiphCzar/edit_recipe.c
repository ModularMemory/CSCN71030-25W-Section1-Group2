#include <ctype.h>
#include <stdio.h>

#include "edit_recipe.h"
#include "make_recipe.h"
#include "user_input.h"
#include "colour_codes.h"

void edit_recipe_menu(app_state_t* app_state) {
    do {
        char response = '\0';
        printf("\n-+-+-+-+-+ Recipe options +-+-+-+-+-\n");
        printf(YELLOW "A: " RESET "Add to recipe\n");
        printf(YELLOW "B: " RESET "View current recipe\n");
        printf(YELLOW "C: " RESET "View current recipe w/ args\n");
        printf(YELLOW "D: " RESET "Delete current recipe\n");
        printf(RED "E: " RESET "Return to main menu\n\n");

        while ('a' > response || 'e' < response) {
            get_user_char(&response);
            response = tolower(response);
        }

        switch (response) {
        case 'a':
            make_recipe(app_state);
            break;

        case 'b':
            print_recipe(app_state->recipe);
            break;

        case 'c':
            print_recipe_long(app_state->recipe);
            break;

        case 'd':
        {
            result_t recipe_remake = create_recipe();
            if (!recipe_remake.success) {
                fprintf(stderr, RED "Error on recipe clear: " RESET "%s\nRecipe left unchanged", recipe_remake.message);
                break;
            }

            recipe_t new_recipe = recipe_remake.data;

            destroy_recipe(app_state->recipe);
            app_state->recipe = new_recipe;
            break;
        }

        case 'e':
            return;
        }

    } while (1);
}