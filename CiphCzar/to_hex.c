#include <assert.h>

#include "num_conv_common.h"
#include "to_hex.h"
#include "utils.h"

status_t to_hex_execute(const data_t input, const pargument_t args, data_t* output) {
    // Run hex conversion
    data_t out_data = { 0 };
    status_t stat = to_number_string(input, "%02X", 2, &out_data);
    if (!stat.success) {
        return stat;
    }

    *output = out_data;

    return status_ok();
}

status_t to_hex_validate_args(const pargument_t args) {
    return status_ok();
}

void to_hex_reset_args(algorithm_t* alg) {}
