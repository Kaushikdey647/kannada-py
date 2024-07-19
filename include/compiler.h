#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>
#include "ast.h"
#include "lexer.h"
#include "parser.h"
#include "semantic_analyzer.h"
#include "symbol_table.h"
#include "codegen.h"

void compile(const char *source_code, FILE *output);

#endif // COMPILER_H