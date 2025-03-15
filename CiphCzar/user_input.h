#pragma once

#include <stddef.h>
#include "status_result.h"

status_t get_user_int(int* userInt);

status_t get_user_flt(float* userFlt);

status_t get_user_char(char* userChar);

RESULT(char*) get_user_string(void);