#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../include/common.h"

// Memory management functions
void *safe_malloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void *safe_realloc(void *ptr, size_t size) {
    void *new_ptr = realloc(ptr, size);
    if (new_ptr == NULL) {
        fprintf(stderr, "Error: Memory reallocation failed\n");
        exit(EXIT_FAILURE);
    }
    return new_ptr;
}

char *safe_strdup(const char *str) {
    char *dup = strdup(str);
    if (dup == NULL) {
        fprintf(stderr, "Error: String duplication failed\n");
        exit(EXIT_FAILURE);
    }
    return dup;
}

// Utility functions for Kannada character handling
// bool is_kannada_digit(uint32_t ch) {
//     return (ch >= 0x0CE6 && ch <= 0x0CEF);
// }

// bool is_kannada_letter(uint32_t ch) {
//     return ((ch >= 0x0C80 && ch <= 0x0CFF) || (ch >= 0x1CD0 && ch <= 0x1CFA));
// }

// int kannada_digit_to_int(uint32_t ch) {
//     if (is_kannada_digit(ch)) {
//         return ch - 0x0CE6;
//     }
//     return -1;  // Invalid Kannada digit
// }

// UTF-8 handling functions
size_t utf8_strlen(const char *str) {
    size_t len = 0;
    while (*str) {
        if ((*str & 0xC0) != 0x80) {
            len++;
        }
        str++;
    }
    return len;
}

uint32_t utf8_nextchar(const char **ptr) {
    const unsigned char *str = (const unsigned char *)*ptr;
    uint32_t ch = 0;
    int bytes = 0;

    if (*str < 0x80) {
        ch = *str++;
        bytes = 1;
    } else if (*str < 0xE0) {
        ch = (*str++ & 0x1F) << 6;
        ch |= *str++ & 0x3F;
        bytes = 2;
    } else if (*str < 0xF0) {
        ch = (*str++ & 0x0F) << 12;
        ch |= (*str++ & 0x3F) << 6;
        ch |= *str++ & 0x3F;
        bytes = 3;
    } else {
        ch = (*str++ & 0x07) << 18;
        ch |= (*str++ & 0x3F) << 12;
        ch |= (*str++ & 0x3F) << 6;
        ch |= *str++ & 0x3F;
        bytes = 4;
    }

    *ptr += bytes;
    return ch;
}