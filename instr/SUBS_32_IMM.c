#include <assert.h>
#include "SUBS_32_IMM.h"
#include "../machine.h"

extern machine_t guest;

void decode_SUBS_32_IMM(instr_t * const insn) {

    //assert(GETBF(insn->insnbits, 23, 8) == 0xE2U);

    uint8_t rd = EXTRACT(insn->insnbits, 0x1FU, 0);
    uint8_t rn = EXTRACT(insn->insnbits, 0x3E0U, 5);
    uint64_t imm12 = GETBF(insn->insnbits, 10, 12);
    unsigned char sh = EXTRACT(insn->insnbits, 0x400000U, 22);
    unsigned char sf = EXTRACT(insn->insnbits, 0x80000000U, 31);
    bool is_aliased = (rd == 31);

    insn->op = is_aliased ? OP_CMP_IMM : OP_SUBS_IMM;
    if (rd != 31) {
        insn->dst = (guest.proc->GPR.names32 + rd);
    }
    insn->src1 = (guest.proc->GPR.names32 + rn);
    
    insn->imm = sh ? imm12 << 12 : imm12;

}

void execute_SUBS_32_IMM(instr_t * const insn) {
    if(insn->src1->bits->wval == 31) {
        insn->opnd1.wval = guest.proc->SP.bits->wval;
    }
    else {
        insn->opnd1.wval = insn->src1->bits->wval;
    }
    insn->opnd2.wval = ~insn->imm;
    //insn->val_ex.wval = insn->opnd1.wval + insn->opnd2.wval + 1;

    uint32_t unsigned_sum = insn->opnd1.wval + insn->opnd2.wval + 1;
    int32_t signed_sum = (signed)insn->opnd1.wval + (signed)insn->opnd2.wval + 1;

    uint32_t result = unsigned_sum;

    unsigned char n = result >> 31;
    unsigned char z;
    if (result == 0) {
        z = 1;
    }
    else {
        z = 0;
    }
    unsigned char c;
    if ((unsigned)result == unsigned_sum) {
        c = 0;
    }
    else {
        c = 1;
    }
    unsigned char v;
    if ((signed)result == signed_sum) {
        v = 0;
    }
    else {
        v = 1;
    }

    unsigned char nzcv = (n << 3) + (z << 2) + (c << 1) + v;

    guest.proc->NZCV.bits->sval = nzcv;

    if (insn->op == OP_SUBS_IMM) {
        insn->dst->bits->wval = result;   
    }

}

void memory_SUBS_32_IMM(instr_t * const insn) {
    return;
}

void wback_SUBS_32_IMM(instr_t * const insn) {
    return;
}

void update_pc_SUBS_32_IMM(instr_t * const insn) {
    guest.proc->PC.bits->xval += 4;
}