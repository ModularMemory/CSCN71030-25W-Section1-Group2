#pragma once

#include "status_result.h"

#include <stddef.h>

RESULT(char*) allocate_string(size_t length);

RESULT(char*) clone_string(const char* origin);

const char* get_file_name(const char* path);