#include "data.h"

data_t create_data(char * data,size_t len) {
    return (data_t) { .data = data, .len = len };
}
