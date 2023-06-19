#include <assert.h>
#include "CBZ_32.h"
#include "../machine.h"

extern machine_t guest;

// Main: C6.2.44 CBNZ
void decode_CBZ_32(instr_t * const insn) {
    assert(EXTRACT(insn->insnbits, 0x1000000U, 24) == 0x0U);
    assert(EXTRACT(insn->insnbits, 0x7E000000, 25) == 0x1AU);
    assert(EXTRACT(insn->insnbits, 0x80000000U, 31) == 0x0U);
   
    uint8_t rt = EXTRACT(insn->insnbits, 0x1FU, 0);
    uint32_t imm19 = EXTRACT(insn->insnbits, 0xFFFFE0, 5);
    imm19 *= 4;

    insn->op = OP_CBZ;
    insn->src1 = guest.proc->GPR.names32 + rt;
    if (imm19 >> 18 & 1) {
        insn->imm = imm19 | 0xFFFFFFFFFFF80000U;
    }
    else {
        insn->imm = imm19;
    }
    insn->cond = C_NE;
}

void execute_CBZ_32(instr_t * const insn) {
    uint32_t operand1 = insn->src1->bits->wval;
    if (operand1 == 0) {
        insn->branch_PC = guest.proc->PC.bits->wval + insn->imm;
    }
    else {
        insn->branch_PC = guest.proc->PC.bits->wval + 4;
    }
}

void memory_CBZ_32(instr_t * const insn) {
    return;
}

void wback_CBZ_32(instr_t * const insn) {
    return;
}

void update_pc_CBZ_32(instr_t * const insn) {
    guest.proc->PC.bits->wval = insn->branch_PC;
}