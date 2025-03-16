#define LOGO                                                                   \
  "\x1b[31m             _______  _________  ______      ___     ___     "      \
  "\x1b[34m_________  ____________   ________    _____\n"                      \
  "\x1b[31m            /AAAAAA/ /AAAAAAAA/ /AAAAAA\\    /AA/    /AA/    "      \
  "\x1b[34m/AAAAAAAA/ /AAAAAAAAAA,*  /AAAAAAAA\\  /AAAAA\\ \n"                 \
  "\x1b[31m           /XXXXXX/ /XXXXXXXX/ /XX/  \\XX\\  /XX/    /XX/    "      \
  "\x1b[34m/XXXXXXXX/ /XXXXX,XXX,*   /XX,^^^,XX/ /XX/ \\XX\\ \n"               \
  "\x1b[31m          /oo/        /oo/    /ooo\\__/oo/ /oo/____/oo/    "        \
  "\x1b[34m/oo/            ,*oo,*    /oo/___/oo/ /oo/__/oo/ \n"                \
  "\x1b[31m         /xx/        /xx/    /xx,xxxxxx/ /xx,xxxx,xx/    "          \
  "\x1b[34m/xx/           ,*xx,*     /xxxxxxxxx/ /xx,xxxxx/ \n"                \
  "\x1b[31m        /~~/____  __/~~/__  /~~/        /~~/    /~~/    "           \
  "\x1b[34m/~~/______    ,*~~,*____  /~~/   /~~/ /~~/\\~~\\ \n"                \
  "\x1b[31m       /'''''''/ /'''''''/ /''/        /''/    /''/    "            \
  "\x1b[34m/'''''''''/  ,*'''''''''/ /''/   /''/ /''/  ^''^ \n"                \
  "\x1b[31m      /_______/ /_______/ /__/        /__/    /__/    "             \
  "\x1b[34m/_________/ ,*__________/ /__/   /__/ /__/    \\__\\ \n"            \
  "\x1b[35m  "                                                                 \
  "__________________________________________________________________________" \
  "________________________________ \n"                                        \
  " /                                                                        " \
  "                                 / \n"                                      \
  "/_________________________________________________________________________" \
  "________________________________/ \n \x1b[0m"

#include "main-ui.h"

void print_intro() {
  printf("\n%s\n\n", LOGO);
  printf("Welcome to CyphCzar!\nPlease enter the (lowercase) letter "
         "corresponding with your "
         "desired action below.\n");
  return;
}

// Might end up depricated, depends on how this is handled
static void execute_recipe(app_state_t *app_state) {
  result_t raw_enum =
      create_recipe_enumerator(app_state->recipe, app_state->current_input);

  if (!raw_enum.success) {
    fprintf(stderr, "Error: %s\n", raw_enum.message);
    return;
  }

  recipe_enumerator_t enumerator = raw_enum.data;

  if (recipe_enumerator_is_empty(enumerator)) {
    fprintf(stderr, "Recipe is empty!\n");
    return;
  }

  while (recipe_enumerator_move_next(enumerator)) {
    status_t execute_stat = recipe_enumerator_execute(enumerator);
    if (!execute_stat.success) {
      fprintf(stderr, "Error: %s\n", execute_stat.message);
    }

    result_t res = recipe_enumerator_current_result(enumerator);
    if (!res.success) {
      fprintf(stderr, "Error: %s\n", res.message);
      return;
    }

    if (app_state->current_output.data) {
      // Free previous execution result
      free(app_state->current_output.data);
    }

    const data_t *dat = (const data_t *)res.data;
    status_t clone_status = clone_data(*dat, &app_state->current_output);

    if (!clone_status.success)
      fprintf(stderr, "Error: %s\n", clone_status.message);
  }
}

// Also might end up depricated
static void print_last_out_menu() {}

// also also might be depricated
static void export_menu() {}

void print_main_menu(app_state_t *app_state) {
  bool exit_con = false;

  do {
    char response = '\0';
    printf("\n-+-+-+-+-+ Main Menu +-+-+-+-+-\n");
    printf("A: Edit recipe\n");
    printf("B: Execute recipe\n");
    printf("C: Print last output\n");
    printf("D: Data options\n");
    printf("E: Export to file\n");
    printf("F: Exit\n\n");

    while ('a' > response || 'f' < response) {
      get_user_char(&response);
    }

    switch (response) {
    case 'a':
      edit_recipe_menu(app_state);
      break;

    case 'b':
      execute_recipe(app_state);
      break;

    case 'c':
      // print output
      break;

    case 'd':
      data_options_menu(app_state);
      break;

    case 'e':
      // export to outfile
      break;

    case 'f':
      exit_con = true;
      break;
    }

  } while (exit_con == false);
  return;
}
