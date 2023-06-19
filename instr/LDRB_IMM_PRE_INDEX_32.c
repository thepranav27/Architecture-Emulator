#include <assert.h>
#include "LDRB_IMM_PRE_INDEX_32.h"
#include "../machine.h"

extern machine_t guest;

// Main: C6.2.135 LDRB (immediate), pre-index variant
void decode_LDRB_IMM_PRE_INDEX_32(instr_t * const insn) {
    assert(EXTRACT(insn->insnbits, 0xC00U, 10) == 0x3U);
    assert(EXTRACT(insn->insnbits, 0x200000U, 21) == 0x0U);
    assert(EXTRACT(insn->insnbits, 0xC00000U, 22) == 0x1U);
    assert(EXTRACT(insn->insnbits, 0x3000000U, 24) == 0x0U);
    assert(EXTRACT(insn->insnbits, 0x4000000U, 26) == 0x0U);
    assert(EXTRACT(insn->insnbits, 0x38000000U, 27) == 0x7U);
    assert(EXTRACT(insn->insnbits, 0xC0000000U, 30) == 0x0U);
 
    uint8_t rt = EXTRACT(insn->insnbits, 0x1FU, 0);
    uint8_t rn = EXTRACT(insn->insnbits, 0x3E0U, 5);
    uint32_t imm9 = EXTRACT(insn->insnbits, 0x1FF000U, 12);
 
    //OPERATIONS (Double Check)
    insn->op = OP_LDRB;
    if (imm9 >> 18 & 1) {
        insn->imm = imm9 | 0xFFFFFFFFFFFFFE00U;
    }
    else {
        insn->imm = imm9;
    }
    insn->dst = guest.proc->GPR.names32 + rt;
    insn->src1 = (rn == 31) ? &(guest.proc->SP) : (guest.proc->GPR.names64 + rn);
    insn->wback = true;
    insn->postindex = false;

    uint64_t address = insn->src1->bits->xval;

    if (!insn->postindex) {
        address += insn->imm;
    }
    insn->val_ex.xval = address;

    insn->val_mem.wval = mem_read_B(insn->val_ex.wval);

    insn->dst->bits->wval = insn->val_mem.wval;
    insn->src1->bits->xval = insn->val_ex.xval;
    guest.proc->PC.bits->xval += 4;
}

void execute_LDRB_IMM_PRE_INDEX_32(instr_t * const insn) {
   
}

void memory_LDRB_IMM_PRE_INDEX_32(instr_t * const insn) {
    
}

void wback_LDRB_IMM_PRE_INDEX_32(instr_t * const insn) {
    
}

void update_pc_LDRB_IMM_PRE_INDEX_32(instr_t * const insn) {
    
}