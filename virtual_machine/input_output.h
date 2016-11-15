// Team name: Compiler Builder 7
// William Cromar
// Luke Myers
// Jonathan Guilbe

#ifndef SILVER_JOURNEY_INPUT_OUTPUT_H
#define SILVER_JOURNEY_INPUT_OUTPUT_H

const char *getOpName(instruction code);
void printInstruction(instruction code, FILE *f);
void printFileInstruction(instruction code, FILE* output);
void formatMString(instruction *instr, char *buffer);
void formatLString(instruction *instr, char *buffer);
void printCode(instructMem memory);
void printStack(vmInstance *vm, FILE *f);
void printVMState(vmInstance *vm, FILE *f);

#endif //SILVER_JOURNEY_INPUT_OUTPUT_H
