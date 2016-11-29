// Team name: Compiler Builder 7
// William Cromar
// Luke Myers
// Jonathan Guilbe

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "symbols.h"

Entry* symbol_table[MAX_SYMBOL_TABLE_SIZE] = {NULL};

Symbol* get(char name[]){
    int hashIndex = hash(name);
    int origin = hashIndex;

    int targetIndex = -1;
    do {
        if (symbol_table[hashIndex] != NULL && strcmp(symbol_table[hashIndex]->name, name) == 0) {
            targetIndex = hashIndex;
        }

        hashIndex++;
        hashIndex %= MAX_SYMBOL_TABLE_SIZE;
    } while (hashIndex != origin && targetIndex == -1);

    if (targetIndex != -1 && symbol_table[targetIndex] != NULL) {
        return symbol_table[targetIndex]->sym;
    } else {
        printf("Symbol not found: %s :'(\n", name);
        exit(-4);
    }
}

void insert(char name[], Symbol* newSymbol){
    int hashIndex = hash(name);
    int targetIndex = -1;
    int firstNull = -1;
    int origin = hashIndex;
    do {
        if (symbol_table[hashIndex] == NULL) {
            firstNull = firstNull == -1 ? hashIndex : firstNull;
        }
        else if (strcmp(symbol_table[hashIndex]->name, name) == 0) {
            targetIndex = hashIndex;
        }

        hashIndex++;
        hashIndex %= MAX_SYMBOL_TABLE_SIZE;
    } while (hashIndex != origin && targetIndex == -1);

    int fillIdx = targetIndex != -1 ? targetIndex : firstNull;

    if (fillIdx != -1) {
        // Push
        Entry *newEntry = calloc(1, sizeof(Entry));
        strcpy(newEntry->name, newSymbol->name);
        newEntry->sym = newSymbol;
        newEntry->next = symbol_table[fillIdx];
        symbol_table[fillIdx] = newEntry;
    } else {
        puts("Symbol table too full!");
        exit(-3);
    }
}

void clearLevel(int level){
    for (int i = 0; i < MAX_SYMBOL_TABLE_SIZE; ++i) {
        if(symbol_table[i] != NULL && symbol_table[i]->sym != NULL && symbol_table[i]->sym->level == level){
            free(symbol_table[i]->sym);

            // Pop
            Entry *temp = symbol_table[i];
            symbol_table[i] = symbol_table[i]->next;
            free(temp);
        }
    }
}

int hash(char *name){
    int hash = 7;
    int i;
    size_t length = strlen(name);
    for (i = 0; i < length; ++i) {
        hash = hash * 31 + name[i];
    }
    return hash % MAX_SYMBOL_TABLE_SIZE;
}