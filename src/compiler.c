// compiler.c
#include <stdio.h>
#include <stdlib.h>
#include "../include/compiler.h"
#include "../include/common.h"
#include "../include/semantic_analyzer.h"

void compile(const char *source_code, FILE *output) {
    // Initialize the lexer
    init_lexer(source_code);

    // Tokenize the input
    Token **tokens = NULL;
    int token_count = 0;
    Token *token;
    do {
        token = get_next_token();
        token_count++;
        tokens = (Token **)safe_realloc(tokens, token_count * sizeof(Token *));
        tokens[token_count - 1] = token;
    } while (token->type != TOKEN_EOF);

    // Create a parser
    Parser *parser = create_parser(tokens, token_count);

    // Parse the source code to generate the AST
    ASTNode *ast = parse_program(parser);

    // Create a symbol table
    SymbolTable *symbol_table = create_symbol_table(128);

    // Perform semantic analysis
    semantic_analysis(ast, symbol_table);

    // Generate code
    generate_code(ast, output);

    // Free resources
    free_ast(ast);
    free_symbol_table(symbol_table);
    free_parser(parser);
    for (int i = 0; i < token_count; i++) {
        free_token(tokens[i]);
    }
    free(tokens);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source file> <output file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *source_file = argv[1];
    const char *output_file = argv[2];

    // Read the source file
    FILE *input = fopen(source_file, "r");
    if (!input) {
        perror("Error opening source file");
        return EXIT_FAILURE;
    }
    fseek(input, 0, SEEK_END);
    size_t length = ftell(input);
    fseek(input, 0, SEEK_SET);

    char *source_code = (char *)safe_malloc(length + 1);
    fread(source_code, 1, length, input);
    fclose(input);
    source_code[length] = '\0';

    // Open the output file
    FILE *output = fopen(output_file, "w");
    if (!output) {
        perror("Error opening output file");
        free(source_code);
        return EXIT_FAILURE;
    }

    // Compile the source code
    compile(source_code, output);

    // Clean up
    fclose(output);
    free(source_code);

    return EXIT_SUCCESS;
}