#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/lexer.h"
#include "../include/common.h"

#define MAX_IDENTIFIER_LENGTH 256
#define MAX_NUMBER_LENGTH 100

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

void init_lexer(const char *input) {
    current_pos = (char *)input;
    line_number = 1;
}

static int is_kannada_digit(char c) {
    // Kannada digits range from U+0CE6 to U+0CEF
    return (c >= 0xCE && c <= 0xCF && (unsigned char)c >= 0xA6);
}

static int kannada_digit_to_int(char c) {
    return c - 0xE6;
}

static int is_kannada_letter(char c) {
    // Simplified check for Kannada letters
    return (c >= 0xC8 && c <= 0xCF);
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
    while ((is_kannada_letter(*current_pos) || is_kannada_digit(*current_pos)) && i < MAX_IDENTIFIER_LENGTH - 1) {
        identifier[i++] = *current_pos++;
    }
    identifier[i] = '\0';

    for (int j = 0; kannada_keywords[j].keyword != NULL; j++) {
        if (strcmp(identifier, kannada_keywords[j].keyword) == 0) {
            return create_token(kannada_keywords[j].type);
        }
    }

    Token *token = create_token(TOKEN_IDENTIFIER);
    token->value.string = strdup(identifier);
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