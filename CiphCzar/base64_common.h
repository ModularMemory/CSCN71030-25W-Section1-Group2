#pragma once

#include "data.h"
#include "status_result.h"

status_t base64_encode(const data_t input, data_t* output);

status_t base64_decode(const data_t input, data_t* output);