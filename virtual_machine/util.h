// Team name: Compiler Builder 7
// William Cromar
// Luke Myers
// Jonathan Guilbe

#include "vm.h"

#ifndef SILVER_JOURNEY_UTIL_H
#define SILVER_JOURNEY_UTIL_H

int base( int level, int b, vmInstance *vm);

/* Stack functions */
int pop(vmInstance *vm);
void push(vmInstance *vm, int val);

#endif //SILVER_JOURNEY_UTIL_H
