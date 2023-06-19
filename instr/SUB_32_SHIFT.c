#include <assert.h>
#include "SUB_32_SHIFT.h"
#include "../machine.h"

extern machine_t guest;

void decode_SUB_32_SHIFT(instr_t * const insn) {
    uint8_t rd = EXTRACT(insn->insnbits, 0x1FU, 0);
    uint8_t rn = EXTRACT(insn->insnbits, 0x3E0U, 5);
    uint8_t imm6 = GETBF(insn->insnbits, 10, 6);
    uint8_t rm = GETBF(insn->insnbits, 16, 5);
    uint8_t shift = GETBF(insn->insnbits, 22, 2);
    //bool is_aliased = (rd == 31);

    insn->op = OP_SUB_SHIFT;
    insn->shift = shift;
    insn->dst = (guest.proc->GPR.names32 + rd);
    
    if (rn != 31) {
        insn->src1 = (guest.proc->GPR.names32 + rn);
    }
    insn->src2 = (guest.proc->GPR.names32 + rm);
    insn->imm = imm6;
}

void execute_SUB_32_SHIFT(instr_t * const insn) {
    if (insn->src1) {
        insn->opnd1.wval = insn->src1->bits->wval;
    }
    else {
        insn->opnd1.wval = 0;
    }

    if (insn->shift == 0) {
        insn->opnd2.wval = ~(insn->src2->bits->wval << insn->imm);
    }
    else if (insn->shift == 1) {
        insn->opnd2.wval = ~((unsigned) insn->src2->bits->wval >> insn->imm);
    }
    else {
        insn->opnd2.wval = ~((signed) insn->src2->bits->wval >> insn->imm);
    }   

    uint32_t result = insn->opnd1.wval + insn->opnd2.wval + 1;
  
    if (insn->op == OP_SUB_SHIFT) {
        insn->dst->bits->wval = result;    
    }

}

void memory_SUB_32_SHIFT(instr_t * const insn) {
    return;
}

void wback_SUB_32_SHIFT(instr_t * const insn) {
    return;
}

void update_pc_SUB_32_SHIFT(instr_t * const insn) {
    guest.proc->PC.bits->xval += 4;
}