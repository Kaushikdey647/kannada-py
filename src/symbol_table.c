#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/symbol_table.h"
#include "../include/common.h"

// Hash function to map names to table indices
static size_t hash(const char *name, size_t table_size) {
    size_t hash_value = 0;
    while (*name) {
        hash_value = (hash_value << 5) + *name++;
    }
    return hash_value % table_size;
}

// Create a new symbol table
SymbolTable *create_symbol_table(size_t size) {
    SymbolTable *symbol_table = (SymbolTable *)safe_malloc(sizeof(SymbolTable));
    symbol_table->table = (Symbol **)safe_malloc(size * sizeof(Symbol *));
    for (size_t i = 0; i < size; i++) {
        symbol_table->table[i] = NULL;
    }
    symbol_table->size = size;
    return symbol_table;
}

// Free a symbol
static void free_symbol(Symbol *symbol) {
    free(symbol->name);
    free(symbol);
}

// Free the symbol table
void free_symbol_table(SymbolTable *symbol_table) {
    for (size_t i = 0; i < symbol_table->size; i++) {
        Symbol *symbol = symbol_table->table[i];
        while (symbol) {
            Symbol *next = symbol->next;
            free_symbol(symbol);
            symbol = next;
        }
    }
    free(symbol_table->table);
    free(symbol_table);
}

// Insert a symbol into the table
Symbol *insert_symbol(SymbolTable *symbol_table, const char *name, SymbolType type) {
    size_t index = hash(name, symbol_table->size);
    Symbol *new_symbol = (Symbol *)safe_malloc(sizeof(Symbol));
    new_symbol->name = safe_strdup(name);
    new_symbol->type = type;
    new_symbol->next = symbol_table->table[index];
    symbol_table->table[index] = new_symbol;
    return new_symbol;
}

// Lookup a symbol in the table
Symbol *lookup_symbol(SymbolTable *symbol_table, const char *name) {
    size_t index = hash(name, symbol_table->size);
    Symbol *symbol = symbol_table->table[index];
    while (symbol) {
        if (strcmp(symbol->name, name) == 0) {
            return symbol;
        }
        symbol = symbol->next;
    }
    return NULL;
}

// Print the symbol table (for debugging)
void print_symbol_table(SymbolTable *symbol_table) {
    for (size_t i = 0; i < symbol_table->size; i++) {
        Symbol *symbol = symbol_table->table[i];
        if (symbol) {
            printf("Bucket %zu:\n", i);
            while (symbol) {
                printf("  Name: %s, Type: %d\n", symbol->name, symbol->type);
                symbol = symbol->next;
            }
        }
    }
}
