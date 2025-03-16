#include <assert.h>

#include "substitution_cipher_common.h"
#include "utils.h"

status_t run_substitution(const data_t input, void* state, char (*substitute_proc)(char input, size_t i, void* state), data_t* output) {
    // Alloc output
    result_t out_res = allocate_string(input.len);
    if (!out_res.success) {
        return to_status(out_res);
    }

    assert(out_res.data);
    char* out_data = out_res.data;

    // Run substitution
    for (size_t i = 0; i < input.len; i++) {
        out_data[i] = substitute_proc(input.data[i], i, state);
    }

    *output = create_data(out_data, input.len);

    return status_ok();
}
