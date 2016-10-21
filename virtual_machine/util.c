// Team name: Compiler Builder 7
// William Cromar
// Luke Myers
// Jonathan Guilbe

#include "util.h"

// Pop the top item off of the vm's stack
int pop(vmInstance *vm) {
    // Grab the top element
    int val = vm->stack[vm->sp];;
    // Decrement the stack pointer
    vm->sp -= 1;

    // Return the top element from before
    return val;
}

// Push the given value to the top of the stack
void push(vmInstance *vm, int val) {
    // Increment the stack pointer
    vm->sp += 1;
    // Add val to the top of the stack
    vm->stack[vm->sp] = val;
}

// Computes the base of the activation level
int base( int level, int b, vmInstance *vm ) {
    while (level > 0) {
        b = vm->stack[ b + 1 ];
        level--;
    }
    return b;
}