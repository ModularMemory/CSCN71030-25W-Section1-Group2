#include <string.h>

#include "algorithm.h"
#include "from_base64.h"
#include "from_route_cipher.h"
#include "rot_13.h"
#include "rot_n.h"
#include "to_base64.h"
#include "to_decimal.h"
#include "to_hex.h"
#include "to_lower.h"
#include "to_route_cipher.h"
#include "to_upper.h"
#include "xor.h"

static algorithm_t algorithms[] = {
    CREATE_ALG_TO_LOWER(void),
    CREATE_ALG_TO_UPPER(void),
    CREATE_ALG_ROT_13(void),
    CREATE_ALG_ROT_N(void),
    CREATE_ALG_TO_BASE64(void),
    CREATE_ALG_FROM_BASE64(void),
    CREATE_ALG_TO_ROUTE_CIPHER(void),
    CREATE_ALG_FROM_ROUTE_CIPHER(void),
    CREATE_ALG_XOR(void),
    CREATE_ALG_TO_HEX(void),
    CREATE_ALG_TO_DECIMAL(void),
};

static size_t algorithm_count = __crt_countof(algorithms);

status_t clone_algorithm(const algorithm_t source, algorithm_t* dest) {
    result_t dest_args = clone_argument_list(source.additional_args);
    if (!dest_args.success) {
        return to_status(dest_args);
    }

    dest->name = source.name;
    dest->description = source.description;
    dest->execute = source.execute;
    dest->validate_args = source.validate_args;
    dest->additional_args = (pargument_t)dest_args.data;
    dest->reset_args = source.reset_args;

    return status_ok();
}

void destroy_algorithm(algorithm_t alg) {
    destroy_argument_list(alg.additional_args);
}

size_t get_algorithms_count(void) {
    return algorithm_count;
}

const algorithm_list_t get_algorithms(void) {
    algorithm_list_t list = { 
        .algorithms = algorithms,
        .len = algorithm_count 
    };

    for (size_t i = 0; i < list.len; i++) {
        list.algorithms[i].reset_args(&algorithms[i]);
    }

    return list;
}

RESULT(algorithm_t) get_algorithm_by_index(int index) {
    algorithm_list_t list = get_algorithms();

    if (index < 0 || index >= list.len) {
        return result_error("Algorithm index out of bounds.");
    }

    return result_ok(&list.algorithms[index]);
}

RESULT(algorithm_t) get_algorithm_by_name(const char* name) {
    algorithm_list_t list = get_algorithms();

    for (size_t i = 0; i < list.len; i++) {
        algorithm_t* current = &list.algorithms[i];
        if (_stricmp(name, current->name) == 0) {
            return result_ok(current);
        }
    }

    return result_error("Algorithm not found.");
}
