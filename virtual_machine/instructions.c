// Team name: Compiler Builder 7
// William Cromar
// Luke Myers
// Jonathan Guilbe

#include <stdlib.h>
#include <stdio.h>
#include "vm.h"
#include "util.h"
#include "instructions.h"

//#define HCF exit(0)

void lit(vmInstance *vm, int M) {
    push(vm, M);
}

void opr(vmInstance *vm, int M) {
    switch(M) {
        case 0:
            ret(vm);
            break;

        case 1:
            neg(vm);
            break;

        case 2:
            add(vm);
            break;

        case 3:
            sub(vm);
            break;

        case 4:
            mul(vm);
            break;

        case 5:
            divOp(vm);
            break;

        case 6:
            odd(vm);
            break;

        case 7:
            mod(vm);
            break;

        case 8:
            eql(vm);
            break;

        case 9:
            neq(vm);
            break;

        case 10:
            lss(vm);
            break;

        case 11:
            leq(vm);
            break;

        case 12:
            gtr(vm);
            break;

        case 13:
            geq(vm);
            break;

        default:
            printf("Error: Invalid M %d passed to OPR\n", M);
            break;
    }
}

void lod(vmInstance *vm, int L, int M) {
    int val = vm->stack[base(L, vm->bp, vm) + M];
    push(vm, val);
}

void sto(vmInstance *vm, int L, int M) {
    int val = pop(vm);
    vm->stack[ base(L, vm->bp, vm) + M ] = val;
}

void cal(vmInstance *vm, int L, int M) {
    vm->stack[vm->sp + 1] = 0;
    vm->stack[vm->sp + 2] = base(L, vm->bp, vm);
    vm->stack[vm->sp + 3] = vm->bp;
    vm->stack[vm->sp + 4] = vm->pc;
    vm->bp = vm->sp + 1;
    vm->pc = M;

    while(vm->arList != NULL){
        vm->arList = vm->arList->next;
    }
    vm->arList = malloc( sizeof(activationLL) * 1);
    vm->arList->endOfRecord = vm->sp;
    vm->arList->next = NULL;
}

void inc(vmInstance *vm, int M) {
    vm->sp += M;
}

void jmp(vmInstance *vm, int M) {
    vm->pc = M;
}

void jpc(vmInstance *vm, int M) {
    int val = pop(vm);

    if (val == 0) jmp(vm, M);
}

void ret(vmInstance *vm) {
    vm->sp = vm->bp - 1;
    vm->pc = vm->stack[vm->sp + 4];
    vm->bp = vm->stack[vm->sp + 3];

    if (vm->arList == NULL) {
        puts("Error: Attempt to return from null function.");
    }
    // assuming there are at least 2 stack frames on the stack if this is called
    while(vm->arList->next != NULL){
        vm->arList = vm->arList->next;
    }
    free(vm->arList->next);
    vm->arList->next = NULL;
}

void neg(vmInstance *vm) {
    vm->stack[vm->sp] *= -1;
}

void add(vmInstance *vm) {
    int op2 = pop(vm);
    int op1 = pop(vm);
    int res = op1 + op2;

    push(vm, res);
}

void sub(vmInstance *vm) {
    int op2 = pop(vm);
    int op1 = pop(vm);
    int res = op1 - op2;

    push(vm, res);
}

void mul(vmInstance *vm) {
    int op2 = pop(vm);
    int op1 = pop(vm);
    int res = op1 * op2;

    push(vm, res);
}

void divOp(vmInstance *vm) {
    int op2 = pop(vm);
    int op1 = pop(vm);
    int res = op1 / op2;

    push(vm, res);
}

void odd(vmInstance *vm) {
    int op1 = pop(vm);
    int res = op1 % 2;

    push(vm, res);
}

void mod(vmInstance *vm) {
    int op2 = pop(vm);
    int op1 = pop(vm);
    int res = op1 % op2;

    push(vm, res);
}

void eql(vmInstance *vm) {
    int op2 = pop(vm);
    int op1 = pop(vm);
    int res = op1 == op2;

    push(vm, res);
}

void neq(vmInstance *vm) {
    int op2 = pop(vm);
    int op1 = pop(vm);
    int res = op1 != op2;

    push(vm, res);
}

void lss(vmInstance *vm) {
    int op2 = pop(vm);
    int op1 = pop(vm);
    int res = op1 < op2;

    push(vm, res);
}

void leq(vmInstance *vm) {
    int op2 = pop(vm);
    int op1 = pop(vm);
    int res = op1 <= op2;

    push(vm, res);
}

void gtr(vmInstance *vm) {
    int op2 = pop(vm);
    int op1 = pop(vm);
    int res = op1 > op2;

    push(vm, res);
}

void geq(vmInstance *vm) {
    int op2 = pop(vm);
    int op1 = pop(vm);
    int res = op1 >= op2;

    push(vm, res);
}

int sio(vmInstance *vm, int M) {
    switch (M) {
        case 0:
            out(vm);
            return 0;

        case 1:
            inp(vm);
            return 0;

        case 2:
            hlt();
            return 1;

        default:
            printf("Error: Invalid M %d passed to SIO\n", M);
            return 1;
    }
}

void out(vmInstance *vm) {
    int val = pop(vm);
    printf("%d\n", val);
}

void inp(vmInstance *vm) {
    int temp;
    scanf("%d", &temp);
    push(vm, temp);
}

void hlt(void) {
    return;
}
