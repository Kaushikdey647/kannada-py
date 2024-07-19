#ifndef LEXER_H
#define LEXER_H

#include "common.h"

// Token types
typedef enum {
    TOKEN_EOF,
    TOKEN_ERROR,

    // Literals
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_STRING,

    // Keywords
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_WHILE,
    TOKEN_PRINT,
    TOKEN_TRUE,
    TOKEN_FALSE,
    TOKEN_NONE,

    // Operators
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_ASSIGN,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_EQUAL,

    // Delimiters
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_SEMICOLON
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    union {
        int number;
        char *string;
    } value;
    int line;
} Token;

// Function prototypes
void init_lexer(const char *input);
Token *get_next_token(void);
void free_token(Token *token);

// Helper function to convert TokenType to string (for debugging)
const char *token_type_to_string(TokenType type);

#endif // LEXER_H