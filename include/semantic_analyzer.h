#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include "ast.h"
#include "symbol_table.h"

// Function prototype for performing semantic analysis on the AST
void semantic_analysis(ASTNode *ast, SymbolTable *symbol_table);

#endif // SEMANTIC_ANALYZER_H