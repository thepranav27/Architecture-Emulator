#include <assert.h>
#include <stdio.h>
#include "SUBS_32_SHIFT.h"
#include "../machine.h"

extern machine_t guest;

void decode_SUBS_32_SHIFT(instr_t * const insn) {

    uint8_t rd = EXTRACT(insn->insnbits, 0x1FU, 0);
    uint8_t rn = EXTRACT(insn->insnbits, 0x3E0U, 5);
    uint8_t imm6 = GETBF(insn->insnbits, 10, 6);
    uint8_t rm = GETBF(insn->insnbits, 16, 5);
    uint8_t shift = GETBF(insn->insnbits, 22, 2);
    bool is_aliased = (rd == 31);

    insn->op = is_aliased ? OP_CMP_SHIFT : OP_SUBS_SHIFT;
    insn->shift = shift;
    if (rd != 31) {
        insn->dst = (guest.proc->GPR.names32 + rd);
    }
    if (rn != 31) {
        insn->src1 = (guest.proc->GPR.names32 + rn);
    }
    insn->src2 = (guest.proc->GPR.names32 + rm);
    insn->imm = imm6;
}

void execute_SUBS_32_SHIFT(instr_t * const insn) {
    insn->opnd1.wval = insn->src1->bits->wval;

    if (insn->shift == 0) {
        insn->opnd2.wval = ~(insn->src2->bits->wval << insn->imm);
    }
    else if (insn->shift == 1) {
        insn->opnd2.wval = ~((unsigned) insn->src2->bits->wval >> insn->imm);
    }
    else {
        insn->opnd2.wval = ~((signed) insn->src2->bits->wval >> insn->imm);
    }

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

    if (insn->op == OP_SUBS_SHIFT) {
        insn->dst->bits->wval = result;   
    }

    return;
}

void memory_SUBS_32_SHIFT(instr_t * const insn) {
    return;
}

void wback_SUBS_32_SHIFT(instr_t * const insn) {
    return;
}

void update_pc_SUBS_32_SHIFT(instr_t * const insn) {
    guest.proc->PC.bits->xval += 4;
}