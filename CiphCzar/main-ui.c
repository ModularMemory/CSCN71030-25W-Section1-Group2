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
#include "algorithm.h"
#include "recipe.h"
#include "user_input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_intro() {
  printf("\n%s\n\n", LOGO);
  printf("Welcome to CyphCzar!\nPlease enter the (lowercase) letter "
         "corrseponding with your "
         "desired action below.\n");
  return;
}

static void make_recipe(app_state_t *app_state) {
  bool exit_con = false;
  algorithm_list_t alg_list = get_algorithms();
  algorithm_t *selected_alg = {0};

  do {
    char response = '\0';
    printf("\n-+-+-+-+-+ Recipe builder +-+-+-+-+-\n");
    printf("A: Return to recipe options\n");
    printf("B: View current recipe\n\n");

    for (int i = 0; i < (int)alg_list.len; i++) {
      printf("%d: %s\n", i + 1, alg_list.algorithms[i].name);
    }

    result_t raw_response = get_user_string();

    // Read error
    if (!raw_response.success) {
      fprintf(stderr, "Error: %s", raw_response.message);
    }

    // atoi fails = probably a string/char
    if (!atoi(raw_response.data)) {
      char *returned_string = raw_response.data;

      if ('a' == returned_string[0]) {
        exit_con = true;
        break;
      }

      else if ('b' == returned_string[0]) {
        print_recipe(app_state->recipe);
        break;
      }

      result_t raw_alg_response = get_algorithm_by_name(raw_response.data);

      // bad string
      if (raw_alg_response.success == false)
        printf("Error reading input string, please double check spelling and "
               "try again\n");

      else {
        selected_alg = raw_alg_response.data;
        recipe_push(app_state->recipe, *selected_alg);
      }
    } else {
      int input_symbol = atoi(raw_response.data);

      if (0 < input_symbol && input_symbol < alg_list.len) {
        result_t raw_alg_response = get_algorithm_by_index(input_symbol - 1);

        if (raw_alg_response.success == false)
          printf("Error when fetching from algorithm list.  This is a bug.\n");

        else {
          selected_alg = raw_alg_response.data;
          status_t push_status = recipe_push(app_state->recipe, *selected_alg);
          if (push_status.success)
            printf("Succesfully pushed %s\n", selected_alg->name);
        }
      } else
        printf(
            "Error reading input symbol, please double check and try again\n");
    }
  } while (exit_con == false);
  return;
}

// Unlikely to be depricated
static void edit_recipe_menu(app_state_t *app_state) {
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

// Might end up depricated, depends on how this is handled
static void execute_recipe_menu() {}

// Also might end up depricated
static void print_last_out_menu() {}

// Definitely not being depricated
static void data_options_menu(app_state_t *app_state) {
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
    }

    switch (response) {
    case 'a':
      printf("Please enter the new input string, or hit enter to cancel\n");

      if (app_state->current_input.data != NULL)
        printf("Current input string: \"%s\"\n", app_state->current_input.data);

      result_t new_input = get_user_string();

      if (!new_input.success) {
        fprintf(stderr, "Error: %s", new_input.message);
      }

      data_t new_data = create_data(new_input.data, strlen(new_input.data));
      app_state->current_input = new_data;
      break;

    case 'b':
      printf("Please enter the new output file's name, or hit enter to "
             "cancel\n");
      printf("Current output file: \"%s\"\n", app_state->filename);

      result_t new_filename = get_user_string();

      if (!new_filename.success) {
        fprintf(stderr, "Error: %s", new_filename.message);
      }

      app_state->filename = new_filename.data;
      break;

    case 'c':
      printf("Current input string: ");
      if (app_state->current_input.data != NULL)
        printf("%s\n", app_state->current_input.data);
      printf("File written to: %s\n", app_state->filename);
      break;

    case 'd':
      exit_con = true;
      break;
    }

  } while (exit_con == false);
  return;
}

// Also also might be depricated
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
      // mods, execute him
      break;

    case 'c':
      // print output
      break;

    case 'd':
      data_options_menu(app_state);

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
