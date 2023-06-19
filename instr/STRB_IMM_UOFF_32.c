#include <assert.h>
#include "STRB_IMM_UOFF_32.h"
#include "../machine.h"

extern machine_t guest;

// Main: C6.2.276 STRB (immediate), unsigned offset variant
void decode_STRB_IMM_UOFF_32(instr_t * const insn) {
    assert(EXTRACT(insn->insnbits, 0xC00000U, 22) == 0x0U);
    assert(EXTRACT(insn->insnbits, 0x3000000U, 24) == 0x1U);
    assert(EXTRACT(insn->insnbits, 0x4000000U, 26) == 0x0U);
    assert(EXTRACT(insn->insnbits, 0x38000000U, 27) == 0x7U);
    assert(EXTRACT(insn->insnbits, 0xC0000000U, 30) == 0x0U);
 
    uint8_t rt = EXTRACT(insn->insnbits, 0x1FU, 0);
    uint8_t rn = EXTRACT(insn->insnbits, 0x3E0U, 5);
    uint32_t imm12 = EXTRACT(insn->insnbits, 0x3FFC00U, 10);
    insn->op = OP_STRB;
    insn->imm = imm12;
    insn->src2 = guest.proc->GPR.names32 + rt;
    insn->src1 = (rn == 31) ? &(guest.proc->SP) : (guest.proc->GPR.names64 + rn);
    insn->wback = false;
    insn->postindex = false;

    uint64_t address = insn->src1->bits->xval;
    if (!insn->postindex) {
        address += insn->imm;
    }
    insn->val_ex.wval = address;

    uint8_t data;
    data = insn->src2->bits->wval;
    insn->mrc = mem_write_B(insn->val_ex.wval, data);

    guest.proc->PC.bits->xval += 4;
}

void execute_STRB_IMM_UOFF_32(instr_t * const insn) {
    
}

void memory_STRB_IMM_UOFF_32(instr_t * const insn) {
    
}

void wback_STRB_IMM_UOFF_32(instr_t * const insn) {

}

void update_pc_STRB_IMM_UOFF_32(instr_t * const insn) {
   
}