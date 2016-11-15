// Team name: Compiler Builder 7
// William Cromar
// Luke Myers
// Jonathan Guilbe

#include <stdio.h>
#include <stdlib.h>

#include "vm.h"
#include "instructions.h"
#include "input_output.h"
#include "../parser/parse.h"

int execute(vmInstance *vm);

int run(FILE *f) {
    instructMem code = getCode();
    printCode(code);


    // Initialize the VM
    vmInstance *vm = malloc(sizeof(vmInstance));
    vm->stack = calloc(MAX_STACK_HEIGHT, sizeof(int));
    vm->sp = 0;
    vm->bp = 1;
    vm->pc = 1;
    vm->ir.op = 0;
    vm->ir.m = 0;
    vm->ir.l = 0;
    vm->arList = NULL;

    vm->stack[1] = 0;
    vm->stack[2] = 0;
    vm->stack[3] = 0;

    // Print execution header
    fputs("Execution:\n", f);
    fputs("                      pc   bp   sp   stack\n", f);
    fprintf(f, "                       0   %2d    0   \n", vm->bp);

    int halt = 0;
    while (1) {
        vm->ir = code.mem[vm->pc];
        halt = execute(vm);
        printVMState(vm, f);
        vm->pc++;
        if(halt){
            break;
        }

    }

    return 0;
}

instructMem parseInput(FILE *fp){
    if(fp == NULL){
        printf("Bad File Pointer\n");
    }
    int trash1, trash2, trash3;

    int numOperations = 0;
    while(fscanf(fp, " %d %d %d", &trash1, &trash2, &trash3) > 0){
        numOperations++;
    }
    rewind(fp);

    instructMem memory;
    instruction *arr = malloc(sizeof(instruction) * (numOperations + 1));
    memory.mem = arr;
    memory.length = numOperations;

    int a;
    for(a = 1; a <= numOperations; a++){
        fscanf(fp, " %d %d %d", &arr[a].op, &arr[a].l, &arr[a].m);
        arr[a].inputNumber = a - 1;
        //printf("%d,%d,%d\n", arr[a].op, arr[a].l, arr[a].m);
    }

    return memory;
}

int execute(vmInstance *vm) {
    instruction *instr = &vm->ir;

    switch (instr->op) {
        case 1:
            lit(vm, instr->m);
            return 0;

        case 2:
            opr(vm, instr->m);
            return 0;

        case 3:
            lod(vm, instr->l, instr->m);
            return 0;

        case 4:
            sto(vm, instr->l, instr->m);
            return 0;

        case 5:
            cal(vm, instr->l, instr->m);
            return 0;

        case 6:
            inc(vm, instr->m);
            return 0;

        case 7:
            jmp(vm, instr->m);
            return 0;

        case 8:
            jpc(vm, instr->m);
            return 0;

        case 9:
            return sio(vm, instr->m);



        default:
            printf("Error: bad instruction %d %d %d\n",
                   instr->op, instr->m, instr->l);
            return 1;
    }
}