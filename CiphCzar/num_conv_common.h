#pragma once

#include "data.h"
#include "status_result.h"

status_t to_number_string(const data_t input, const char* format_str, unsigned int number_len, data_t* output);

status_t from_number_string(const data_t input, const char* format_str, unsigned int number_len, data_t* output);