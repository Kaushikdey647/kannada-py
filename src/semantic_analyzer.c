#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/semantic_analyzer.h"
#include "../include/common.h"

// Function to perform semantic analysis on the AST
void semantic_analysis(ASTNode *ast, SymbolTable *symbol_table) {
    // Perform semantic analysis based on the node type
    switch (ast->type) {
        case AST_PROGRAM:
            for (int i = 0; i < ast->data.program.count; i++) {
                semantic_analysis(ast->data.program.statements[i], symbol_table);
            }
            break;
        case AST_BLOCK:
            for (int i = 0; i < ast->data.block.count; i++) {
                semantic_analysis(ast->data.block.statements[i], symbol_table);
            }
            break;
        case AST_IF:
            semantic_analysis(ast->data.if_stmt.condition, symbol_table);
            semantic_analysis(ast->data.if_stmt.if_body, symbol_table);
            if (ast->data.if_stmt.else_body) {
                semantic_analysis(ast->data.if_stmt.else_body, symbol_table);
            }
            break;
        case AST_WHILE:
            semantic_analysis(ast->data.while_loop.condition, symbol_table);
            semantic_analysis(ast->data.while_loop.body, symbol_table);
            break;
        case AST_PRINT:
            semantic_analysis(ast->data.print_stmt.expression, symbol_table);
            break;
        case AST_ASSIGN:
            if (!lookup_symbol(symbol_table, ast->data.assign.name)) {
                fprintf(stderr, "Error: Undeclared variable '%s' at line %d\n", ast->data.assign.name, ast->line);
                exit(EXIT_FAILURE);
            }
            semantic_analysis(ast->data.assign.value, symbol_table);
            break;
        case AST_BINARY_OP:
            semantic_analysis(ast->data.binary_op.left, symbol_table);
            semantic_analysis(ast->data.binary_op.right, symbol_table);
            break;
        case AST_UNARY_OP:
            semantic_analysis(ast->data.unary_op.operand, symbol_table);
            break;
        case AST_VARIABLE:
            if (!lookup_symbol(symbol_table, ast->data.variable.name)) {
                fprintf(stderr, "Error: Undeclared variable '%s' at line %d\n", ast->data.variable.name, ast->line);
                exit(EXIT_FAILURE);
            }
            break;
        case AST_NUMBER:
        case AST_STRING:
        case AST_BOOLEAN:
            // No semantic checks needed for literals
            break;
        default:
            fprintf(stderr, "Error: Unknown AST node type at line %d\n", ast->line);
            exit(EXIT_FAILURE);
    }
}
