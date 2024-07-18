#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// Version information
#define COMPILER_VERSION "0.1.0"
#define COMPILER_NAME "KannadaPython"

// Maximum lengths
#define MAX_IDENTIFIER_LENGTH 256
#define MAX_STRING_LENGTH 1024
#define MAX_ERROR_MESSAGE_LENGTH 512

// Error handling
typedef enum {
    ERROR_NONE,
    ERROR_LEXER,
    ERROR_PARSER,
    ERROR_SEMANTIC,
    ERROR_CODEGEN
} ErrorType;

typedef struct {
    ErrorType type;
    int line;
    char message[MAX_ERROR_MESSAGE_LENGTH];
} Error;

// Memory management
void *safe_malloc(size_t size);
void *safe_realloc(void *ptr, size_t size);
char *safe_strdup(const char *str);

// Utility functions
// bool is_kannada_digit(uint32_t ch);
// bool is_kannada_letter(uint32_t ch);
// int kannada_digit_to_int(uint32_t ch);

// UTF-8 handling
size_t utf8_strlen(const char *str);
uint32_t utf8_nextchar(const char **ptr);

// Debugging
#ifdef DEBUG
    #define DEBUG_PRINT(fmt, ...) fprintf(stderr, "DEBUG: " fmt "\n", ##__VA_ARGS__)
#else
    #define DEBUG_PRINT(fmt, ...)
#endif

#endif // COMMON_H