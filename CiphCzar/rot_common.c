#include "rot_common.h"

void rotate_impl(const char* source, char* dest, size_t len, bool do_lower, bool do_upper, bool do_num, int rotate_count) {
    for (size_t i = 0; i < len; i++) {
        // long long to ensure we don't overflow/underflow the type
        long long c = source[i];

        if (do_lower && c >= 'a' && c <= 'z') {
            c += rotate_count;

            // Wrap char around range
            while (c < 'a') {
                c += 26;
            }

            while (c > 'z') {
                c -= 26;
            }
        } else if (do_upper && c >= 'A' && c <= 'Z') {
            c += rotate_count;

            // Wrap char around range
            while (c < 'A') {
                c += 26;
            }

            while (c > 'Z') {
                c -= 26;
            }
        } else if (do_num && c >= '0' && c <= '9') {
            c += rotate_count;

            // Wrap char around range
            while (c < '0') {
                c += 10;
            }

            while (c > '9') {
                c -= 10;
            }
        }

        dest[i] = (char)c;
    }
}