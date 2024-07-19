#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/ast.h"
#include "../include/common.h"

ASTNode *create_ast_node(ASTNodeType type) {
    ASTNode *node = safe_malloc(sizeof(ASTNode));
    node->type = type;
    node->line = 0;  // Line number should be set by the parser
    return node;
}

void free_ast(ASTNode *node) {
    if (node == NULL) return;

    switch (node->type) {
        case AST_PROGRAM:
        case AST_BLOCK:
            for (int i = 0; i < node->data.program.count; i++) {
                free_ast(node->data.program.statements[i]);
            }
            free(node->data.program.statements);
            break;
        case AST_IF:
            free_ast(node->data.if_stmt.condition);
            free_ast(node->data.if_stmt.if_body);
            free_ast(node->data.if_stmt.else_body);
            break;
        case AST_WHILE:
            free_ast(node->data.while_loop.condition);
            free_ast(node->data.while_loop.body);
            break;
        case AST_PRINT:
            free_ast(node->data.print_stmt.expression);
            break;
        case AST_ASSIGN:
            free(node->data.assign.name);
            free_ast(node->data.assign.value);
            break;
        case AST_BINARY_OP:
            free_ast(node->data.binary_op.left);
            free_ast(node->data.binary_op.right);
            break;
        case AST_UNARY_OP:
            free_ast(node->data.unary_op.operand);
            break;
        case AST_VARIABLE:
            free(node->data.variable.name);
            break;
        case AST_STRING:
            free(node->data.string);
            break;
        default:
            // AST_NUMBER and AST_BOOLEAN don't need additional freeing
            break;
    }

    free(node);
}

ASTNode *create_program_node(ASTNode **statements, int count) {
    ASTNode *node = create_ast_node(AST_PROGRAM);
    node->data.program.statements = statements;
    node->data.program.count = count;
    return node;
}

ASTNode *create_block_node(ASTNode **statements, int count) {
    ASTNode *node = create_ast_node(AST_BLOCK);
    node->data.block.statements = statements;
    node->data.block.count = count;
    return node;
}

ASTNode *create_if_node(ASTNode *condition, ASTNode *if_body, ASTNode *else_body) {
    ASTNode *node = create_ast_node(AST_IF);
    node->data.if_stmt.condition = condition;
    node->data.if_stmt.if_body = if_body;
    node->data.if_stmt.else_body = else_body;
    return node;
}

ASTNode *create_while_node(ASTNode *condition, ASTNode *body) {
    ASTNode *node = create_ast_node(AST_WHILE);
    node->data.while_loop.condition = condition;
    node->data.while_loop.body = body;
    return node;
}

ASTNode *create_print_node(ASTNode *expression) {
    ASTNode *node = create_ast_node(AST_PRINT);
    node->data.print_stmt.expression = expression;
    return node;
}

ASTNode *create_assign_node(char *name, ASTNode *value) {
    ASTNode *node = create_ast_node(AST_ASSIGN);
    node->data.assign.name = safe_strdup(name);
    node->data.assign.value = value;
    return node;
}

ASTNode *create_binary_op_node(TokenType op, ASTNode *left, ASTNode *right) {
    ASTNode *node = create_ast_node(AST_BINARY_OP);
    node->data.binary_op.op = op;
    node->data.binary_op.left = left;
    node->data.binary_op.right = right;
    return node;
}

ASTNode *create_unary_op_node(TokenType op, ASTNode *operand) {
    ASTNode *node = create_ast_node(AST_UNARY_OP);
    node->data.unary_op.op = op;
    node->data.unary_op.operand = operand;
    return node;
}

ASTNode *create_variable_node(char *name) {
    ASTNode *node = create_ast_node(AST_VARIABLE);
    node->data.variable.name = safe_strdup(name);
    return node;
}

ASTNode *create_number_node(int value) {
    ASTNode *node = create_ast_node(AST_NUMBER);
    node->data.number = value;
    return node;
}

ASTNode *create_string_node(char *value) {
    ASTNode *node = create_ast_node(AST_STRING);
    node->data.string = safe_strdup(value);
    return node;
}

ASTNode *create_boolean_node(bool value) {
    ASTNode *node = create_ast_node(AST_BOOLEAN);
    node->data.boolean = value;
    return node;
}

void print_ast(ASTNode *node, int indent) {
    if (node == NULL) return;

    for (int i = 0; i < indent; i++) {
        printf("  ");
    }

    switch (node->type) {
        case AST_PROGRAM:
            printf("Program (%d statements)\n", node->data.program.count);
            for (int i = 0; i < node->data.program.count; i++) {
                print_ast(node->data.program.statements[i], indent + 1);
            }
            break;
        case AST_BLOCK:
            printf("Block (%d statements)\n", node->data.block.count);
            for (int i = 0; i < node->data.block.count; i++) {
                print_ast(node->data.block.statements[i], indent + 1);
            }
            break;
        case AST_IF:
            printf("If\n");
            print_ast(node->data.if_stmt.condition, indent + 1);
            print_ast(node->data.if_stmt.if_body, indent + 1);
            if (node->data.if_stmt.else_body) {
                for (int i = 0; i < indent; i++) printf("  ");
                printf("Else\n");
                print_ast(node->data.if_stmt.else_body, indent + 1);
            }
            break;
        case AST_WHILE:
            printf("While\n");
            print_ast(node->data.while_loop.condition, indent + 1);
            print_ast(node->data.while_loop.body, indent + 1);
            break;
        case AST_PRINT:
            printf("Print\n");
            print_ast(node->data.print_stmt.expression, indent + 1);
            break;
        case AST_ASSIGN:
            printf("Assign: %s\n", node->data.assign.name);
            print_ast(node->data.assign.value, indent + 1);
            break;
        case AST_BINARY_OP:
            printf("Binary Op: %d\n", node->data.binary_op.op);
            print_ast(node->data.binary_op.left, indent + 1);
            print_ast(node->data.binary_op.right, indent + 1);
            break;
        case AST_UNARY_OP:
            printf("Unary Op: %d\n", node->data.unary_op.op);
            print_ast(node->data.unary_op.operand, indent + 1);
            break;
        case AST_VARIABLE:
            printf("Variable: %s\n", node->data.variable.name);
            break;
        case AST_NUMBER:
            printf("Number: %d\n", node->data.number);
            break;
        case AST_STRING:
            printf("String: %s\n", node->data.string);
            break;
        case AST_BOOLEAN:
            printf("Boolean: %s\n", node->data.boolean ? "true" : "false");
            break;
    }
}