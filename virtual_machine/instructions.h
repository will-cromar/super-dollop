// Team name: Compiler Builder 7
// William Cromar
// Luke Myers
// Jonathan Guilbe

#include "vm.h"

#ifndef SILVER_JOURNEY_INSTRUCTIONS_H
#define SILVER_JOURNEY_INSTRUCTIONS_H


void lit(vmInstance *vm, int M);
void opr(vmInstance *vm, int M);
void lod(vmInstance *vm, int L, int M);
void sto(vmInstance *vm, int L, int M);
void cal(vmInstance *vm, int L, int M);
void inc(vmInstance *vm, int M);
void jmp(vmInstance *vm, int M);
void jpc(vmInstance *vm, int M);
void ret(vmInstance *vm);
void neg(vmInstance *vm);
void add(vmInstance *vm);
void sub(vmInstance *vm);
void mul(vmInstance *vm);
void divOp(vmInstance *vm); //changed to divOp because of name conflict with c stdlib function div.
void odd(vmInstance *vm);
void mod(vmInstance *vm);
void eql(vmInstance *vm);
void neq(vmInstance *vm);
void lss(vmInstance *vm);
void leq(vmInstance *vm);
void gtr(vmInstance *vm);
void geq(vmInstance *vm);
int sio(vmInstance *vm, int M);
void out(vmInstance *vm);
void inp(vmInstance *vm);
void hlt(void);

#endif