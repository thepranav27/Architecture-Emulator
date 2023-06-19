#include <assert.h>
#include "CSEL_32.h"
#include "../machine.h"

extern machine_t guest;

// Main: C6.2.192 MOVZ
// Alias: C6.2.187 MOV (wide immediate)
void decode_CSEL_32(instr_t * const insn) {

    uint8_t d = EXTRACT(insn->insnbits, 0x1FU, 0);
    uint8_t n = EXTRACT(insn->insnbits, 0x3E0U, 5);
    uint8_t m = EXTRACT(insn->insnbits, 0x1f0000u, 16);
    unsigned char cond = EXTRACT(insn->insnbits, 0xF000U, 12);

    insn->op = OP_CSEL; 
    insn->dst = guest.proc->GPR.names32 + d;
    insn->src1 = guest.proc->GPR.names32 + n;
    insn->src2 = guest.proc->GPR.names32 + m;
    
    switch(cond) {
        case 0: insn->cond = C_EQ; break;
        case 1: insn->cond = C_NE; break;
        case 2: assert(false); break;
        case 3: assert(false); break;
        case 4: assert(false); break;
        case 5: assert(false); break;
        case 6: assert(false); break;
        case 7: assert(false); break;
        case 8: assert(false); break;
        case 9: assert(false); break;
        case 10: insn->cond = C_GE; break;
        case 11: insn->cond = C_LT; break;
        case 12: insn->cond = C_GT; break;
        case 13: insn->cond = C_LE; break;
        case 14: assert(false); break;
        case 15: assert(false); break;
        default: assert(false); break; 
    }

}

void execute_CSEL_32(instr_t * const insn) {
  uint32_t result;
    insn->opnd1.wval = insn->src1->bits->wval;
    insn->opnd2.wval = insn->src2->bits->wval;

    bool j;
    char n = (guest.proc->NZCV.bits->sval >> 3 & 1);
    char z = (guest.proc->NZCV.bits->sval >> 2 & 1);
    char c = (guest.proc->NZCV.bits->sval >> 1 & 1);
    char v = (guest.proc->NZCV.bits->sval >> 0 & 1);

    switch(insn->cond) {
        case C_EQ:
            if (z) {
                j = true;
            }
            break;
        case C_NE:
            if (!z) {
                j = true;
            }
            break;
        case C_GE:
            if (n == v) {
                j = true;
            }
            break;
        case C_LT: 
            if (!(n == v)) {
                j = true;
            }
            break;
        case C_GT:
            if ((n == v) && !(z)) {
                j = true;
            }
            break;
        case C_LE:
            if (!((n == v) && !(z))) {
                j = true;
            }
            break;
        default: 
            j = true;
            break;
    }

    if (j) {
        result = insn->opnd1.wval;
    }
    else {
        result = insn->opnd2.wval;
    }

    insn->val_ex.wval = result;
}

void memory_CSEL_32(instr_t * const insn) {
    return;
}

void wback_CSEL_32(instr_t * const insn) {
    insn->dst->bits->wval = insn->val_ex.wval;
}

void update_pc_CSEL_32(instr_t * const insn) {
    guest.proc->PC.bits->xval += 4;
}