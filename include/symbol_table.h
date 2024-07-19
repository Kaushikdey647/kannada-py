#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "common.h"

// Symbol types
typedef enum {
    SYMBOL_VARIABLE,
    SYMBOL_FUNCTION
} SymbolType;

// Symbol structure
typedef struct Symbol {
    char *name;
    SymbolType type;
    union {
        // Variable-specific information
        struct {
            // Variable type information (e.g., int, float)
        } variable;
        // Function-specific information
        struct {
            // Function parameters and return type information
        } function;
    } info;
    struct Symbol *next; // For chaining in case of hash collisions
} Symbol;

// Symbol table structure
typedef struct {
    Symbol **table;  // Array of symbol pointers
    size_t size;     // Size of the table (number of buckets)
} SymbolTable;

// Function prototypes
SymbolTable *create_symbol_table(size_t size);
void free_symbol_table(SymbolTable *symbol_table);
Symbol *insert_symbol(SymbolTable *symbol_table, const char *name, SymbolType type);
Symbol *lookup_symbol(SymbolTable *symbol_table, const char *name);
void print_symbol_table(SymbolTable *symbol_table);

#endif // SYMBOL_TABLE_H