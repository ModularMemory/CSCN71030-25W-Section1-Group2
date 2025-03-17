#pragma once

#include "status_result.h"

RESULT(char*) allocate_string(size_t length);

RESULT(char*) clone_string(const char* origin);