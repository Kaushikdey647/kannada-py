#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include "common.h"
#include "ast.h"
#include "symbol_table.h"
#include <stdio.h>
// Function prototypes for code generation
void generate_code(ASTNode *ast, FILE *output);

#endif // CODE_GENERATOR_H