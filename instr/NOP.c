#include <assert.h>
#include "NOP.h"
#include "../machine.h"

extern machine_t guest;

void decode_NOP(instr_t * const insn) {
    insn->op = OP_NOP;
    return;    
}

void execute_NOP(instr_t * const insn) {
    return;    
}

void memory_NOP(instr_t * const insn) {
    return;
}

void wback_NOP(instr_t * const insn) {
    return;    
}

void update_pc_NOP(instr_t * const insn) {
    guest.proc->PC.bits->xval += 4;
}