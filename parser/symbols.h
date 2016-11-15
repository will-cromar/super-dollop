// Team name: Compiler Builder 7
// William Cromar
// Luke Myers
// Jonathan Guilbe

#ifndef SUPER_DOLLOP_SYMBOLS_H
#define SUPER_DOLLOP_SYMBOLS_H

#define MAX_SYMBOL_TABLE_SIZE 100

typedef struct symbol {
    int kind;
    char name[12];
    int val;
    int level;
    int addr;
} symbol;

int hash(char* name);
symbol* get(char name[]);
void insert(char name[], symbol* newSymbol);
int hash(char *name);
int contains(char name[]);


#endif //SUPER_DOLLOP_SYMBOLS_H
