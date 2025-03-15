#pragma once
#include <stddef.h>
#include "status_result.h"
#include "data.h"


void printIntro();

void printMainMenu();

typedef struct {
	data_t current_input;
	char* filename;
	bool quiet;

} app_state_t;
