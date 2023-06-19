#include <assert.h>
#include "B.h"
#include "../machine.h"

extern machine_t guest;

void decode_B(instr_t * const insn) {
    assert(GETBF(insn->insnbits, 26, 6) == 0x5U);
    
    uint64_t imm26 = GETBF(insn->insnbits, 0, 26) << 2;
    insn->op = OP_B;
     if (imm26 >> 25 & 1) {
        insn->imm = imm26 | 0xFFFFFFFFFFF80000U;
    }
    else {
        insn->imm = imm26;
    }

}

void execute_B(instr_t * const insn) {
    insn->branch_PC = guest.proc->PC.bits->xval + insn->imm;
}

void memory_B(instr_t * const insn) {
    return;
}

void wback_B(instr_t * const insn) {
    return;    
}

void update_pc_B(instr_t * const insn) {
    guest.proc->PC.bits->xval = insn->branch_PC;
}