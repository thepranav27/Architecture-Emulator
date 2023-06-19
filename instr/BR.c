#include <assert.h>
#include "BR.h"
#include "../machine.h"

extern machine_t guest;

void decode_BR(instr_t * const insn) {
    uint8_t rn = EXTRACT(insn->insnbits, 0x3e0U, 5);
    insn->src1 = guest.proc->GPR.names64 + rn;
    insn->op = OP_BR;
}

void execute_BR(instr_t * const insn) {
    uint64_t target = insn->src1->bits->xval;
    insn->branch_PC = target; 
}

void memory_BR(instr_t * const insn) {
    return;
}

void wback_BR(instr_t * const insn) {
    return;    
}

void update_pc_BR(instr_t * const insn) {
    guest.proc->PC.bits->xval = insn->branch_PC;
}