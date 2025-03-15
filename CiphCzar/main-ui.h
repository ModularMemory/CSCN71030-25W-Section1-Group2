#pragma once
#include "data.h"
#include "recipe.h"
#include "status_result.h"

#include <stddef.h>

typedef struct {
  data_t current_input;
  bool quiet;
  char *filename;
  recipe_t recipe;
} app_state_t;

void print_intro();

void print_main_menu(app_state_t *app_state);
