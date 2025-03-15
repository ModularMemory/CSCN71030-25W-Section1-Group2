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
#include "user_input.h"
#include <stdio.h>
#include <string.h>

void print_intro() {
  printf("\n%s\n\n", LOGO);
  printf("Welcome to CyphCzar!\nPlease enter the (lowercase) letter "
         "corrseponding with your "
         "desired action below.\n\n");
  return;
}

// Unlikely to be depricated
static void edit_recipe_menu() {}

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
    printf("C: Return to main menu\n\n");

    while ('a' > response || 'c' < response) {
      get_user_char(&response);
    }

    switch (response) {
    case 'a':
        printf("Please enter the new input string, or hit enter to cancel\n");
        if (app_state->current_input.data != NULL)
            printf("Current input string: \"%s\"", app_state->current_input.data);
        result_t new_input = get_user_string();

        if (!new_input.success) {
            fprintf(stderr, "Error: %s", new_input.message);
        }

        data_t new_data = create_data(new_input.data, strlen(new_input.data));
        app_state->current_input = new_data;
        break;

    case 'b':
      // change filename
      break;

    case 'c':
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
    printf("-+-+-+-+-+ Main Menu +-+-+-+-+-\n");
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
      // create recipe
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
