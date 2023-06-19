#include <assert.h>
#include "ORR_SHIFT.h"
#include "../machine.h"

extern machine_t guest;

void decode_ORR_SHIFT(instr_t * const insn) {

    assert(GETBF(insn->insnbits, 24, 5) == 0xAU);

    uint8_t d = EXTRACT(insn->insnbits, 0x1FU, 0);
    uint8_t n = EXTRACT(insn->insnbits, 0x3E0U, 5);
    uint8_t m = EXTRACT(insn->insnbits, 0x1F0000U, 16);
    uint8_t imm6 = EXTRACT(insn->insnbits, 0xFC00U, 10);
    uint8_t shift = EXTRACT(insn->insnbits, 0xC00000U, 22);

    insn->shift = shift;
    if((shift == 0) && (imm6 == 0) && (n == 31)) {
        insn->op = OP_MOV_SHIFT;
    } else {
        insn->op = OP_ORR_SHIFT;
    }

    insn->dst = guest.proc->GPR.names32 + d;
    if (n != 31) {
        insn->src1 = (guest.proc->GPR.names32 + n);       
    }
    
    insn->imm = imm6;
    
    insn->src2 = (guest.proc->GPR.names32 + m);
    
}

void execute_ORR_SHIFT(instr_t * const insn) {
    uint32_t result;
    if (insn->src1) {
        insn->opnd1.wval = insn->src1->bits->wval;
    }
    else {
        insn->opnd1.wval = 0;
    }

    if (insn->shift == 0) {
        insn->opnd2.wval = (insn->src2->bits->wval << insn->imm);
    }
    else if (insn->shift == 1) {
        insn->opnd2.wval = ((unsigned) insn->src2->bits->wval >> insn->imm);
    }
    else {
        insn->opnd2.wval = ((signed) insn->src2->bits->wval >> insn->imm);
    }

    result = insn->opnd1.wval | insn->opnd2.wval;

     
    insn->dst->bits->wval = result; 
    

}

void memory_ORR_SHIFT(instr_t * const insn) {
    return;
}

void wback_ORR_SHIFT(instr_t * const insn) {
    return;
}

void update_pc_ORR_SHIFT(instr_t * const insn) {
    guest.proc->PC.bits->xval += 4;
}