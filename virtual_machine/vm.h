// Team name: Compiler Builder 7
// William Cromar
// Luke Myers
// Jonathan Guilbe

#ifndef SILVER_JOURNEY_VM_H
#define SILVER_JOURNEY_VM_H

#include <stdio.h>

#define MAX_STACK_HEIGHT 2000
#define MAX_CODE_LENGTH 500
#define MAX_LEXI_LEVELS 3

struct _instruction {
    int op;
    int l;
    int m;
    int inputNumber;
};
typedef struct _instruction instruction;

struct _activationLL{
    int endOfRecord;
    struct _activationLL *next;
}; typedef struct _activationLL activationLL;


struct _vmInstance {
    int *stack;
    int bp;
    int sp;
    int pc;
    instruction ir;
    activationLL *arList;
};
typedef struct _vmInstance vmInstance;

struct _instructMem {
    instruction* mem;
    int length;
};
typedef struct _instructMem instructMem;

instructMem parseInput(FILE *fp);

#endif