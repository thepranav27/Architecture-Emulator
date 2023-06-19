#include <assert.h>
#include "STR_IMM_UOFF_32.h"
#include "../machine.h"

extern machine_t guest;

// Main: C6.2.276 STRB (immediate), unsigned offset variant
void decode_STR_IMM_UOFF_32(instr_t * const insn) {
    //assert(EXTRACT(insn->insnbits, 0xC00000U, 22) == 0x0U);
    //assert(EXTRACT(insn->insnbits, 0x3000000U, 24) == 0x1U);
    //assert(EXTRACT(insn->insnbits, 0x4000000U, 26) == 0x0U);
    //assert(EXTRACT(insn->insnbits, 0x38000000U, 27) == 0x7U);
    //assert(EXTRACT(insn->insnbits, 0xC0000000U, 30) == 0x0U);
 
    uint8_t rt = GETBF(insn->insnbits, 0, 5);
    uint8_t rn = GETBF(insn->insnbits, 5, 5);
    uint32_t imm12 = GETBF(insn->insnbits, 10, 12);
    insn->op = OP_STR;
    insn->imm = imm12;
    insn->src2 = (rt == 31) ? &(guest.proc->SP) : (guest.proc->GPR.names32 + rt);
    insn->src1 = (rn == 31) ? &(guest.proc->SP) : (guest.proc->GPR.names64 + rn);
    insn->wback = false;
    insn->postindex = false;
}

void execute_STR_IMM_UOFF_32(instr_t * const insn) {
    uint64_t address = insn->src1->bits->wval;
    if (!insn->postindex) {
        address += insn->imm;
    }
    insn->val_ex.wval = address;
}

void memory_STR_IMM_UOFF_32(instr_t * const insn) {
    uint32_t data;
    data = insn->src2->bits->wval;
    insn->mrc = mem_write_I(insn->val_ex.wval, data);
}

void wback_STR_IMM_UOFF_32(instr_t * const insn) {

}

void update_pc_STR_IMM_UOFF_32(instr_t * const insn) {
    guest.proc->PC.bits->xval += 4;
}