//  Хэш-функции и функции сравнения для интов и строк

#include <stdio.h>


#define ht_int_hash(x) ((size_t) (x))
#define ht_int_eq(a, b) ((a) == (b))

static inline size_t ht_str_hash(const char *s) {
    size_t h = (size_t) *s;
    if (h) {
        for (++s; *s; ++s) {
            h = (h << 5) - h + (size_t) *s;
        }
    }
    return h;
}

#define ht_str_eq(a, b) (strcmp((a), (b)) == 0)