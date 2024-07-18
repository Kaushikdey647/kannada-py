#ifndef COMPILER_H
#define COMPILER_H

#include "common.h"
#include "lexer.h"
#include "parser.h"
#include "semantic_analyzer.h"
#include "codegen.h"
#include "symbol_table.h"

// Function prototypes for the main compiler driver
void compile(const char *source_code, FILE *output);

#endif // COMPILER_H