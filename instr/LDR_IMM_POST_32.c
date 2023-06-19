#include <assert.h>
#include "LDR_IMM_POST_32.h"
#include "../machine.h"

extern machine_t guest;

// Main: C6.2.131 LDR (immediate), unsigned offset variant
void decode_LDR_IMM_POST_32(instr_t * const insn) {
   
    uint8_t rt = GETBF(insn->insnbits, 0, 5);
    uint8_t rn = GETBF(insn->insnbits, 5, 5);
    uint16_t imm9 = GETBF(insn->insnbits, 12, 9);
 
    //OPERATIONS
    insn->op = OP_LDRP;
    insn->imm = imm9 | 0xFFFFFFFFFFFFFE00;
    insn->dst = guest.proc->GPR.names32 + rt;
    
    insn->src1 = (rn == 31) ? &(guest.proc->SP) : (guest.proc->GPR.names32 + rn);
    insn->wback = true;
    insn->postindex = true;
}

void execute_LDR_IMM_POST_32(instr_t * const insn) {
    uint64_t address = insn->src1->bits->wval;

    if (!insn->postindex) {
        address += insn->imm;
    }
    insn->val_ex.wval = address;
}

void memory_LDR_IMM_POST_32(instr_t * const insn) {
    insn->val_mem.wval = mem_read_LL(insn->val_ex.wval);
}

void wback_LDR_IMM_POST_32(instr_t * const insn) {
    insn->dst->bits->wval = insn->val_mem.wval;
}

void update_pc_LDR_IMM_POST_32(instr_t * const insn) {
    guest.proc->PC.bits->xval += 4;
}