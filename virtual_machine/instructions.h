// Team name: Compiler Builder 7
// William Cromar
// Luke Myers
// Jonathan Guilbe

#include "vm.h"

#ifndef SILVER_JOURNEY_INSTRUCTIONS_H
#define SILVER_JOURNEY_INSTRUCTIONS_H

void LIT(vmInstance *vm, int M);
void OPR(vmInstance *vm, int M);
void LOD(vmInstance *vm, int L, int M);
void STO(vmInstance *vm, int L, int M);
void CAL(vmInstance *vm, int L, int M);
void INC(vmInstance *vm, int M);
void JMP(vmInstance *vm, int M);
void JPC(vmInstance *vm, int M);
void RET(vmInstance *vm);
void NEG(vmInstance *vm);
void ADD(vmInstance *vm);
void SUB(vmInstance *vm);
void MUL(vmInstance *vm);
void DIV(vmInstance *vm);
void ODD(vmInstance *vm);
void MOD(vmInstance *vm);
void EQL(vmInstance *vm);
void NEQ(vmInstance *vm);
void LSS(vmInstance *vm);
void LEQ(vmInstance *vm);
void GTR(vmInstance *vm);
void GEQ(vmInstance *vm);
int SIO(vmInstance *vm, int M);
void OUT(vmInstance *vm);
void INP(vmInstance *vm);
void HLT(void);

#endif