// Team name: Compiler Builder 7
// William Cromar
// Luke Myers
// Jonathan Guilbe

#include "vm.h"
#include "input_output.h"
#include "../compiler.h"

const char *opNames[10][14] = {{"NIL"},
                               {"LIT"},
                               {"RET", "NEG", "ADD", "SUB", "MUL", "DIV", "ODD",
                                       "MOD", "EQL", "NEQ", "LSS", "LEQ", "GTR", "GEQ"}, // OPR
                               {"LOD"},
                               {"STO"},
                               {"CAL"},
                               {"INC"},
                               {"JMP"},
                               {"JPC"},
                               {"OUT", "IN", "HLT"} // SIO
};

const char *getOpName(instruction instr){
    int opcode = instr.op;
    int m = 0;

    if (opcode < 1 || opcode > 9)
        printf("Error: Invalid OP code = %d.\n", opcode);

    if (opcode == 2 || opcode == 9)
        m = instr.m;

    return opNames[opcode][m];
}

void printInstruction(instruction code) {
    char l_str[5];
    formatLString(&code, l_str);

    char m_str[5];
    formatMString(&code, m_str);

    printf("%3d  %s %s %s  ", code.inputNumber, getOpName(code), l_str, m_str);
}

void printFileInstruction(instruction code, FILE* output) {
    char l_str[5];
    formatLString(&code, l_str);

    char m_str[5];
    formatMString(&code, m_str);

    fprintf(output,"%d %d %d  ",code.op, code.l, code.m);
}

void formatMString(instruction *instr, char *buffer) {
    sprintf(buffer, "%4d", instr->m);

    // Only print M for OPR and SIO
    if (instr->op == 2 || instr->op == 9)
        sprintf(buffer, "    ");
}

void formatLString(instruction *instr, char *buffer) {
    sprintf(buffer, "    ");

    // Only print L for STO, LOD, and CAL
    if (instr->op == 3 || instr->op == 4 || instr->op == 5)
        sprintf(buffer, "%4d", instr->l);
}

void printCode(instructMem memory){
    FILE* output = getOutputFile();
    for(int a = 1; a <= memory.length; a++){
        printFileInstruction(memory.mem[a], output);
        fprintf(output, "\n");
    }
}

void printStack(vmInstance *vm){
    activationLL *current = vm->arList;
    for(int a = 1; a <= vm->sp; a++){
        printf("%d ", vm->stack[a]);

        if(current != NULL){
            if(a == current->endOfRecord && a != vm->sp){
                printf("| ");
                current = current->next;
            }
        }
    }

}

void printVMState(vmInstance *vm){
    printInstruction(vm->ir);
    printf("%4d %4d %4d   ", vm->pc, vm->bp, vm->sp);
    printStack(vm);
    printf("\n");
}