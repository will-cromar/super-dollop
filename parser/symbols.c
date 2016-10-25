//
// Created by Jonathan on 10/24/2016.
//
#include <string.h>
#include "symbols.h"
#include <stdio.h>

symbol* symbol_table[MAX_SYMBOL_TABLE_SIZE] = {NULL};

int contains(char name[]){
    int hashIndex = hash(name);
    int origin = hashIndex;
    while(symbol_table[hashIndex] != NULL){
        if(strcmp(symbol_table[hashIndex]->name,name) == 0){
            return 1;
        }
        hashIndex++;
        hashIndex %= MAX_SYMBOL_TABLE_SIZE;
        if(hashIndex == origin)
            return 0;
    }
    return 0;
}

symbol* get(char name[]){
    int hashIndex = hash(name);
    while(1){
        if(strcmp(symbol_table[hashIndex]->name,name) == 0){
            return symbol_table[hashIndex];
        }
        hashIndex++;
        hashIndex %= MAX_SYMBOL_TABLE_SIZE;
    }
}

void insert(char name[], symbol* newSymbol){
    int hashIndex = hash(name);
    int origin = hashIndex;

    while(symbol_table[hashIndex] != NULL){
        hashIndex++;
        hashIndex %= MAX_SYMBOL_TABLE_SIZE;
        //Table is full, how do we handle this?
        if(hashIndex == origin) {
            printf("Error: Symbol table is full.\n");
            return;
        }
    }
    symbol_table[hashIndex] = newSymbol;
}

//Not sure how effective a hash function like this is with a small symbol table.
int hash(char *name){
    int hash = 7;
    int i;
    int length = strlen(name);
    for (i = 0; i < length; ++i) {
        hash = hash * 31 + name[i];
    }
    return hash % MAX_SYMBOL_TABLE_SIZE;
}
