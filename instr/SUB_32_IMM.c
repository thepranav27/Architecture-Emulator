#include <assert.h>
#include "SUB_32_IMM.h"
#include "../machine.h"

extern machine_t guest;

void decode_SUB_32_IMM(instr_t * const insn) {

    //assert(GETBF(insn->insnbits, 23, 8) == 0xE2U);

    uint8_t rd = EXTRACT(insn->insnbits, 0x1FU, 0);
    uint8_t rn = EXTRACT(insn->insnbits, 0x3E0U, 5);
    uint16_t imm12 = GETBF(insn->insnbits, 10, 12);
    unsigned char sh = EXTRACT(insn->insnbits, 0x400000U, 22);
    unsigned char sf = EXTRACT(insn->insnbits, 0x80000000U, 31);

    insn->op = OP_SUB_IMM;
    
    insn->dst = (guest.proc->GPR.names32 + rd);
    
    insn->src1 = (guest.proc->GPR.names32 + rn);
    
    insn->imm = sh ? imm12 << 12 : imm12;

}

void execute_SUB_32_IMM(instr_t * const insn) {
    if(insn->src1->bits->wval == 31) {
        insn->opnd1.wval = guest.proc->SP.bits->wval;
    }
    else {
        insn->opnd1.wval = insn->src1->bits->wval;
    }
    insn->opnd2.wval = ~insn->imm;

    uint32_t unsigned_sum = insn->opnd1.wval + insn->opnd2.wval + 1;
    int32_t signed_sum = (signed)insn->opnd1.wval + (signed)insn->opnd2.wval + 1;

    uint32_t result = unsigned_sum;

    if (insn->dst->bits->wval == 31) {
        guest.proc->SP.bits->wval = result;
    }
    else {
        insn->dst->bits->wval = result;
    }
}

void memory_SUB_32_IMM(instr_t * const insn) {
    return;
}

void wback_SUB_32_IMM(instr_t * const insn) {
    return;
}

void update_pc_SUB_32_IMM(instr_t * const insn) {
    guest.proc->PC.bits->xval += 4;
}