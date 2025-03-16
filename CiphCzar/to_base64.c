#include "base64_common.h"
#include "to_base64.h"

status_t to_base64_execute(const data_t input, const pargument_t args, data_t* output) {
    // Run Base64 encode
    data_t out_data = { 0 };
    status_t stat = base64_encode(input, &out_data);
    if (!stat.success) {
        return stat;
    }

    *output = out_data;

    return status_ok();
}

status_t to_base64_validate_args(const pargument_t args) {
    return status_ok();
}

void to_base64_reset_args(algorithm_t* alg) {}
