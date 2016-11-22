// Team name: Compiler Builder 7
// William Cromar
// Luke Myers
// Jonathan Guilbe

#include <string.h>
#include "symbols.h"
#include <stdio.h>
#include <stdlib.h>

Symbol* symbol_table[MAX_SYMBOL_TABLE_SIZE] = {NULL};

Symbol* get(char name[]){
    int hashIndex = hash(name);
    int origin = hashIndex;
    Symbol* currentSymbol = symbol_table[hashIndex];
    int currentLevel = -1;
    int flag = 0;
    while(symbol_table[hashIndex] != NULL){
        if(strcmp(symbol_table[hashIndex]->name,name) == 0 && currentLevel <= symbol_table[hashIndex]->level){
            currentSymbol = symbol_table[hashIndex];
            currentLevel = currentSymbol->level;
            flag = 1;
        }
        hashIndex++;
        hashIndex %= MAX_SYMBOL_TABLE_SIZE;
        if(flag)
            return currentSymbol;
        if(hashIndex == origin){
            exit(-1);
        }
    }
    return currentSymbol;
}

void insert(char name[], Symbol* newSymbol){
    int hashIndex = hash(name);
    int origin = hashIndex;
    while(symbol_table[hashIndex] != NULL){
        hashIndex++;
        hashIndex %= MAX_SYMBOL_TABLE_SIZE;
        if(hashIndex == origin) {
            exit(-1);
        }
    }
    symbol_table[hashIndex] = newSymbol;
}
void clearLevel(int level){
    for (int i = 0; i < 100; ++i) {
        if(symbol_table[i] != NULL && symbol_table[i]->level == level){
            free(symbol_table[i]);
            symbol_table[i] = NULL;
        }
    }
}

int hash(char *name){
    int hash = 7;
    int i;
    int length = strlen(name);
    for (i = 0; i < length; ++i) {
        hash = hash * 31 + name[i];
    }
    return hash % MAX_SYMBOL_TABLE_SIZE;
}
