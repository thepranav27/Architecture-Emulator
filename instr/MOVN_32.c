#include <assert.h>
#include "MOVN_32.h"
#include "../machine.h"

extern machine_t guest;

// Main: C6.2.192 MOVZ
// Alias: C6.2.187 MOV (wide immediate)
void decode_MOVN_32(instr_t * const insn) {
    assert(EXTRACT(insn->insnbits, 0xFF800000U, 23) == 0x25U);

    uint8_t d = EXTRACT(insn->insnbits, 0x1FU, 0);
    uint16_t imm16 = EXTRACT(insn->insnbits, 0x1FFFE0U, 5);
    uint8_t hw = EXTRACT(insn->insnbits, 0x600000U, 21);
    uint8_t pos = hw << 4;
    //bool is_aliased = ! ((imm16 == 0) && (hw != 0));

    insn->op = OP_MOVN;
    insn->dst = guest.proc->GPR.names32 + d;
    insn->imm = imm16;
    insn->shift = pos;
}

void execute_MOVN_32(instr_t * const insn) {
    uint32_t result;
    result = insn->imm << insn->shift;
    result = ~result;
    insn->val_ex.wval = result;
}

void memory_MOVN_32(instr_t * const insn) {
    return;
}

void wback_MOVN_32(instr_t * const insn) {
    insn->dst->bits->wval = insn->val_ex.wval;
}

void update_pc_MOVN_32(instr_t * const insn) {
    guest.proc->PC.bits->xval += 4;
}