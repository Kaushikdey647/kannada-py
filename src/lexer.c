//lexer.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/lexer.h"
#include "../include/common.h"

#define MAX_IDENTIFIER_LENGTH 256
#define MAX_NUMBER_LENGTH 100
#define _POSIX_C_SOURCE 200809L  // This enables strdup in string.h

static char *current_pos;
static int line_number = 1;

// Kannada keyword mappings
static const struct {
    const char *keyword;
    TokenType type;
} kannada_keywords[] = {
    {"ಯದಿ", TOKEN_IF},
    {"ಅನ್ಯಥಾ", TOKEN_ELSE},
    {"ಆಗಿರುವ", TOKEN_WHILE},
    {"ಮುದ್ರಿಸು", TOKEN_PRINT},
    {"ನಿಜ", TOKEN_TRUE},
    {"ಸುಳ್ಳು", TOKEN_FALSE},
    {"ಶೂನ್ಯ", TOKEN_NONE},
    {NULL, TOKEN_EOF}
};

const char *token_type_to_string(TokenType type) {
    switch (type) {
        case TOKEN_EOF: return "TOKEN_EOF";
        case TOKEN_ERROR: return "TOKEN_ERROR";
        case TOKEN_IDENTIFIER: return "TOKEN_IDENTIFIER";
        case TOKEN_NUMBER: return "TOKEN_NUMBER";
        case TOKEN_STRING: return "TOKEN_STRING";
        case TOKEN_IF: return "TOKEN_IF";
        case TOKEN_ELSE: return "TOKEN_ELSE";
        case TOKEN_WHILE: return "TOKEN_WHILE";
        case TOKEN_PRINT: return "TOKEN_PRINT";
        case TOKEN_TRUE: return "TOKEN_TRUE";
        case TOKEN_FALSE: return "TOKEN_FALSE";
        case TOKEN_NONE: return "TOKEN_NONE";
        case TOKEN_PLUS: return "TOKEN_PLUS";
        case TOKEN_MINUS: return "TOKEN_MINUS";
        case TOKEN_MULTIPLY: return "TOKEN_MULTIPLY";
        case TOKEN_DIVIDE: return "TOKEN_DIVIDE";
        case TOKEN_ASSIGN: return "TOKEN_ASSIGN";
        case TOKEN_STAR: return "TOKEN_STAR";
        case TOKEN_SLASH: return "TOKEN_SLASH";
        case TOKEN_EQUAL: return "TOKEN_EQUAL";
        case TOKEN_LPAREN: return "TOKEN_LPAREN";
        case TOKEN_RPAREN: return "TOKEN_RPAREN";
        case TOKEN_LBRACE: return "TOKEN_LBRACE";
        case TOKEN_RBRACE: return "TOKEN_RBRACE";
        case TOKEN_SEMICOLON: return "TOKEN_SEMICOLON";
        default: return "UNKNOWN_TOKEN";
    }
}

void init_lexer(const char *input) {
    current_pos = (char *)input;
    line_number = 1;
}

static bool is_kannada_digit(uint32_t c) {
    // Kannada digits range from U+0CE6 to U+0CEF
    return (c >= 0x0CE6 && c <= 0x0CEF);
}

static int kannada_digit_to_int(uint32_t c) {
    return c - 0x0CE6;
}

static bool is_kannada_letter(uint32_t c) {
    // Kannada letters range from U+0C80 to U+0CFF
    return (c >= 0x0C80 && c <= 0x0CFF);
}

static void skip_whitespace() {
    while (*current_pos == ' ' || *current_pos == '\t' || *current_pos == '\n' || *current_pos == '\r') {
        if (*current_pos == '\n') {
            line_number++;
        }
        current_pos++;
    }
}

static Token *create_token(TokenType type) {
    Token *token = (Token *)malloc(sizeof(Token));
    token->type = type;
    token->line = line_number;
    return token;
}

static Token *tokenize_number() {
    char number[MAX_NUMBER_LENGTH] = {0};
    int i = 0;
    while (is_kannada_digit(*current_pos) && i < MAX_NUMBER_LENGTH - 1) {
        number[i++] = *current_pos++;
    }
    number[i] = '\0';

    Token *token = create_token(TOKEN_NUMBER);
    token->value.number = 0;
    for (int j = 0; j < i; j++) {
        token->value.number = token->value.number * 10 + kannada_digit_to_int(number[j]);
    }
    return token;
}

static Token *tokenize_identifier_or_keyword() {
    char identifier[MAX_IDENTIFIER_LENGTH] = {0};
    int i = 0;
    const char *temp = current_pos;
    while ((is_kannada_letter(utf8_nextchar(&temp)) || is_kannada_digit(utf8_nextchar(&temp))) && i < MAX_IDENTIFIER_LENGTH - 1) {
        identifier[i++] = *current_pos++;
    }
    identifier[i] = '\0';

    for (int j = 0; kannada_keywords[j].keyword != NULL; j++) {
        if (strcmp(identifier, kannada_keywords[j].keyword) == 0) {
            return create_token(kannada_keywords[j].type);
        }
    }

    Token *token = create_token(TOKEN_IDENTIFIER);
    token->value.string = safe_strdup(identifier);
    return token;
}

static Token *tokenize_string() {
    current_pos++; // Skip opening quote
    const char *start = current_pos;
    while (*current_pos != '"' && *current_pos != '\0') {
        if (*current_pos == '\n') line_number++;
        current_pos++;
    }

    if (*current_pos == '\0') {
        fprintf(stderr, "Error: Unterminated string at line %d\n", line_number);
        return create_token(TOKEN_ERROR);
    }

    int length = current_pos - start;
    Token *token = create_token(TOKEN_STRING);
    token->value.string = (char *)malloc(length + 1);
    strncpy(token->value.string, start, length);
    token->value.string[length] = '\0';

    current_pos++; // Skip closing quote
    return token;
}

Token *get_next_token() {
    skip_whitespace();

    if (*current_pos == '\0') {
        return create_token(TOKEN_EOF);
    }

    if (is_kannada_digit(*current_pos)) {
        return tokenize_number();
    }

    if (is_kannada_letter(*current_pos)) {
        return tokenize_identifier_or_keyword();
    }

    if (*current_pos == '"') {
        return tokenize_string();
    }

    // Single-character tokens
    switch (*current_pos) {
        case '+': current_pos++; return create_token(TOKEN_PLUS);
        case '-': current_pos++; return create_token(TOKEN_MINUS);
        case '*': current_pos++; return create_token(TOKEN_MULTIPLY);
        case '/': current_pos++; return create_token(TOKEN_DIVIDE);
        case '=': current_pos++; return create_token(TOKEN_ASSIGN);
        case '(': current_pos++; return create_token(TOKEN_LPAREN);
        case ')': current_pos++; return create_token(TOKEN_RPAREN);
        case '{': current_pos++; return create_token(TOKEN_LBRACE);
        case '}': current_pos++; return create_token(TOKEN_RBRACE);
        case ';': current_pos++; return create_token(TOKEN_SEMICOLON);
    }

    fprintf(stderr, "Error: Unknown token at line %d: %c\n", line_number, *current_pos);
    current_pos++;
    return create_token(TOKEN_ERROR);
}

void free_token(Token *token) {
    if (token->type == TOKEN_IDENTIFIER || token->type == TOKEN_STRING) {
        free(token->value.string);
    }
    free(token);
}