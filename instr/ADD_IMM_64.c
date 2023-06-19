#include <assert.h>
#include "ADD_IMM_64.h"
#include "../machine.h"

extern machine_t guest;

// Main: C6.2.4 ADD (immediate)
// Alias: C6.2.185 MOV (to/from SP)
void decode_ADD_IMM_64(instr_t * const insn) {
    assert(EXTRACT(insn->insnbits, 0x1F800000, 23) == 0x22U);

    uint8_t d = EXTRACT(insn->insnbits, 0x1FU, 0);
    uint8_t n = EXTRACT(insn->insnbits, 0x3E0U, 5);
    uint16_t imm12 = EXTRACT(insn->insnbits, 0x3FFC00U, 10);
    uint8_t sh = EXTRACT(insn->insnbits, 400000U, 22);
    bool is_aliased = (sh == 0 && imm12 == 0 && (d == 31 || n == 31));

    insn->op = is_aliased ? OP_MOV : OP_ADD;
    insn->dst = (d == 31) ? &(guest.proc->SP) : (guest.proc->GPR.names64 + d);
    insn->src1 = (n == 31) ? &(guest.proc->SP) : (guest.proc->GPR.names64 + n);
    insn->imm = sh ? imm12 << 12 : imm12;

    insn->val_ex.xval = insn->src1->bits->xval + insn->imm;
    insn->dst->bits->xval = insn->val_ex.xval;
    guest.proc->PC.bits->xval += 4;
}

void execute_ADD_IMM_64(instr_t * const insn) {
}

void memory_ADD_IMM_64(instr_t * const insn) {
}

void wback_ADD_IMM_64(instr_t * const insn) {
}

void update_pc_ADD_IMM_64(instr_t * const insn) {
}