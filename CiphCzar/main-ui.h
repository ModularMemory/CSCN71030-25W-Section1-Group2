#pragma once
#include "algorithm.h"
#include "recipe.h"
#include "user_input.h"
#include "data.h"
#include "status_result.h"

#include "data_options.h"
#include "edit_recipe.h"
#include "make_recipe.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef struct {
  data_t current_input;
  bool quiet;
  char *filename;
  recipe_t recipe;
} app_state_t;

void print_intro();

void print_main_menu(app_state_t *app_state);
