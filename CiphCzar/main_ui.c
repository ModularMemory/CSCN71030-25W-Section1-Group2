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

#include "app_state.h"
#include "data_options.h"
#include "edit_recipe.h"
#include "executor.h"
#include "main_ui.h"
#include "user_input.h"
#include "export_menu.h"

#include <ctype.h>
#include <stdio.h>

void print_intro() {
  printf("\n%s\n\n", LOGO);
  printf("Welcome to CyphCzar!\nPlease enter the letter "
         "corresponding with your "
         "desired action below.\n");
  return;
}

void main_menu(app_state_t* app_state) {
  bool exit_con = false;

  do {
    char response = '\0';
    printf("\n-+-+-+-+-+ Main Menu +-+-+-+-+-\n");
    printf("A: Edit recipe\n");
    printf("B: Execute recipe\n");
    printf("C: Print recipe result\n");
    printf("D: Data options\n");
    printf("E: Export to file\n");
    printf("F: Exit\n\n");

    while ('a' > response || 'f' < response) {
      get_user_char(&response);
      response = tolower(response);
    }

    switch (response) {
    case 'a':
      edit_recipe_menu(app_state);
      break;

    case 'b':
      execute_recipe(app_state);
      break;

    case 'c':
      if (!app_state->current_output.data) {
        printf("A recipe has not been executed yet.");
        break;
      }

      printf("Last recipe result (as text)\n");
      print_data(app_state->current_output);
      break;

    case 'd':
      data_options_menu(app_state);
      break;

    case 'e':
      export_menu(*app_state);
      break;

    case 'f':
      exit_con = true;
      break;
    }

  } while (exit_con == false);
  return;
}
