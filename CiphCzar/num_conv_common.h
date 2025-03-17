#pragma once

#include "data.h"
#include "status_result.h"

status_t to_number_string(const data_t input, const char* format_str, unsigned char number_len, data_t* output);