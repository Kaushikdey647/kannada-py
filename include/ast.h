#ifndef AST_H
#define AST_H

#include "common.h"
#include "lexer.h"

// AST node types
typedef enum {
    AST_PROGRAM,
    AST_BLOCK,
    AST_IF,
    AST_WHILE,
    AST_PRINT,
    AST_ASSIGN,
    AST_BINARY_OP,
    AST_UNARY_OP,
    AST_VARIABLE,
    AST_NUMBER,
    AST_STRING,
    AST_BOOLEAN
} ASTNodeType;

// Forward declaration of ASTNode
typedef struct ASTNode ASTNode;

// AST node structure
struct ASTNode {
    ASTNodeType type;
    union {
        struct {
            ASTNode **statements;
            int count;
        } program;
        struct {
            ASTNode **statements;
            int count;
        } block;
        struct {
            ASTNode *condition;
            ASTNode *if_body;
            ASTNode *else_body;
        } if_stmt;
        struct {
            ASTNode *condition;
            ASTNode *body;
        } while_loop;
        struct {
            ASTNode *expression;
        } print_stmt;
        struct {
            char *name;
            ASTNode *value;
        } assign;
        struct {
            TokenType op;
            ASTNode *left;
            ASTNode *right;
        } binary_op;
        struct {
            TokenType op;
            ASTNode *operand;
        } unary_op;
        struct {
            char *name;
        } variable;
        int number;
        char *string;
        bool boolean;
    } data;
    int line;
};

// Function prototypes
ASTNode *create_ast_node(ASTNodeType type);
void free_ast(ASTNode *node);

// Helper functions for creating specific node types
ASTNode *create_program_node(ASTNode **statements, int count);
ASTNode *create_block_node(ASTNode **statements, int count);
ASTNode *create_if_node(ASTNode *condition, ASTNode *if_body, ASTNode *else_body);
ASTNode *create_while_node(ASTNode *condition, ASTNode *body);
ASTNode *create_print_node(ASTNode *expression);
ASTNode *create_assign_node(char *name, ASTNode *value);
ASTNode *create_binary_op_node(TokenType op, ASTNode *left, ASTNode *right);
ASTNode *create_unary_op_node(TokenType op, ASTNode *operand);
ASTNode *create_variable_node(char *name);
ASTNode *create_number_node(int value);
ASTNode *create_string_node(char *value);
ASTNode *create_boolean_node(bool value);

// Function to print the AST (for debugging)
void print_ast(ASTNode *node, int indent);

#endif // AST_H