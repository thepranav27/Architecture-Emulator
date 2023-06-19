#include <assert.h>
#include "LDR_IMM_UOFF_64.h"
#include "../machine.h"

extern machine_t guest;

// Main: C6.2.131 LDR (immediate), unsigned offset variant
void decode_LDR_IMM_UOFF_64(instr_t * const insn) {
    assert(EXTRACT(insn->insnbits, 0xC00000U, 22) == 0x1U);
    assert(EXTRACT(insn->insnbits, 0x3000000U, 24) == 0x1U);
    assert(EXTRACT(insn->insnbits, 0x4000000U, 26) == 0x0U);
    assert(EXTRACT(insn->insnbits, 0x38000000U, 27) == 0x7U);
    assert(EXTRACT(insn->insnbits, 0xC0000000U, 30) == 0x3U);
 
    uint8_t rt = EXTRACT(insn->insnbits, 0x1FU, 0);
    uint8_t rn = EXTRACT(insn->insnbits, 0x3E0U, 5);
    uint16_t imm12 = EXTRACT(insn->insnbits, 0x3FFC00U, 10);
 
    //OPERATIONS
    insn->op = OP_LDR;
    insn->imm = imm12 * 8;
    insn->dst = guest.proc->GPR.names64 + rt;
    insn->src1 = (rn == 31) ? &(guest.proc->SP) : (guest.proc->GPR.names64 + rn);
    insn->wback = false;
    insn->postindex = false;
}

void execute_LDR_IMM_UOFF_64(instr_t * const insn) {
    uint64_t address = insn->src1->bits->xval;

    if (!insn->postindex) {
        address += insn->imm;
    }
    insn->val_ex.xval = address;
}

void memory_LDR_IMM_UOFF_64(instr_t * const insn) {
    insn->val_mem.xval = mem_read_LL(insn->val_ex.xval);
}

void wback_LDR_IMM_UOFF_64(instr_t * const insn) {
    insn->dst->bits->xval = insn->val_mem.xval;
}

void update_pc_LDR_IMM_UOFF_64(instr_t * const insn) {
    guest.proc->PC.bits->xval += 4;
}