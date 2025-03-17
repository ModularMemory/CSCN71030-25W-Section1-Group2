#include "edit_recipe.h"
#include "make_recipe.h"

void edit_recipe_menu(app_state_t* app_state) {
    do {
        char response = '\0';
        printf("\n-+-+-+-+-+ Recipe options +-+-+-+-+-\n");
        printf("A: Remake recipe\n");
        printf("B: View current recipe\n");
        printf("C: View current recipe w/ args\n");
        printf("D: Delete current recipe\n");
        printf("E: Return to main menu\n\n");

        while ('a' > response || 'e' < response) {
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
            print_recipe_long(app_state->recipe);
            break;

        case 'd':
            // adding a semicolon gets intellisense to stop complaining about nothing so :p
            ;result_t recipe_remake = create_recipe();
            if (!recipe_remake.success) {
                fprintf(stderr, "Error on recipe clear: %s\nRecipe left unchanged", recipe_remake.message);
                break;
            }

            recipe_t wiped_recipe = recipe_remake.data;

            destroy_recipe(app_state->recipe);
            app_state->recipe = wiped_recipe;
            break;

        case 'e':
            return;
        }

    } while (1);
}