#pragma once

#include <stddef.h>
#include "status_result.h"

status_t getUserFlt(int* userInt);

status_t getUserFlt(float* userFlt);

status_t getUserChar(char* userChar);

char* getUserString(void);