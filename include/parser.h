#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lexer.h"

// Function declarations for the parser

typedef struct {
    Token **tokens;
    int current;
    int length;
} Parser;

Parser *create_parser(Token **tokens, int length);
void free_parser(Parser *parser);

ASTNode *parse_program(Parser *parser);
ASTNode *parse_block(Parser *parser);
ASTNode *parse_statement(Parser *parser);
ASTNode *parse_if_statement(Parser *parser);
ASTNode *parse_while_statement(Parser *parser);
ASTNode *parse_print_statement(Parser *parser);
ASTNode *parse_assign_statement(Parser *parser);
ASTNode *parse_expression(Parser *parser);
ASTNode *parse_term(Parser *parser);
ASTNode *parse_factor(Parser *parser);
ASTNode *parse_primary(Parser *parser);

#endif // PARSER_H
