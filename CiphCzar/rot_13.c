#include <assert.h>
#include <stdlib.h>

#include "rot_13.h"
#include "rot_common.h"
#include "utils.h"

status_t rot_13_execute(const data_t input, const pargument_t args, data_t* output) {
    // Alloc output
    result_t out_res = allocate_string(input.len);
    if (!out_res.success) {
        return to_status(out_res);
    }

    assert(out_res.data);
    char* out_data = out_res.data;

    // Run rotation
    rotate_impl(input.data, out_data, input.len, true, true, false, 13);

    *output = create_data(out_data, input.len);

    return status_ok();
}

status_t rot_13_validate_args(const pargument_t args) {
    return status_ok();
}

void rot_13_reset_args(algorithm_t* alg) {}
