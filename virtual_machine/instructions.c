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

void LIT(vmInstance *vm, int M) {
    push(vm, M);
}

void OPR(vmInstance *vm, int M) {
    switch(M) {
        case 0:
            RET(vm);
            break;

        case 1:
            NEG(vm);
            break;

        case 2:
            ADD(vm);
            break;

        case 3:
            SUB(vm);
            break;

        case 4:
            MUL(vm);
            break;

        case 5:
            DIV(vm);
            break;

        case 6:
            ODD(vm);
            break;

        case 7:
            MOD(vm);
            break;

        case 8:
            EQL(vm);
            break;

        case 9:
            NEQ(vm);
            break;

        case 10:
            LSS(vm);
            break;

        case 11:
            LEQ(vm);
            break;

        case 12:
            GTR(vm);
            break;

        case 13:
            GEQ(vm);
            break;

        default:
            printf("Error: Invalid M %d passed to OPR\n", M);
            break;
    }
}

void LOD(vmInstance *vm, int L, int M) {
    int val = vm->stack[base(L, vm->bp, vm) + M];
    push(vm, val);
}

void STO(vmInstance *vm, int L, int M) {
    int val = pop(vm);
    vm->stack[ base(L, vm->bp, vm) + M ] = val;
}

void CAL(vmInstance *vm, int L, int M) {
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

void INC(vmInstance *vm, int M) {
    vm->sp += M;
}

void JMP(vmInstance *vm, int M) {
    vm->pc = M;
}

void JPC(vmInstance *vm, int M) {
    int val = pop(vm);

    if (val == 0) JMP(vm, M);
}

void RET(vmInstance *vm) {
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

void NEG(vmInstance *vm) {
    vm->stack[vm->sp] *= -1;
}

void ADD(vmInstance *vm) {
    int op2 = pop(vm);
    int op1 = pop(vm);
    int res = op1 + op2;

    push(vm, res);
}

void SUB(vmInstance *vm) {
    int op2 = pop(vm);
    int op1 = pop(vm);
    int res = op1 - op2;

    push(vm, res);
}

void MUL(vmInstance *vm) {
    int op2 = pop(vm);
    int op1 = pop(vm);
    int res = op1 * op2;

    push(vm, res);
}

void DIV(vmInstance *vm) {
    int op2 = pop(vm);
    int op1 = pop(vm);
    int res = op1 / op2;

    push(vm, res);
}

void ODD(vmInstance *vm) {
    int op1 = pop(vm);
    int res = op1 % 2;

    push(vm, res);
}

void MOD(vmInstance *vm) {
    int op2 = pop(vm);
    int op1 = pop(vm);
    int res = op1 % op2;

    push(vm, res);
}

void EQL(vmInstance *vm) {
    int op2 = pop(vm);
    int op1 = pop(vm);
    int res = op1 == op2;

    push(vm, res);
}

void NEQ(vmInstance *vm) {
    int op2 = pop(vm);
    int op1 = pop(vm);
    int res = op1 != op2;

    push(vm, res);
}

void LSS(vmInstance *vm) {
    int op2 = pop(vm);
    int op1 = pop(vm);
    int res = op1 < op2;

    push(vm, res);
}

void LEQ(vmInstance *vm) {
    int op2 = pop(vm);
    int op1 = pop(vm);
    int res = op1 <= op2;

    push(vm, res);
}

void GTR(vmInstance *vm) {
    int op2 = pop(vm);
    int op1 = pop(vm);
    int res = op1 > op2;

    push(vm, res);
}

void GEQ(vmInstance *vm) {
    int op2 = pop(vm);
    int op1 = pop(vm);
    int res = op1 >= op2;

    push(vm, res);
}

int SIO(vmInstance *vm, int M) {
    switch (M) {
        case 0:
            OUT(vm);
            return 0;

        case 1:
            INP(vm);
            return 0;

        case 2:
            HLT();
            return 1;

        default:
            printf("Error: Invalid M %d passed to SIO\n", M);
            return 1;
    }
}

void OUT(vmInstance *vm) {
    int val = pop(vm);
    printf("%d\n", val);
}

void INP(vmInstance *vm) {
    int temp;
    scanf("%d", &temp);
    push(vm, temp);
}

void HLT(void) {
    return;
}
