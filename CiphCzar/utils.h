#pragma once

#include <stddef.h>

#include "result.h"

result_t allocate_string(size_t length);

result_t clone_string(const char* origin);