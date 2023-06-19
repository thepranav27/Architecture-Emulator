#include <assert.h>
#include "ADRP.h"
#include "../machine.h"

extern machine_t guest;

// Main: C6.2.11 ADRP
void decode_ADRP(instr_t * const insn) {
    assert(EXTRACT(insn->insnbits, 0x80000000U, 31) == 0x1U);
    assert(EXTRACT(insn->insnbits, 0x1F000000U, 24) == 0x10U);
    
    uint8_t d = EXTRACT(insn->insnbits, 0x1FU, 0);
    int8_t immlo = EXTRACT(insn->insnbits, 0x60000000U, 29);
    int32_t immhi = EXTRACT(insn->insnbits, 0x00FFFFE0, 5);
    int64_t imm = ((int64_t) ((immhi << 2) | immlo)) << 12;

    insn->op = OP_ADRP;
    insn->dst = guest.proc->GPR.names64 + d;
    insn->imm = imm;

    uint64_t base = guest.proc->PC.bits->xval;
    base &= 0xFFFFFFFFFFFFF000ULL;
    insn->val_ex.xval = base + insn->imm;

    insn->dst->bits->xval = insn->val_ex.xval;

    guest.proc->PC.bits->xval += 4;

}

void execute_ADRP(instr_t * const insn) {
    
}

void memory_ADRP(instr_t * const insn) {
}

void wback_ADRP(instr_t * const insn) {
}

void update_pc_ADRP(instr_t * const insn) {
}