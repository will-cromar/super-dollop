// Team name: Compiler Builder 7
// William Cromar
// Luke Myers
// Jonathan Guilbe

#include <stdio.h>
#include <stdlib.h>

#include "vm.h"
#include "instructions.h"
#include "input_output.h"

int execute(vmInstance *vm);

/*int main(int argc, char **argv) {
    if (argc < 2) {
        puts("Error: at least one argument required. (The name of the file you wish to exectute.)");
        return 1;
    }
    FILE *fp = fopen(argv[1], "r");
    instructMem code = parseInput(fp);
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
    puts("\nExecution:");
    puts("                      pc   bp   sp   stack");
    printf("                       0   %2d    0   \n", vm->bp);

    int halt = 0;
    while (1) {
        vm->ir = code.mem[vm->pc];
        halt = execute(vm);
        printVMState(vm);
        vm->pc++;
        if(halt){
            break;
        }

    }

    return 0;
}*/

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
            LIT(vm, instr->m);
            return 0;

        case 2:
            OPR(vm, instr->m);
            return 0;

        case 3:
            LOD(vm, instr->l, instr->m);
            return 0;

        case 4:
            STO(vm, instr->l, instr->m);
            return 0;

        case 5:
            CAL(vm, instr->l, instr->m);
            return 0;

        case 6:
            INC(vm, instr->m);
            return 0;

        case 7:
            JMP(vm, instr->m);
            return 0;

        case 8:
            JPC(vm, instr->m);
            return 0;

        case 9:
            return SIO(vm, instr->m);



        default:
            printf("Error: bad instruction %d %d %d\n",
                   instr->op, instr->m, instr->l);
            return 1;
    }
}