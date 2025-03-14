#pragma once

#include <stdbool.h>
#include <stddef.h>

void rotate_impl(const char* source, char* dest, size_t len, bool do_lower, bool do_upper, bool do_num, int rotate_count);