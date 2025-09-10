#include <string.h>


int num_of_symbols(char* s[], int size) {
    if (size == 0) { return 0; }
    return strlen(s[0]) + num_of_symbols(s + 1, size - 1);
}