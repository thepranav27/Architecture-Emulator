#include <assert.h>
#include "BLR.h"
#include "../machine.h"

extern machine_t guest;

void decode_BLR(instr_t * const insn) {
    uint8_t rn = EXTRACT(insn->insnbits, 0x3e0U, 5);
    insn->src1 = guest.proc->GPR.names64 + rn;
    insn->op = OP_BLR;
}

void execute_BLR(instr_t * const insn) {
    uint64_t target = insn->src1->bits->xval;
    (guest.proc->GPR.names64+30)->bits->xval = guest.proc->PC.bits->xval + 4;
    insn->branch_PC = target; 
}

void memory_BLR(instr_t * const insn) {
    return;
}

void wback_BLR(instr_t * const insn) {
    return;    
}

void update_pc_BLR(instr_t * const insn) {
    guest.proc->PC.bits->xval = insn->branch_PC;
}