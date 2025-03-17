#pragma once

#include "status_result.h"

status_t get_user_int(int* user_int);

status_t get_user_flt(float* user_flt);

status_t get_user_char(char* user_char);

RESULT(char*) get_user_string(void);