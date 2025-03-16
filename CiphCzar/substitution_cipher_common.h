#pragma once

#include "data.h"

status_t run_substitution(const data_t input, void* state, char (*char_proc)(char input, size_t i, void* state), data_t* output);