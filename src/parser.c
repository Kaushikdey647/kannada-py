#include <stdio.h>
#include <stdlib.h>
#include "../include/parser.h"
#include "../include/common.h"

Parser *create_parser(Token *tokens, int length) {
    Parser *parser = (Parser *)safe_malloc(sizeof(Parser));
    parser->tokens = tokens;
    parser->current = 0;
    parser->length = length;
    return parser;
}

void free_parser(Parser *parser) {
    free(parser);
}

Token *advance(Parser *parser) {
    if (parser->current < parser->length) {
        return &parser->tokens[parser->current++];
    }
    return NULL;
}

Token *peek(Parser *parser) {
    if (parser->current < parser->length) {
        return &parser->tokens[parser->current];
    }
    return NULL;
}

Token *consume(Parser *parser, TokenType type, const char *message) {
    if (peek(parser)->type == type) {
        return advance(parser);
    }
    fprintf(stderr, "Parser error: %s\n", message);
    exit(EXIT_FAILURE);
}

ASTNode *parse_program(Parser *parser) {
    ASTNode **statements = NULL;
    int count = 0;

    while (peek(parser)->type != TOKEN_EOF) {
        statements = (ASTNode **)safe_realloc(statements, sizeof(ASTNode *) * (count + 1));
        statements[count++] = parse_statement(parser);
    }

    return create_program_node(statements, count);
}

ASTNode *parse_block(Parser *parser) {
    ASTNode **statements = NULL;
    int count = 0;

    consume(parser, TOKEN_LBRACE, "Expected '{' at the beginning of a block");

    while (peek(parser)->type != TOKEN_RBRACE) {
        statements = (ASTNode **)safe_realloc(statements, sizeof(ASTNode *) * (count + 1));
        statements[count++] = parse_statement(parser);
    }

    consume(parser, TOKEN_RBRACE, "Expected '}' at the end of a block");

    return create_block_node(statements, count);
}

ASTNode *parse_statement(Parser *parser) {
    switch (peek(parser)->type) {
        case TOKEN_IF:
            return parse_if_statement(parser);
        case TOKEN_WHILE:
            return parse_while_statement(parser);
        case TOKEN_PRINT:
            return parse_print_statement(parser);
        case TOKEN_IDENTIFIER:
            return parse_assign_statement(parser);
        default:
            fprintf(stderr, "Unexpected token: %s\n", token_type_to_string(peek(parser)->type));
            exit(EXIT_FAILURE);
    }
}

ASTNode *parse_if_statement(Parser *parser) {
    consume(parser, TOKEN_IF, "Expected 'if'");

    ASTNode *condition = parse_expression(parser);
    ASTNode *if_body = parse_block(parser);
    ASTNode *else_body = NULL;

    if (peek(parser)->type == TOKEN_ELSE) {
        advance(parser);  // consume 'else'
        else_body = parse_block(parser);
    }

    return create_if_node(condition, if_body, else_body);
}

ASTNode *parse_while_statement(Parser *parser) {
    consume(parser, TOKEN_WHILE, "Expected 'while'");

    ASTNode *condition = parse_expression(parser);
    ASTNode *body = parse_block(parser);

    return create_while_node(condition, body);
}

ASTNode *parse_print_statement(Parser *parser) {
    consume(parser, TOKEN_PRINT, "Expected 'print'");

    ASTNode *expression = parse_expression(parser);
    consume(parser, TOKEN_SEMICOLON, "Expected ';' after print statement");

    return create_print_node(expression);
}

ASTNode *parse_assign_statement(Parser *parser) {
    Token *identifier = consume(parser, TOKEN_IDENTIFIER, "Expected identifier");

    consume(parser, TOKEN_EQUAL, "Expected '=' after identifier");
    ASTNode *value = parse_expression(parser);
    consume(parser, TOKEN_SEMICOLON, "Expected ';' after assignment");

    return create_assign_node(identifier->value.string, value);
}

ASTNode *parse_expression(Parser *parser) {
    ASTNode *left = parse_term(parser);

    while (peek(parser)->type == TOKEN_PLUS || peek(parser)->type == TOKEN_MINUS) {
        Token *op = advance(parser);
        ASTNode *right = parse_term(parser);
        left = create_binary_op_node(op->type, left, right);
    }

    return left;
}

ASTNode *parse_term(Parser *parser) {
    ASTNode *left = parse_factor(parser);

    while (peek(parser)->type == TOKEN_STAR || peek(parser)->type == TOKEN_SLASH) {
        Token *op = advance(parser);
        ASTNode *right = parse_factor(parser);
        left = create_binary_op_node(op->type, left, right);
    }

    return left;
}

ASTNode *parse_factor(Parser *parser) {
    if (peek(parser)->type == TOKEN_MINUS) {
        Token *op = advance(parser);
        ASTNode *operand = parse_primary(parser);
        return create_unary_op_node(op->type, operand);
    }

    return parse_primary(parser);
}

ASTNode *parse_primary(Parser *parser) {
    Token *token = advance(parser);

    switch (token->type) {
        case TOKEN_NUMBER:
            return create_number_node(token->value.number);
        case TOKEN_STRING:
            return create_string_node(token->value.string);
        case TOKEN_TRUE:
            return create_boolean_node(true);
        case TOKEN_FALSE:
            return create_boolean_node(false);
        case TOKEN_IDENTIFIER:
            return create_variable_node(token->value.string);
        case TOKEN_LPAREN:
            {
                ASTNode *expression = parse_expression(parser);
                consume(parser, TOKEN_RPAREN, "Expected ')' after expression");
                return expression;
            }
        default:
            fprintf(stderr, "Unexpected token: %s\n", token_type_to_string(token->type));
            exit(EXIT_FAILURE);
    }
}
