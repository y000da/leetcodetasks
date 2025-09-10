#include <stdio.h>
#include <string.h>


void reverse(char *str, int start, int end) {
    if (start >= end) {
        return;
    }
    
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    
    reverse(str, start + 1, end - 1);
}

void reverse_string(char *str) {
    int length = strlen(str);
    if (length > 1) {
        reverse(str, 0, length - 1);
    }
}