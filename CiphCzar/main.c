#include "main-ui.h"
#include "recipe.h"

#include <stdbool.h>

int main(void) {
  app_state_t app_state = {0};
  result_t rec = create_recipe();
  app_state.recipe = rec.data;
  app_state.quiet = false;
  app_state.filename = "output";

  // TEMPS!!!
  bool QUIET_BOOL_PLACEHOLDER = false;
  bool NAME_GIVEN = false;

  // Plug it in when arg passing is implemented
  if (QUIET_BOOL_PLACEHOLDER == true)
    app_state.quiet = true;
  if (NAME_GIVEN == true)
    app_state.filename = "put the filename given in arg here";

  print_intro();
  print_main_menu(&app_state);

  return 0;
}
