#include <stdlib.h>
#include "../include/codegen.h"
#include "../include/common.h"

// Function to generate code from the AST
void generate_code(ASTNode *ast, FILE *output) {
    switch (ast->type) {
        case AST_PROGRAM:
            for (int i = 0; i < ast->data.program.count; i++) {
                generate_code(ast->data.program.statements[i], output);
            }
            break;
        case AST_BLOCK:
            for (int i = 0; i < ast->data.block.count; i++) {
                generate_code(ast->data.block.statements[i], output);
            }
            break;
        case AST_IF:
            fprintf(output, "if (");
            generate_code(ast->data.if_stmt.condition, output);
            fprintf(output, ") {\n");
            generate_code(ast->data.if_stmt.if_body, output);
            if (ast->data.if_stmt.else_body) {
                fprintf(output, "} else {\n");
                generate_code(ast->data.if_stmt.else_body, output);
            }
            fprintf(output, "}\n");
            break;
        case AST_WHILE:
            fprintf(output, "while (");
            generate_code(ast->data.while_loop.condition, output);
            fprintf(output, ") {\n");
            generate_code(ast->data.while_loop.body, output);
            fprintf(output, "}\n");
            break;
        case AST_PRINT:
            fprintf(output, "print(");
            generate_code(ast->data.print_stmt.expression, output);
            fprintf(output, ");\n");
            break;
        case AST_ASSIGN:
            fprintf(output, "%s = ", ast->data.assign.name);
            generate_code(ast->data.assign.value, output);
            fprintf(output, ";\n");
            break;
        case AST_BINARY_OP:
            generate_code(ast->data.binary_op.left, output);
            fprintf(output, " %s ", token_type_to_string(ast->data.binary_op.op));
            generate_code(ast->data.binary_op.right, output);
            break;
        case AST_UNARY_OP:
            fprintf(output, "%s", token_type_to_string(ast->data.unary_op.op));
            generate_code(ast->data.unary_op.operand, output);
            break;
        case AST_VARIABLE:
            fprintf(output, "%s", ast->data.variable.name);
            break;
        case AST_NUMBER:
            fprintf(output, "%d", ast->data.number);
            break;
        case AST_STRING:
            fprintf(output, "\"%s\"", ast->data.string);
            break;
        case AST_BOOLEAN:
            fprintf(output, "%s", ast->data.boolean ? "true" : "false");
            break;
        default:
            fprintf(stderr, "Error: Unknown AST node type at line %d\n", ast->line);
            exit(EXIT_FAILURE);
    }
}