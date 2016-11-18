// Team name: Compiler Builder 7
// William Cromar
// Luke Myers
// Jonathan Guilbe

#ifndef SUPER_DOLLOP_SYMBOLS_H
#define SUPER_DOLLOP_SYMBOLS_H

#define MAX_SYMBOL_TABLE_SIZE 100

typedef enum _SymbolType {
    variable = 0,
    constant = 1,
    procedure = 2
} SymbolType;

typedef struct symbol {
    SymbolType symbolType;
    char name[12];
    int value;
    int level;
    int offset;
    int instructionIndex;
} Symbol;

int hash(char* name);
Symbol* get(char name[]);
void insert(char name[], Symbol* newSymbol);
int hash(char *name);
int contains(char name[]);


#endif //SUPER_DOLLOP_SYMBOLS_H
